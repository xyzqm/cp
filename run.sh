start=$(gdate +%s%3N)
file=$1
echo "compiling $file"
# clang++ -std=c++23 -O2 -Wall -I./lib -I./include $file -g || exit 1
clang++ -std=c++23 -O2 -Wall -fsanitize=undefined -fsanitize=address -I./lib -I./include $file -g || exit 1
echo "compiled $file in $(($(gdate +%s%3N) - start)) ms"
start=$(gdate +%s%3N)
MallocNanoZone=0 ./a.out<a.in || exit 1
echo "finished in $(($(gdate +%s%3N) - start)) ms"
