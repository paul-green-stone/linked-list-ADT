cc = gcc
OBJDIR = objects
CFLAGS = -c -Wall -O1 -fpic
AR = ar
ARFLAGS = -r -c

lib: $(OBJDIR)/list.o
	$(AR) $(ARFLAGS) liblist.a $(OBJDIR)/list.o $(OBJDIR)/guard.o

$(OBJDIR)/list.o: list.h list.c $(OBJDIR)/guard.o
	$(CC) -g $(CFLAGS) -o $(OBJDIR)/list.o list.c

$(OBJDIR)/guard.o: guard/guard.h guard/guard.c
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/guard.o guard/guard.c

test: $(OBJDIR)/main.o liblist.a
	$(CC) -o a.out $(OBJDIR)/main.o -L. -llist

$(OBJDIR)/main.o: main.c
	$(cc) -g $(CFLAGS) -o $(OBJDIR)/main.o main.c

.PHONY: clean

clean:
	rm -rf $(OBJDIR) ./*.o *.out
	rm -rf guard/$(OBJDIR)

$(shell mkdir -p $(OBJDIR))