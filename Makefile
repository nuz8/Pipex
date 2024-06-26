# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 14:30:19 by pamatya           #+#    #+#              #
#    Updated: 2024/06/27 01:40:41 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC		=	cc
CC		=	cc -g -fsanitize=address

CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -f

NAME	=	pipex
PIP_LIB	=	pipex.a
DIR		=	lib
LIB		=	libft.a
EXEC_IN	=	./bin/$(NAME)

INFILE	=	./io_files/infile.txt
OUTFILE	=	./io_files/outfile.txt
CMD1	=	cat
C2_ARG	=	\"nn   1087 May\"
CMD2	=	"grep $(C2_ARG)"

TEST	=	./src/ft_parse.c

SRCS	=	./src/pipex_main.c ./src/pipex_utils.c ./src/children.c ./src/fields.c ./src/ft_parse.c

OBJS	=	$(SRCS:.c=.o)

DEBUG	=	$(TEST)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	cp ./$(DIR)/$(LIB) ./$(PIP_LIB)
	ar rcs $(PIP_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(PIP_LIB) -o $(EXEC_IN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB):
	$(MAKE) -C $(DIR) all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(PIP_LIB)
	$(RM) $(EXEC_IN)
	$(RM) $(EXEC_IN)2
	$(RM) ./bin/test
	$(RM) ./bin/test_main
	$(RM) ./bin/bug
	$(RM) -r ./bin/bug.dSYM

re: fclean all

cleanx:
	$(RM) $(OBJS)
	$(MAKE) -C $(DIR) clean

fcleanx: cleanx
	$(RM) $(PIP_LIB)
	$(RM) $(EXEC_IN)
	$(MAKE) -C $(DIR) fclean

exe:
	$(EXEC_IN) $(INFILE) $(CMD1) $(CMD2) $(OUTFILE)

exe2:
	$(CC) $(CFLAGS) ./src/pipex2.c -o ./bin/pipex2
	$(EXEC_IN)2
	
bug:
	$(CC) -g $(CFLAGS) ./lib/libft.a $(DEBUG) -o ./bin/bug

test:
	$(CC) $(CFLAGS) ./lib/libft.a $(TEST) -o ./bin/test
	./bin/test
	

.PHONY: all clean fclean re cleanx fcleanx
