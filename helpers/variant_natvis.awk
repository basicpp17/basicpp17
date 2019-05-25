function repeat( str, n,    rep, i )
{
    for( ; i<n; i++ )
        rep = rep str
    return rep
}


function viewer(i)
{
    return "*($T"i+1" *)&amp;(m)"
}

BEGIN {

 print("<?xml version='1.0' encoding='utf-8'?>")
 print("<AutoVisualizer xmlns=\"http://schemas.microsoft.com/vstudio/debugger/natvis/2010\">")

 print "<Type Name=\"variant17::Variant&lt;*&gt;\">"


 print "  <Intrinsic Name=\"which\" Expression=\"(int)whichValue\"/>"

 for (i = 0; i < 64; i++) {
   printf "  <DisplayString Condition=\"which() == "(i)"\" Optional=\"true\">"
   printf "{" viewer(i) "}"
   print "  </DisplayString>"
 }

 
 print "  <Expand>"
 print "  <Item Name=\"which\">which()</Item>"
 for (i = 0; i < 64; i++) {
   printf "    <Item Name=\"[value]\" Condition=\"which() == " i "\" Optional=\"true\">"
   printf viewer(i)
   print "    </Item>"
 }
 print "</Expand>"

 print "</Type>"

 print "</AutoVisualizer>"
}
