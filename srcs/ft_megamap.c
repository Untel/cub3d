/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_megamap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 18:20:35 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/26 15:58:51 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define MEGAMAP_SQUARE_SIZE 32

int	ft_update_megamap(t_game *game, t_ray *ray)
{
	int 	color;
	t_ipos	pos;

	if (ray->vert)
		color = ray->pos.y > game->player.pos.x ? 0x00ff00 : 0x0000ff;
	else
		color = ray->pos.x > game->player.pos.y ? 0xeba434 : 0x7d34eb;

	// pos.x = (ray->vert ? (int)ceil(ray->pos.x) : (int)floor(ray->pos.x));
	// pos.y = (ray->vert ? (int)ceil(ray->pos.y) : (int)floor(ray->pos.y));
	pos.x = (int)(ray->pos.x * MEGAMAP_SQUARE_SIZE);
	pos.y = (int)(ray->pos.y * MEGAMAP_SQUARE_SIZE);
	// pos.x += (int)((ray->pos.x - floor(ray->pos.x)) * MEGAMAP_SQUARE_SIZE);
	// pos.y += (int)((ray->pos.y - floot(ray->pos.x)) * MEGAMAP_SQUARE_SIZE);
	ft_set_pixel(&(game->map.mega), pos, color);
	// ft_draw_megamap_pix(game, ray->pos, color);
}

int	ft_draw_megamap_square(t_game *game, t_ipos pos, t_image tex)
{
	t_ipos	pix;
	t_ipos	to_draw;
	int		color;

	pix.x = -1;
	while (++pix.x < MEGAMAP_SQUARE_SIZE && (pix.y = -1))
		while (++pix.y < MEGAMAP_SQUARE_SIZE)
		{
			to_draw.x = pos.x * MEGAMAP_SQUARE_SIZE + pix.x;										
			to_draw.y = pos.y * MEGAMAP_SQUARE_SIZE + pix.y;
			color = ft_get_pixel(&tex, pix);
			// printf("drawing %d at %d %d", color, pix.x, pix.y);
			ft_set_pixel(&(game->map.mega), to_draw, color);
		}
}

int	ft_draw_megamap_pix(t_game *game, t_dpos pos, int color)
{
	t_ipos	pix;
	t_ipos	to_draw;

	to_draw.x = (int)(pos.x * MEGAMAP_SQUARE_SIZE);
	to_draw.y = (int)(pos.y * MEGAMAP_SQUARE_SIZE);
	ft_set_pixel(&(game->map.mega), to_draw, color);
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
				ft_draw_megamap_square(game, pos, game->env.SO);
	// ft_printf("Player pos is %.2f/%.2f\n", game->player.pos.x, game->player.pos.y);
	to_intpos(&pos, game->player.pos);
	ft_draw_megamap_square(game, pos, game->env.EA);
}

int	ft_render_megamap(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mega.ref, 0, 0);
}

int	ft_generate_megamap(t_game *game)
{
	printf("Map w/h is %d/%d\n\n", game->map.width, game->map.height);
	if (ft_generate_image(game, &(game->map.mega), (game->map.width + 1) * MEGAMAP_SQUARE_SIZE, (game->map.height + 1) * MEGAMAP_SQUARE_SIZE) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
