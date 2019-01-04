import qbs

Application {
    name: "one_of17.tests"
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "one_of17" }
    Depends { name: "googletest" }

    files: [
        "OneOf.test.cpp",
    ]
}