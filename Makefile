PRINTF_PATH			= libs/ft_printf
LIBFTPRINTF_MAKE	= $(MAKE) -C $(PRINTF_PATH)
MINILIBX_PATH		= libs/minilibx_mms
MINILIBX_MAKE		= $(MAKE) -C $(PRINTF_PATH)

SRCS_DIR			= srcs
SRCS_FILES			= main.c ft_parse_map.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I . -I $(PRINTF_PATH) -I $(PRINTF_PATH)/srcs -I $(PRINTF_PATH)/libft -I./headers

CFLAGS				= -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= clang
NAME				= a.out

LIBFTPRINTF			= -L$(PRINTF_PATH) -lftprintf

ARGS				= 

all:				$(OBJS) cub3d.h
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(CC) $(OBJS) $(LIBFTPRINTF) -lmlx -framework OpenGL -framework AppKit -lm -o $(NAME)

run:				all
					./$(NAME) $(ARGS)

clean:
					$(RM) $(OBJS)
					$(LIBFTPRINTF_MAKE) clean
fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME) $(TEST_OUTPUT)
					$(LIBFTPRINTF_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re libft retest run