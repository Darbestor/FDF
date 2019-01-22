# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 09:59:38 by dmorgil           #+#    #+#              #
#    Updated: 2019/01/22 13:06:10 by ghalvors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
GCC = gcc -Wall -Wextra -Werror
SRCS = ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strstr.c \
	 ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
	 ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
	 ft_memset.c ft_bzero.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
	 ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c \
	 ft_strequ.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strnequ.c \
	 ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c \
	 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_memcpy.c ft_memccpy.c \
	 ft_memmove.c ft_memchr.c ft_memcmp.c ft_strcat.c ft_strncat.c \
	 ft_strlcat.c ft_strchr.c ft_strrchr.c ft_strsub.c ft_strjoin.c \
	 ft_strtrim.c ft_strsplit.c ft_itoa.c ft_lstnew.c ft_lstdelone.c \
	 ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_swap.c \
	 get_next_line.c ft_count_words.c ft_arrdel.c ft_getnbr.c
OBJECTS = $(SRCS:.c=.o)
PRINTF=printf $(VERBOSE)$(TRAVIS)

all:
	@$(PRINTF) "%-20s\r\033[0;33m$(NAME)\033[0m"
	$(MAKE) -q $(NAME) ; \
	if [ $$? -eq 0 ] ; then $(PRINTF) "\r\x1b[20C\x1b[0K\033[0;31m $(NAME) is already up to date\033[0m\n"; \
	else $(MAKE) $(NAME) && $(PRINTF) "\r\x1b[20C\x1b[0K\033[1;32m✔\033[0m\n"; fi


$(NAME): $(OBJECTS)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o : %.c
	@$(PRINTF) "\r\x1b[20C\x1b[0K$<"
	$(GCC) -c $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif