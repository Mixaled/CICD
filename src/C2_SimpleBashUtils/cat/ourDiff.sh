diff <(cat -b test.txt) <(./s21_cat -b test.txt) -s
diff <(cat -e test.txt) <(./s21_cat -e test.txt) -s
diff <(cat -n test.txt) <(./s21_cat -n test.txt) -s
diff <(cat -s test.txt) <(./s21_cat -s test.txt) -s
diff <(cat -t test.txt) <(./s21_cat -t test.txt) -s
diff <(cat test.txt) <(./s21_cat test.txt) -s
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat -b test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat -e test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat -n test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat -s test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat -t test.txt
#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./s21_cat test.txt
