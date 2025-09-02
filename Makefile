clean:
	rm *.exe *.h.gch *.html *.info *.gcda *.gcno
	rm -rf coverage-report
clang:
	clang-format -i *.cpp *.h
push:
	make clean 
	git add .
	git commit -m "немнго чистки "
	git push 
report:
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage-report
r:
	g++  -g -O0 -fprofile-arcs -ftest-coverage -DRUN2 \
    test.cpp apple.cpp snake1.cpp functions_of_fields.cpp snake.cpp frontend.cpp \
    -lncursesw -lgtest -lgtest_main -pthread -o test.exe



go:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp \
	snake.cpp frontend.cpp -DRUN1
god:
	g++ snake.h apple.cpp snake1.cpp   snake_apple.h functions_of_fields.cpp main.cpp \
	snake.cpp frontend.cpp   -DNOT_TEST -Wall -Wextra -Werror -o snake.exe  -lncursesw
tests:
	g++ test.cpp snake.h apple.cpp snake1.cpp snake_apple.h functions_of_fields.cpp  snake.cpp \
	 -lncursesw -lgtest  -pthread -fprofile-arcs -ftest-coverage -o test.exe  