#!/bin/sh -e

_IFS=$IFS
IFS=''

read -d '' INTRO << 'INTRO'
<?xml version='1.0' encoding='utf-8'?>
<AutoVisualizer xmlns="http://schemas.microsoft.com/vstudio/debugger/natvis/2010">
INTRO

read -d '' OUTRO << 'OUTRO'
</AutoVisualizer>
OUTRO

read -d '' TYPE_BEGIN << 'TYPE_BEGIN'
    <Intrinsic Name="dataEmpty" Expression="m_data._Mypair._Myval2 == 0" />
    <Intrinsic Name="dataPtr" Expression="m_data._Mypair._Myval2" />

    <Intrinsic Name="has" ReturnType="bool" Expression="(bool)((m_bits._Array[idx / m_bits._Bitsperword] &gt;&gt; (idx % m_bits._Bitsperword)) &amp; 1)">
      <Parameter Type="int" Name="idx" />
    </Intrinsic>

    <Intrinsic Name="alignOffset" Expression="0 == offset * Align ? offset : (((offset - 1) / Align) + 1) * Align">
      <Parameter Type="int" Name="offset" />
      <Parameter Type="int" Name="Align" />
    </Intrinsic>

    <DisplayString Condition="!dataEmpty()" >{{Count = {max_count} }</DisplayString>
    <DisplayString Condition="dataEmpty()" >empty</DisplayString>
    
    <Expand>
      <CustomListItems MaxItemsPerView="5000" ExcludeView="Test">
        <Variable Name="offset" InitialValue="0" />
        <Variable Name="i" InitialValue="0" />

        <Loop>
          <Break Condition="dataEmpty()" />
          <Break Condition="i == max_count" />
          
          <If Condition="has(i)">
            <Exec>offset = alignOffset(offset, alignments[i])</Exec>

TYPE_BEGIN


read -d '' TYPE_END << 'TYPE_END'
            <Exec>offset = offset + sizes[i]</Exec>
          </If>

          <If Condition="!has(i)" >
            <Item>nullptr</Item>
          </If>

          <Exec>i = i + 1</Exec>
        </Loop>
      </CustomListItems>
    </Expand>
  </Type>
TYPE_END


IFS=$_IFS

function asterisks() {
    echo -n "*"
    for i in $(seq $1)
    do
        echo -n ",*"
    done
}

function typeVariadicHeader() {
    echo -n '<Type Name="partial17::Partial&lt;'
    asterisks $i
    echo '&gt;">'
}

function typeVariadicItem() {
    for i in $(seq 0 $i)
    do
        echo -n "          "
        echo -n "<Item Condition=\"i == $i\">"
        echo -n "*(\$T$[i+1] *)(dataPtr() + offset)"
        echo  "</Item>"
    done
}


echo "$INTRO"

for i in $(seq 0 15)
do
  typeVariadicHeader $i
  echo "$TYPE_BEGIN"
  typeVariadicItem $i
  echo "$TYPE_END"
done

echo "$OUTRO"
