OS					= 2
MLXFLAG				= -framework OpenGL -framework Appkit -lmlx

LIBS_DIR			= ./libs
LIBFTPRINTF_PATH	= $(LIBS_DIR)/ft_printf
LIBFTPRINTF_MAKE	= $(MAKE) -C $(LIBFTPRINTF_PATH)
LIBFTPRINTF			= -L$(LIBFTPRINTF_PATH) -lftprintf
LIBFTPRINTF_INCL	= -I $(LIBFTPRINTF_PATH) -I $(LIBFTPRINTF_PATH)/srcs -I $(LIBFTPRINTF_PATH)/libft

GNL_PATH			= $(LIBS_DIR)/get_next_line
GNL_MAKE			= $(MAKE) -C $(GNL_PATH)
GNL					= -L$(GNL_PATH) -lgnl
GNL_INCL			= -I $(GNL_PATH)

LIBS				= -lm $(LIBFTPRINTF) $(GNL) $(MLXFLAG)

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

INCLUDES			= -I . -I./headers $(GNL_INCL) $(LIBFTPRINTF_INCL)

CFLAGS				= -Ofast -D OS=$(OS) -Wall -Wextra -Werror $(INCLUDES)
OBJS				= $(SRCS:.c=.o)
CC					= gcc
NAME				= cub3d

ARGS				= 1.cub

all:				$(OBJS) srcs/cub3d.h


					$(LIBFTPRINTF_MAKE)
					$(GNL_MAKE)
					$(CC) -I./srcs $(OBJS) $(LIBS) -o $(NAME)

bonus:				all

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