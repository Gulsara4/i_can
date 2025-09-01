clean:
	rm a.exe *.h.gch
clang:
	clang-format -i *.cpp *.h
push:
	make clean 
	git add .
	git commit -m "немнго чистки "
	git push 
go:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -DRUN1
god:
	g++ snake.h apple.cpp snake1.cpp   snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -lncurses -DRUN2 -o snake.exe -Wall -Wextra -Werror