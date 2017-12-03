CPP = g++ -std=c++11 -Wall -c
.SUFFIXES: .cpp .o

output: main.o pizzahawai.o pizzabase.o pizzadiavola.o 
	g++ -std=c++11 -Wall main.o pizzahawai.o pizzabase.o pizzadiavola.o -o output

.cpp.o:
	$(CPP) $<

clean :
	rm *.o output

