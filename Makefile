NAME = fractol

SRC = fractol.c transformations.c fractal_drawer.c mouse_work.c

OBJ = fractol.o transformations.o fractal_drawer.o mouse_work.o

HEADER = fdf.h

$(NAME): $(OBJ)
	@make -C libft/
	@gcc -Wall -Wextra -Werror $(SRC) -o $(NAME) -L libft -lft -L ./mlx/ -lmlx -framework OpenGL -framework AppKit 

%.o:%.c $(HEADER)
	@gcc -Wall -Wextra -Werror -I . -c $< -o $@

clean:
	@/bin/rm -f *~
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean

all: $(NAME)

re: fclean all

.PHONY: clean fclean all re
