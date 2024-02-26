start=$SECONDS
file=$(find -E . -regex '.*\.(cc|cpp)' | xargs ls -t | head -1)
g++ -std=c++17 -Wall $file
echo "compiled $file in $((SECONDS - start)) seconds"
start=$SECONDS
./a.out
echo "finished in $((SECONDS - start)) seconds"
