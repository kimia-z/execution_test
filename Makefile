NAME = mini

SRCS = execute.c echo.c #env.c exit.c export.c pwd.c unset.c cd.c

FLAGS = -Wall -Wextra -Werror -g

HEADER = mini.h

SANITIZER = -fsanitize=address #-fsanitize=thread  #-fsanitize=address

all: $(NAME)

$(NAME): $(SRCS) $(HEADER)
	@cc $(FLAGS) -o $(NAME) $(SRCS) $(SANITIZER)

clean:
	@rm -f $(NAME)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re