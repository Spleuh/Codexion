CFLAGS= gcc -Wall -Wextra -Werror -pthread

DEBUG_FLAGS= -fsanitize=thread -g

SRC= main.c parser.c data_init.c

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

debug: CFLAGS += $(DEBUG_FLAGS)

debug: re

re: fclean all


.PHONY : all clean fclean re bonus cleanbonus fcleanbonus rebonus