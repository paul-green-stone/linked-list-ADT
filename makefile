cc := gcc

OBJDIR := objects
CFLAGS := -g -O1

all: $(OBJDIR)/list.o $(OBJDIR)/guard.o

# Make a list.o object file
$(OBJDIR)/list.o: ./src/list.h ./src/list.c
	$(cc) -c $(CFLAGS) -o $@ ./src/list.c

# Make a guard.o object file
$(OBJDIR)/guard.o: ./guard/guard.h ./guard/guard.c
	$(cc) -c $(CFLAGS) -o $@ ./guard/guard.c

# Make a main.o object file
$(OBJDIR)/main.o: ./test/main.c
	$(cc) -c $(CFLAGS) -o $@ $^

# Make a test program
test: $(OBJDIR)/list.o $(OBJDIR)/guard.o $(OBJDIR)/main.o
	$(cc) $(CFLAGS) -o a.out $^
	
# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.a ./*.o ./*.out

# ================================ #

$(shell mkdir -p $(OBJDIR))