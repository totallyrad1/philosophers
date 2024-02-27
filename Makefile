NAME= philo
SOURCES= mandatory/philo.c mandatory/init.c utils/ft_atoi.c
COMPFLAGS= -Wall -Wextra -Werror -g 
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