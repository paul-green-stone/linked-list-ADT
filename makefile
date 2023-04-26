cc = gcc
objs = temp/main.o temp/list.o temp/guard.o
dirs = temp
CFLAGS = -O1

main: $(objs) 
	$(cc) $(CFLAGS) -o a.out $(objs)

temp/main.o: main.c
	$(cc) -c -g -o temp/main.o main.c

temp/list.o: list.h list.c
	$(cc) -c -g -o temp/list.o list.c

temp/guard.o:	guard.h guard.c
	$(cc) -c -g -o temp/guard.o guard.c

.PHONY: clean

clean:
	rm -rf temp ./*.o a.out 

$(shell mkdir -p $(dirs))