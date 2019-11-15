PRINTF_PATH			= ft_printf
TEST_DIR			= .
TEST_FILES			= main.c
TESTER				= $(addprefix $(TEST_DIR)/, $(TEST_FILES))
INCLUDES			= -I . -I $(PRINTF_PATH) -I $(PRINTF_PATH)/srcs -I $(PRINTF_PATH)/libft
CFLAGS				= -w -g $(INCLUDES)
LIBFTPRINTF_MAKE	= $(MAKE) -C $(PRINTF_PATH)
TEST_OBJS			= $(TESTER:.c=.o)
CC					= clang
NAME				= a.out
LIBFTPRINTF			= -L$(PRINTF_PATH) -lftprintf
ARGS				= 

all:				$(TEST_OBJS)
					$(LIBFTPRINTF_MAKE)
					$(CC) $(TEST_OBJS) $(LIBFTPRINTF) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

run:				all
					./$(NAME) $(ARGS)

clean:
					$(RM) $(OBJS) $(TEST_OBJS)
					$(LIBFTPRINTF_MAKE) clean
fclean:
					$(RM) $(OBJS) $(TEST_OBJS)
					$(RM) $(NAME) $(TEST_OUTPUT)
					$(LIBFTPRINTF_MAKE) fclean

re:					fclean all

.PHONY:				all clean fclean re libft retest run