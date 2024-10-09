echo '#include "bits/stdc++.h"' >scratch.cc
g++ -E -P -I./lib -DCOMPILED -nostdinc++ $1 >>scratch.cc
