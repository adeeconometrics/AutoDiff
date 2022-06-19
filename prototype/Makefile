MainProgram: main.o reverse_mode.o forward_mode.o
	g++ Main.o reverse_mode.o forward_mode.o -o MainProgram

main.o: main.cpp reverse_mode.h reverse_mode.cpp forward_mode.h forward_mode.cpp
	g++ -std=c++2a -Wall -Werror -Wextra -pedantic -c main.cpp

reverse_mode.o: reverse_mode.h reverse_mode.cpp
	g++ -std=c++2a -Wall -Werror -Wextra -pedantic -c reverse_mode.cpp

forward_mode.o: forward_mode.h forward_mode.cpp
	g++ -std=c++2a -Wall -Werror -Wextra -pedantic -c forward_mode.cpp

clean:
	rm *.o MainProgram

