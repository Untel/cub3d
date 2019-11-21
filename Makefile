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
GNL_INCL			= -I $(GNL_PATH)
LIBS				= $(LIBFTPRINTF) $(GNL) $(MINILIBX) -lmlx -framework OpenGL -framework AppKit -lm

SRCSv1_DIR			= srcsv1
SRCSv1_FILES		= main.c ft_config.c ft_move.c ft_draw.c ft_texture.c
SRCSv1				= $(addprefix $(SRCSv1_DIR)/, $(SRCSv1_FILES))
SRCS_DIR			= srcs
SRCS_FILES			= main.c ft_config.c ft_move.c ft_draw.c ft_texture.c ft_minimap.c ft_engine.c ft_image.c
SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))
INCLUDES			= -I . -I./headers -I./srcs $(GNL_INCL) $(LIBFTPRINTF_INCL)

CFLAGS				= -w -g $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
OBJSv1				= $(SRCSv1:.c=.o)
CC					= clang
NAME				= a.out

ARGS				= config.cub

all:				$(OBJS) srcs/cub3d.h
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(GNL_MAKE)
					export DYLD_LIBRARY_PATH=~/in/cub3d/libs/minilibx_mms
					$(CC) $(OBJS) $(LIBS) -o $(NAME)

v1:					$(OBJSv1) srcsv1/cub3d.h
					$(LIBFTPRINTF_MAKE)
					$(MINILIBX_MAKE)
					$(GNL_MAKE)
					export DYLD_LIBRARY_PATH=~/in/cub3d/libs/minilibx_mms
					$(CC) $(OBJSv1) $(LIBS) -o $(NAME)
# libs:				
# 					$(LIBFTPRINTF_MAKE)
# 					$(MINILIBX_MAKE)
# 					$(GNL_MAKE)

run:				all
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