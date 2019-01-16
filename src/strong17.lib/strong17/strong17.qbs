import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "tuple17" }

    files: [
        "Strong.cpp",
        "Strong.extract.h",
        "Strong.h",
        "Strong.hash.h",
        "Strong.inspect.h",
        "Strong.make.h",
        "Strong.manip.h",
        "Strong.ops.h",
        "Strong.ostream.h",
        "Strong.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "tuple17" }
    }
}
