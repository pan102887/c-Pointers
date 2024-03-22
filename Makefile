cc := gcc-12
project := c-demo
cflags := -m64 -std=c2x -O3 -D_TEST_ -g

object := $(patsubst %.c,%.o,$(wildcard *.c))

c-demo: ${object}
	${cc} ${cflags} -o ${project} ${object} -lm

${object}: %.o: %.c
	${cc} -c ${cflags} $< -o $@


.PHONY: clean clean-all print
clean:
	-rm -f ${object} ${project}

clean-all:
	-rm -f ${object} ${project}

print:
	echo $(patsubst %.c,%.o,$(wildcard *.c))

