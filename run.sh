start=$SECONDS
file=$(find -E . -regex '.*\.(cc|cpp)' | xargs ls -t | head -1)
echo "compiling $file"
g++ -std=c++17 -O2 -Wall -fsanitize=undefined -fsanitize=address -I./lib $file -g || exit 1
echo "compiled $file in $((SECONDS - start)) seconds"
start=$SECONDS
./a.out<a.in || exit 1
echo "finished in $((SECONDS - start)) seconds"
