BINARY = Cub3D

LIBFT = ./libft/libft.a
LIBFT_SRC := $(wildcard libft/*.c)
LIBFT_OBJ := $(patsubst libft/%.c, libft/%.o, $(LIBFT_SRC))

COMP = gcc -Wall -Wextra -Werror -g3 -fsanitize=address
INCLUDES = -Iincludes -Imlx -Llibft -lft -L/usr/X11/lib -lX11 -lXext -Lmlx -lmlx
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))

GREEN = \e[1m\e[32m
RESET = \e[0m

all: $(BINARY)

$(BINARY): $(LIBFT) $(OBJ)
	@echo -e "$(GREEN)==> Making Cub3D$(RESET)"
	$(COMP) $(INCLUDES) $(OBJ) $(LIBFT) -o $(BINARY)

$(LIBFT): $(LIBFT_OBJ)
	@echo -e "$(GREEN)==> Making LIBFT$(RESET)"
	ar rcs $(LIBFT) $(LIBFT_OBJ)

libft/%.o: libft/%.c
	$(COMP) -Iincludes -c $< -o $@

obj/%.o: src/%.c
	mkdir -p obj
	$(COMP) -Iincludes -c $< -o $@

run: $(BINARY)
	@echo -e "$(GREEN)==> Running binary$(RESET)"
	@./$(BINARY)

norme:
	grep "printf" */*.[ch]
	norminette *.[ch]

clean:
	rm -rf libft/*.o obj/* mlx/*.o

fclean: clean
	rm -rf $(BINARY) $(LIBFT)

re: fclean all
