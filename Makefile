UNAME_S				:= $(shell uname -s)
OS					= 0

ifeq ($(UNAME_S), Linux)
	OS = 1
	LGL := -lGL -lm
	LGL_INC := /usr/include/GL
	MLXFLAG := -lXext -lX11
else ifeq ($(UNAME_S), Darwin)
	OS = 2
	MLXFLAG := -framework OpenGL -framework Appkit
endif

LIBFT_PATH			= ./libft
LIBFT_LINK			= -L$(LIBFT_PATH) -lft
LIBFT_MAKE			= @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INCL			= -I $(LIBFT_PATH) -I $(LIBFT_PATH)/headers

MLX_PATH			= ./mlx
MLX_LINK			= -L$(MLX_PATH) -lmlx
MLX_MAKE			= @$(MAKE) -C $(MLX_PATH)
MLX_INCL			= -I $(MLX_PATH)

LIBS				= -lm $(LIBFT_LINK) $(MLX_LINK) $(MLXFLAG)

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
	ft_minimap.c\
	ft_engine.c\
	ft_image.c\
	ft_gameloop.c\
	ft_megamap.c\
	ft_errors.c\
	ft_events.c\
	ft_hooks.c\
	ft_ray.c\
	ft_shades.c\
	ft_rotation.c\
	ft_actions.c\

SRCS				= $(addprefix $(SRCS_DIR)/, $(SRCS_FILES))

INCLUDES			= -I./srcs $(LIBFT_INCL) $(MLX_INCL)

CC					= gcc
CFLAGS				= -Ofast -D OS=$(OS) -Wall -Wextra -Werror $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
NAME				= cub3D

ARGS				= 1.cub		
OBJ_DIR				= objs


all:				makelib
					@$(MAKE) $(NAME)

$(NAME):			$(OBJS) srcs/cub3d.h
					$(CC) $(OBJS) $(LIBS) -o $(NAME)

bonus:				all

run:				all
					./$(NAME) $(ARGS)		

makelib:			
					$(LIBFT_MAKE)
					$(MLX_MAKE)

norme:
					$(LIBFT_MAKE) norme
					norminette $(SRCS) srcs/cub3d.h

clean:
					$(RM) $(OBJS)

fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME)
					$(LIBFT_MAKE) fclean

re:					clean all

fre:				fclean all

.PHONY:				all clean fclean re fre norme bonus run makelib
