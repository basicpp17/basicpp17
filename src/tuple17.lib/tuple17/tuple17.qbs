import qbs

Product {
    Depends { name: "cpp" }
    Depends { name: "meta17" }

    files: [
        "Tuple.h",
        "Tuple.make.h",
        "Tuple.ops.h",
        "Tuple.ostream.h",
        "Tuple.trait.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "meta17" }
    }
}
