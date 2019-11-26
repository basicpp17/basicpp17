import qbs

Product {
    Group {
        name: "Bool"
        files: [
            "Bool.h",
            "Bool.wrap.h",
        ]
    }
    Group {
        name: "Const"
        files: [
            "Const.h",
            "Const.ops.h",
            "Const.trait.h",
            "Const.typeOf.h",
            "Const.wrap.h",
        ]
    }
    Group {
        name: "ConstPack"
        files: [
            "ConstPack.access.h",
            "ConstPack.extract.h",
            "ConstPack.fold.h",
            "ConstPack.h",
            "ConstPack.indexOf.h",
            "ConstPack.ops.h",
            "ConstPack.recurse.h",
            "ConstPack.sizeof.h",
            "ConstPack.trait.h",
            "ConstPack.wrap.h",
        ]
    }
    Group {
        name: "Index"
        files: [
            "Index.h",
            "Index.ops.h",
            "Index.trait.h",
            "Index.wrap.h",
        ]
    }
    Group {
        name: "IndexPack"
        files: [
            "IndexPack.extract.h",
            "IndexPack.for.h",
            "IndexPack.h",
            "IndexPack.make.h",
            "IndexPack.ops.h",
            "IndexPack.trait.h",
            "IndexPack.wrap.h",
        ]
    }
    Group {
        name: "IndexType"
        files: [
            "IndexType.extract.h",
            "IndexType.h",
            "IndexType.ops.h",
            "IndexType.trait.h",
        ]
    }
    Group {
        name: "IndexTypePack"
        files: [
            "IndexTypePack.extract.h",
            "IndexTypePack.h",
            "IndexTypePack.make.h",
            "IndexTypePack.trait.h",
        ]
    }
    Group {
        name: "None"
        files: [
            "None.h",
            "None.ops.h",
            "None.ostream.h",
        ]
    }
    Group {
        name: "TemplateOfTypes"
        files: [
            "TemplateOfTypes.h",
            "TemplateOfTypes.indexOf.h",
            "TemplateOfTypes.iterate.h",
            "TemplateOfTypes.manip.h",
            "TemplateOfTypes.recurse.h",
            "TemplateOfTypes.trait.h",
            "TemplateOfTypes.transform.h",
            "TemplateOfTypes.wrap.h",
        ]
    }
    Group {
        name: "TemplateOfValues"
        files: [
            "TemplateOfValues.h",
            "TemplateOfValues.recurse.h",
            "TemplateOfValues.trait.h",
        ]
    }
    Group {
        name: "Type"
        files: [
            "Type.h",
            "Type.ops.h",
            "Type.trait.h",
            "Type.wrap.h",
        ]
    }
    Group {
        name: "TypeList"
        files: [
            "TypeList.h",
            "TypeList.make.h",
            "TypeList.ops.h",
            "TypeList.trait.h",
        ]
    }
    Group {
        name: "TypePack"
        files: [
            "TypePack.access.h",
            "TypePack.extract.h",
            "TypePack.h",
            "TypePack.indexOf.h",
            "TypePack.iterate.h",
            "TypePack.manip.h",
            "TypePack.ops.h",
            "TypePack.recurse.h",
            "TypePack.trait.h",
            "TypePack.wrap.h",
        ]
    }
    Group {
        name: "Value"
        files: [
            "Value.const.h",
            "Value.h",
            "Value.ref.h",
        ]
    }

    files: [
        "Arguments.fold.h",
        "DeferStaticError.h",
        "StaticErrorExpr.h",
        "Unreachable.h",
        "align.h",
        "same.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "cpp17" }
    }
}
