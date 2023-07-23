CC = gcc
CFLAGS = -Wall -Wextra
EXECUTABLE = calculator

$(EXECUTABLE): calculator.c addition.c multiplication.c division.c subtraction.c
		$(CC) $(CFLAGS) $^ -o $@

clean:
		rm -f $(EXECUTABLE)
