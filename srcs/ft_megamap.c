/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_megamap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:20:35 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/24 21:16:02 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MEGAMAP_SQUARE_SIZE 64

int	ft_draw_megamap_square(t_game *game, t_ipos pos, t_image tex)
{
	t_ipos pix;
	t_ipos to_draw;

	pix.x = -1;
	while (++pix.x < MEGAMAP_SQUARE_SIZE && (pos.y = -1))
		while (++pix.y < MEGAMAP_SQUARE_SIZE)
		{
			to_draw.x = pos.x * MEGAMAP_SQUARE_SIZE + pix.x;
			to_draw.y = pos.y * MEGAMAP_SQUARE_SIZE + pix.y;
			ft_set_pixel(&(game->map.mega), to_draw, ft_get_pixel(&tex, pix));
		}
}

int	ft_draw_megamap(t_game *game)
{
	t_ipos pos;

	pos.x = -1;
	while (++pos.x <= game->map.width && (pos.y = -1))
		while (++pos.y <= game->map.height)
			if (game->map.grid[pos.y][pos.x] == WALL)
				ft_draw_megamap_square(game, pos, game->env.NO);
			else if (game->map.grid[pos.y][pos.x] == OBJECT)
				ft_draw_megamap_square(game, pos, game->env.WE);
			else
				ft_draw_megamap_square(game, pos, game->env.EA);
	// ft_printf("Player pos is %.2f/%.2f\n", game->player.pos.x, game->player.pos.y);
	to_intpos(&pos, game->player.pos);
	ft_draw_megamap_square(game, pos, game->env.SO);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mega.ref, 0, 0);
}

int	ft_update_megamap(t_game *game, t_ray *ray)
{
	int 		color;
	t_ipos	pos;

	if (ray->vert)
		color = ray->pos.y > game->player.pos.x ? 0x00ff00 : 0x0000ff;
	else
		color = ray->pos.x > game->player.pos.y ? 0xeba434 : 0x7d34eb;
	pos.x = (int)ray->pos.x;
	pos.y = (int)ray->pos.y;
	// ft_draw_megamap_square(game, pos, color);
}

int	ft_generate_megamap(t_game *game)
{
	printf("Map w/h is %d/%d\n\n", game->map.width, game->map.height);
	if (ft_generate_image(game, &(game->map.mega), (game->map.width + 1) * MEGAMAP_SQUARE_SIZE, (game->map.height + 1) * MEGAMAP_SQUARE_SIZE) == ERROR)
		return (ERROR);
	return (SUCCESS);
}