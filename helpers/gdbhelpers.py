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

    offsets = value["offsets"].type.templateArguments()
    m = value["m"].address()

    d.putNumChild(numTypes)

    if d.isExpanded():
        with Children(d):
            for i in range(numTypes):
                d.putSubItem(i, d.createValue(m + offsets[i], allTypes[i]))

"""
    Um diese Funktionen zu debuggen:
    Stacktraces oder Fehlermeldungen gibt es nicht. Dafür braucht man printf-debugging.
    $ touch /tmp/log.txt
    $ tail -f /tmp/log.txt
    Terminal auf den zweiten Bildschirm schieben
    Bei print() IMMER darauf achten, dass file=open("/tmp/log.txt", "a") gesetzt ist.
    In QtCreator rumpfuschen, Ergebnisse live und in Echtzeit auf dem zweiten Bildschirm verfolgen.

    Typische Probleme
    P: Mein Output kommt nicht in der Konsole an.
    A: Du hast file=open("/tmp/log.txt", "a") vergessen!
    P: Der Output kommt trotz file=open... nicht in der Konsole an.
    A: Dann wurde die Stelle nicht ausgeführt, weil das Script vorher abgekackt ist.
"""
def accessBitsetIndex(d, bitset, index):
    data = bitset['__first_']
    bitsPerWord = int(bitset['__bits_per_word'])
    currentWord = int(d.createValue(data.address() + index // bitsPerWord, data.type))
    return currentWord >> (index % bitsPerWord) & 1

def qdump__partial17__Partial(d, value):
    allTypes = value.type.templateArguments()
    numTypes = len(allTypes)

    alignments = value["alignments"]
    sizes = value["sizes"]
    m_data = int(value["m_data"])
    m_bits = value["m_bits"]

    existingTypes = [i for i in range(numTypes) if accessBitsetIndex(d, m_bits, i)]
    d.putNumChild(len(existingTypes))

    if d.isExpanded():
        with Children(d):
            offset = 0
            for i in existingTypes:
                alignment = int(alignments.nativeValue[i])
                if offset * alignment != 0: # algorithm copied from meta17::alignOffset
                    offset = (((offset - 1) // alignment) + 1) * alignment
                d.putSubItem(i, d.createValue(m_data + offset, allTypes[i]))
                offset += int(sizes.nativeValue[i])
