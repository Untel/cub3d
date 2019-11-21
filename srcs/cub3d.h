/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/21 15:28:30 by adda-sil         ###   ########.fr       */
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
# define GAME_WIDTH		800
# define GAME_HEIGHT	600
# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define PATH_URL_SIZE	1024
# define KEYCODE_MAX	256
# define ERR(...) 		(((printf("[\e[0;31mERROR\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1) * -1)
# define SUC(...) 		(((printf("[\e[0;32mSUCCESS\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1))
# define ERROR 			-1
# define SUCCESS		1
# define HAS_ERR(x)		(x == ERROR)
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
	CTRL		= 256,
	TAB			= 48,
}				t_keybinds;
typedef struct	s_image
{
	void		*ref;
	char		*data;
	int			height;
	int			width;
	int			bits;
	int			endian;
	int			s_line;
}				t_image;
typedef struct	s_map
{
	int			width;
	int			height;
	int			grid[MAX_WIDTH][MAX_HEIGHT];
	t_image		mini;
}				t_map;
typedef struct	position_s
{
	double		x;
	double		y;
}				position_t;
typedef struct	s_player
{
	position_t	pos;
	double		angle;
	double 		ms;
	double		rs;
}				t_player;
typedef struct	s_window
{
	int			height;
	int			width;
    void		*ref;
}				t_window;
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
typedef struct	s_texture
{
}				t_texture;
typedef struct	s_settings
{
	int			collision;
	char		foreward;
	char		backward;
	char		rotate_r;
	char		rotate_l;
	char		strafe_r;
	char		strafe_l;
	char		jump;
	char		crouch;
}				t_settings;
typedef struct	s_ray
{
    int			stepx;
    int			stepy;
    int			x;
    int			y;
    double		distx;
    double		disty;
    double		step_distx;
    double		step_disty;
    int			vert;
    double		dist;
    double		pos;
    // t_list		*lst_objects;
}               t_ray;
typedef struct	s_game
{
    void		*mlx;
	t_window	win;
	t_image		renderer;
	t_map		map;
	t_player	player;
	env_t		env;
	t_texture	tex[256];
	t_image		image;
	t_settings	s;
	char		collision;
	char		event[KEYCODE_MAX];
}				t_game;

int				move_forward(t_game *game);
int				generate_texture(t_game *game);
int				move_backward(t_game *game);
int 			rotate(t_game *game, double deg);
int				strafe_left(t_game *game);
int				strafe_right(t_game *game);
int				draw_frame(t_game *game);

int				ft_args(t_game *game, int ac, char **argv);
int				ft_generate_renderer(t_game *game);
int				ft_generate_minimap(t_game *game);
int				ft_generate_image(t_game *game, t_image *ptr, int w, int h);
int				ft_set_pixel(t_image *ptr, int x, int y, int color);

#endif