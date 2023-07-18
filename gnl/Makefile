NAME := gnl.a
SRC := get_next_line.c get_next_line_utils.c
OBJS := $(SRC:.c=.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror

$(NAME): $(OBJS)
	ar r $(NAME) $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)
clean : 
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean
	make all

.PHONY: clean fclean re all