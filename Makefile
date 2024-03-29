# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/19 13:35:34 by jesuserr          #+#    #+#              #
#    Updated: 2023/06/16 12:59:44 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft/
LIBX_DIR = minilibx_macos/

NAME = fdf
NAME_BONUS = fdf_bonus
SRCS = errors.c graphics.c hooks.c hooks_mouse.c main.c map_utils.c moves.c \
projections.c rotations.c z_utils.c
OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)

INCLUDE = -I./ -I./minilibx_macos/ -I./libft/includes/
RM = rm -f
CFLAGS = -O3 -Wall -Wextra -Werror

NORM = ${SRCS} fdf.h controls.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

LIBX = -lmlx -framework OpenGL -framework Appkit -Lminilibx_macos/

all: makelibft makelibx $(NAME)

makelibft:
	@make --no-print-directory -C $(LIBFT_DIR)	
	@echo ${GREEN}"Libft Compiled!\n"${NC};

makelibx:
	@make --no-print-directory -C $(LIBX_DIR) 2> ERRORS
	@rm ERRORS
	@echo ${GREEN}"MiniLibx Compiled!\n"${NC};
	
%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@
	
$(NAME): $(OBJS) $(LIBFT_DIR)libft.a $(LIBX_DIR)libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)libft.a $(LIBX) -o $@
	@echo ${GREEN}"fdf Compiled!\n"${NC};
-include $(DEPS)

bonus: makelibft makelibx $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(LIBFT_DIR)libft.a $(LIBX_DIR)libmlx.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_DIR)libft.a $(LIBX) -o $@
	@echo ${GREEN}"fdf_bonus Compiled!\n"${NC};
-include $(DEPS)

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(LIBX_DIR)
	$(RM) $(OBJS) $(DEPS)
		
fclean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@make clean --no-print-directory -C $(LIBX_DIR)
	$(RM) $(OBJS) $(DEPS)
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re makelibft norm makelibx bonus
