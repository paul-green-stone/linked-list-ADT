CC = gcc
objs = temp/main.o temp/list.o guard/temp/guard.o
dirs = temp

temp/list.o: list.h list.c guard/temp/guard.o
	$(CC) -c -g -o temp/list.o list.c

guard/temp/guard.o:
	$(MAKE) -C guard

.PHONY: clean

clean:
	rm -rf temp ./*.o *.out
	rm -rf guard/temp

$(shell mkdir -p $(dirs))