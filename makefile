jmake: jsonParser.c main.c 
	gcc -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror -o Jason jsonParser.c main.c 
