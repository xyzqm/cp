#!/bin/bash
g++ -std=c++23 a.cc -o a
g++ -std=c++23 b.cc -o b
for ((i = 1; ; i++)); do
	echo $i
	python3 gen.py >test.in
	./a <test.in >a.out || break
	./b <test.in >b.out || break
	diff -w a.out b.out || break
done
