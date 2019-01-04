import qbs

Project {
    minimumQbsVersion: "1.7.1"

    StaticLibrary {
        name: "googletest"

        files: [
            "googletest/googlemock/src/gmock-all.cc",
            "googletest/googletest/src/gtest-all.cc"
        ]

        Depends { name: "cpp" }
        cpp.cxxLanguageVersion: "c++17"
        cpp.includePaths: [
            "googletest/googlemock",
            "googletest/googlemock/include",
            "googletest/googletest",
            "googletest/googletest/include",
        ]
        cpp.defines: ["GTEST_LANG_CXX11"]

        Properties {
            condition: qbs.toolchain.contains('clang')
            cpp.cxxStandardLibrary: "libc++"
        }

        Export {
            Depends { name: "cpp" }
            cpp.includePaths: [
                "googletest/googlemock/include",
                "googletest/googletest/include"
            ]
            cpp.defines: ["GTEST_LANG_CXX11"]

            Properties {
                condition: qbs.toolchain.contains('clang')
                cpp.linkerFlags: ["-lpthread"]
            }

            property bool useMain: true
            Group {
                name: "Main"
                condition: product.googletest.useMain

                files: "googletest/googlemock/src/gmock_main.cc"
            }
        }
    }
}
