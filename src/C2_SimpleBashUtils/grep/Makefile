CC = gcc

all: s21_grep test test1 test2 clean

s21_grep:
	$(CC) s21_grep.c -o s21_grep

test: s21_grep
	bash ourDiff.sh

clean: 
	rm s21_grep 
