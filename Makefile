# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pamatya <pamatya@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 14:30:19 by pamatya           #+#    #+#              #
#    Updated: 2024/06/25 19:43:40 by pamatya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	cc -g
# CC		=	cc -g -fsanitize=address
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
C2_ARG	=	"file"
CMD2	=	"grep $(C2_ARG)"
# CMD2	=	cat

SRCS	=	./src/pipex_main.c ./src/pipex_utils.c

OBJS	=	$(SRCS:.c=.o)

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

re: fclean all

cleanx:
	$(RM) $(OBJS)
	$(MAKE) -C $(DIR) clean

fcleanx: cleanx
	$(RM) $(PIP_LIB)
	$(RM) $(EXEC_IN)
	$(MAKE) -C $(DIR) fclean
	$(RM) $(EXEC_IN)2
	$(RM) ./bin/bug

exe:
	$(EXEC_IN) $(INFILE) $(CMD1) $(CMD2) $(OUTFILE)

exe2:
	$(CC) $(CFLAGS) ./src/pipex2.c -o ./bin/pipex2
	$(EXEC_IN)2
	
debug:
	$(CC) $(CFLAGS) ./lib/libft.a ./src/pipex_main.c ./src/pipex_utils.c -o ./bin/bug

.PHONY: all clean fclean re cleanx fcleanx
