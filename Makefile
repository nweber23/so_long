MAKEFLAGS += --no-print-directory
NAME = fdf

SRC_DIR = srcs
OBJ_DIR = objs
INC_DIR = include

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3 -flto -funroll-loops \
	-ftree-vectorize -fomit-frame-pointer \
	-I$(INC_DIR) -I$(MLX42_DIR)/include
DEPFLAGS = -MMD -MP

UNAME_S := $(shell uname -s)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
LIBMLX42 = $(MLX42_BUILD)/libmlx42.a

ifeq ($(UNAME_S),Linux)
	LIBS = $(LIBMLX42) $(LIBFT) -ldl -lglfw -pthread -lm
else ifeq ($(UNAME_S),Darwin)
	LIBS = $(LIBMLX42) $(LIBFT) -lglfw -framework Cocoa \
		-framework OpenGL -framework IOKit
else
	$(error OS not supported: $(UNAME_S))
endif

all: $(LIBMLX42) $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEP)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX42_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR)

$(LIBMLX42): | $(MLX42_DIR)
	cmake $(MLX42_DIR) -B $(MLX42_BUILD) -DCMAKE_BUILD_TYPE=Release
	cmake --build $(MLX42_BUILD) -j$(shell nproc 2>/dev/null || echo 4)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(MLX42_DIR)

re: fclean all

.PHONY: all clean fclean re