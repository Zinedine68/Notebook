# Solver calculating CFL number at every cell and write as a volScalarField thus visualizable by paraview.

## What happens when a GeometricField is initialized ?
Constructor is called but note that GeometricBoundaryField is defined inside the GeometricField, its own constructor will also be called.

## Env 
This is tested on PC with ubuntu precompiled OF-2.3.1

```cpp
// For CFLField

    Info<< "Reading field CFLField\n" << endl;
    volScalarField CFLField
    (
        IOobject
        (
            "CFLField",
            runTime.timeName(),
            mesh,
            IOobject::NO_READ,     // change this to MUST_READ and you'll find a Warning
            IOobject::AUTO_WRITE
        ),
        mesh,
        //dimensionedScalar("CFLField",dimensionSet(0,0,0,0,0,0,0),Foam::scalar 0) // however this does not compile
        //dimensionedScalar()           // this actually compiles, believe it or not
        dimensionedScalar("CFLField", dimless, 0.0)
    );

// Turn on debugSwitch GeometricField ? No, this does not work for templates but their specializations
// volScalarField, volVectorField. 
// Found that these two does not work by adding to system/controDict but in ~.OpenFOAM/2.3.1/controDict

// GeometricField.H

        //- Constructor given IOobject, mesh, dimensioned<Type> and patch type.
        GeometricField
        (
            const IOobject&,
            const Mesh&,
            const dimensioned<Type>&,
            const word& patchFieldType=PatchField<Type>::calculatedType()
        );

// GeometricField.C

// Constructor given a GeometricField and dimensioned<Type>
template<class Type, template<class> class PatchField, class GeoMesh>
Foam::GeometricField<Type, PatchField, GeoMesh>::GeometricField
(
    const IOobject& io,
    const Mesh& mesh,
    const dimensioned<Type>& dt,
    const word& patchFieldType
)
:
    DimensionedField<Type, GeoMesh>(io, mesh, dt, false),
    timeIndex_(this->time().timeIndex()),
    field0Ptr_(NULL),
    fieldPrevIterPtr_(NULL),
    boundaryField_(mesh.boundary(), *this, patchFieldType) // see output below

// GeometricBoundaryField.H

            //- Construct from a BoundaryMesh,
            //  reference to the internal field
            //  and a patch type
            GeometricBoundaryField
            (
                const BoundaryMesh&,
                const DimensionedInternalField&,
                const word&
            );

// GeometricBoundaryField.C

template<class Type, template<class> class PatchField, class GeoMesh>
Foam::GeometricField<Type, PatchField, GeoMesh>::GeometricBoundaryField::
GeometricBoundaryField
(
    const BoundaryMesh& bmesh,
    const DimensionedField<Type, GeoMesh>& field,
    const word& patchFieldType
)
:
    FieldField<PatchField, Type>(bmesh.size()),
    bmesh_(bmesh)
{
    if (debug)
    {
        Info<< "GeometricField<Type, PatchField, GeoMesh>::"
               "GeometricBoundaryField::"
               "GeometricBoundaryField(const BoundaryMesh&, "
               "const DimensionedField<Type>&, const word&)"
            << endl;
    }

    forAll(bmesh_, patchi)
    {
        this->set
        (
            patchi,
            PatchField<Type>::New
            (
                patchFieldType,
                bmesh_[patchi],
                field
            )
        );
    }
}

// For p and U

template<class Type, template<class> class PatchField, class GeoMesh>
Foam::GeometricField<Type, PatchField, GeoMesh>::GeometricField
(
    const IOobject& io,
    const Mesh& mesh
)
:
    DimensionedField<Type, GeoMesh>(io, mesh, dimless, false),
    timeIndex_(this->time().timeIndex()),
    field0Ptr_(NULL),
    fieldPrevIterPtr_(NULL),
    boundaryField_(mesh.boundary())  // no output
{
    readFields();    // -> call readFields -> call readField : output GeometricField<Type, PatchField, GeoMesh>::GeometricBoundaryField::readField(const DimensionedField<Type, GeoMesh>&, const dictionary&)

    ...
}
```
