NAME= philo_bonus
SOURCES=  ft_atoi.c parsing.c print.c init.c philo_bonus.c
COMPFLAGS= -Wall -Wextra -Werror -pthread -g -fsanitize=thread
CC = cc
OBJECT=$(SOURCES:.c=.o)

all: $(NAME)

%.o : %.c philo_bonus.h
	$(CC) $(COMPFLAGS) -c $< -o $@

$(NAME) : $(OBJECT)
	$(CC) $(COMPFLAGS) $^ -o $@ 

clean:
	rm -f $(OBJECT)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean make re