# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: epainter <epainter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 18:11:39 by epainter          #+#    #+#              #
#    Updated: 2020/11/03 23:12:29 by epainter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf

### COMPILATION ###

CC = gcc
FLAGS =  `./SDL2/bin/sdl2-config --cflags`

### INCLUDES ###

SDL2 = `./SDL2/bin/sdl2-config --libs`
H_DIR = .

### SOURCE ###

SRCS = camera.c \
       cleanup.c \
       init.c \
       main.c \
       loop.c \
       vec2d.c \
       wall.c

### OBJECTS ###

OBJS = $(SRCS:.c=.o)

### HEADERS ###

H_FILES = wolf.h

HEADERS = $(addprefix $(H_DIR)/, $(H_FILES))


SDLDIR = SDL2

all: lib sdl $(NAME)

lib:
#	@make -C $(LIBFT)

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
	../configure --prefix=$(CURDIR)/SDL2;) ;\
	make -C $(CURDIR)/SDL2_image-2.0.5/build))

%.o: %.c $(HEADERS)
	if $(CC) $(FLAGS) -I $(H_DIR) -o $@ -c $<; then\
		echo $(notdir $@); \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -o $@ -c $<; \
		echo $(notdir $@); \
	fi

$(NAME): $(OBJS)
	if $(CC) $(FLAGS) -I $(H_DIR) -o $@ $^ $(SDL2) -lSDL2main -lSDL2_image -lm; then \
		echo "Project successfully compiled"; \
	else \
		make -C $(CURDIR)/SDL2-2.0.12/build install; \
		make -C $(CURDIR)/SDL2_image-2.0.5/build install; \
		$(CC) $(FLAGS) -I $(H_DIR) -o $@ $^ $(SDL2) -lSDL2main -lSDL2_image -lm; \
		echo "Project successfully compiled"; \
	fi

clean:
	@rm -rf SDL2-2.0.12
	@rm -rf SDL2_image-2.0.5
#	@$(MAKE) fclean -C $(LIBFT)
	@/bin/rm -f $(OBJS)

fclean: clean
	@rm -rf SDL2
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re lib all sdl sdlinstall
