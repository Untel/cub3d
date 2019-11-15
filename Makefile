LIBS_DIR			= ./libs
LIBFTPRINTF_PATH	= $(LIBS_DIR)/ft_printf
LIBFTPRINTF_MAKE	= $(MAKE) -C $(LIBFTPRINTF_PATH)
LIBFTPRINTF			= -L$(PRINTF_PATH) -lftprintf
MINILIBX_PATH		= $(LIBS_DIR)/minilibx_mms
MINILIBX_MAKE		= $(MAKE) -C $(MINILIBX_MAKE)
MINILIBX			= -L$(MINILIBX_PATH) -lmlx
GNL_PATH			= $(LIBS_DIR)/get_next_line
GNL_MAKE			= $(MAKE) -C $(GNL_MAKE)
GNL					= -L$(GNL_PATH) -lgnl
LIBS				= $(LIBFTPRINTF) $(GNL) $(MINILIBX) -lmlx -framework OpenGL -framework AppKit -lm

SRCS_DIR			= srcs
SRCS_FILES			= main.c ft_parse_map.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I . -I $(LIBFTPRINTF_PATH) -I $(LIBFTPRINTF_PATH)/srcs -I $(LIBFTPRINTF_PATH)/libft -I./headers

CFLAGS				= -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= clang
NAME				= a.out

ARGS				= 

all:				$(OBJS) cub3d.h libs
					$(CC) $(OBJS) $(LIBS) -o $(NAME)

libs:				
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(GNL_MAKE)

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

.PHONY:				all clean fclean re run