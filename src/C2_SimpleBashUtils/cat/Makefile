CC = gcc

all: s21_cat test leak_test clean

s21_cat:
	$(CC) s21_cat.c -o s21_cat

test: s21_cat
	bash ourDiff.sh
	
clean: 
	rm s21_cat 
	rm -f *.out
	rm -f *.o
