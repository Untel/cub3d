OS					= 2
MLXFLAG				= -framework OpenGL -framework Appkit -lmlx

LIBFT_LINK			= -L$(LIBFT_PATH) -lft
LIBFT_PATH			= libft
LIBFT_MAKE			= $(MAKE) -C $(LIBFT_PATH)
LIBFT_INCL			= -I $(LIBFT_PATH) -I $(LIBFT_PATH)/headers

LIBS				= -lm $(LIBFT_LINK) $(MLXFLAG)

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

INCLUDES			= -I./srcs $(LIBFT_INCL)

CFLAGS				= -Ofast -D OS=$(OS) -Wall -Wextra -Werror $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= gcc
NAME				= cub3d

ARGS				= 1.cub

libft:
					$(LIBFT_MAKE)

all:				libft $(OBJS) srcs/cub3d.h
					$(CC) $(OBJS) $(LIBS) -o $(NAME)

bonus:				all

run:				all
					./$(NAME) $(ARGS)

norme:
					norminette $(SRCS)

clean:
					$(RM) $(OBJS)

fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME)
					$(LIBFT_MAKE) fclean

re:					clean all

.PHONY:				all clean fclean re run