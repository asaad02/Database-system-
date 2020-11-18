all:
	gcc -Wall -std=c99 -pedantic buildidx.c util.c hashfn.c -o buildidx

	gcc -Wall -std=c99 -pedantic key2val.c util.c hashfn.c -o key2val

	gcc -Wall -std=c99 -pedantic val2key.c util.c hashfn.c -o val2key

	gcc -Wall -std=c99 -pedantic actors.c util.c hashfn.c -o actors

Clean:

	rm* .o

buildidx.o:
	gcc -Wall -std=c99 -pedantic buildidx buildidx.c util.c hashfn.c 

key2val.o:
	gcc -Wall -std=c99 -pedantic key2val key2val.c util.c hashfn.c 

val2key.o:
	gcc -Wall -std=c99 -pedantic val2key val2key.c util.c hashfn.c 

actors.o:
	gcc -Wall -std=c99 -pedantic actors actors.c util.c hashfn.c 





