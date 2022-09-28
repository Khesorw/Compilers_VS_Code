output: MainReader.o Compilers.o Reader.o
	gcc MainReader.o Compilers.o Reader.o -o output

MainReader.o: MainReader.c
	gcc -c MainReader.c

Compilers.o: Compilers.c 
	gcc -c Compilers.c

Reader.o: Reader.c
	gcc -c Reader.c

clean:
	rm *.o output