# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 12:52:23 by frfrance          #+#    #+#              #
#    Updated: 2021/01/27 12:52:26 by frfrance         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 				=	minishell

SRCS_PATH			=	./srcs/
INC_PATH			=	./includes/
OBJS_PATH			=	./objs/

SRCS_NAME			=	main.c \
						env.c\
						built_in.c\
						cd.c\
						cd_path.c\
						cd_util.c\
						export.c\
						export_aff_env.c\
						unset.c\
						ft_sort_matrice.c\
						pipe_prsg.c\
						pipe_center.c\
						pipe_arg.c\
						exec_center.c\
						pipe_co.c\
						prsg_th.c\
						exec_u.c\
						pipe_u.c\
						pipe_init.c\
						prsg_center.c\
						prsg_ry.c\
						prsg_dollars.c\
						bin_center.c\
						bin_exec.c\
						bin_error.c\
						prsg_u.c\
						prsg_var.c\
						prsg_arg.c\
						signaux.c\
						utile.c\
						print_shell.c




INC_NAME			=	ft_shell.h

OBJS_NAME			=	$(SRCS_NAME:.c=.o)

OBJS				=	$(addprefix $(OBJS_PATH), $(OBJS_NAME))
INC					=	$(addprefix $(INC_PATH), $(INC_NAME))

CC					=	clang

CFLAGS				=	-Wall -Wextra -Werror -g -I./
LIB					=	./libft/libft.a

all:					$(NAME)

$(NAME):				$(OBJS)
						@(make -C ./libft/)
						$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)
						@(echo "\033[32m=== COMPILATION MINISHELL OK ===\033[0m")

fg:				$(OBJS)
						@(make -C ./libft/)
						$(CC) $(CFLAGS) -g3 -fsanitize=address $(OBJS) $(LIB) -o $(NAME)
						@(echo "\033[32m=== COMPILATION MINISHELL OK ===\033[0m")

$(OBJS_PATH)%.o:		$(SRCS_PATH)%.c
						@mkdir $(OBJS_PATH) 2> /dev/null || true
						@($(CC) $(CFLAGS) -o $@ -c $<)

clean:
						@(make clean -C ./libft/)
						rm -rf $(OBJS)

fclean:
						@(rm -rf $(OBJS_PATH) $(NAME))
						@echo "\033[34m=== REPERTORY MINISHELL CLEANED ===\033[0m"
						@(make fclean -C ./libft/)

re:						fclean all

.PHONY:					clean fclean re all bonus

.SILENT:
