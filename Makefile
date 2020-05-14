##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SRC     =	$(shell find $(SOURCEDIR) -name '*.c' ! -name 'unit_tests.c')

OBJ     =       $(SRC:.c=.o)

TEST	=	$(shell find ./ -name '*.c' ! -name 'main.c')	\

CC	=	gcc -I ./include/ -O2 -pipe -g3

NAME    =	myftp

FLAG	=	-W -Wall -Werror -Wextra -pedantic -g3

all:	$(NAME)

tests_run:	$(TEST)
	$(CC) -o unit_tests $(TEST) -lcriterion --coverage -D DEBUG
	./unit_tests | gcovr

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(FLAG) -I ./include 
	@echo -e '\033[0;36m[\033[0m\033[0;34m$(OBJ)\033[0m\033[0;36m]\033[0m\033[0;32m ✔\033[0m'
	@echo -e '\033[0;32m✔ Server Compiled\033[0m'

clean:
	-@rm -f $(shell find $(SOURCEDIR) -name '*.o')
	-@rm -f $(shell find $(SOURCEDIR) -name '*~')
	-@rm -f $(shell find $(SOURCEDIR) -name '*#')
	-@rm -f $(shell find $(SOURCEDIR) -name '*gc*')
	-@rm -f vgcore*

fclean: clean
	-@rm -f $(NAME)
	@echo -e '\033[0;32m✔ Clean\033[0m'

re:     fclean all

.PHONY: all clean fclean re
