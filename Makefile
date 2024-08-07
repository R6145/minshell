# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaqdasi <fmaqdasi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/03 18:19:18 by fmaqdasi          #+#    #+#              #
#    Updated: 2024/07/04 20:29:59 by fmaqdasi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := minishell
CC          := cc 
CFLAGS       := -Wall -Wextra -Werror
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
							excuationv.c \
							cleanupio.c \
							cleanupio2.c \
							cleanupio3.c \
							parscingiii.c \
							mini_util.c \
							mini_util2.c \
							mini_util3.c \
							env.c \
							env2.c \
							env_util.c \
							bulidin.c \
							error.c \
							error2.c \
							heredoc.c \
							heredocii.c \
							signals.c \
							signal2.c \
							


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