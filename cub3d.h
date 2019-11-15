/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 07:43:02 by adda-sil         ###   ########.fr       */
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
typedef struct	map_s
{
	int	width;
	int	height;
	int	grid[MAX_WIDTH][MAX_HEIGHT];
}				map_t;
typedef struct	player_s
{
				int	x;
				int	y;
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