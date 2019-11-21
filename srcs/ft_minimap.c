/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:45:11 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/21 22:17:58 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define MINIMAP_WALL_SIZE 10

int	ft_draw_minimap_square(t_game *game, int x, int y, int color)
{
	int	add_x;
	int	add_y;

	add_x = -1;
	while (++add_x < MINIMAP_WALL_SIZE && (add_y = -1))
		while (++add_y < MINIMAP_WALL_SIZE)
			ft_set_pixel(&(game->map.mini), x * MINIMAP_WALL_SIZE + add_x, y * MINIMAP_WALL_SIZE + add_y, color);
}

int	ft_draw_minimap(t_game *game)
{
	int x;
	int y;

	x = -1;
	while (++x <= game->map.width && (y = -1))
		while (++y <= game->map.height)
			if (game->map.grid[y][x] == WALL)
				ft_draw_minimap_square(game, x, y, 0xffffff);
			else if (game->map.grid[y][x] == OBJECT)
				ft_draw_minimap_square(game, x, y, 0x00ffff);
			else
				ft_draw_minimap_square(game, x, y, 0x000000);
	ft_draw_minimap_square(game, (int)game->player.pos.y, (int)game->player.pos.x, 0xff00ff);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
}

int	ft_generate_minimap(t_game *game)
{

	printf("Map w/h is %d/%d\n\n", game->map.width, game->map.height);
	if (ft_generate_image(game, &(game->map.mini), (game->map.width + 1) * MINIMAP_WALL_SIZE, (game->map.height + 1) * MINIMAP_WALL_SIZE) == ERROR)
		return (ERROR);
	return (SUCCESS);
}