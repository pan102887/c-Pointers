cc := gcc
project := c-demo

object := main.o my_average.o chapt_7_practice.o


c-demo: ${object}
	${cc} -o ${project} ${object}

main.o:
	${cc} -c main.c -o main.o

my_average.o: my_average.c my_average.h
	${cc} -c my_average.c -o my_average.o

chapt_7_practice.o: chapt_7_practice.h chapt_7_practice.c
	${cc} -c chapt_7_practice.c -o chapt_7_practice.o	

.PHONY: clean
clean:
	-rm ${object}

clean-all:
	-rm ${object} ${project}
