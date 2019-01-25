import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "meta17" }

    files: [
        "Variant.cpp",
        "Variant.h",
        "Variant.make.h",
        "Variant.ops.h",
        "Variant.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "meta17" }
    }
}
