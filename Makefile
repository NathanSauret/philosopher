NAME 	= philosopher
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3

SRC =	debug.c	\
		main.c	\
		philosophers_utils.c	\
		utils.c	\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(CFLAGS) $(OBJ)
	@clear
	@echo "Compilation done!"

clean:
	@rm -f $(OBJ)
	@clear
	@echo "Cleaning done!"

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -rf
	@clear
	@echo "Full cleaning done!"

re: fclean all
	@clear
	@echo "Re:Zero - Re:Clean and compile again."

fsanitize:
	@$(CC) -o $(NAME) $(CFLAGS) -fsanitize=thread $(OBJ)
	@clear
	@echo "Compilation done!"

.PHONY: all clean fclean re
