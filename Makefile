TARGET=nima
SRC=src
INC=include

CC=gcc
CFLAGS=-Wall -std=c99 -I$(INC)
LDFLAGS=-lncurses

OBJS += $(SRC)/main.o \
		$(SRC)/sheet.o \
		$(SRC)/animation.o

%.o : $(SRC)/%.c
	@gcc -c $<

.PHONY: all clean

all: $(TARGET)
$(TARGET): $(OBJS)
	@echo "Start build $(TARGET)"
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

clean:
	@echo "Clean build"
	@find . -name '*.o' | xargs rm -rf
	@rm -f $(TARGET)
