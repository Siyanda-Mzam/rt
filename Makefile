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

PARAMS = -lmlx -framework OpenGL -framework AppKit -I libft/ -L libft -lft

all: $(NAME)

$(DEBUG): ARGS = -Wall -Wextra

$(NAME):
	@make -C imod/ezxml clean all
	@make -C libft/ 
	@gcc -I. -L imod/ezxml -lezxml $(SRC) $(ARGS) $(LIBS) $(PARAMS) -I vector -lm -o $(NAME) -I matrix/

clean:
	@make -C libft/ clean
	@rm -f $(NAME)

fclean: clean
	@make -C libft/ fclean

re: fclean all
