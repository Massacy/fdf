NAME := fdf
NAME_LIBFT := libft/libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
# CFLAGS := -Wall -Wextra -Werror -framework OpenGL -framework AppKit -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
SRCS := fdf.c
OBJS := $(patsubst %.c, %.o, $(SRCS))
INCLUDES := -I/usr/X11/include
MINILIBXDIR := minilibx-linux

MINILIBX := $(MINILIBXDIR)/libmlx_Darwin.a

all: $(NAME)

$(NAME_LIBFT):
	make -C libft


$(NAME) : $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -L $(MINILIBXDIR) -L /usr/X11/lib -lmlx_Darwin -lXext -lX11 -framework OpenGL -framework AppKit -o $(NAME)

$(MINILIBX):
	$(MAKE)	-C $(MINILIBXDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS)
	make -C libft clean
	make -C $(MINILIBXDIR) clean
fclean : clean
	rm -f $(NAME)
	make -C libft fclean
# TODO gnlのcleanとfcleanを追加する
re : fclean $(NAME)

.PHONY: clean fclean re all