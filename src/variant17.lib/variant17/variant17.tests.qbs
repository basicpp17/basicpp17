import qbs

Application {
    name: "variant17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "variant17" }
    Depends { name: "googletest" }

    files: [
        "Variant.test.cpp",
    ]
}
