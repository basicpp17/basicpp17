import qbs

StaticLibrary {
    Depends { name: "meta17" }

    files: [
        "StringStore.byteCount.h",
        "StringStore.cpp",
        "StringStore.foreach.h",
        "StringStore.h",
        "StringStore.ops.h",
        "StringStore.ostream.h",
        "StringView.cpp",
        "StringView.h",
        "StringView.ops.h",
        "StringView.ostream.h",
        "append.h",
        "byteCount.h",
        "concat.h",
        "storeLiteral.h",
        "storeView.h",
        "viewCString.h",
        "viewLiteral.h",
        "viewStore.h",
    ]

    Export {
        Depends { name: "meta17" }
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
    }
}
