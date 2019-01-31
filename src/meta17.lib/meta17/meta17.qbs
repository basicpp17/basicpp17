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
            "ConstPack.fold.h",
            "ConstPack.h",
            "ConstPack.ops.h",
            "ConstPack.recurse.h",
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
            "TemplateOfTypes.extract.h",
            "TemplateOfTypes.h",
            "TemplateOfTypes.manip.h",
            "TemplateOfTypes.trait.h",
            "TemplateOfTypes.wrap.h",
        ]
    }
    Group {
        name: "TemplateOfValues"
        files: [
            "TemplateOfValues.extract.h",
            "TemplateOfValues.h",
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

    files: [
        "Arguments.fold.h",
        "Unreachable.h",
        "align.h",
    ]

    Export {
        Depends { name: "cpp" }
        cpp.includePaths: [".."]
        Depends { name: "cpp17" }
    }
}
