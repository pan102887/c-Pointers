cc := gcc
project := c-demo

object := main.o chapt_7_practice.o chapt_8_demo.o chapt_8_practice.o eight_queens.o linked_list.o chapt_9_demo.o global.o kmp.o chapt_10_demo.o
common := 
common_param := -m64


c-demo: ${object}
	${cc} ${common_param} -o ${project} ${object}

main.o:
	${cc} ${common_param} -c main.c -o main.o ${common}

chapt_7_practice.o: chapt_7_practice.h chapt_7_practice.c ${common}
	${cc} ${common_param} -c chapt_7_practice.c -o chapt_7_practice.o	

chapt_8_demo.o: chapt_8_demo.c chapt_8_demo.h ${common}
	${cc} ${common_param} -c chapt_8_demo.c -o chapt_8_demo.o

chapt_8_practice.o: chapt_8_practice.c chapt_8_practice.h ${common}
	${cc} ${common_param} -c chapt_8_practice.c -o chapt_8_practice.o

eight_queens.o: eight_queens.c eight_queens.h ${common}
	${cc} ${common_param} -c eight_queens.c -o eight_queens.o

linked_list.o: linked_list.c linked_list.h ${common}
	${cc} ${common_param} -c linked_list.c -o linked_list.o

chapt_9_demo.o: chapt_9_demo.c chapt_9_demo.h ${common}
	${cc} ${common_param} -c chapt_9_demo.c -o chapt_9_demo.o

kmp.o: kmp.c kmp.h ${common}
	${cc} ${common_param} -c kmp.c -o kmp.o

global.o: global.c global.h ${common}
	${cc} ${common_param} -c global.c -o global.o

chapt_10_demo.o: chapt_10_demo.c chapt_10_demo.h ${common}
	${cc} ${common_param} -c chapt_10_demo.c -o chapt_10_demo.o

.PHONY: clean
clean:
	-rm ${object} ${project}

clean-all:
	-rm ${object} ${project}
