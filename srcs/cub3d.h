/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:12:36 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 15:27:10 by adda-sil         ###   ########.fr       */
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
# include <errno.h>
# define MAX_WIDTH			2560
# define MAX_HEIGHT			1440
# define MAX_MAP_HEIGHT		500
# define MAX_MAP_WIDTH		500
# define GAME_WIDTH			800
# define GAME_HEIGHT		600
# define TEX_HEIGHT			64
# define TEX_WIDTH			64
# define PATH_URL_SIZE		1024
# define ERROR 				-1
# define SUCCESS			1
# define RED				0x00ff0000
# define ORANGE				0x00ffA500
# define YELLOW				0x00ffff00
# define GREEN				0x0000ff00
# define WHITE				0x00ffffff
# define BLACK				0x0
# define OCTET				0xFF
# define CH_RADIAN			10
# define CH_COLOR			GREEN
# define CH_SIZE			2
# define HEALTHBAR_WIDTH	150
# define HEALTHBAR_HEIGHT	20
# define HEALTHBAR_PADDING	5
# define HEALTHBAR_BORDER	WHITE
# define LINUX_OS			1
# define ERR0               "Key 'R' for resolution is missing in config file."
# define ERR1               "Key 'NO' for north wall texture path is missing in config file."
# define ERR2               "Key 'SO' for south wall texture path is missing in config file."
# define ERR3               "Key 'WE' for west wall texture path is missing in config file."
# define ERR4               "Key 'EA' for east wall texture path is missing in config file."
# define ERR5               "Key 'S' for sprite texture path is missing in config file."
# define ERR6               "Key 'F' for floor color is missing in config file."
# define ERR7               "Key 'C' for ceil color is missing in config file."
# if OS == LINUX_OS
#  include "keys_linux.h"
#  include "mlx.h"
# else
#  include "keys_darwin.h"
#  include <mlx.h>
# endif

typedef enum	e_entity
{
	EMPTY,
	WALL,
	OBJECT
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
	TOGGLE_SHADING,
	INC_SPEED,
	DEC_SPEED,
	FIRE,
	JUMP,
	CROUCH,
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
	t_ipos		draw;
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
	double		old_ms;
	double		rs;
	int			view;
	int			view2;
	int			jumping;
	int			crouched;
	int			hp;
	int			max_hp;
}				t_player;
typedef struct	s_window
{
	int			height;
	int			width;
    void		*ref;
	t_image		renderer;
	double		*cos;
	double		*sin;
	double		*floor_dist;
	double		*sky_dist;
	
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
	t_player	p;
	env_t		env;
	t_image		image;
	t_sprite	weapon;
	char		collision;
	int			max_jump;
	char		hud;
	char		shading;
	char		event[EXIT + 1];
}				t_game;

typedef struct	s_drawer
{
    int			start;
    int			end;
	t_image		*tex;
    double		step_posy;
    double		posy;
	int			delta;
}				t_drawer;

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
void			crouch(t_game *game);
void			jump(t_game *game);
void			fire(t_game *game);
int				ft_draw_frame(t_game *game);
void			ft_game_loop(t_game *game);
int				ft_read_events(t_game *game);
int				ft_args(t_game *game, int ac, char **argv);
int				ft_generate_renderer(t_game *game);
int				ft_generate_image(t_game *game, t_image *ptr, int w, int h);
int				ft_render(t_game *game);
int				ft_draw_renderer(t_game *game, t_ipos pos, unsigned int color);
int				ft_destroy_window(t_game *game);
int				ft_generate_floor_dist(t_game *game);
void			ft_increment_sprite_index(t_sprite *spr);
void			init_ray(t_game *game, t_ray *ray);
void			ft_compute_ray(t_game *game, t_ray *ray);
void			ft_draw_objects(t_game *game, int column, t_ray *ray, t_drawer *drawer);
void			ft_draw_object(t_game *game, int column, t_object *obj, t_drawer *drawer);
t_object		*ft_newobject(t_game *game, t_ray *ray);
int				ft_hud(t_game *game);
int				ft_set_pixel(t_image *ptr, t_ipos pos, unsigned int color);
unsigned int	ft_get_pixel(t_image *ptr, t_ipos pos);
int				ft_init_drawer(t_game *game, t_drawer *drawer, double height);
void			ft_draw_sprite(t_game *game, t_sprite *spr, t_dpos draw_tex, double rate);
int				ft_transfert_pixel(t_image *from, t_image *to, double rate);
unsigned char	ft_shade(unsigned char oct, double divide, int idx);
int				ft_shader(int color, double divide);
int				ft_generate_minimap(t_game *game);
int				ft_draw_minimap(t_game *game);
int				ft_draw_minimap_square(t_game *game, t_ipos pos, unsigned int color);
int				ft_draw_minimap_pix(t_game *game, double x, double y, unsigned int color);
void			to_intpos(t_ipos *ret, t_dpos pos);
int				ft_generate_megamap(t_game *game);
int				ft_draw_megamap(t_game *game);
int				ft_render_megamap(t_game *game);
int				ft_update_megamap(t_game *game, t_ray *ray);
int				ft_keypress_hook(int keycode, t_game *game);
int				ft_keyrelease_hook(int keycode, t_game *game);
int				ft_init_hook(t_game *game);
int				ft_read_events(t_game *game);
int				ft_destroy_window(t_game *game);
void			ft_leave_program(t_game *game);
void 			ft_toggle_key(t_game *game, int keycode, int value);
int 			ft_print_err(char *txt);
int 			ft_print_defined_err();
double			decim(double val);
int				ft_check_ext(char *path, char *ext);
int				ft_get_next_number(char **str, char ignorable);
int				ft_set_player_position(t_game *game, char dir, int x, int y);
int				ft_set_image(t_game *game, t_image *img, char *path);
int				ft_verify_opts(char *opts);
int				ft_check_opts(char *opts, char key);
int             ft_generate_cos_sin_table(t_game *game);
void            ft_draw_floor(t_game *g, t_drawer *drawer, t_ipos *d);
void            ft_draw_sky(t_game *g, t_drawer *drawer, t_ipos *d);
int             ft_set_window_size(t_game *game, char *str);
#endif