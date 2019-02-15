from dumper import *

def qdump__variant17__Variant(d, value):
    whichValue = value["whichValue"].integer()

    prettyType = value.type.templateArguments()[whichValue].name
    
    d.putValue(prettyType)
    d.putNumChild(1)
    
    if d.isExpanded():
        with Children(d):
            d.putSubItem(0, d.createValue(value["m"].address(), value.type[whichValue]))


def qdump__tuple17__Tuple(d, value):
    allTypes = value.type.templateArguments()
    numTypes = len(allTypes)

    d.putNumChild(numTypes)

    offsets=value["offsets"].type.templateArguments()
    m = value["m"].address() 

    if d.isExpanded():
        with Children(d):
            for i in range(numTypes):
                d.putSubItem(i, d.createValue(m + offsets[i], allTypes[i]))
