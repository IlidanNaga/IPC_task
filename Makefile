all: master.o sender.o launch.o
	gcc -o 1st -Wall master.o
	gcc -o 2nd -Wall sender.o
	gcc -o help -Wall launch.o

master.o: master.c
	gcc -c master.c

sender.o: sender.c
	gcc -c sender.c

launch.o: launch.c
	gcc -c launch.c


clear:
	*.o
