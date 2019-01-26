# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghalvors <ghalvors@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/27 16:55:32 by ghalvors          #+#    #+#              #
#    Updated: 2019/01/26 19:06:18 by ghalvors         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
GCC = gcc -Wall -Wextra -Werror
SRCDIR = src
OBJDIR = obj
SRCS := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS := $(patsubst src/%,obj/%,$(SRCS:%.c=%.o))
INCLUDESDIR = includes
HEADER = $(shell find $(INCLUDESDIR) -type f -name '*.h')
SUBDIRS = Libft minilibx
LIB_INC =  -LLibft -lft -lm
MLX_INC = -Lminilibx -lmlx -framework OpenGL -framework AppKit
PRINTF=test $(VERBOSE)$(TRAVIS) || printf

.PHONY: all

all:
	@$(PRINTF) "\r\033[1;32mCompiling external libraries\033[0m\n"
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done
	@$(PRINTF) "\r\033[1;36mCompiling main program\n"
	@$(PRINTF) "%-20s\r\033[0;36m$(NAME)\033[0m"
	$(MAKE) -q $(NAME) ; \
	if [ $$? -eq 0 ] ; then $(PRINTF) "\r\x1b[20C\x1b[0K\033[0;31m $(NAME) \
	is already up to date\033[0m\n"; \
	else $(MAKE) $(NAME) && $(PRINTF) "\r\x1b[20C\x1b[0K\033[1;32m✔\033[0m\n"; \
	fi
	@$(PRINTF) "\r\033[1;35mProgram compiled succesfuly\n"


$(NAME): $(OBJECTS)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	$(GCC) $(OBJECTS) $(LIB_INC) $(MLX_INC) -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADER)
	@$(PRINTF) "\r\x1b[20C\x1b[0K$@"
	$(GCC) -c $< -o $@ -I $(INCLUDESDIR)

clean:
	rm -rf $(OBJECTS)
	@for dir in $(SUBDIRS); do \
		$(MAKE) clean -C $$dir; \
	done

fclean: clean
	rm -rf $(NAME)
	$(MAKE) fclean -C Libft; \

re: fclean all

.PHONY: all clean fclean re

ifndef VERBOSE
 ifndef TRAVIS
.SILENT:
 endif
endif