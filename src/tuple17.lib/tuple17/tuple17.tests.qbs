import qbs

Application {
    name: "tuple17.tests"
    condition: googletest.present

    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "tuple17" }
    Depends { name: "googletest" }

    files: [
        "Tuple.test.cpp",
    ]
}
