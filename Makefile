OS					= 2

LIBFT_LINK			= -L$(LIBFT_PATH) -lft
LIBFT_PATH			= ./libft
LIBFT_MAKE			= @$(MAKE) -C $(LIBFT_PATH)
LIBFT_INCL			= -I $(LIBFT_PATH) -I $(LIBFT_PATH)/headers

LIBS				= -lm  -framework OpenGL -framework Appkit -lmlx $(LIBFT_LINK)

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

norme:
					norminette $(SRCS)

clean:
					$(RM) $(OBJS)
					$(LIBFT_MAKE) clean

fclean:
					$(RM) $(OBJS)
					$(RM) $(NAME)
					$(LIBFT_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re run makelib