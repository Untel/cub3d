/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/19 15:27:36 by adda-sil         ###   ########.fr       */
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
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# define FRAMERATE 		30
# define TICK_DELAY 	(1000 / FRAMERATE)
# define MAX_WIDTH		1920
# define MAX_HEIGHT		1080
# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define PATH_URL_SIZE	1024
# define ERR(...) 		(((printf("[\e[0;31mERROR\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1) * -1)
# define SUC(...) 		(((printf("[\e[0;32mSUCCESS\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1))
# define ERROR 			-1
# define SUCCESS		1
# define HAS_ERR(x)		(x == ERROR)
typedef enum	e_dir
{
	N 			= 'N',
	S 			= 'S',
	W 			= 'W',
	E 			= 'E'
}				t_dir;
typedef enum	e_entity
{
	EMPTY		= 0,
	WALL		= 1,
	OBJECT		= 2
}				t_entity;
typedef enum	e_keybinds
{
	FORWARD 	= 13,
	BACKWARD 	= 1,
	STRAFE_LEFT = 0,
	STRAFE_RIGHT= 2,
	ROTATE_LEFT = 12,
	ROTATE_RIGHT= 14,
	ESCAPE		= 53,
	CTRL		= 256
}				t_keybinds;
typedef struct	map_s
{
	int			width;
	int			height;
	int			grid[MAX_WIDTH][MAX_HEIGHT];
}				map_t;
typedef struct	position_s
{
	double		x;
	double		y;
}				position_t;
typedef struct	player_s
{
	position_t	pos;
	position_t	dir;
	position_t	plane;
	double 		ms;
	double		rs;
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
typedef int 	texture_t[TEX_HEIGHT * TEX_WIDTH];

typedef struct	image_s
{
	void		*ref;
	int			height;
	int			width;
}				image_t;
typedef struct	game_s
{
    void		*mlx;
	window_t	win;
	map_t		map;
	player_t	player;
	env_t		env;
	double		time;
	int			collision;
	texture_t	texture[8];
	image_t		image[4];
}				game_t;

int				move_forward(void);
int				generate_texture(void);
int				move_backward(void);
int 			rotate(int deg);
int				strafe_left(void);
int				strafe_right(void);
int				ft_args(int ac, char **argv);
int				draw_frame(void);
game_t			game;
#endif