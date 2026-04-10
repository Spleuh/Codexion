CFLAGS= gcc -Wall -Wextra -Werror -pthread -g


SRC= main.c parser.c utils.c coder.c dongle.c monitor.c scheduler.c

OBJ= $(SRC:.c=.o)


NAME= codexion


all: $(NAME)


%.o: %.c codexion.h
	$(CFLAGS) -c $< -o $@


$(NAME) : $(OBJ)
	$(CFLAGS) $(OBJ) -o $(NAME)

$(NAMEBONUS) : $(OBJBONUS)
	$(CFLAGS) $(OBJBONUS) -o $(NAMEBONUS)


clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)


re: fclean all


.PHONY : all clean fclean re bonus cleanbonus fcleanbonus rebonus