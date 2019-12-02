/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/02 20:09:30 by adda-sil         ###   ########.fr       */
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
	ray->objects = NULL;
}

void    compute_ray(t_game *game, t_ray *ray)
{
    int    i;

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
        if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] == OBJECT)
			ft_lstadd_front(&(ray->objects), ft_lstnew(
				ft_newobject(game, ray), sizeof(t_object *)));
        if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] == WALL)
		{
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
            break ;
		}
    }
}

double	decim(double val)
{
	return (val - (int)val);
}

void	ft_floor_cast(t_game *game, t_ray *ray, t_ipos draw)
{
	if (ray->vert == 0 && ray->dir.x > 0)
		ray->floor = (t_dpos){ ray->pos.x, ray->pos.y + ray->draw_dist };
	else if (ray->vert == 0 && ray->dir.x < 0)
		ray->floor = (t_dpos){ ray->pos.x + 1., ray->pos.y + ray->draw_dist };
	else if (ray->vert && ray->dir.y > 0)
		ray->floor = (t_dpos){ ray->pos.x + ray->draw_dist, ray->pos.y};
	else if (ray->vert && ray->dir.y < 0)
		ray->floor = (t_dpos){ ray->pos.x + ray->draw_dist, ray->pos.y + 1.};
}

void	ft_draw_floor(t_game *game, t_ray *ray, t_ipos draw)
{
	t_dpos floorpos;
	double distWall, distPlayer, currentDist;

	ft_floor_cast(game, ray, draw);
	distWall = sqrt(pow((ray->pos.y), 2) + pow(ray->pos.x, 2));
	distPlayer = 0.0;
	//draw the floor from drawEnd to the bottom of the screen
	t_image *tex = &(game->env.EA);
	double weight;
	t_dpos ratio;
	t_ipos draw_tex;
	// printf("hey %d|%d\n", draw->y, draw->y < game->map.height);
	while(draw.y < game->win.height)
	{
		// printf("hey %d\n", draw->y);
		currentDist = game->win.height / (2.0 * draw.y - game->map.height);
		weight = (currentDist - distPlayer) / (distWall - distPlayer);

		ratio.x = weight * ray->floor.x + (1.0 - weight) * game->player.pos.x;
		ratio.y = weight * ray->floor.y + (1.0 - weight) * game->player.pos.y;
		draw_tex.x = (int)(ratio.x * tex->width) % tex->width;
		draw_tex.y = (int)(ratio.y * tex->height) % tex->height;
		// draw_tex.x = (int)(ray->floor.x * tex->width);
		// if (ray->vert == 0 && ray->dir.x > 0.)
		// 	draw_tex.x = tex->width - draw_tex.x - 1.;
		// else if (ray->vert == 1 && ray->dir.y < 0.)
		// 	draw_tex.x = tex->width - draw_tex.x - 1.;

		//floor
		// unsigned int color = ft_get_pixel(tex, draw_tex);
		// ft_set_pixel(&(game->win.renderer), *draw, color & 0x00FFFFFF);
		ft_transfert_pixel(tex, draw_tex, &(game->win.renderer), draw);
		// draw->y = game->win.height - draw->y;
		// ft_transfert_pixel(tex, draw_tex, &(game->win.renderer), *draw);
		// buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
		//ceiling (symmetrical!)
		// buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
		draw.y++;
	}
}

int	ft_init_drawer(t_game *game, t_drawer *drawer, double height)
{
	int			delta;
	
	drawer->delta =	(height - fabs(game->player.view + game->player.view2)) - game->win.height;
	if (game->player.view + game->player.view2 > 0)
		drawer->delta -= game->player.view + game->player.view2;
	else if (game->player.view + game->player.view2 < 0)
		drawer->delta += game->player.view + game->player.view2;
	drawer->step_posy = 1 / height;
	drawer->start = (game->win.height / 2 - height / 2) - game->player.view - game->player.view2;
	drawer->end = (game->win.height / 2 + height / 2) - game->player.view - game->player.view2;
	drawer->posy = 0;
	if (drawer->delta > 0)
	{
		drawer->start += delta / 2;
		drawer->end -= delta / 2;
		drawer->posy += (drawer->step_posy * (delta / 2));
	}
	if (drawer->start < 0)
	{
		drawer->posy += (-drawer->start * drawer->step_posy);
		drawer->start = 0;
	}
	if (drawer->start > game->win.height)
		drawer->start = game->win.height;
	if (drawer->end < 0)
		drawer->end = 0;
	if (drawer->end > game->win.height)
		drawer->end = game->win.height;
	// if (column == 0 || column == 800 || column == 750)
	// 	printf("%d == Sky = %dpx Wall %dpx Floor %dpx\n", column, drawer->start, drawer->end - drawer->start, game->win.height - drawer->end);
	return (drawer->delta);
}

void    ft_draw_column(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
    double		posy;
	t_ipos		draw;
	t_ipos		draw_tex;
	int			delta;

	draw.x = column;
	draw.y = 0;
	delta = ft_init_drawer(game, drawer, (game->win.height / ray->draw_dist / game->win.cos[column]));
	while (draw.y < drawer->start)
		ft_set_pixel(&(game->win.renderer), draw, game->env.CEIL) && draw.y++;
    while (draw.y < drawer->end)
    {
		draw_tex.x = (int)(ray->po * drawer->texture->height);
		draw_tex.y = (int)(drawer->posy * drawer->texture->width);
		ft_transfert_pixel(drawer->texture, draw_tex, &(game->win.renderer), draw);
		// ft_set_pixel(&(game->win.renderer), draw, 
		// 	ft_get_pixel(drawer->texture, draw_tex));
        drawer->posy += drawer->step_posy;
		draw.y++;
    }
	while (draw.y < game->win.height)
		ft_set_pixel(&(game->win.renderer), draw, game->env.FLOOR) && draw.y++;
}

int	ft_draw_frame(t_game *game)
{
	int			column;
    t_ray		ray;
    t_drawer	drawer;

    column = 0;
	if (game->hud)
		ft_draw_minimap(game);
	while (column < game->win.width)
    {
		game->player.plane.x = game->player.dir.x * game->win.cos[column] - game->player.dir.y * game->win.sin[column];
		game->player.plane.y = game->player.dir.y * game->win.cos[column] + game->player.dir.x * game->win.sin[column];
        init_ray(game, &ray);
        compute_ray(game, &ray);
        ray.draw_dist = (ray.vert ? ray.dist.y : ray.dist.x);
        ray.po = decim((ray.vert ? game->player.pos.x + ray.draw_dist * game->player.plane.x :
            game->player.pos.y + ray.draw_dist * game->player.plane.y));
   		if (ray.vert)
            drawer.texture = (game->player.pos.y < ray.pos.y ? &(game->env.SO) : &(game->env.NO));
        else
            drawer.texture = (game->player.pos.x < ray.pos.x ? &(game->env.EA) : &(game->env.WE));
		ft_draw_column(game, column, &ray, &drawer);
		ft_update_minimap(game, &ray);
		ft_draw_objects(game, column, &ray, &drawer);
		if (game->map.show_mega)
			ft_update_megamap(game, &ray);
        column++;
    }
	ft_hud(game);
}
