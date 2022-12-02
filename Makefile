output: MainParser.o Compilers.o Reader.o Scanner.o Parser.o mainReader.o MainScanner.o
	gcc MainParser.o Compilers.o Reader.o Scanner.o Parser.o mainReader.o MainScanner.o -o output

MainParser.o: MainParser.c
	gcc -c MainParser.c

Parser.o: Parser.c
	gcc -c Parser.c

Compilers.o: Compilers.c 
	gcc -c Compilers.c

Reader.o: Reader.c
	gcc -c Reader.c

Scanner.o: Scanner.c
	gcc -c Scanner.c

mainReader.o: mainReader.c
	gcc -c mainReader.c

MainScanner.o: MainScanner.c
	gcc -c MainScanner.c
	
clean:
	rm *.o output
