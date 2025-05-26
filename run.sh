start=$(gdate +%s%3N)
file=$1
echo "compiling $file"
g++ -std=c++17 -O2 -Wall -fsanitize=undefined -fsanitize=address -I./lib $file -g || exit 1
echo "compiled $file in $(($(gdate +%s%3N) - start)) ms"
start=$(gdate +%s%3N)
MallocNanoZone=0 ./a.out<a.in || exit 1
echo "finished in $(($(gdate +%s%3N) - start)) ms"
