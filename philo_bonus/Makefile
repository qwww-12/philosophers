CC = cc

# CFLAGS = -Wall -Wextra -Werror

SRC =	philo_bonus.c				\
		parsing_bonus.c				\
		init_bonus.c				\
		actions_bonus.c				\
		start_simulation_bonus.c	\
		reaper_eye_bonus.c			\
		utils_bonus.c				\

OBJ = $(SRC:.c=.o)

HDR = philo_bonus.h

NAME = philo_bonus

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