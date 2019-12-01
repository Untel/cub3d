UNAME_S				:= $(shell uname -s)
OS					= 0

ifeq ($(UNAME_S), Linux)
	OS = 1
	LGL := -lGL -lm
	LGL_INC := /usr/include/GL
	MLXFLAG := -lm -lpthread -lXext -lX11
else ifeq ($(UNAME_S), Darwin)
	OS = 2
	LGL := -framework OpenGL -framework AppKit
	# LGL_INC := /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.14.sdk/System/Library/Frameworks/OpenGL.framework/Headers
	LGL_INC := ~/.brew/include
	CFLAGS += -Wno-deprecated-declarations
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
SRCS_FILES			= main.c ft_hud.c ft_snapshot.c ft_config.c ft_move.c ft_utils.c ft_draw.c ft_texture.c ft_minimap.c ft_engine.c ft_image.c ft_gameloop.c ft_megamap.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I . -I./headers $(GNL_INCL) $(LIBFTPRINTF_INCL) -I$(MINILIBX_PATH)/

CFLAGS				= -Ofast -D OS=$(OS) -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= clang
NAME				= a.out

ARGS				= config.cub

all:				$(OBJS) srcs/cub3d.h
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(GNL_MAKE)
					$(CC) -I./srcs $(OBJS) $(LIBS) -o $(NAME)

# libs:				
# 					$(LIBFTPRINTF_MAKE)
# 					$(MINILIBX_MAKE)
# 					$(GNL_MAKE)

run:				all
					rm -f snapshot.bmp
					./$(NAME) $(ARGS)

runv1:				v1
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