NAME := fdf
CC := clang
CFLAGS := -Wall -Wextra -Werror -O2 -fno-builtin
CPPFLAGS := -MMD -MP #-I include
RM := rm -rf
SRC_DIR := src
BUILD_DIR := build
MLX := mlx/libmlx.a
HEADER := fdf.h get_next_line.h
HEADER := $(HEADER:%=$(SRC_DIR)/%)
SRCS := fdf.c map_load.c map_load2.c inputs.c inputs2.c malloc_list.c graphics.c graphics2.c free_and_exit.c str.c projections.c matrices.c get_next_line.c get_next_line_utils.c ft_split.c ft_atoi.c atoui.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

all: $(NAME)

$(MLX): mlx
	make -C mlx

$(NAME): $(BUILD_DIR) $(OBJS) $(HEADER) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -Imlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -Imlx -c $< -o $@
#  -I/usr/include
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# -include $(DEPS)

clean:
	$(RM) $(BUILD_DIR)
	make clean -C mlx
#	$(RM) $(wildcard $(OBJS) $(DEPS) $(BUILD_DIR))

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
