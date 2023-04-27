CC = gcc
objs = temp/list.o guard/temp/guard.o
dirs = temp

# Object files
temp/list.o: list.h list.c guard/temp/guard.o
	$(CC) -c -g -o temp/list.o list.c

guard/temp/guard.o:
	$(MAKE) -C guard

# If there is a main.c file
test: main.o $(objs)
	$(CC) -o a.out main.o $(objs)

temp/main.o: main.o $(objs)
	$(cc) -c -g -o temp/main.o main.c

.PHONY: clean

clean:
	rm -rf temp ./*.o *.out
	rm -rf guard/temp

$(shell mkdir -p $(dirs))