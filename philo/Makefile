CC = cc

CFLAGS = -Wall -Wextra -Werror

SRC =	philo.c			\
		parsing.c		\
		leaks.c			\
		init.c			\
		start_feast.c	\
		utils.c			\
		reaper_eye.c	\
		actions.c		\

OBJ = $(SRC:.c=.o)

HDR = philo.h

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean
