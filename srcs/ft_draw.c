/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/30 21:54:13 by adda-sil         ###   ########.fr       */
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

t_object	*ft_newobject(t_game *game, t_ray *ray, t_ipos pos)
{
	t_object *obj;

    if (!(obj = malloc(sizeof(t_object))))
        return (NULL);
    obj->pos.x = pos.x;
    obj->pos.y = pos.y;
    obj->dist = (ray->vert ? ray->dist.y : ray->dist.x);
    obj->angle = asin(((obj->pos.x - game->player.pos.x) * game->player.plane.y * -1 +
                        (obj->pos.y - game->player.pos.y) * game->player.plane.x) / obj->dist);
    obj->dir = 0.5 + obj->dist * tan(obj->angle);
	return (obj);
}

int	ft_add_object(t_game *game, t_ray *ray, t_ipos pos)
{
	// if (game->map.sprites[pos.x][pos.y] == 1)
	// 	return (1);
	// printf("Adding obj");
	// game->map.sprites[pos.x][pos.y] = 1;
	ft_lstadd_front(&(ray->objects), ft_lstnew(ft_newobject(game, ray, pos), sizeof(t_object *)));
	return (1);
}

void    compute_ray(t_game *game, t_ray *ray)
{
    int    i;
	t_ipos pos;
    i = -1;
    while (++i < 100)
    {
		pos.y = (int)ray->pos.y;
		pos.x = (int)ray->pos.x;
        if (ray->dist.x < ray->dist.y)
        {
            ray->vert = 0;
            ray->pos.x += ray->step.x;
			pos.x = (int)ray->pos.x;
            if (game->map.grid[pos.y][pos.x] != WALL)
                ray->dist.x += ray->step_dist.x;
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
        }
        else
        {
            ray->vert = 1;
            ray->pos.y += ray->step.y;
			pos.y = (int)ray->pos.y;
            if (game->map.grid[pos.y][pos.x] != WALL)
                ray->dist.y += ray->step_dist.y;
			if (game->map.show_mega)
				ft_update_megamap(game, ray);
        }
        if (game->map.grid[pos.y][pos.x] == OBJECT)
			ft_add_object(game, ray, pos);
        if (game->map.grid[pos.y][pos.x] == WALL)
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

	// printf("drawing obj");
    height = game->win.height / obj->dist;
    drawer->start = game->win.height / 2 - height / 2;
    drawer->start = fmax(drawer->start, 0);
    drawer->end = game->win.height / 2 + height / 2;
    drawer->end = fmin(drawer->end, game->win.height - 1);
    drawer->step_posy = 1 / ((double)(drawer->end - drawer->start));
    draw.y = drawer->start;
	draw.x = column;
    posy = 0;
    while (++draw.y < drawer->end)
    {
		draw_tex.x = (int)(obj->dir);
		draw_tex.y = (int)(posy);
		ft_transfert_pixel(&(game->env.S.img), draw_tex, &(game->win.renderer), draw);
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
    drawer->start = delta <= 0 ? (game->win.height / 2 - height / 2) : 0;
    drawer->end = delta <= 0 ? (game->win.height / 2 + height / 2) : game->win.height;
	drawer->step_posy = 1 / (delta <= 0 ?
		((double)(drawer->end - drawer->start)) : height);
    draw.y = 0;
	if (delta <= 0)
		while (draw.y < drawer->start)
			ft_set_pixel(&(game->win.renderer), draw, game->env.CEIL) && draw.y++;
	posy = delta > 0 ? (drawer->step_posy * (delta / 2)) : 0;
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
    	while (draw.y < game->win.height)
			ft_set_pixel(&(game->win.renderer), draw, game->env.FLOOR) && draw.y++;
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
        //printf("");
        compute_ray(game, &ray);
        ray.draw_dist = (ray.vert ? ray.dist.y : ray.dist.x);
        ray.po = decimal_part((ray.vert ? game->player.pos.x + ray.draw_dist * game->player.plane.x :
            game->player.pos.y + ray.draw_dist * game->player.plane.y));
   		if (ray.vert)
            drawer.texture = (game->player.pos.y < ray.pos.y ? &(game->env.SO) : &(game->env.NO));
        else
            drawer.texture = (game->player.pos.x < ray.pos.x ? &(game->env.EA) : &(game->env.WE));
		game->zbuffer[column] = ray.draw_dist;
		ft_draw_column(game, column, &ray, &drawer);
		ft_update_minimap(game, &ray);
		ft_draw_objects(game, column, &ray, &drawer);
		if (game->map.show_mega)
			ft_update_megamap(game, &ray);
        column++;
    }
}
