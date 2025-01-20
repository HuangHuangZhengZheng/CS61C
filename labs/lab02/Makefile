UNAME_S := $(shell uname -s)
# Which compiler is currently being used?
CC=gcc
LD=gcc
# What C standard are we currently using?
CFLAGS=-ggdb -Wall -std=c99
LDFLAGS=
# mac OS: Darwin
ifeq ($(UNAME_S), Darwin)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes --dsymutil=yes
endif

ifeq ($(UNAME_S), Linux)
    MEMCHECK=valgrind --tool=memcheck --leak-check=full --track-origins=yes
endif

BIT_OPS_OBJS = bit_ops.o test_bit_ops.o
BIT_OPS_PROG = bit_ops

LFSR_OBJS = lfsr.o test_lfsr.o
LFSR_PROG = lfsr

VECTOR_OBJS=vector.o vector-test.o
VECTOR_PROG=vector-test

BINARIES=$(VECTOR_PROG) $(BIT_OPS_PROG) $(LFSR_PROG)

# What C standard are we currently using? $(FOO)


all: $(BINARIES)

# Which target is part of a rule that makes all the compiled programs?
$(BIT_OPS_PROG): $(BIT_OPS_OBJS)
	$(CC) $(CFLAGS) -g -o $(BIT_OPS_PROG) $(BIT_OPS_OBJS) $(LDFLAGS)

# What line creates the lfsr program from its object files? (Give its line number.)
$(LFSR_PROG): $(LFSR_OBJS)
	$(CC) $(CFLAGS) -g -o $(LFSR_PROG) $(LFSR_OBJS) $(LDFLAGS)

# here we implements a rule for vector.test
$(VECTOR_PROG): $(VECTOR_OBJS)
	$(CC) $(CFLAGS) -g -o $(VECTOR_PROG) $(VECTOR_OBJS) $(LDFLAGS)

lfsr.c: lfsr.h
test_lfsr.c: lfsr.h

bit_ops.c: bit_ops.h
test_bit_ops.c: bit_ops.h

.c.o:
	$(CC) -c $(CFLAGS) $<

vector-memcheck: $(VECTOR_PROG)
	$(MEMCHECK) ./$(VECTOR_PROG)
# Which target is part of a rule that deletes all the compiled programs?
clean:
	-rm -rf core *.o *~ "#"*"#" Makefile.bak $(BINARIES) *.dSYM  

vector.c: vector.h
vector-test.c: vector.h
