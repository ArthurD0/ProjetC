CC = gcc
CFLAGS = 
LDFLAGS = 

SRCDIR = .
BINDIR = .

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)
HEADERS = $(wildcard $(SRCDIR)/*.h)

EXEC = main

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(BINDIR)/$@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXEC)
	./$(BINDIR)/$(EXEC)

clean:
	rm -f $(OBJS) $(BINDIR)/$(EXEC)