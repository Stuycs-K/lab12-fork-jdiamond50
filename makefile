compile:
	gcc -o parent parent.c
parent.o: parent.c
	gcc -c parent.c
run: parent
	./parent
clean:
	rm parent
	rm *.o
