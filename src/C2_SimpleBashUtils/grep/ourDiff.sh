diff <(grep int s21_grep.c test.txt) <(./s21_grep int s21_grep.c test.txt) -s
diff <(grep -e int s21_grep.c) <(./s21_grep -e int s21_grep.c) -s
diff <(grep -i int s21_grep.c) <(./s21_grep -i int s21_grep.c) -s
diff <(grep -v c test.txt) <(./s21_grep -v c test.txt) -s
diff <(grep -c c test.txt) <(./s21_grep -c c test.txt) -s
diff <(grep -l c test.txt s21_grep.c) <(./s21_grep -l c test.txt s21_grep.c) -s
diff <(grep -n c test.txt) <(./s21_grep -n c test.txt) -s 
diff <(grep -h int s21_grep.c) <(./s21_grep -h int s21_grep.c) -s
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep int s21_grep.c test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -e int s21_grep.c
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -i int s21_grep.c
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -v c test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -c c test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -l c test.txt s21_grep.c
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -n c test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_grep -h int s21_grep.c
