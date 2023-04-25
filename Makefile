CC=gcc
CFLAGS=-Wall -std=c99
EXEC=main

SRCDIR=src/main
TESTDIR=src/test

OBJDIR=obj
OBJDIRMAIN=$(OBJDIR)/main
OBJDIRTEST=$(OBJDIR)/test

SRCFILES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJFILESWITHMAIN :=  $(patsubst $(SRCDIR)/%.c,$(OBJDIRMAIN)/%.o,$(SRCFILES))
OBJFILES := $(filter-out $(OBJDIRMAIN)/$(EXEC).o, $(OBJFILESWITHMAIN) )

TESTSRCFILES := $(wildcard $(TESTDIR)/*.c) $(wildcard $(TESTDIR)/**/*.c)
TESTOBJFILES := $(patsubst $(TESTDIR)/%.c,$(OBJDIRTEST)/%.o,$(TESTSRCFILES))

# Create obj directory at the beginning
$(shell mkdir -p $(OBJDIRMAIN))
$(shell mkdir -p $(OBJDIRTEST))

$(OBJDIRMAIN)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIRTEST)/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)


.PHONY:all, clean 

all: main 

main: $(OBJFILESWITHMAIN) 
	$(CC) -o $@ $^ $(CFLAGS)
	
test: $(OBJFILES) $(TESTOBJFILES)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(OBJDIR) main test
