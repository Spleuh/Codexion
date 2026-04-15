CFLAGS= gcc -Wall -Wextra -Werror -pthread

DEBUG_FLAGS= -g -fsanitize=thread

SRC= main.c args.c coder.c data.c dongle.c monitor.c parser.c scheduler.c thread.c utils.c routine_coder.c mutex_env.c print.c routine_monitor.c routine_scheduler.c

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