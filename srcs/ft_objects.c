/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:34:03 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 21:45:23 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_object
	*ft_newobject(t_game *game, t_ray *ray)
{
	t_object *obj;

	if (!(obj = malloc(sizeof(t_object))))
		return (NULL);
	obj->pos.x = (int)ray->pos.x + .5;
	obj->pos.y = (int)ray->pos.y + .5;
	obj->dist = sqrt(pow((game->p.pos.y - obj->pos.y), 2)
		+ pow(game->p.pos.x - obj->pos.x, 2));
	obj->angle = asin(((obj->pos.x - game->p.pos.x) * game->p.plane.y * -1 +
		(obj->pos.y - game->p.pos.y) * game->p.plane.x) / obj->dist);
	obj->dir = .5 + obj->dist * tan(obj->angle);
	return (obj);
}

void
	ft_clear_object(t_list *el)
{
	if (el->content)
		free(el->content);
}

void
	ft_draw_object(t_game *game, int column, t_object *obj, t_drawer *drawer)
{
	double	height;
	t_ipos	draw;
	t_dpos	draw_tex;

	if (obj->dir <= 0 || obj->dir >= 1)
		return ;
	height = game->win.height / obj->dist;
	ft_init_drawer(game, drawer, height);
	draw.y = drawer->start;
	draw.x = column;
	while (++draw.y < drawer->end)
	{
		draw_tex.x = (obj->dir);
		draw_tex.y = (drawer->posy);
		game->win.renderer.draw = draw;
		ft_draw_sprite(game, &game->env.s, draw_tex,
			game->shading ? obj->dist / 2 : 0);
		drawer->posy += drawer->step_posy;
	}
}

void
	ft_draw_objects(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
	t_list	*el;

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
