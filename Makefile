# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanan <sanan@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 08:47:36 by sanan             #+#    #+#              #
#    Updated: 2023/03/08 09:38:58 by sanan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

DIR_PARSING = ./parsing/
SRC_PARSING = $(addprefix $(DIR_PARSING),\
check_wall.c\
elements_init.c\
info_init.c\
map_init.c)

DIR_GNL= ./get_next_line/
SRC_GNL =$(addprefix $(DIR_GNL),\
get_next_line.c\
get_next_line_utils.c)

DIR_LIBFT= ./libft/
SRC_LIBFT =$(addprefix $(DIR_LIBFT),\
ft_atoi.c\
ft_linedup.c\
ft_split.c\
ft_strcmp.c\
ft_strncmp.c)

DIR_ERROR= ./error/
SRC_ERROR =$(addprefix $(DIR_ERROR),\
err_msg.c)

SRC_MAIN =\
cub3d_utils.c\
cub3d.c

SRCS = \
$(SRC_PARSING)\
$(SRC_GNL)\
$(SRC_LIBFT)\
$(SRC_ERROR)\
$(SRC_MAIN)

OBJS = $(SRCS:.c=.o)

CC = cc

WFLAGS = -Wall -Wextra -Werror

INCLUDE = -I./

all : $(NAME)
	@$(ECHO) $(PURPLE) "🐶 cub3D is ready!" $(RESET)

$(NAME) : $(OBJS)
	@$(ECHO) $(CYAN) 🐶 assembling $(GREEN) $@
	@$(CC) $(WFLAGS) $(SRCS) $(INCLUDE) -o $(NAME)

%.o : %.c
	@$(ECHO) $(BLUE) 🐶 compiling $(GREEN) $<
	@$(CC) $(WFLAGS) $(INCLUDE) -c $< -o $@

clean :
	@rm -rf $(OBJS)
	@echo $(RED) "	   🐶 cleaned object files!" $(RESET)

fclean : clean
	@rm -rf $(NAME)
	@echo $(RED) "	   🐶 cleaned archive, target files!" $(RESET)

re :
	@make fclean
	@make all

RESET	=	"\x1b[0m"
GREY	=	"\x1b[30m"
RED		=	"\x1b[31m"
GREEN	=	"\x1b[32m"
YELLOW	=	"\x1b[33m"
BLUE	=	"\x1b[34m"
PURPLE	=	"\x1b[35m"
CYAN	=	"\x1b[36m"
WHITE	=	"\x1b[37m"

ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
      -nrRf $(firstword $(MAKEFILE_LIST)) \
      ECHO="COUNTTHIS" | grep -c "COUNTTHIS")

N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo $(YELLOW) "`expr " [ \`expr $C '*' 100 / $T\`" : '.*\(....\)$$'`% ]" $(RESET)
endif

.PHONY : all clean fclean re