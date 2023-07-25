NAME := fdf
NAME_LIBFT := libft/libft.a
NAME_GNL := gnl/gnl.a
CC := cc
# CFLAGS := -Wall -Wextra -Werror 
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -framework OpenGL -framework AppKit -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
SRCS := fdf.c bresenham.c get_int_color_from_base16.c change_view1.c change_view2.c make_map1.c make_map2.c mlx_utils1.c mlx_utils2.c
OBJS := $(patsubst %.c, %.o, $(SRCS))
INCLUDES := -I/usr/X11/include
MINILIBXDIR := minilibx-linux

MINILIBX := $(MINILIBXDIR)/libmlx_Darwin.a

all: $(NAME)

$(NAME_LIBFT):
	make -C libft

$(NAME_GNL):
	make -C gnl

$(NAME) : $(MINILIBX) $(OBJS) $(NAME_LIBFT) $(NAME_GNL)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(NAME_LIBFT) $(NAME_GNL) -L $(MINILIBXDIR) -L /usr/X11/lib -lmlx_Darwin -lXext -lX11 -framework OpenGL -framework AppKit -o $(NAME)

$(MINILIBX):
	$(MAKE)	-C $(MINILIBXDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean :
	rm -f $(OBJS)
	make -C libft clean
	make -C gnl clean
	make -C $(MINILIBXDIR) clean
fclean : clean
	rm -f $(NAME)
	make -C libft fclean
	make -C gnl fclean
re : fclean 
	make $(NAME)

.PHONY: clean fclean re all