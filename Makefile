NAME		=	philo

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror -pthread

SRCDIR		=	src
OBJDIR		=	objs
INCDIR		=	includes

SRCS		=	$(SRCDIR)/philo.c \
				$(SRCDIR)/simulation.c \
				$(SRCDIR)/check_end.c \
				$(SRCDIR)/utils.c \
				$(SRCDIR)/forks.c \

OBJS		=	$(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
