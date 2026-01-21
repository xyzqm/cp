#!/bin/bash
g++ -std=c++23 -DONLINE_JUDGE $1 -o a
g++ -std=c++23 -DONLINE_JUDGE $2 -o b
for ((i = 1; ; i++)); do
	echo $i
	python3 $3 >test.in
	./a <test.in >a.out || break
	./b <test.in >b.out || break
	diff -w a.out b.out || break
done
