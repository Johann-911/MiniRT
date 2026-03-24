# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stliu <stliu@student.42heilbronn.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/24 00:00:00 by stliu             #+#    #+#              #
#    Updated: 2026/03/24 23:49:11 by stliu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./inc -I./Printf -I./Printf/Libft -I"./minilibx-linux" -I./GetNextLine

# Directories
SRC_DIR		= main
OBJ_DIR		= obj
GNL_DIR		= GNL

# Libraries
PRINTF_DIR	= Printf
PRINTF		= $(PRINTF_DIR)/libftprintf.a
PRINTF_FLAGS	= -L$(PRINTF_DIR) -lftprintf
LIBFT_DIR	= $(PRINTF_DIR)/Libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBFT_FLAGS	= -L$(LIBFT_DIR) -lft
MLX_DIR		= "minilibx-linux"
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Source files
SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/parse.c \
			  $(SRC_DIR)/colours.c \
			  $(SRC_DIR)/intersection.c \
			  $(SRC_DIR)/ray_gen.c \
			  $(SRC_DIR)/bump_mapping.c \
			  $(SRC_DIR)/rt_math.c \
			  $(SRC_DIR)/rt_math_helper.c \
			  $(SRC_DIR)/parse_helper.c \
			  $(GNL_DIR)/get_next_line.c \
			  $(GNL_DIR)/get_next_line_utils.c \
			  

# Object files
OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): printf libft $(MLX) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(PRINTF_FLAGS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

printf:
	@echo "$(GREEN)Building Printf library...$(RESET)"
	@$(MAKE) -C $(PRINTF_DIR)

libft:
	@echo "$(GREEN)Building Libft library...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "$(GREEN)Building MLX library...$(RESET)"
	@$(MAKE) -C $(MLX_DIR)

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(PRINTF_DIR) clean
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@make -C $(PRINTF_DIR) fclean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re printf libft
