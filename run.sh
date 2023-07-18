start=$SECONDS
file=$(find . -type f -name "*.cpp" | xargs ls -t | head -1)
g++ -std=c++17 -Wall $file
echo "compiled $file in $((SECONDS - start)) seconds"
start=$SECONDS
./a.out
echo "finished in $((SECONDS - start)) seconds"