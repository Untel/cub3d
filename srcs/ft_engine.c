/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:16:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/24 21:16:02 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_draw_renderer(t_game *game, t_ipos pos, int color)
{
	if (!(pos.x < game->map.mini.width && pos.y < game->map.mini.height))
		ft_set_pixel(&(game->renderer), pos, color);
}

int	ft_generate_renderer(t_game *game)
{
	t_ipos pos;

	if (ft_generate_image(game, &(game->renderer), game->win.width, game->win.height) == ERROR)
		return (ERROR);
	pos.x = -1;
	while (++pos.x < game->win.width && (pos.y = -1))
		while (++pos.y < game->win.height)
			ft_draw_renderer(game, pos, 0xff0000);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->renderer.ref, 0, 0);
	return (SUCCESS);
}

int	ft_render(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win.ref, game->renderer.ref, 0, 0);
}