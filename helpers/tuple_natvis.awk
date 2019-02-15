function repeat( str, n,    rep, i )
{
    for( ; i<n; i++ )
        rep = rep str
    return rep
}


function viewer(depth)
{
    return "*(DebugTypes::" repeat("Tail::", i) "Head *)(((const char*)&amp;(m)) + DebugTypes::" repeat("Tail::", i) "Offset)"
}

BEGIN {

 print("<?xml version='1.0' encoding='utf-8'?>")
 print("<AutoVisualizer xmlns=\"http://schemas.microsoft.com/vstudio/debugger/natvis/2010\">")

 print "<Type Name=\"tuple17::Tuple&lt;*&gt;\">"

 for (i = 1; i < 6; i++) {
   printf "  <DisplayString Condition=\"npos == "(i)"\" Optional=\"true\">"
   for (j = 0; j < i; j++) printf "{" viewer(j) "}, "
   print "  </DisplayString>"
 }

 print "  <Expand>"
 for (i = 0; i < 64; i++) {
   print "<Item Name=\""i"\" Condition=\"(npos > " i ")\"  Optional=\"true\">" viewer(i) "</Item>"
 }

 print "  </Expand>"
 print "</Type>"

 print "</AutoVisualizer>"
}
