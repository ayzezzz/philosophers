NAME= philo

SRCS= main.c\
		check_argv.c\
		check_thread.c\
		init.c\
		thread_create.c\
		thread_destroy.c\
		utils.c\

OBJS= ${SRCS:.c=.o}

CC= gcc
CFLAGS= -Wall -Wextra -Werror -g
RM= rm -rf

all: $(NAME)

$(NAME) : $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean: 
	$(RM) $(OBJS)


fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY:all clean fclean re