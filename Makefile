CFLAGS=-Wall -Wextra -Werror
LFLAGS=-Llibft -Lminilibx
IFLAGS=-Iheader -I. -Iminilibx

BUILD_DIR=build
SOURCE_DIR=source

MODULES=main render hook parse
OBJ=$(addprefix $(BUILD_DIR)/, $(addsuffix .o, $(MODULES)))

.PHONY: all clean fclean re bonus memcheck

all: fractol

bonus: all

memcheck: CFLAGS+=-g -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
memcheck: LFLAGS+=-static-libsan
memcheck: all

fractol: $(BUILD_DIR) libft/libft.a minilibx/libmlx.a $(OBJ)
	cc $(CFLAGS) -o $@ $(OBJ) $(LFLAGS) -lm -lft -lmlx -framework OpenGL -framework AppKit

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c header/fractol.h Makefile
	cc $(CFLAGS) $(IFLAGS) -o $@ -c $<

$(BUILD_DIR):
	mkdir $@

minilibx/libmlx.a:
	make -C minilibx all

libft/libft.a:
	make -C libft all

clean:
	rm -rf $(BUILD_DIR)
	make -C minilibx clean

fclean: clean
	rm -f fractol

re: fclean all
