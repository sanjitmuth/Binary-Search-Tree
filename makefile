main: TreeType.cpp TreeDr.cpp
	g++ -o TreeDr TreeType.cpp TreeDr.cpp
TreeType.o: TreeType.cpp
	g++ -c TreeType.cpp
TreeDr.o: TreeDr.cpp
	g++ -c TreeDr.cpp
run: TreeDr
	./TreeDr
clean:
	rm -rf TreeDr
	rm -rf *.o
