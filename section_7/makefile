### If you wish to use extra libraries (math.h for instance),
### add their flags here (-lm in our case) in the "LIBS" variable.

LIBS = -lm
LIBS += $(shell pkg-config --libs gtk4)

###
CFLAGS  = -std=c99
CFLAGS += $(shell pkg-config --cflags gtk4)

ASANFLAGS  = -fsanitize=address
ASANFLAGS += -fno-common
ASANFLAGS += -fno-omit-frame-pointer

.PHONY: clean
clean:
		rm -rf *.o *.out *.out.dSYM

build: ./*.c
		@echo Compiling $@
		@$(CC) $(CFLAGS) ./main.c -o main.out $(LIBS)

