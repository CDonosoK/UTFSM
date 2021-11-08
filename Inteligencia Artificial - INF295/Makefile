CC = g++

CFLAGS =-I.

SRCS = etpSolver.cpp

OBJS = $(SRCS: .cpp =o.)

MAIN = ETPSolver


%.o: %.cpp $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

ETPSolver: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

clean:
	-rm *.o $(OBJ) ETPSolver