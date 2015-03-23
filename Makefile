

all: pong.o court.o ball.o paddle.o pong_util.o
	g++ pong.o court.o ball.o paddle.o pong_util.o -lncurses -lrt -o pong 

pong.o: pong.cpp pong_util.h
	g++ pong.cpp pong_util.h -c

court.o: court.h court.cpp pong_util.h
	g++ court.h court.cpp pong_util.h -c

ball.o: ball.h ball.cpp pong_util.h
	g++ ball.h ball.cpp pong_util.h -c


paddle.o: paddle.h paddle.cpp pong_util.h
	g++ paddle.h paddle.cpp pong_util.h -c

pong_util.o: pong_util.h pong_util.cpp
	g++ pong_util.h pong_util.cpp -c

clean:
	rm *.o
