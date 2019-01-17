import qbs

Application {
    name: "partial17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "partial17" }
    Depends { name: "googletest" }

    files: [
        "Partial.test.cpp",
    ]
}
