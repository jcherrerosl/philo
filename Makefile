NAME	=	philo
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -pthread

SRCS	=	philo.c \

OBJS_DIR = objs
OBJS	=	$(SRCS:.c=.o)
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

all: $(NAME)

$(NAME): $(OBJS_PATH)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS_PATH)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
