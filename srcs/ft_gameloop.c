/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:47:25 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/24 21:51:00 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_game *game, t_ray *ray)
{
    ray->pos.x = game->player.pos.x;
    ray->pos.y = game->player.pos.y;
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

    i = -1;
    while (++i < 100)
    {
        if (ray->dist.x < ray->dist.y)
        {
            ray->vert = 0;
            ray->pos.x += ray->step.x;
            if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] != WALL)
                ray->dist.x += ray->step_dist.x;
        }
        else
        {
            ray->vert = 1;
            ray->pos.y += ray->step.y;
            if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] != WALL)
                ray->dist.y += ray->step_dist.y;
        }
        if (game->map.grid[(int)ray->pos.y][(int)ray->pos.x] == WALL)
            break ;
    }
}

double	decimal_part(double val)
{
	return ((int)val - val);
}

int	ft_game_loop(t_game *game)
{
	char		txt[300];
    int			column;
	double		dist;
    t_ray		ray;
    // t_drawer	drawer;

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
        dist = (ray.vert ? ray.dist.y : ray.dist.x);
        ray.po = decimal_part((ray.vert ? game->player.pos.x + dist * game->player.dir.x :
            game->player.pos.y + dist * game->player.dir.y));
		ft_update_minimap(game, &ray);
		if (game->map.show_mega)
			ft_update_megamap(game, &ray);
    }
	// draw_frame(game);
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
	if (game->map.show_mega)
		ft_render_megamap(game);
	ft_sprintf(txt, "Pos: x%.2f/y%.2f | Dir x%.2f/y%.2f | Plane x%.2f/y%.2f",
		game->player.pos.x, game->player.pos.y,
		game->player.dir.x, game->player.dir.y,
		game->player.plane.x, game->player.plane.y);
	mlx_string_put(game->mlx, game->win.ref, 10, game->win.height - 20, 0xffffff, txt);
}