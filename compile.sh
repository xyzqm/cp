g++ -E -P -C -I./lib -DCOMPILED -nostdinc++ $1 >scratch.cc
echo "#include <bits/stdc++.h>
$(sed '/./,$!d' scratch.cc)" >scratch.cc
grep . scratch.cc | pbcopy
