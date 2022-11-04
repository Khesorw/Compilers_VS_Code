output: MainScanner.o Compilers.o Reader.o Scanner.o
	gcc MainScanner.o Compilers.o Reader.o Scanner.o -o output

MainScanner.o: MainScanner.c
	gcc -c MainScanner.c

Compilers.o: Compilers.c 
	gcc -c Compilers.c

Reader.o: Reader.c
	gcc -c Reader.c

Scanner.o: Scanner.c
	gcc -c Scanner.c

clean:
	rm *.o output
