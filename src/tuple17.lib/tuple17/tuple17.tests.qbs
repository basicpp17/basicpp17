import qbs

Application {
    name: "tuple17.tests"
    condition: googletest.present

    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "tuple17" }
    Depends { name: "googletest" }

    files: [
        "Tuple.make.test.cpp",
        "Tuple.ops.cpp",
        "Tuple.ostream.test.cpp",
        "Tuple.test.cpp",
        "Tuple.trait.test.cpp",
    ]
}
