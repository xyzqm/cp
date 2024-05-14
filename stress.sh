#!/bin/bash
g++ -std=c++17 gen.cc -o gen
g++ -std=c++17 a.cc -o a
g++ -std=c++17 b.cc -o b
for ((i = 1; ; i++)); do
	echo $i
	./gen $i >test.in
	./a <test.in >a.out
	./b <test.in >b.out
	diff -w a.out b.out || break
done

