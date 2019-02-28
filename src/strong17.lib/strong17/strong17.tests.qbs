import qbs

Application {
    name: "strong17.tests"
    condition: googletest.present
    consoleApplication: true
    type: ["application", "autotest"]

    Depends { name: "strong17" }
    Depends { name: "googletest" }

    files: [
        "Strong.base.test.cpp",
        "Strong.extract.test.cpp",
        "Strong.hash.test.cpp",
        "Strong.inspect.test.cpp",
        "Strong.make.test.cpp",
        "Strong.manip.test.cpp",
        "Strong.ops.test.cpp",
        "Strong.ostream.cpp",
        "Strong.test.cpp",
        "Strong.trait.test.cpp",
        "Strong.weaken.test.cpp",
    ]
}
