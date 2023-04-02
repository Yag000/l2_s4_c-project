CC=gcc
CFLAGS=-I. -Wall
SRCDIR=src/main
TESTDIR=src/test

MAINFILE=main

OBJDIR=obj
OBJDIRMAIN=$(OBJDIR)/main
OBJDIRTEST=$(OBJDIR)/test

SRCFILES := $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/**/*.c)
OBJFILES := $(filter-out $(OBJDIRMAIN)/$(MAINFILE).o, $(patsubst $(SRCDIR)/%.c,$(OBJDIRMAIN)/%.o,$(SRCFILES)))
OBJFILESWITHMAIN := $(patsubst $(SRCDIR)/%.c,$(OBJDIRMAIN)/%.o,$(SRCFILES))

TESTSRCFILES := $(wildcard $(TESTDIR)/*.c) $(wildcard $(TESTDIR)/**/*.c)
TESTOBJFILES := $(patsubst $(TESTDIR)/%.c,$(OBJDIRTEST)/%.o,$(TESTSRCFILES))

# Create obj directory at the beginning
$(shell mkdir -p $(OBJDIRMAIN))
$(shell mkdir -p $(OBJDIRTEST))

$(OBJDIRMAIN)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJDIRTEST)/%.o: $(TESTDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)



main: $(OBJFILESWITHMAIN)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(OBJFILES) $(TESTOBJFILES)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(OBJDIR) main test
