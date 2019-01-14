import qbs

Application {
    name: "strong17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "strong17" }
    Depends { name: "googletest" }

    files: [
        "Strong.test.cpp",
    ]
}
