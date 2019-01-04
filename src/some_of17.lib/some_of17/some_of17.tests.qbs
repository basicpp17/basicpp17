import qbs

Application {
    name: "some_of17.tests"
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "some_of17" }
    Depends { name: "googletest" }

    files: [
        "SomeOf.test.cpp",
    ]
}