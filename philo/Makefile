NAME	= philo
CC		= cc
OBJ_PATH = .o_files/

SRC		= main.c initialization.c strange_things.c utils.c
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
CFLAGS = -Wall -Wextra -Werror

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: %.c philo.h
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
