SRC = my_mastermind.c
OBJ = (SRC: .c=.o)
TARGET = my_mastermind
CFLAGS = -Wall -Wextra -Werror

all : $(TARGET)

	gcc	$(CFLAG)	$(SRC)	-o	$(TARGET)
	
clean:
	rm -f *.o

fclean: clean
	rm -f $(TARGET)

re: fclean all