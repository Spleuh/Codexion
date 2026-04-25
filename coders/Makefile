CFLAGS= cc -Wall -Wextra -Werror -pthread

DEBUG_FLAGS= -fsanitize=thread -g

SRC= main.c parser.c data_init.c data_init_mtx_cond.c data_cleanup.c dongles_init.c dongles_cleanup.c \
coders_init.c coders_cleanup.c thread_create.c thread_join.c utils.c data_utils.c \
data_utils_2.c coders_routine.c coders_routine_utils.c monitor_routine.c heap_utils.c\
coders_utils.c heap.c 

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


.PHONY : all clean fclean re debug
