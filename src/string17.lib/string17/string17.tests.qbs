import qbs

Application {
    name: "string17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "string17" }
    Depends { name: "googletest" }

    files: [
        "StringStore.foreach.test.cpp",
        "StringStore.test.cpp",
        "StringView.ops.test.cpp",
        "StringView.test.cpp",
        "concat.test.cpp",
        "storeLiteral.test.cpp",
        "storeView.test.cpp",
    ]
}
