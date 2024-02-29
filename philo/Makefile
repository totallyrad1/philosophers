NAME= philo
SOURCES= philo.c init.c ft_atoi.c parsing.c freeall.c print.c
COMPFLAGS= -Wall -Wextra -Werror
CC = cc
OBJECT=$(SOURCES:.c=.o)

all: $(NAME)

%.o : %.c philo.h
	$(CC) $(COMPFLAGS) -c $< -o $@

$(NAME) : $(OBJECT)
	$(CC) $(COMPFLAGS) -o $@ $^ 

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean make re