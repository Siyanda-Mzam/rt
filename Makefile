# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smamba <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/10 16:06:16 by smamba            #+#    #+#              #
#    Updated: 2016/08/12 17:11:35 by smamba           ###   ########.fr        #
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
	  scene1.c utils.c\
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
	  matrix/transformation_matrices.c

NAME = rtv1

PARAMS = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(DEBUG): ARGS = -Wall -Wextra

$(NAME):
	@gcc $(SRC) $(ARGS) $(LIBS) -I. $(PARAMS) -I vector -lm -o $(NAME) -I matrix/

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
