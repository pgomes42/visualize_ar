# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgomes <pgomes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 09:44:09 by pgomes            #+#    #+#              #
#    Updated: 2025/09/30 10:58:48 by pgomes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  				= vizualizer_ar
CC					= cc

RM					= rm -rf

FLAGS				= -Wall -Wextra -Werror -g
LFLAGS      		= -lmlx -lmlx_Linux -lX11 -lXext -lm
INCLUDES 			= -Iincludes 

MLX_PATH    		= lib/minilibx-linux
OBJ_DIR				= obj
PATH_LIBS 			=  -L$(MLX_PATH)
SRCS      			=	src/main.c\
						src/render.c\
						src/ast.c\
						src/ast_adapter.c
               
OBJS				= $(addprefix $(OBJ_DIR)/, $(SRCS:src/%.c=%.o)) 
             
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@ ${INCLUDES}

$(NAME): ${OBJS}
	@echo "$(GREEN)Compiling${CLR_RMV} of ${YELLOW}$(NAME) ${CLR_RMV}..."
	@make -C $(MLX_PATH)
	@${CC} ${FLAGS} $(OBJS) -o $(NAME) $(PATH_LIBS) $(LFLAGS)
	@echo "$(GREEN)$(NAME) created${CLR_RMV} ✔️"

	
all: $(NAME) clean

clean:
	@${RM} ${OBJ_DIR} 
	@echo "$(RED)Deleting $(CYAN)$(NAME) ${CLR_RMV}objs ✔️"

fclean: clean
	@${RM} ${NAME}
	@echo "$(RED)Deleting $(CYAN)$(NAME) ${CLR_RMV}binary ✔️"

re: fclean all

.PHONY: all clean fclean re
