# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 18:19:18 by fmaqdasi          #+#    #+#              #
#    Updated: 2024/03/26 16:24:49 by fmaqdasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC          := cc
CFLAGS       := -Wall -Wextra -Werror -fsanitize=address -g3
RM		    := rm -f
INCLUDE = -Ilibft/
LIBFT_DIR = libft/
LIBFT = libft/libft.a

SRCS        := 				parscing.c \
                            parscingii.c \
							excuation.c \
							excuationii.c \
							excuationiii.c \
							excuationiv.c \
							parscingiii.c \
							mini_util.c \
							env.c \
							bulidin.c \
							


SRCSM1       :=            minishell.c \


                          
OBJS        := $(SRCS:.c=.o)
OBJSNAME    := $(SRCSM1:.c=.o)

LIBS = -L$(LIBFT_DIR) $(LIBFT)

.c.o:
	@${CC} ${CFLAGS} $(INCLUDE) -c $< -o $@
	
    
${NAME}:	${OBJS} ${OBJSNAME} $(LIBFT)
			@${CC} ${CFLAGS} $(INCLUDES) ${OBJS} ${OBJSNAME} $(LIBS) -o ${NAME} -lreadline
			@echo "\033[0;32mMINISHELL compiled successfully"

$(LIBFT):
	        @make -C $(LIBFT_DIR) -s
			@echo "\033[0;32mLibft compiled successfully"


all:		${NAME}

clean:
			@${RM} *.o
			@make -C $(LIBFT_DIR) clean -s
			@echo "\033[0;31mObjects removed successfully"


fclean:		clean
			@${RM} ${NAME}
			@make -C $(LIBFT_DIR) fclean -s
			@echo "\033[0;31mAll created objects were removed successfully"

re:			fclean all
			@echo "\033[0;32mMINISHELL was recompiled successfully"

.PHONY:		all clean fclean re bonus