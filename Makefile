CFLAGS=-Wall -Wextra -Werror
LFLAGS=-Llibft -Lminilibx
IFLAGS=-Iheader -I. -Iminilibx

BUILD_DIR=build
SOURCE_DIR=source

MODULES=main
OBJ=$(addprefix $(BUILD_DIR), $(addsuffix .o, $(MODULES)))

all: fractol

fractol: $(BUILD_DIR) libft/libft.a minilibx/libmlx.a $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) -lm -lft -lmlx -framework OpenGL -framework AppKit

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c header/fractol.h Makefile
	cc $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f fractol

re: fclean all
