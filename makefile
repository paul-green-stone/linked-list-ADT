CC = gcc
objs = temp/main.o temp/list.o guard/temp/guard.o
dirs = temp
CFLAGS = -O1

main: $(objs) 
	$(CC) $(CFLAGS) -o a.out $(objs)

temp/main.o: main.c
	$(CC) -c -g -o temp/main.o main.c

temp/list.o: list.h list.c
	$(CC) -c -g -o temp/list.o list.c

guard/temp/guard.o:
	$(MAKE) -C guard

.PHONY: clean

clean:
	rm -rf temp ./*.o a.out

$(shell mkdir -p $(dirs))