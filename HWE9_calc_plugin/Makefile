CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -shared

PLUGINS = addition subtraction multiplication division

all: libcalculator.so

libcalculator.so: $(addsuffix .o, $(PLUGINS))
		$(CC) $(LDFLAGS) -o &@ &^

%.o: %.c
		$(CC) $(CFLAGS) -fPIC -c -o $@ $<

clean:
		rm -f $(addsuffix .o, $(PLUGINS)) libcalculator.so
