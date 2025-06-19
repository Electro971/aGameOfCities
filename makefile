compile:
	g++ player.cpp -c
	g++ territory.cpp -c
	g++ board.cpp -c
	g++ player.o territory.o board.o main.cpp -losmanip
run:
	./a.out
clean:
	rm *.o a.out