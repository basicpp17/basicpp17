import qbs

Application {
    name: "one_of17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "one_of17" }
    Depends { name: "googletest" }

    files: [
        "Variant.test.cpp",
    ]
}
