cmake_minimum_required(VERSION 3.16)
project(wolf3d C)

set(CMAKE_C_STANDARD 11)

set(SDL2_INCLUDE_DIR ./SDL2/include/SDL2)
set(SDL2_LIB_DIR ./SDL2/lib)

add_library(libft STATIC
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_lstadd.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strjoinfree.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strsplit.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/ft_atoi_base.c
        libft/ft_putstr.c
        libft/ft_putchar.c
        )

include_directories(${SDL2_INCLUDE_DIR} libft .)
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_INCLUDE_DIRS}
        ${SDL2IMAGE_INCLUDE_DIRS})
add_compile_options()

add_executable(wolf3d main.c wolf.h
        init.c cleanup.c loop.c wall.c vec2d.c camera.c light.c texture.c error_parser.c ini_parser.c parser_utils.c parsing.c cleanup_ini_blocks.c)

target_link_libraries(${PROJECT_NAME} SDL2 SDL2_image libft m)