import qbs

Application {
    name: "meta17.tests"

    Depends { name: "meta17" }
    // all tests are compile time only!

    Depends { name: "cpp" }
    // cpp.combineCxxSources: true

    Group {
        name: "Bool"
        files: [
            "Bool.test.cpp",
            "Bool.wrap.test.cpp",
        ]
    }
    Group {
        name: "Const"
        files: [
            "Const.ops.test.cpp",
            "Const.test.cpp",
            "Const.trait.test.cpp",
            "Const.typeOf.test.cpp",
            "Const.wrap.test.cpp",
        ]
    }
    Group {
        name: "ConstPack"
        files: [
            "ConstPack.access.test.cpp",
            "ConstPack.fold.test.cpp",
            "ConstPack.indexOf.test.cpp",
            "ConstPack.ops.test.cpp",
            "ConstPack.recurse.test.cpp",
            "ConstPack.test.cpp",
            "ConstPack.trait.test.cpp",
            "ConstPack.wrap.test.cpp",
        ]
    }
    Group {
        name: "Index"
        files: [
            "Index.ops.test.cpp",
            "Index.test.cpp",
            "Index.trait.test.cpp",
            "Index.wrap.test.cpp",
        ]
    }
    Group {
        name: "IndexPack"
        files: [
            "IndexPack.extract.test.cpp",
            "IndexPack.for.test.cpp",
            "IndexPack.make.test.cpp",
            "IndexPack.ops.test.cpp",
            "IndexPack.test.cpp",
            "IndexPack.trait.test.cpp",
            "IndexPack.wrap.test.cpp",
        ]
    }
    Group {
        name: "IndexType"
        files: [
            "IndexType.extract.test.cpp",
            "IndexType.ops.test.cpp",
            "IndexType.test.cpp",
            "IndexType.trait.test.cpp",
        ]
    }
    Group {
        name: "IndexTypePack"
        files: [
            "IndexTypePack.extract.test.cpp",
            "IndexTypePack.make.test.cpp",
            "IndexTypePack.test.cpp",
            "IndexTypePack.trait.test.cpp",
        ]
    }
    Group {
        name: "None"
        files: [
            "None.ops.test.cpp",
            "None.ostream.test.cpp",
            "None.test.cpp",
        ]
    }
    Group {
        name: "TemplateOfTypes"
        files: [
            "TemplateOfTypes.indexOf.test.cpp",
            "TemplateOfTypes.iterate.test.cpp",
            "TemplateOfTypes.manip.test.cpp",
            "TemplateOfTypes.recurse.test.cpp",
            "TemplateOfTypes.test.cpp",
            "TemplateOfTypes.trait.test.cpp",
            "TemplateOfTypes.transform.test.cpp",
            "TemplateOfTypes.wrap.test.cpp",
        ]
    }
    Group {
        name: "TemplateOfValues"
        files: [
            "TemplateOfValues.extract.test.cpp",
            "TemplateOfValues.test.cpp",
            "TemplateOfValues.trait.test.cpp",
        ]
    }
    Group {
        name: "Type"
        files: [
            "Type.ops.test.cpp",
            "Type.test.cpp",
            "Type.trait.test.cpp",
            "Type.wrap.test.cpp",
        ]
    }
    Group {
        name: "TypeList"
        files: [
            "TypeList.test.cpp",
        ]
    }
    Group {
        name: "TypePack"
        files: [
            "TypePack.access.test.cpp",
            "TypePack.indexOf.test.cpp",
            "TypePack.iterate.test.cpp",
            "TypePack.manip.test.cpp",
            "TypePack.ops.test.cpp",
            "TypePack.recurse.test.cpp",
            "TypePack.test.cpp",
            "TypePack.trait.test.cpp",
            "TypePack.wrap.test.cpp",
        ]
    }
    Group {
        name: "Value"
        files: [
            "Value.const.test.cpp",
            "Value.ref.test.cpp",
            "Value.test.cpp",
        ]
    }

    files: [
        "Arguments.fold.test.cpp",
        "StaticErrorExpr.test.cpp",
        "align.test.cpp",
        "main.cpp",
    ]
}
