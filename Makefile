cc := gcc
project := c-demo

object := main.o chapt_7_practice.o chapt_8_demo.o chapt_8_practice.o eight_queens.o linked_list.o chapt_9_demo.o global.o kmp.o chapt_10_demo.o \
	chapt_11_demo.o alloc.o chapt_12_demo.o chapt_13_demo.o my_data.o chapt_14_demo.o chapt_15_demo.o test.o b_tree.o chapt_16_demo.o
common := 
common_param := -m64 -D_TEST_ -g


c-demo: ${object}
	${cc} ${common_param} -o ${project} ${object} -lm

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

chapt_10_demo.o: chapt_10_demo.c chapt_10_demo.h ${common}
	${cc} ${common_param} -c chapt_10_demo.c -o chapt_10_demo.o

alloc.o: alloc.c alloc.h ${common}
	${cc} ${common_param} -c alloc.c -o alloc.o

chapt_11_demo.o: chapt_11_demo.c chapt_11_demo.h ${common}
	${cc} ${common_param} -c chapt_11_demo.c -o chapt_11_demo.o

chapt_12_demo.o: chapt_12_demo.c chapt_12_demo.h ${common}
	${cc} ${common_param} -c chapt_12_demo.c -o chapt_12_demo.o

chapt_13_demo.o: chapt_13_demo.c chapt_13_demo.h ${common}
	${cc} ${common_param} -c chapt_13_demo.c -o chapt_13_demo.o

chapt_14_demo.o: chapt_14_demo.c chapt_14_demo.h ${common}
	${cc} -DMICRO=100 ${common_param} -c chapt_14_demo.c -o chapt_14_demo.o

chapt_15_demo.o: chapt_15_demo.c chapt_15_demo.h ${common}
	${cc} ${common_param} -c chapt_15_demo.c -o chapt_15_demo.o

chapt_16_demo.o: chapt_16_demo.c chapt_16_demo.h ${common}
	${cc} ${common_param} -c chapt_16_demo.c -o chapt_16_demo.o -lm

kmp.o: kmp.c kmp.h ${common}
	${cc} ${common_param} -c kmp.c -o kmp.o

global.o: global.c global.h ${common}
	${cc} ${common_param} -c global.c -o global.o

my_data.o : my_data.c my_data.h ${common}
	${cc} ${common_param} -c my_data.c -o my_data.o

b_tree.o : b_tree.c b_tree.h ${common}
	${cc} ${common_param} -c b_tree.c -o b_tree.o

test.o: test.c test.h ${common}
	${cc} ${common_param} -c test.c -o test.o



.PHONY: clean
clean:
	-rm ${object} ${project}

clean-all:
	-rm ${object} ${project}
