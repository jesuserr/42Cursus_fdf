# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/01 17:30:23 by marvin            #+#    #+#              #
#    Updated: 2023/04/18 17:37:32 by jesuserr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft/
LIBFT = libft.a

NAME_SERVER = fdf
SRCS_SERVER = main.c
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
DEPS_SERVER = $(SRCS_SERVER:.c=.d)

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

NORM = ${SRCS_SERVER} fdf.h
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

all: makelibft $(NAME_SERVER)

makelibft:
	@make --no-print-directory -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

$(NAME_SERVER): $(OBJS_SERVER) $(LIBFT_DIR)$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT_DIR)$(LIBFT) -o $@
-include $(DEPS_SERVER)

clean:
	@make clean --no-print-directory -C $(LIBFT_DIR)
	$(RM) $(OBJS_SERVER) $(DEPS_SERVER)
		
fclean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)	
	$(RM) $(OBJS_SERVER) $(DEPS_SERVER)
	$(RM) $(NAME_SERVER)

norm:
	@echo ${BLUE}"\nChecking Norminette..."${NC}
	@if norminette $(NORM); then echo ${GREEN}"Norminette OK!\n"${NC}; \
	else echo ${RED}"Norminette KO!\n"${NC}; \
	fi

re: fclean all

.PHONY: all clean fclean re makelibft norm
