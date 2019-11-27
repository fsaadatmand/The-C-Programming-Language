CC = clang
CFLAGS = -g -Wall -Wextra -Werror -pedantic-errors
DEPS = functions.h
TARGET = main
OBJ = $(TARGET).o functions.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o $(TARGET) $(TEST)
