import qbs

Application {
    name: "partial17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "partial17" }
    Depends { name: "googletest" }

    files: [
        "Partial.make.test.cpp",
        "Partial.ops.test.cpp",
        "Partial.ostream.test.cpp",
        "Partial.test.cpp",
        "Partial.trait.test.cpp",
    ]
}
