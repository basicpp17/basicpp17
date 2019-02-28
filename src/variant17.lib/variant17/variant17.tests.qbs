import qbs

Application {
    name: "variant17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "variant17" }
    Depends { name: "googletest" }

    files: [
        "Variant.make.test.cpp",
        "Variant.ops.test.cpp",
        "Variant.ostream.test.cpp",
        "Variant.test.cpp",
        "Variant.trait.test.cpp",
    ]
}
