res: main.cpp
	mkdir bin
	gcc -lstdc++ -O2 main.cpp BFinterpreter.cpp BFcompiler.cpp -o bin/bfci
install: bin/bfci
	cp bin/bfci /usr/bin/bfci
clean: bin/
	rm -r bin