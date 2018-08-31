    Info<< "Reading transportProperties\n" << endl;

    IOdictionary transportProperties
    (
        IOobject
        (
            "transportProperties",
            runTime.constant(),
            mesh,
            IOobject::MUST_READ_IF_MODIFIED,
            IOobject::NO_WRITE
        )
    );

    dimensionedScalar nu
    (
        transportProperties.lookup("nu")
    );

    Info<< "Reading field p\n" << endl;
    volScalarField p
    (
        IOobject
        (
            "p",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

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

    Info<< "Reading field U\n" << endl;
    volVectorField U
    (
        IOobject
        (
            "U",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );


#   include "createPhi.H"


    label pRefCell = 0;
    scalar pRefValue = 0.0;
    setRefCell(p, mesh.solutionDict().subDict("PISO"), pRefCell, pRefValue);
