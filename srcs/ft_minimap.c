/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:45:11 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 19:43:11 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MINIMAP_SQUARE_SIZE 6

void
	ft_update_minimap(t_game *game, t_ray *ray)
{
	int		color;
	t_ipos	pos;

	if (ray->vert)
		color = ray->pos.y > game->p.pos.y ? 0xff0000 : 0x00ff00;
	else
		color = ray->pos.x > game->p.pos.x ? 0xffff00 : 0x00ffff;
	pos.x = (int)ray->pos.x;
	pos.y = (int)ray->pos.y;
	ft_draw_minimap_square(game, pos, color);
}

void
	ft_draw_minimap_square(t_game *game, t_ipos pos, unsigned int color)
{
	t_ipos add;
	t_ipos to_draw;

	add.x = -1;
	while (++add.x < MINIMAP_SQUARE_SIZE && (add.y = -1))
		while (++add.y < MINIMAP_SQUARE_SIZE)
		{
			to_draw.x = pos.x * MINIMAP_SQUARE_SIZE + add.x;
			to_draw.y = pos.y * MINIMAP_SQUARE_SIZE + add.y;
			ft_set_pixel(&(game->map.mini), to_draw, color);
		}
}

void
	ft_draw_minimap(t_game *game)
{
	t_ipos pos;

	pos.x = -1;
	while (++pos.x <= game->map.width && (pos.y = -1))
		while (++pos.y <= game->map.height)
			if (game->map.grid[pos.y][pos.x] == WALL)
				ft_draw_minimap_square(game, pos, 0xbbffffff);
			else if (game->map.grid[pos.y][pos.x] == OBJECT)
				ft_draw_minimap_square(game, pos, 0xbb00ffff);
			else
				ft_draw_minimap_square(game, pos, 0xff000000);
	pos.x = (int)game->p.pos.x;
	pos.y = (int)game->p.pos.y;
	ft_draw_minimap_square(game, pos, 0xff00ff);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
}

int
	ft_generate_minimap(t_game *game)
{
	if (ft_generate_image(game, &(game->map.mini), (game->map.width + 1)
		* MINIMAP_SQUARE_SIZE, (game->map.height + 1)
		* MINIMAP_SQUARE_SIZE) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
