LIBS_DIR			= ./libs
LIBFTPRINTF_PATH	= $(LIBS_DIR)/ft_printf
LIBFTPRINTF_MAKE	= $(MAKE) -C $(LIBFTPRINTF_PATH)
LIBFTPRINTF			= -L$(LIBFTPRINTF_PATH) -lftprintf
LIBFTPRINTF_INCL	= -I $(LIBFTPRINTF_PATH) -I $(LIBFTPRINTF_PATH)/srcs -I $(LIBFTPRINTF_PATH)/libft
MINILIBX_PATH		= $(LIBS_DIR)/minilibx_mms
MINILIBX_MAKE		= $(MAKE) -C $(MINILIBX_PATH)
MINILIBX			= -L$(MINILIBX_PATH) -lmlx
GNL_PATH			= $(LIBS_DIR)/get_next_line
GNL_MAKE			= $(MAKE) -C $(GNL_PATH)
GNL					= -L$(GNL_PATH) -lgnl
GNl_INCL			= -I $(GNL_PATH)
LIBS				= $(LIBFTPRINTF) $(GNL) $(MINILIBX) -lmlx -framework OpenGL -framework AppKit -lm

SRCS_DIR			= srcs
SRCS_FILES			= main.c ft_config.c ft_move.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I . -I./headers $(GNl_INCL) $(LIBFTPRINTF_INCL)

CFLAGS				= -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= clang
NAME				= a.out

ARGS				= config.cub

all:				$(OBJS) cub3d.h
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(GNL_MAKE)
					$(CC) $(OBJS) $(LIBS) -o $(NAME)

# libs:				
# 					$(LIBFTPRINTF_MAKE)
# 					$(MINILIBX_MAKE)
# 					$(GNL_MAKE)

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