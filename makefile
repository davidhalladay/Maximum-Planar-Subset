PP = g++

main : ./src/main.cpp ./src/mpsMgr.cpp
	$(PP) ./src/main.cpp ./src/mpsMgr.cpp -o ./mps

clean : 
	rm ./src/*.o
	