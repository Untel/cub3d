/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/27 22:21:12 by adda-sil         ###   ########.fr       */
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
# include "mlx.h"
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# define MAX_WIDTH		1920
# define MAX_HEIGHT		1080
# define GAME_WIDTH		800
# define GAME_HEIGHT	600
# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define PATH_URL_SIZE	1024
# define KEYCODE_MAX	300
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

// typedef enum	e_keybinds
// {
// 	W		 	= 13,
// 	S			= 1,
// 	A			= 0,
// 	D			= 2,
// 	Q			= 12,
// 	E			= 14,
// 	ROW_RIGHT	= 124,
// 	ROW_LEFT	= 123,
// 	ESCAPE		= 53,
// 	CTRL		= 256,
// 	SHIFT		= 257,
// 	TAB			= 48,
// 	PLUS		= 69,
// 	MINUS		= 78,
// }				t_keybinds;

typedef enum	e_keybinds
{
	W		 	= 122,
	S			= 115,
	A			= 113,
	D			= 100,
	Q			= 97,
	E			= 101,
	ROW_RIGHT	= 0,
	ROW_LEFT	= 0,
	ESCAPE		= 0,
	CTRL		= 0,
	SHIFT		= 0,
	TAB			= 0,
	PLUS		= 0,
	MINUS		= 0,
}				t_keybinds;

typedef struct	s_doublepos
{
	double		x;
	double		y;
}				t_dpos;
typedef struct	s_intpos
{
	int			x;
	int			y;
}				t_ipos;
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
typedef struct	t_sprite
{
	t_image		img;
	int			frame_size;
	int			index;
}				t_sprite;
typedef struct	s_object
{
	int			dist;
	double		angle;
	t_dpos		pos;
}				t_object;
typedef int 	t_texture[TEX_HEIGHT * TEX_WIDTH];
typedef struct	s_map
{
	int			width;
	int			height;
	int			grid[MAX_WIDTH][MAX_HEIGHT];
	t_image		mini;
	t_image		mega;
	int			show_mega;
}				t_map;
typedef struct	s_player
{
	t_dpos		pos;
	t_dpos		dir;
	t_dpos		plane;
	double		angle;
	double		ms;
	double		rs;
}				t_player;
typedef struct	s_window
{
	int			height;
	int			width;
    void		*ref;
	t_image		renderer;
	double		cos[MAX_WIDTH];
	double		sin[MAX_WIDTH];
}				t_window;
typedef struct	env_s
{
	t_image		NO;
	t_image		SO;
	t_image		WE;
	t_image		EA;
	t_sprite	S;
	int			FLOOR;
	int			CEIL;
}				env_t;
typedef struct	s_ray
{
    t_ipos		step;
    t_dpos		dist;
    t_dpos		step_dist;
	t_ipos		pos;
	t_dpos		dir;
	double		draw_dist;
    int			vert;
    double		po;
	t_list		*objects;
}               t_ray;
typedef struct	s_game
{
    void		*mlx;
	t_window	win;
	t_map		map;
	t_player	player;
	env_t		env;
	t_image		image;
	char		zbuffer[MAX_WIDTH];
	char		collision;
	char		event[KEYCODE_MAX];
}				t_game;

typedef struct	s_drawer
{
    int			start;
    int			end;
	t_image		*texture;
    double		step_posy;
}				t_drawer;

// Movements
int				move_forward(t_game *game);
int				move_backward(t_game *game);
int 			rotate(t_game *game, double deg);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);
void			update_orientation(double angle, t_dpos *dir);
int				strafe_left(t_game *game);
int				strafe_right(t_game *game);
int				draw_frame(t_game *game);
int				ft_game_loop(t_game *game);
int				ft_read_events(t_game *game);
int				ft_args(t_game *game, int ac, char **argv);
int				ft_generate_renderer(t_game *game);
int				ft_generate_image(t_game *game, t_image *ptr, int w, int h);
int				ft_render(t_game *game);
int				ft_draw_renderer(t_game *game, t_ipos pos, int color);

// Image
int				ft_set_pixel(t_image *ptr, t_ipos pos, int color);
int				ft_get_pixel(t_image *ptr, t_ipos pos);

// Minimap
int				ft_generate_minimap(t_game *game);
int				ft_draw_minimap(t_game *game);
int				ft_draw_minimap_square(t_game *game, t_ipos pos, int color);
int				ft_draw_minimap_pix(t_game *game, double x, double y, int color);
void			to_intpos(t_ipos *ret, t_dpos pos);

// Megamap
int				ft_generate_megamap(t_game *game);
int				ft_draw_megamap(t_game *game);
int				ft_render_megamap(t_game *game);
int				ft_update_megamap(t_game *game, t_ray *ray);
#endif