/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:16:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/28 22:51:07 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw_renderer(t_game *game, t_ipos pos, unsigned int color)
{
	// if (pos.x < game->map.mini.width && pos.y < game->map.mini.height)
	// 	return (0);
	// if (game->map.show_mega && pos.x < game->map.mega.width && pos.y < game->map.mega.height)
	// 	return (0);
	ft_set_pixel(&(game->win.renderer), pos, color);
}

int	ft_generate_renderer(t_game *game)
{
	t_ipos pos;

	if (ft_generate_image(game, &(game->win.renderer), game->win.width, game->win.height) == ERROR)
		return (ERROR);
	pos.x = -1;
	// while (++pos.x < game->win.width && (pos.y = -1))
	// 	while (++pos.y < game->win.height)
	// 		ft_draw_renderer(game, pos, 0xff0000);
	// mlx_put_image_to_window(game->mlx, game->win.ref, game->win.renderer.ref, 0, 0);
	return (SUCCESS);
}

int	ft_render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win.ref, game->win.renderer.ref, 0, 0);
}