NAME    = film_programs

RM	= rm -f

HEADER	= -I include/

OBJS	= $(SRC:.c=.o)

LIB		= 

SRC	= src/main.c\
	  src/requests.c\
	  src/test.c\

CC	= gcc -Wall -Wextra -lcjson -lcurl `pkg-config --cflags --libs gtk+-3.0`

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(HEADER) -lcjson -lcurl `pkg-config --cflags --libs gtk+-3.0`
	rm -f .o

clean:
	$(RM) $(OBJS)
	$(RM) *~
	$(RM) *#
	$(RM) *a.out

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)

re: fclean all

.PHONY: all clean fclean re
