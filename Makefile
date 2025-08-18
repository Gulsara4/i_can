clean:
	rm a.exe *.h.gch
clang:
	clang-format -i *.cpp *.h
push:
	make clean 
	git add .
	git commit -m "highscore ++"
	git push origin master
go:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -DRUN1
god:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -lncurses -DRUN2