
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:47:25 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/26 15:42:55 by adda-sil         ###   ########.fr       */	
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_game_loop(t_game *game)
{
	char		txt[300];

	ft_read_events(game);
	ft_draw_minimap(game);
	if (game->map.show_mega)
		ft_draw_megamap(game);
	ft_draw_frame(game);
	ft_render(game);
	mlx_put_image_to_window(game->mlx, game->win.ref, game->map.mini.ref, 0, 0);
	if (game->map.show_mega)
		ft_render_megamap(game);
	ft_sprintf(txt, "Pos: x%.2f/y%.2f | Dir x%.2f/y%.2f | Plane x%.2f/y%.2f | Angle %.2f",
		game->player.pos.x, game->player.pos.y,
		game->player.dir.x, game->player.dir.y,
		game->player.plane.x, game->player.plane.y,
		game->player.angle);
	mlx_string_put(game->mlx, game->win.ref, 10, game->win.height - 20, 0xffffff, txt);
}

