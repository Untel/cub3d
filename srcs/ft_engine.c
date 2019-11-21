/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_engine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 19:16:36 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/21 15:32:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_generate_renderer(t_game *game)
{
	int x;
	int y;

	if (ft_generate_image(game, &(game->renderer), game->win.width, game->win.height) == ERROR)
		return (ERROR);
	x = -1;
	y = -1;
	while (++x < game->win.width)
		while (++y < game->win.height)
			ft_set_pixel(&(game->renderer), x, y, 0xFF0000);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->renderer.ref, 0, 0);
	return (SUCCESS);
}
