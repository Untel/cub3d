/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 18:21:14 by adda-sil         ###   ########.fr       */
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
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# define MAX_WIDTH		1920
# define MAX_HEIGHT		1080
# define MAX_MAP_HEIGHT	300
# define MAX_MAP_WIDTH	200
# define GAME_WIDTH		800
# define GAME_HEIGHT	600
# define TEX_HEIGHT		64
# define TEX_WIDTH		64
# define PATH_URL_SIZE	1024
# define ERR(...) 		(((printf("[\e[0;31mERROR\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1) * -1)
# define SUC(...) 		(((printf("[\e[0;32mSUCCESS\e[0m] ") && printf(__VA_ARGS__) && printf("\n")) || 1))
# define ERROR 			-1
# define SUCCESS		1
# define HAS_ERR(x)		(x == ERROR)
# define RED 0x00ff0000
# define ORANGE 0x00ffA500
# define YELLOW 0x00ffff00
# define GREEN 0x0000ff00
# define WHITE 0x00ffffff
# define BLACK 0x0
# define OCTET 0xFF
# define CH_RADIAN 10
# define CH_COLOR GREEN
# define CH_SIZE 2
# define HEALTHBAR_WIDTH 150
# define HEALTHBAR_HEIGHT 20
# define HEALTHBAR_PADDING 5
# define HEALTHBAR_BORDER WHITE
# define LINUX_OS 1
# if OS == LINUX_OS
#  include "keys_linux.h"
#  include "mlx.h"
# else
#  include "keys_darwin.h"
#  include <mlx.h>
# endif

typedef enum	e_entity
{
	EMPTY		= 0,
	WALL		= 1,
	OBJECT		= 2
}				t_entity;
typedef enum	e_keybinds
{
	FORWARD,
	BACKWARD,
	STR_LEFT,
	STR_RIGHT,
	ROT_LEFT,
	ROT_RIGHT,
	ROT_UP,
	ROT_DOWN,
	TOGGLE_MAP,
	TOGGLE_COLLISION,
	INC_SPEED,
	DEC_SPEED,
	FIRE,
	EXIT,
}				t_keybings;
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
	t_ipos		index;
	t_ipos		frame_size;
}				t_sprite;
typedef struct	s_object
{
	double		dist;
	double		angle;
	double		dir;
	t_dpos		pos;
}				t_object;
typedef struct	s_map
{
	int			width;
	int			height;
	int			grid[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
	int			sprites[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
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
	double		view;
	int			hp;
	int			max_hp;
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
	t_dpos		floor;
	double		draw_dist;
    double		po;
    int			vert;
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
	t_sprite	weapon;
	char		collision;
	char		event[EXIT + 1];
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
void			rotate_up(t_game *game);
void			rotate_down(t_game *game);
void			update_orientation(double angle, t_dpos *dir);
int				strafe_left(t_game *game);
int				strafe_right(t_game *game);
int				ft_draw_frame(t_game *game);
int				ft_game_loop(t_game *game);
int				ft_read_events(t_game *game);
int				ft_args(t_game *game, int ac, char **argv);
int				ft_generate_renderer(t_game *game);
int				ft_generate_image(t_game *game, t_image *ptr, int w, int h);
int				ft_render(t_game *game);
int				ft_draw_renderer(t_game *game, t_ipos pos, unsigned int color);
int				ft_destroy_window(t_game *game);

int				ft_increment_sprite_index(t_sprite *spr);
//rays
// void			init_ray(t_game *game, t_ray *ray);
// void			compute_ray(t_game *game, t_ray *ray);
void			ft_draw_objects(t_game *game, int column, t_ray *ray, t_drawer *drawer);
void			ft_draw_object(t_game *game, int column, t_object *obj, t_drawer *drawer);
t_object		*ft_newobject(t_game *game, t_ray *ray);
int				ft_hud(t_game *game);

// Image
int				ft_set_pixel(t_image *ptr, t_ipos pos, unsigned int color);
unsigned int	ft_get_pixel(t_image *ptr, t_ipos pos);
void			ft_draw_sprite(t_game *game, t_sprite *spr, t_ipos draw, t_dpos draw_tex);

// Minimap
int				ft_generate_minimap(t_game *game);
int				ft_draw_minimap(t_game *game);
int				ft_draw_minimap_square(t_game *game, t_ipos pos, unsigned int color);
int				ft_draw_minimap_pix(t_game *game, double x, double y, unsigned int color);
void			to_intpos(t_ipos *ret, t_dpos pos);
int				ft_transfert_pixel(t_image *from, t_ipos from_pos, t_image *to, t_ipos to_pos);

// Megamap
int				ft_generate_megamap(t_game *game);
int				ft_draw_megamap(t_game *game);
int				ft_render_megamap(t_game *game);
int				ft_update_megamap(t_game *game, t_ray *ray);
#endif