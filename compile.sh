echo '#include "bits/stdc++.h"' >scratch.cc
g++ -E -P -I./impls -DCOMPILED -nostdinc++ $1 >>scratch.cc
