import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "meta17" }

    files: [
        "OneOf.cpp",
        "OneOf.h",
        "OneOf.make.h",
        "OneOf.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "meta17" }
    }
}
