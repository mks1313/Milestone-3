# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmarinov <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/27 13:09:50 by mmarinov          #+#    #+#              #
#    Updated: 2024/12/27 13:50:08 by mmarinov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

END     = \033[0m
YELLOW  = \033[0;93m
GREEN   = \033[0;32m
RED     = \033[0;91m
CYAN    = \033[0;96m
BLUE    = \033[0;94m

NAME = philo

SRC_PATH  = src/
SRC       = utils.c \
			pfilos.c




SRCS      = $(addprefix $(SRC_PATH), $(SRC))

OBJ_DIR   = objs
OBJS      = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC        = gcc
CFLAGS    = -Wall -Wextra -Werror -g
RM        = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(YELLOW)Executable $(NAME) created successfully!$(END)"

$(OBJ_DIR)/%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(BLUE)Cleaned up object & dependency files!$(END)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR) >  /dev/null
	@echo "$(RED)Executable $(NAME) removed!$(END)"

re: fclean all
	@echo "$(CYAN)Everything clean & recompiled!$(END)"

.PHONY: all clean fclean re
