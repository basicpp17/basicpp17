import qbs

Application {
    name: "meta17.tests"

    Depends { name: "meta17" }
    // all tests are compile time only!

    Depends { name: "cpp" }
    cpp.combineCxxSources: true

    files: [
        "Arguments.test.cpp",
        "Bool.test.cpp",
        "Const.test.cpp",
        "Const.typeOf.test.cpp",
        "ConstPack.test.cpp",
        "Index.test.cpp",
        "IndexPack.for.test.cpp",
        "IndexPack.test.cpp",
        "IndexType.test.cpp",
        "IndexTypePack.test.cpp",
        "None.test.cpp",
        "TemplateOfTypes.test.cpp",
        "Type.test.cpp",
        "TypeList.test.cpp",
        "TypePack.test.cpp",
        "align.test.cpp",
        "main.cpp",
    ]
}
