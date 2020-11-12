# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epainter <epainter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 18:11:39 by epainter          #+#    #+#              #
#    Updated: 2020/11/12 23:55:50 by epainter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf

### COMPILATION ###

CC = gcc
FLAGS =  `./SDL2/bin/sdl2-config --cflags`
LIBFT = libft

### INCLUDES ###

SDL2 = `./SDL2/bin/sdl2-config --libs`
H_DIR = .
H_LIB = libft

### SOURCE ###

SRCS =	camera.c\
		cleanup.c\
		cleanup_ini_blocks.c\
		error_parser.c\
		ini_parser.c\
		init.c\
		light.c\
		loop.c\
		main.c\
		parser_utils.c\
		parsing.c\
		render.c\
		texture.c\
		vec2d2.c\
		vec2d.c\
		wall.c\
		wall_render.c \
		keyboard.c


### OBJECTS ###

OBJS = $(SRCS:.c=.o)

### HEADERS ###

H_FILES = wolf.h

HEADERS = $(H_FILES)


SDLDIR = SDL2

all: lib sdl $(NAME)

lib:
	@make -C $(LIBFT)

sdl:
	@(make -C $(CURDIR)/SDL2-2.0.12/build \
	|| ( tar xfz SDL2-2.0.12.tar.gz; \
	mkdir -p SDL2-2.0.12/build; cd $(CURDIR)/SDL2-2.0.12/build; \
	../configure --prefix=$(CURDIR)/SDL2; \
	make -C $(CURDIR)/SDL2-2.0.12/build))
	@(make -C $(CURDIR)/SDL2_image-2.0.5/build || \
	( tar xfz SDL2_image-2.0.5.tar.gz; \
	mkdir -p SDL2_image-2.0.5/build; \
	cd SDL2_image-2.0.5/build; \
	../configure --prefix=$(CURDIR)/SDL2 ||\
	(make -C $(CURDIR)/SDL2-2.0.12/build install; \
	../configure --prefix=$(CURDIR)/SDL2;);\
	make -C $(CURDIR)/SDL2_image-2.0.5/build))

%.o: %.c $(HEADERS)
	if $(CC) $(FLAGS) -I $(H_DIR) -I $(H_LIB) -o $@ -c $<; then\
		echo $(notdir $@); \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -I $(H_DIR) -I $(H_LIB) -o $@ -c $<; \
		echo $(notdir $@); \
	fi

$(NAME): $(OBJS)
	if $(CC) $(FLAGS) -I $(H_DIR) -I $(H_LIB) -L $(LIBFT) -o $@ $^ $(SDL2) -lSDL2main -lSDL2_image -lm -lft; then \
		echo "Project successfully compiled"; \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -I $(H_DIR) -I $(H_LIB) -L $(LIBFT) -o $@ $^ $(SDL2) -lSDL2main -lSDL2_image -lm -lft; \
		echo "Project successfully compiled"; \
	fi

clean:
	@rm -rf SDL2-2.0.12
	@rm -rf SDL2_image-2.0.5
	@$(MAKE) fclean -C $(LIBFT)
	@/bin/rm -f $(OBJS)

fclean: clean
	@rm -rf SDL2
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re lib all sdl sdlinstall
