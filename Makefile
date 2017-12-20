CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
#PROFFLAG = -pg
#DEFINES = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --track-origins=yes --leak-check=full --show-leak-kinds=all  --log-file=
GCC = gcc $(CFLAGS) $(COVFLAGS) #$(DEFINES)
#OBJS = pa13.o 

all: pa13

pa13: bmp.o filter.o pa13.o
	$(GCC) pa13.o bmp.o filter.o -o pa13 -lm

pa13.o: pa13.c filter.h bmp.h
	$(GCC) -c pa13.c -o pa13.o

bmp.o: bmp.c bmp.h 
	$(GCC) -c bmp.c -o bmp.o
filter.o: filter.c filter.h bmp.h
	$(GCC) -c filter.c -o filter.o

test: pa13
	  echo "Testing filter" ; \
	./pa13 test.bmp out.bmp sharpen.filter
inspect: pa13
	./pa13 test.bmp out.bmp
	gcov pa13.c
	gcov bmp.c
	gcov filter.c
memory: pa13
	$(VALGRIND)memory ./pa13 test.bmp out.bmp sharpen.filter
clean: 
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa13
	/bin/rm -f memory
	/bin/rm -f validate
	/bin/rm -f out.bmp

memory: pa13
	$(VALGRIND)vallog ./pa13 test.bmp out.bmp sharpen.filter


