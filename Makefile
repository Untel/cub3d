UNAME_S				:= $(shell uname -s)
OS					= 0

ifeq ($(UNAME_S), Linux)
	OS = 1
	LGL := -lGL -lm
	LGL_INC := /usr/include/GL
	MLXFLAG := -lm -lpthread -lXext -lX11
else ifeq ($(UNAME_S), Darwin)
	OS = 2
	MLXFLAG := -framework OpenGL -framework Appkit
endif

LIBS_DIR			= ./libs
LIBFTPRINTF_PATH	= $(LIBS_DIR)/ft_printf
LIBFTPRINTF_MAKE	= $(MAKE) -C $(LIBFTPRINTF_PATH)
LIBFTPRINTF			= -L$(LIBFTPRINTF_PATH) -lftprintf
LIBFTPRINTF_INCL	= -I $(LIBFTPRINTF_PATH) -I $(LIBFTPRINTF_PATH)/srcs -I $(LIBFTPRINTF_PATH)/libft

MINILIBX_PATH		= $(LIBS_DIR)/minilibx
MINILIBX_MAKE		= $(MAKE) -C $(MINILIBX_PATH)
MINILIBX			= $(MLXFLAG) -L$(MINILIBX_PATH) -lmlx


GNL_PATH			= $(LIBS_DIR)/get_next_line
GNL_MAKE			= $(MAKE) -C $(GNL_PATH)
GNL					= -L$(GNL_PATH) -lgnl
GNL_INCL			= -I $(GNL_PATH)

LIBS				= -lm $(LIBFTPRINTF) $(GNL) $(MINILIBX)

SRCS_DIR			= srcs
SRCS_FILES			= \
	main.c\
	ft_objects.c\
	ft_hud.c\
	ft_snapshot.c\
	ft_config.c\
	ft_config_setters.c\
	ft_config_map.c\
	ft_move.c\
	ft_utils.c\
	ft_draw.c\
	ft_texture.c\
	ft_minimap.c\
	ft_engine.c\
	ft_image.c\
	ft_gameloop.c\
	ft_megamap.c\
	ft_errors.c\
	ft_events.c\
	ft_hooks.c\

SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I . -I./headers $(GNL_INCL) $(LIBFTPRINTF_INCL) -I$(MINILIBX_PATH)/

CFLAGS				= -Ofast -D OS=$(OS) -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= clang
NAME				= cub3d

ARGS				= 1.cub

all:				$(OBJS) srcs/cub3d.h
					$(LIBFTPRINTF_MAKE)
ifeq ($(UNAME_S), Linux)
					$(MINILIBX_MAKE)
endif
					$(GNL_MAKE)
					$(CC) -I./srcs $(OBJS) $(LIBS) -o $(NAME)

bonus:				re

run:				all
					./$(NAME) $(ARGS)

norme:
					norminette $(SRCS)

clean:
					$(RM) $(OBJS)
					$(LIBFTPRINTF_MAKE) clean
fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME) $(TEST_OUTPUT)
					$(LIBFTPRINTF_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re run