

all: pong.o court.o ball.o paddle.o  
	g++ pong.o court.o ball.o paddle.o -lncurses -o pong 

pong.o: pong.cpp definitions.h
	g++ pong.cpp definitions.h -c

court.o: court.h court.cpp definitions.h
	g++ court.h court.cpp definitions.h -c

ball.o: ball.h ball.cpp definitions.h
	g++ ball.h ball.cpp definitions.h -c


paddle.o: paddle.h paddle.cpp definitions.h
	g++ paddle.h paddle.cpp definitions.h -c


clean:
	rm *.o
