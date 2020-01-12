# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsance <jsance@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/07 09:50:40 by jsance            #+#    #+#              #
#    Updated: 2019/09/14 14:21:40 by jsance           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_list_push_back.c ft_memccpy.c ft_putnbr.c ft_strequ.c ft_strnequ.c \
ft_list_reverse.c ft_memchr.c ft_putnbr_fd.c ft_striter.c ft_strnew.c \
ft_atoi.c ft_list_size.c ft_memcmp.c ft_putstr.c ft_striteri.c ft_strnstr.c \
ft_bzero.c ft_list_sort.c ft_memcpy.c ft_putstr_fd.c ft_strjoin.c ft_strrchr.c \
ft_isalnum.c ft_lstadd.c ft_memdel.c ft_strcat.c ft_strlcat.c ft_strsplit.c \
ft_isalpha.c ft_lstdel.c ft_memmove.c ft_strchr.c ft_strlen.c ft_strstr.c \
ft_isascii.c ft_lstdelone.c ft_memset.c ft_strclr.c ft_strmap.c ft_strsub.c \
ft_isdigit.c ft_lstiter.c ft_putchar.c ft_strcmp.c ft_strmapi.c ft_strtrim.c \
ft_isprint.c ft_lstmap.c ft_putchar_fd.c ft_strcpy.c ft_strncat.c ft_tolower.c \
ft_itoa.c ft_lstnew.c ft_putendl.c ft_strdel.c ft_strncmp.c ft_toupper.c \
ft_list_last.c ft_memalloc.c ft_putendl_fd.c ft_strdup.c ft_strncpy.c
FILE_O = ft_list_push_back.o ft_memccpy.o ft_putnbr.o ft_strequ.o ft_strnequ.o \
ft_list_reverse.o ft_memchr.o ft_putnbr_fd.o ft_striter.o ft_strnew.o \
ft_atoi.o ft_list_size.o ft_memcmp.o ft_putstr.o ft_striteri.o ft_strnstr.o \
ft_bzero.o ft_list_sort.o ft_memcpy.o ft_putstr_fd.o ft_strjoin.o ft_strrchr.o \
ft_isalnum.o ft_lstadd.o ft_memdel.o ft_strcat.o ft_strlcat.o ft_strsplit.o \
ft_isalpha.o ft_lstdel.o ft_memmove.o ft_strchr.o ft_strlen.o ft_strstr.o \
ft_isascii.o ft_lstdelone.o ft_memset.o ft_strclr.o ft_strmap.o ft_strsub.o \
ft_isdigit.o ft_lstiter.o ft_putchar.o ft_strcmp.o ft_strmapi.o ft_strtrim.o \
ft_isprint.o ft_lstmap.o ft_putchar_fd.o ft_strcpy.o ft_strncat.o ft_tolower.o \
ft_itoa.o ft_lstnew.o ft_putendl.o ft_strdel.o ft_strncmp.o ft_toupper.o \
ft_list_last.o ft_memalloc.o ft_putendl_fd.o ft_strdup.o ft_strncpy.o
FLAG = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(FILE_O)
		@ar rc $(NAME) $(FILE_O)
		@ranlib $(NAME)
		@tput setaf 2; tput bold; echo "All right!"

%.o: %.c 
	gcc $(FLAG) -c $< -I ./libft.h -o $@

clean:
		@rm -f $(FILE_O)
		@tput setaf 2; tput bold; echo "clean: OK!"

fclean: clean
		@rm -f $(NAME)
		@tput setaf 2; tput bold; echo "fclean: OK!"

re: fclean all