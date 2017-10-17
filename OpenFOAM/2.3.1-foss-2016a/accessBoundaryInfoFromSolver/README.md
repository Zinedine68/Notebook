# Access boundary info (coordinates, U ...)

## Source
```cpp
// /OpenFOAM_2.3.1-foss-2016a/src/finiteVolume/fields/fvsPatchFields/fvsPatchField/fvsPatchFieldsFwd.H
 template<class Type> class fvPatchField;
 
 typedef fvPatchField<scalar> fvPatchScalarField;
 typedef fvPatchField<vector> fvPatchVectorField;
 typedef fvPatchField<sphericalTensor> fvPatchSphericalTensorField;
 typedef fvPatchField<symmTensor> fvPatchSymmTensorField;
 typedef fvPatchField<tensor> fvPatchTensorField;


// /OpenFOAM_2.3.1-foss-2016a/src/finiteVolume/fields/fvPatchFields/fvPatchField/fvPatchFieldsFwd.H
template<class Type> class fvsPatchField;
 
 typedef fvsPatchField<scalar> fvsPatchScalarField;
 typedef fvsPatchField<vector> fvsPatchVectorField;
 typedef fvsPatchField<sphericalTensor> fvsPatchSphericalTensorField;
 typedef fvsPatchField<symmTensor> fvsPatchSymmTensorField;
 typedef fvsPatchField<tensor> fvsPatchTensorField;
```

## Code Analysis
Note these two return different type.
```cpp
const word w0("fixedWalls");
const word w1("movingWall");

const label w0PatchID = mesh.boundaryMesh().findPatchID(w0); //findPatchID return const label
const label w1PatchID = mesh.boundaryMesh().findPatchID(w1);

const fvsPatchVectorField& faceCentreshub = mesh.Cf().boundaryField()[w0PatchID];
fvPatchVectorField& U_b = U.boundaryField()[w1PatchID];
```

Just for the first one

`mesh.Cf()` is of `surfaceVectorField` equivalence to `typedef GeometricField<vector, fvsPatchField, surfaceMesh> surfaceVectorField;`   
`mesh.Cf().boundaryField()` is of `GeometricBoundaryField` which is not a templated class but inherited from one --- 
`FieldField<PatchField, Type>` which will here be instantiated as `FieldField<fvsPatchField, vector>` inheritated from `PtrList<Field<Type> >`
which is instantiated as `PtrList<fvsPatchField<vector> >`.   
Now, access an element of `fvsPatchVectorField` is to access an element of `PtrList<fvsPatchField<vector> >` object using its `operator[]`. The type
of the element is `fvsPatchField<vector>`. As the argument is `const`, it is of type `const fvsPatchField<vector>`. **Why not a pointer? See Annexe**.


## Annexe
Class
    Foam::PtrList

Description
    A templated 1D list of **pointers** to objects of type \<T\>, where the
    size of the array is known and used for subscript bounds checking, etc.

    The element operator [] returns a reference to the object **rather than a
    pointer**.
