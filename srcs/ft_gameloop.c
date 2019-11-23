/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:47:25 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/23 18:48:47 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_ray(t_game *game, t_ray *ray)
{
    ray->x = (int)game->player.pos.x;
    ray->y = (int)game->player.pos.y;
    ray->stepx = (game->player.dir.x <= 0 ? 1 : -1);
    ray->stepy = (game->player.dir.y <= 0 ? 1 : -1);
    ray->step_distx = sqrt(1 + (game->player.dir.y * game->player.dir.y) / (game->player.dir.x * game->player.dir.x));
    ray->step_disty = sqrt(1 + (game->player.dir.x * game->player.dir.x) / (game->player.dir.y * game->player.dir.y));
    ray->distx = ray->step_distx *
        (game->player.dir.x >= 0 ? 1. - (game->player.pos.x - (double)ray->x) :
        (game->player.pos.x - (double)ray->x));
    ray->disty = ray->step_disty *
        (game->player.dir.y >= 0 ? 1. - (game->player.pos.y - (double)ray->y) :
        (game->player.pos.y - (double)ray->y));
    ray->vert = (ray->distx >= ray->disty);
}

void    compute_ray(t_game *game, t_ray *ray)
{
    int    i;

    i = -1;
    while (++i < 100)
    {
        if (ray->distx < ray->disty)
        {
            ray->vert = 0;
            ray->x += ray->stepx;
            if (game->map.grid[ray->y][ray->x] != WALL)
                ray->distx += ray->step_distx;
        }
        else
        {
            ray->vert = 1;
            ray->y += ray->stepy;
            if (game->map.grid[ray->y][ray->x] != WALL)
                ray->disty += ray->step_disty;
        }
        if (game->map.grid[ray->y][ray->x] == WALL)
            break ;
    }
}

double	decimal_part(double val)
{
	return ((int)val - val);
}

int	ft_update_minimap(t_game *game, t_ray *ray)
{
	int color;
	if (ray->vert)
		color = ray->y > (int)game->player.pos.x ? 0x00ff00 : 0x0000ff;
	else
		color = ray->x > (int)game->player.pos.y ? 0xeba434 : 0x7d34eb;
	ft_draw_minimap_square(game, ray->x, ray->y, color);
}

int	ft_game_loop(t_game *game)
{
	char		txt[300];
    int			column;
    t_ray		ray;
    // t_drawer	drawer;

    column = -1;
	ft_read_events(game);
	ft_draw_minimap(game);
    while (++column < game->win.width)
    {
        game->player.dir.x = game->player.plane.x * game->map.table_cos[column] - game->player.plane.y * game->map.table_sin[column];
        game->player.dir.y = game->player.plane.y * game->map.table_cos[column] + game->player.plane.x * game->map.table_sin[column];
        init_ray(game, &ray);
        compute_ray(game, &ray);
        ray.dist = (ray.vert ? ray.disty : ray.distx);
        ray.po = decimal_part((ray.vert ? game->player.pos.x + ray.dist * game->player.dir.x :
                                game->player.pos.y + ray.dist * game->player.dir.y));
		ft_update_minimap(game, &ray);
    }
	draw_frame(game);
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
	ft_sprintf(txt, "Pos: x%.2f/y%.2f | Dir x%.2f/y%.2f | Plane x%.2f/y%.2f",
		game->player.pos.x, game->player.pos.y,
		game->player.dir.x, game->player.dir.y,
		game->player.plane.x, game->player.plane.y);
	mlx_string_put(game->mlx, game->win.ref, 10, game->win.height - 20, 0xffffff, txt);
}