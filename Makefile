TARGET=nima
OBJS += main.c \
		sheet.c \
		animation.c

.PHONY: all clean
all:
	@echo "Start build $(TARGET)"
	@gcc -o $(TARGET) $(OBJS) -std=c99 -lncurses -Wall
clean:
	@echo "Clean build"
	@rm -f $(TARGET)
