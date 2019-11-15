/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 12:05:36 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# define MAX_WIDTH		1920
# define MAX_HEIGHT		1080
# define PATH_URL_SIZE	1024
# define ERR(...) (((printf("[\e[0;31mERROR\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1) * -1)
# define SUC(...) (((printf("[\e[0;32mSUCCESS\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1))
# define ERROR -1
# define SUCCESS 1
# define HAS_ERR(x) (x == ERROR)
typedef enum	e_dir
{
	N = 'N',
	S = 'S',
	W = 'W',
	E = 'E'
}				t_dir;
typedef enum	e_entity
{
	EMPTY	= 0,
	WALL	= 1,
	OBJECT	= 2
}				t_entity;
typedef struct	map_s
{
	int	width;
	int	height;
	int	grid[MAX_WIDTH][MAX_HEIGHT];
}				map_t;
typedef struct	player_s
{
	double	x;
	double	y;
	t_dir	dir;		
}				player_t;
typedef struct	window_s
{
	int			height;
	int			width;
    void		*ref;
}				window_t;
typedef struct	env_s
{
	char		NO[PATH_URL_SIZE];
	char		SO[PATH_URL_SIZE];
	char		WE[PATH_URL_SIZE];
	char		EA[PATH_URL_SIZE];
	char		SPRITE[PATH_URL_SIZE];
	int			FLOOR;
	int			CEIL;
}				env_t;
typedef struct	sprite_s
{
}				sprite_t;
typedef struct	game_s
{
    void		*mlx;
	window_t	win;
	map_t		map;
	player_t	player;
	env_t		env;
}				game_t;
game_t			game;
int	ft_args(int ac, char **argv);
#endif