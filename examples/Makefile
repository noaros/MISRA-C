# Build the MISRA C examples.
#
#   make          build all good examples (strict C99, warnings are errors)
#                 and compile all bad examples (warnings expected)
#   make run      build and run the good examples
#   make misra    run the cppcheck MISRA addon (via misra.sh) on all files
#   make clean    remove build output

CC       ?= gcc

CHAPTERS := dir r01 r02 r03 r04 r05 r06 r07 r08 r09 r10 r11 \
            r12 r13 r14 r15 r16 r17 r18 r19 r20 r21 r22

GOOD_CFLAGS := -std=c99 -pedantic-errors -Wall -Wextra -Werror -Iinclude
# Bad examples use GNU C so that the language-extension examples compile.
BAD_CFLAGS  := -std=gnu11 -Wall -Wextra -Iinclude

GOOD_OBJS := $(CHAPTERS:%=build/%/good.o)
BAD_OBJS  := $(CHAPTERS:%=build/%/bad.o)

.PHONY: all good bad run misra misra-good misra-bad clean

all: good bad

good: build/good_examples

bad: $(BAD_OBJS)

build/good_examples: $(GOOD_OBJS) build/main.o
	$(CC) -o $@ $^ -lm

build/main.o: main.c include/misra_examples.h
	@mkdir -p $(dir $@)
	$(CC) $(GOOD_CFLAGS) -c -o $@ $<

build/%/good.o: %/good.c include/misra_examples.h
	@mkdir -p $(dir $@)
	$(CC) $(GOOD_CFLAGS) -I$* -c -o $@ $<

build/%/bad.o: %/bad.c include/misra_examples.h
	@mkdir -p $(dir $@)
	-$(CC) $(BAD_CFLAGS) -I$* -c -o $@ $<

run: build/good_examples
	./build/good_examples && echo "All good examples ran."

misra: misra-good misra-bad

misra-good:
	@./misra.sh $(CHAPTERS:%=%/good.c)

misra-bad:
	@./misra.sh $(CHAPTERS:%=%/bad.c)

clean:
	rm -rf build
