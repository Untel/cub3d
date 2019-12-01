/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 04:56:39 by adda-sil         ###   ########.fr       */
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

t_object	*ft_newobject(t_game *game, t_ray *ray)
{
	t_object *obj;

    if (!(obj = malloc(sizeof(t_object))))
        return (NULL);
    obj->pos.x = (int)ray->pos.x + .5;
    obj->pos.y = (int)ray->pos.y + .5;
	obj->dist = sqrt(pow((game->player.pos.y - obj->pos.y), 2) + pow(game->player.pos.x - obj->pos.x, 2));
    obj->angle = asin(((obj->pos.x - game->player.pos.x) * game->player.plane.y * -1 +
                        (obj->pos.y - game->player.pos.y) * game->player.plane.x) / obj->dist);
    obj->dir = .5 + obj->dist * tan(obj->angle);
	return (obj);
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

void	ft_clear_object(t_list *el)
{
	if (el->content)
		free(el->content);
}

void    ft_draw_object(t_game *game, int column, t_object *obj, t_drawer *drawer)
{
    double	posy;
    double	height;
	t_ipos	draw;
	t_ipos	draw_tex;
	unsigned int color;
	int		delta;

    if (obj->dir <= 0 || obj->dir >= 1)
        return ;
    height = game->win.height / obj->dist;
	delta =	height - game->win.height;

    drawer->start = delta <= 0 ? (double)game->win.height / game->player.view - height / game->player.view : 0;
    drawer->end = delta <= 0 ? (double)game->win.height / game->player.view + height / game->player.view : game->win.height;
    drawer->step_posy = 1 / (delta <= 0 ? (double)(drawer->end - drawer->start) : height);
    draw.y = drawer->start;
	draw.x = column;
	posy = delta > 0 ? (drawer->step_posy * (delta / game->player.view)) : 0;
    while (++draw.y < drawer->end)
    {
		draw_tex.x = (obj->dir * game->env.S.img.width);
		draw_tex.y = (posy * game->env.S.img.height);
		color = ft_get_pixel(&(game->env.S.img), draw_tex);
		if (color > 0)
			ft_set_pixel(&(game->win.renderer), draw, color & 0x00FFFFFF);
		// ft_transfert_pixel(&(game->env.S.img), draw_tex,
		// 	&(game->win.renderer), draw);
        posy += drawer->step_posy;
    }
}

void    ft_draw_objects(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
	t_list *el;

	if (!ray->objects)
		return ;
	el = ray->objects;
	while (el)
	{
		ft_draw_object(game, column, (t_object *)el->content, drawer);
		el = el->next;
	}
	ft_lstclear(&(ray->objects), ft_clear_object);
}

void	ft_draw_floor(t_game *game, t_ray *ray, t_ipos *draw)
{
	t_dpos floorpos;

	if(!ray->vert && ray->dir.x > 0)
	{
        floorpos.x = (int)game->player.pos.x;
        floorpos.y = (int)game->player.pos.y + ray->dist.y;
	}
	else if(!ray->vert && ray->dir.x < 0)
	{
		floorpos.x = (int)game->player.pos.x + 1.0;
        floorpos.y = (int)game->player.pos.y + ray->dist.y;
	}
	else if(ray->vert && ray->dir.y > 0)
	{
        floorpos.x = (int)game->player.pos.x + ray->dist.x;
        floorpos.y = (int)game->player.pos.y;
	}
	else
	{
        floorpos.x = (int)game->player.pos.x + ray->dist.x;
        floorpos.y = (int)game->player.pos.y + 1;
	}

	double distWall, distPlayer, currentDist;

	distWall = ray->draw_dist;
	distPlayer = 0.0;

	//draw the floor from drawEnd to the bottom of the screen
	t_image *tex = &(game->env.EA);
	double weight;
	t_dpos ratio;
	t_ipos draw_tex;
	// printf("hey %d|%d\n", draw->y, draw->y < game->map.height);
	while(draw->y < game->win.height)
	{
		// printf("hey %d\n", draw->y);
		currentDist = game->win.height / (2.0 * draw->y - game->map.height); //you could make a small lookup table for this instead
		weight = (currentDist - distPlayer) / (distWall - distPlayer);

		ratio.x = weight * floorpos.x + (1.0 - weight) * game->player.pos.x;
		ratio.y = weight * floorpos.y + (1.0 - weight) * game->player.pos.y;
		draw_tex.x = (int)(ratio.x * tex->width) % tex->width;
		draw_tex.y = (int)(ratio.y * tex->height) % tex->height;

		//floor
		// unsigned int color = ft_get_pixel(tex, draw_tex);
		// ft_set_pixel(&(game->win.renderer), *draw, color & 0x00FFFFFF);
		ft_transfert_pixel(tex, draw_tex, &(game->win.renderer), *draw);
		// buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
		//ceiling (symmetrical!)
		// buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
		draw->y++;
	}
}

void    ft_draw_column(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
    double		posy;
    double		height;
	t_ipos		draw;
	t_ipos		draw_tex;
	int			delta;

	draw.x = column;
    height = game->win.height / ray->draw_dist / game->win.cos[column];
	delta =	height - game->win.height;
    drawer->start = delta <= 0 ? (game->win.height / game->player.view - height / game->player.view) : 0;
    drawer->end = delta <= 0 ? (game->win.height / game->player.view + height / game->player.view) : game->win.height;
	drawer->step_posy = 1 / (delta <= 0 ?
		((double)(drawer->end - drawer->start)) : height);
    draw.y = 0;
	if (delta <= 0)
		while (draw.y < drawer->start)
			ft_set_pixel(&(game->win.renderer), draw, game->env.CEIL) && draw.y++;
	posy = delta > 0 ? (drawer->step_posy * (delta / game->player.view)) : 0;
    while (draw.y < drawer->end)
    {
		draw_tex.x = (int)(ray->po * drawer->texture->height);
		draw_tex.y = (int)(posy * drawer->texture->width);
		ft_transfert_pixel(drawer->texture, draw_tex, &(game->win.renderer), draw);
		// ft_set_pixel(&(game->win.renderer), draw, 
		// 	ft_get_pixel(drawer->texture, draw_tex));
        posy += drawer->step_posy;
		draw.y++;
    }
	if (delta <= 0)
		// ft_draw_floor(game, ray, &draw);
    	while (draw.y < game->win.height)
			ft_set_pixel(&(game->win.renderer), draw, game->env.FLOOR) && draw.y++;
}

#define CH_RADIAN 10
#define CH_COLOR 0xcf00ff00
#define CH_SIZE 2
int	ft_draw_crosshair(t_game *game)
{
	t_ipos pos;
	int i;

	i = -1;
	pos.x = game->win.width / 2 - CH_RADIAN;
	pos.y = game->win.height / 2;
	while (pos.x++ < game->win.width / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
	pos.x = game->win.width / 2;
	pos.y = game->win.height / 2 - CH_RADIAN;	
	while (pos.y++ < game->win.height / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
}

int	ft_draw_frame(t_game *game)
{
	int			column;
    t_ray		ray;
    t_drawer	drawer;

    column = 0;
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
	ft_draw_crosshair(game);
	ft_hud(game);
}
