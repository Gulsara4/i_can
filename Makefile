clean:
	rm a.exe *.h.gch
go:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -DRUN1
god:
	g++ common_structure.cpp common_structure.h snake_apple.h functions_of_fields.cpp main.cpp snake.cpp frontend.cpp -lncurses -DRUN2