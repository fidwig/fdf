NAME := fdf
CC := clang
CFLAGS := -Wall -Wextra -Werror
CPPFLAGS := -MMD -MP -I include
RM := rm -rf
SRC_DIR := src
BUILD_DIR := build
MLX := mlx/libmlx.a
HEADER := fdf.h get_next_line.h keysymdef.h
HEADER := $(HEADER:%=$(SRC_DIR)/%)
SRCS := fdf.c parse.c graphics.c get_next_line.c get_next_line_utils.c ft_split.c ft_atoi.c atoui.c free_and_exit.c str.c vector_math.c matrices.c
SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

all: $(NAME)

$(MLX): mlx
	make -C mlx

$(NAME): $(BUILD_DIR) $(OBJS) $(HEADER) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -Imlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -I/usr/include -Imlx -c $< -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

-include $(DEPS)

clean:
	$(RM) $(wildcard $(OBJS) $(DEPS) $(BUILD_DIR))
	make clean -C mlx

fclean: clean
	$(RM) $(wildcard $(NAME) $(BUILD_DIR))

re: fclean all

.PHONY: all clean fclean re