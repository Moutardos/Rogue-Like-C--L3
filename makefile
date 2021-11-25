TARGET = rlike

CC = gcc 
CFLAGS = -Wall -pedantic -ansi 
CPPFLAGS = -Iinclude 
LDLIBS = -lMLV
SRCDIR := src
OBJDIR := obj
BINDIR := .

EXE := $(TARGET)
SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(EXE): $(OBJ) | $(BINDIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $@
