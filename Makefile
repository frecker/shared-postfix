CFLAGS=-Wall -O3

all:create bruteforce

bruteforce:md5sum.o bruteforce.o
	$(CC) -o bruteforce md5sum.o bruteforce.o -lssl

create:md5sum.o create.o
	$(CC) -o create md5sum.o create.o -lssl

md5sum.o create.o bruteforce.o:md5sum.h
