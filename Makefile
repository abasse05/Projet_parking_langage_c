main.exe:fonction.o main.o
	gcc -I include/ -o main.exe fonction.o main.o -lmysqlclient
	rm -r *.o
	./main.exe

fonction.o: include/fonction.h src/fonction.c
	gcc -I include/ -o fonction.o -c src/fonction.c -lmysqlclient

main.o: include/fonction.h  src/main.c
	gcc -I include/  -c src/main.c -lmysqlclient