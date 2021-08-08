NAME = philo

SRCS = main_all.c forks2.c philos2.c table2.c f_phil2.c f_monitor.c ft_atoi.c

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -rf

CFLAGS = -Wextra -Werror -Wall

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $(<:.c=.o)

clean: 
		$(RM) $(OBJC)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all		


.PHONY:		all clean fclean re
