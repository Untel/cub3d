/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 01:25:55 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 21:19:56 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	init_ray(t_game *game, t_ray *ray)
{
    ray->pos.x = (int)game->player.pos.x;
    ray->pos.y = (int)game->player.pos.y;
    ray->step.x = (game->player.plane.x > 0 ? 1 : -1);
    ray->step.y = (game->player.plane.y > 0 ? 1 : -1);
    ray->step_dist.x = sqrt(1 + pow(game->player.plane.y, 2) / pow(game->player.plane.x, 2));
    ray->step_dist.y = sqrt(1 + pow(game->player.plane.x, 2) / pow(game->player.plane.y, 2));
    ray->dist.x = ray->step_dist.x *
        (game->player.plane.x >= 0 ? 1. - (game->player.pos.x - ray->pos.x) :
        (game->player.pos.x - ray->pos.x));
    ray->dist.y = ray->step_dist.y *
        (game->player.plane.y >= 0 ? 1. - (game->player.pos.y - ray->pos.y) :
        (game->player.pos.y - ray->pos.y));
    ray->vert = (ray->dist.x >= ray->dist.y);
	ray->objects = NULL;
}

void
	compute_ray(t_game *game, t_ray *ray)
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
