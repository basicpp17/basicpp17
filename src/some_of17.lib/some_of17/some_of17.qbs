import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "meta17" }

    files: [
        "SomeOf.cpp",
        "SomeOf.h",
        "SomeOf.make.h",
        "SomeOf.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "meta17" }
    }
}
