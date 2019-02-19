import qbs

StaticLibrary {
    Depends { name: "cpp" }
    Depends { name: "tuple17" }

    files: [
        "Strong.base.h",
        "Strong.cpp",
        "Strong.extract.h",
        "Strong.h",
        "Strong.hash.h",
        "Strong.inspect.h",
        "Strong.make.h",
        "Strong.manip.h",
        "Strong.opaque.h",
        "Strong.ops.h",
        "Strong.ostream.h",
        "Strong.trait.h",
        "Strong.weaken.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "tuple17" }

        Properties {
            condition: qbs.toolchain.contains('clang')
            cpp.cxxFlags: [
                "-Wno-gnu-zero-variadic-macro-arguments" // accept this extensions for opaque strong types
            ]
        }
    }
}
