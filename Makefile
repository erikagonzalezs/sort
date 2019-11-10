all: csortp csortpexec csorth

csortp: csortp.o
	gcc csortp.o -ansi -o csortp
csortp.o: csortp.c csortp.h
	gcc -c csortp.c

csortpexec: csortpexec.o
	gcc csortpexec.o -o csortpexec -ansi
csortpexec.o: csortpexec.c csortpexec.h
	gcc -c csortpexec.c

csorth: csorth.o
	gcc csorth.o -o csorth -ansi -lpthread
csorth.o: csorth.c csorth.h
	gcc -c csorth.c
clean: 
	rm *.o csortp csortpexec csorth
