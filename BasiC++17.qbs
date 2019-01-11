import qbs

Project {
    name: "Basic C++17"

    references: [
        "thirdparty",
        "src/meta17.lib",
        "src/tuple17.lib",
        "src/strong17.lib",
        "src/some_of17.lib",
        "src/one_of17.lib",
    ]

    AutotestRunner {}

    // note: if do not use this .qbs project you need a similar setup
    Product {
        name: "cpp17"

        Export {
            Depends { name: "cpp" }
            cpp.cxxLanguageVersion: "c++17"
            cpp.treatWarningsAsErrors: true

            Properties {
                condition: qbs.toolchain.contains('msvc')
                cpp.cxxFlags: [
                    "/permissive-", "/Zc:__cplusplus", // best C++ compatibility
                    "/diagnostics:caret", // better errors
                    "/wd4068", // ignore unknown pragmas
                ]
            }
            Properties {
                condition: qbs.toolchain.contains('clang')
                cpp.cxxFlags: [
                    "--pedantic", // best C++ compatibility
                    "-Wall", "-Wextra", // enable more warnings
                    "-ftemplate-backtrace-limit=0", // do not cut template backtraces
                ]
                cpp.cxxStandardLibrary: "libc++"
                cpp.staticLibraries: ["c++", "c++abi"]
            }
        }
    }

    Product {
        name: "Extra Files"
        files: [
            ".clang-format",
            ".clang-tidy",
            ".editorconfig",
            ".gitignore",
            "LICENSE",
            "Readme.md",
        ]
    }
}
