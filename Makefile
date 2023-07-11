NAME := fdf
# NAME_FT_PRINTF := ft_printf/libftprintf.a
# NAME_LIBFT := libft/libft.a
# INCLUDES := -I./ft_printf -I./
CC := cc
# CFLAGS := -Wall -Wextra -Werror
# CFLAGS := -Wall -Wextra -Werror -framework OpenGL -framework AppKit -fsanitize=address -g
# CFLAGS := -Wall -Wextra -Werror -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
CFLAGS := -Wall -Werror -Wextra 
SRCS := fdf.c
OBJS := $(patsubst %.c, %.o, $(SRCS))
# INCLUDES := -I/usr/X11/include
MINILIBXDIR := minilibx-linux
# MINILIBXDIR := mms

# MINILIBX = $(MINILIBXDIR)/libmlx.dylib
MINILIBX := $(MINILIBXDIR)/libmlx_Darwin.a

all: $(NAME)

# $(NAME_FT_PRINTF):
# 	make -C ft_printf
$(NAME_LIBFT):
	make -C libft
# $(NAME): $(NAME_FT_PRINTF) $(NAME_LIBFT) $(OBJS)
# $(CC) $(CFLAGS) $(OBJS) $(NAME_FT_PRINTF) $(NAME_LIBFT) -o $(NAME)

$(NAME) : $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(MINILIBX) -lX11 -lXext -L/usr/X11R6/lib -framework OpenGL -framework AppKit -o $(NAME)


$(MINILIBX):
	$(MAKE)	-C $(MINILIBXDIR)

# cp $(MINILIBXDIR)/$(MINILIBX) ./

# %.o: %.c
# $(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

clean :
	rm -f $(OBJS)
# make -C ft_printf clean
# make -C libft clean
fclean : clean
	rm -f $(NAME)
# make -C ft_printf fclean
# make -C libft fclean
re : fclean $(NAME)

.PHONY: clean fclean re all