/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:47:25 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/26 15:42:55 by adda-sil         ###   ########.fr       */	
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_game *game, t_ray *ray)
{
    ray->pos.x = (int)game->player.pos.x;
    ray->pos.y = (int)game->player.pos.y;
    ray->step.x = (game->player.plane.x > 0 ? 1 : -1);
    ray->step.y = (game->player.plane.y > 0 ? 1 : -1);
    ray->step_dist.x = sqrt(1 + (game->player.plane.y * game->player.plane.y) / (game->player.plane.x * game->player.plane.x));
    ray->step_dist.y = sqrt(1 + (game->player.plane.x * game->player.plane.x) / (game->player.plane.y * game->player.plane.y));
    ray->dist.x = ray->step_dist.x *
        (game->player.plane.x >= 0 ? 1. - (game->player.pos.x - ray->pos.x) :
        (game->player.pos.x - ray->pos.x));
    ray->dist.y = ray->step_dist.y *
        (game->player.plane.y >= 0 ? 1. - (game->player.pos.y - ray->pos.y) :
        (game->player.pos.y - ray->pos.y));
    ray->vert = (ray->dist.x >= ray->dist.y);
}

void    compute_ray(t_game *game, t_ray *ray)
{
    int    i;
	t_ipos pos;
    i = -1;
    while (++i < 100)
    {
        if (ray->dist.x < ray->dist.y)
        {
            ray->vert = 0;
            ray->pos.x += ray->step.x;
            if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] != WALL)
                ray->dist.x += ray->step_dist.x;
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
        }
        else
        {
            ray->vert = 1;
            ray->pos.y += ray->step.y;
            if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] != WALL)
                ray->dist.y += ray->step_dist.y;
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
        }
        if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] == WALL)
		{
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
            break ;
		}
    }
}

double	decimal_part(double val)
{
	return (val - (int)val);
}

// void    draw_object(t_params *p, int column, char *content, t_drawer *pdrawer)
// {
//     t_object	*pobj;
//     int            line;
//     double        posy;
//     double        height;
//     int            pix;

//     pobj = (t_object*)content;
//     if (pobj->pos <= 0 || pobj->pos >= 1)
//         return ;
//     height = p->win_height / pobj->dist;
//     pdrawer->start = p->win_height / 2 - height / 2;
//     pdrawer->start = fmax(pdrawer->start, 0);
//     pdrawer->end = p->win_height / 2 + height / 2;
//     pdrawer->end = fmin(pdrawer->end, p->win_height - 1);
//     pdrawer->step_posy = 1 / ((double)(pdrawer->end - pdrawer->start));
//     line = pdrawer->start;
//     posy = 0;
//     while (++line < pdrawer->end)
//     {
//         pix = get_pixel(&p->textures[SPRITE], pobj->pos, posy);
//         if (((pix >> 24) & 0xFF) < 128)
//             p->mlx.img.data[p->win_width * line + column] = pix;
//         posy += pdrawer->step_posy;
//     }
// }

void    ft_draw_column(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
    double		posy;
    double		height;
	t_ipos		draw;
	t_ipos		draw_tex;
	int			delta;

	draw.x = column;
    height = game->win.height / ray->draw_dist / game->map.table_cos[column];
	delta =	height - game->win.height;
    drawer->start = delta <= 0 ? (game->win.height / 2 - height / 2) : 0;
    drawer->end = delta <= 0 ? (game->win.height / 2 + height / 2) : game->win.height;
	drawer->step_posy = 1 / (delta <= 0 ?
		((double)(drawer->end - drawer->start)) : height);
    draw.y = 0;
	if (delta <= 0)
		while (draw.y < drawer->start)
			ft_set_pixel(&(game->renderer), draw, game->env.CEIL) && draw.y++;
	posy = delta > 0 ? (drawer->step_posy * (delta / 2)) : 0;
    while (draw.y < drawer->end)
    {
		draw_tex.x = (int)(ray->po * drawer->texture->height);
		draw_tex.y = (int)(posy * drawer->texture->width);
		ft_set_pixel(&(game->renderer), draw, 
			ft_get_pixel(drawer->texture, draw_tex));
        posy += drawer->step_posy;
		draw.y++;
    }
	if (delta <= 0)
    	while (draw.y < game->win.height)
			ft_set_pixel(&(game->renderer), draw, game->env.FLOOR) && draw.y++;
}

int	ft_game_loop(t_game *game)
{
	char		txt[300];
    int			column;
	double		dist;
    t_ray		ray;
    t_drawer	drawer;

    column = -1;
	ft_read_events(game);
	ft_draw_minimap(game);
	if (game->map.show_mega)
		ft_draw_megamap(game);
    while (++column < game->win.width)
    {
		game->player.plane.x = game->player.dir.x * game->map.table_cos[column] - game->player.dir.y * game->map.table_sin[column];
		game->player.plane.y = game->player.dir.y * game->map.table_cos[column] + game->player.dir.x * game->map.table_sin[column];
        init_ray(game, &ray);
        compute_ray(game, &ray);
        ray.draw_dist = (ray.vert ? ray.dist.y : ray.dist.x);
        ray.po = decimal_part((ray.vert ? game->player.pos.x + ray.draw_dist * game->player.plane.x :
            game->player.pos.y + ray.draw_dist * game->player.plane.y));
   		if (ray.vert)
            drawer.texture = (game->player.pos.y < ray.pos.y ? &(game->env.SO) : &(game->env.NO));
        else
            drawer.texture = (game->player.pos.x < ray.pos.x ? &(game->env.EA) : &(game->env.WE));
		ft_draw_column(game, column, &ray, &drawer);
		ft_update_minimap(game, &ray);
		if (game->map.show_mega)
			ft_update_megamap(game, &ray);
    }
	// draw_frame(game);
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
	if (game->map.show_mega)
		ft_render_megamap(game);
	ft_sprintf(txt, "Pos: x%.2f/y%.2f | Dir x%.2f/y%.2f | Plane x%.2f/y%.2f | Angle %.2f",
		game->player.pos.x, game->player.pos.y,
		game->player.dir.x, game->player.dir.y,
		game->player.plane.x, game->player.plane.y,
		game->player.angle);
	mlx_string_put(game->mlx, game->win.ref, 10, game->win.height - 20, 0xffffff, txt);
}

