import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "meta17" }

    files: [
        "Partial.cpp",
        "Partial.h",
        "Partial.make.h",
        "Partial.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "meta17" }
    }
}
