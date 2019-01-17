import qbs

Application {
    name: "some_of17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "some_of17" }
    Depends { name: "googletest" }

    files: [
        "Partial.test.cpp",
    ]
}
