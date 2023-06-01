cc := gcc
project := c-demo

object := main.o chapt_7_practice.o chapt_8_demo.o chapt_8_practice.o eight_queens.o linked_list.o
common := 


c-demo: ${object}
	${cc} -o ${project} ${object}

main.o:
	${cc} -c main.c -o main.o ${common}

chapt_7_practice.o: chapt_7_practice.h chapt_7_practice.c ${common}
	${cc} -c chapt_7_practice.c -o chapt_7_practice.o	

chapt_8_demo.o: chapt_8_demo.c chapt_8_demo.h ${common}
	${cc} -c chapt_8_demo.c -o chapt_8_demo.o

chapt_8_practice.o: chapt_8_practice.c chapt_8_practice.h ${common}
	${cc} -c chapt_8_practice.c -o chapt_8_practice.o

eight_queens.o: eight_queens.c eight_queens.h ${common}
	${cc} -c eight_queens.c -o eight_queens.o

linked_list.o: linked_list.c linked_list.h ${common}
	${cc} -c linked_list.c -o linked_list.o

.PHONY: clean
clean:
	-rm ${object}

clean-all:
	-rm ${object} ${project}
