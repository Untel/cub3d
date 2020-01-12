/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_megamap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:20:35 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 18:04:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MEGAMAP_SQUARE_SIZE 32

int	ft_update_megamap(t_game *game, t_ray *ray)
{
	int 	color;
	t_ipos	pos;
	color = 0xffffff;
	pos.x = (int)(ray->pos.x * MEGAMAP_SQUARE_SIZE);
	pos.y = (int)(ray->pos.y * MEGAMAP_SQUARE_SIZE);
	ft_set_pixel(&(game->map.mega), pos, color);
}

int	ft_draw_megamap_square(t_game *game, t_dpos pos, t_image *tex, unsigned int color)
{
	t_ipos	pix;
	t_ipos	to_draw;
	// int		color;

	pix.x = -1;
	while (++pix.x < MEGAMAP_SQUARE_SIZE && (pix.y = -1))
		while (++pix.y < MEGAMAP_SQUARE_SIZE)
		{
			to_draw.x = pos.x * MEGAMAP_SQUARE_SIZE + pix.x;										
			to_draw.y = pos.y * MEGAMAP_SQUARE_SIZE + pix.y;
			if (tex)
			{
				tex->draw = to_draw;
				game->map.mega.draw = to_draw;
				ft_transfert_pixel(tex, &(game->map.mega), 0);
			}
			else
				ft_set_pixel(&(game->map.mega), to_draw, color);
			// color = ft_get_pixel(&tex, pix);
			// // printf("drawing %d at %d %d", color, pix.x, pix.y);
		}
}

int	ft_draw_megamap_pix(t_game *game, t_dpos pos, unsigned int color)
{
	t_ipos	pix;
	t_ipos	to_draw;

	to_draw.x = (int)(pos.x * MEGAMAP_SQUARE_SIZE);
	to_draw.y = (int)(pos.y * MEGAMAP_SQUARE_SIZE);
	ft_set_pixel(&(game->map.mega), to_draw, color);
}

int	ft_draw_megamap(t_game *game)
{
	t_dpos pos;

	pos.x = -1;
	while (++pos.x <= game->map.width && (pos.y = -1))
		while (++pos.y <= game->map.height)
			if (game->map.grid[(int)pos.y][(int)pos.x] == WALL)
				ft_draw_megamap_square(game, pos, &(game->env.NO), 0);
			else if ((int)game->map.grid[(int)pos.y][(int)pos.x] == OBJECT)
				ft_draw_megamap_square(game, pos, NULL, 0x8fffff00);
			else
				ft_draw_megamap_square(game, pos, NULL, 0xad000000);
	pos.x = game->player.pos.x - .5;
	pos.y = game->player.pos.y - .5;
	ft_draw_megamap_square(game, pos, NULL, 0x8fff0000);
}

int	ft_render_megamap(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mega.ref, 0, 0);
}

int	ft_generate_megamap(t_game *game)
{
	if (ft_generate_image(game, &(game->map.mega), (game->map.width + 1) * MEGAMAP_SQUARE_SIZE, (game->map.height + 1) * MEGAMAP_SQUARE_SIZE) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
