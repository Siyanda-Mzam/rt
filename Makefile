# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamba <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/10 16:06:16 by smamba            #+#    #+#              #
#    Updated: 2016/08/19 16:02:28 by smamba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c \
	  ft_camera.c \
	  manager/app_environ.c\
	  manager/window.c\
	  vector/ft_vector.c \
	  vector/ft_vector_ops.c \
	  vector/ft_vector_arithmetic.c \
	  ft_color.c ft_objects.c ft_ray.c ft_stack.c \
	  scene2.c utils.c\
	  engine/operations.c \
	  engine/shading_model.c \
	  engine/core.c \
	  engine/intersections.c \
	  engine/ft_normals.c \
	  matrix/ft_matrix.c \
	  matrix/ft_matrix_ops.c \
	  matrix/matrix_utils.c\
	  matrix/garbage_collector.c\
	  matrix/matrix_ops2.c\
	  matrix/matrix_utils_2.c\
	  matrix/transformation_matrices.c\
	  imod/imod.c\
	  imod/process_values.c\
	  imod/ezxml_utils.c\
	  imod/get_vector.c\
	  imod/interface.c\
	  imod/ft_atodouble.c\

NAME = RT

INC = -I. -I/usr/include/X11 -Iincludes/ -Ilibft/ -Ivector -Imatrix/

LIXLIB = -lXext -lX11

MACLIB = -framework OpenGL -framework AppKit -lm

LIBS = -Llibft -lft -Limod/ezxml -lezxml -lmlx -lm

OBJ = $(SRC:.c=.o)

ARGS = -Wall -Wextra -Werror -g


all: $(NAME)

$(DEBUG): $(ARGS)

%.o: %.c
		@echo "\033[33m$^\033[0m changed.\nRecompiling..."
		@gcc $(ARGS) -c -o $@ $^ $(INC)
		@echo "\033[33m$^\033[0m Compiled."

$(NAME): $(OBJ)

ifeq ($(shell uname), Linux)
		@make -s -C imod/ezxml clean all
		@make -s -C libft/ 
		@gcc $(ARGS) $(INC) $(SRC) $(LIBS) $(LIXLIB) -o $(NAME)
else
		@make -s -C imod/ezxml clean all
		@make -s -C libft/ 
		@gcc $(ARGS) $(INC) $(SRC) $(LIBS) $(MACLIB) -o $(NAME)
endif

clean:
	@make -C libft/ clean
	@rm -f $(NAME)

fclean: clean
	@make -C libft/ fclean

re: fclean all

.PHONY: all clean fclean re