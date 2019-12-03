/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_objects.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:34:03 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/03 17:54:41 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	t_dpos	draw_tex;
	unsigned int color;
	int		delta;

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
		// printf("show sprite\n\n");
		ft_draw_sprite(game, &game->env.S, draw_tex, game->shading ? obj->dist / 2 : 0);
		// color = ft_get_pixel(&(game->env.S.img), draw_tex);
		// if (color > 0)
		// 	ft_set_pixel(&(game->win.renderer), draw, color & 0x00FFFFFF);
		// ft_transfert_pixel(&(game->env.S.img), draw_tex,
		// 	&(game->win.renderer), draw);
        drawer->posy += drawer->step_posy;
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