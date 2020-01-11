/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:58:30 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/11 16:58:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_keypress_hook(int keycode, t_game *game)
{
	printf("Key %d press\n", keycode);
	toggle_key(game, keycode, 1);
	return (1);
}
int	ft_keyrelease_hook(int keycode, t_game *game)
{
	printf("Key %d release\n", keycode);

	if (keycode == KEY_H)
		game->hud = !game->hud;
	if (keycode == KEY_O)
	{
		game->shading = !game->shading;
		if (game->shading && (!game->win.floor_dist))
			ft_generate_floor_dist(game);
	}
	else if (keycode == KEY_ESC)
		return (ft_destroy_window(game));
	else
		toggle_key(game, keycode, 0);
	return (1);
}

int	ft_init_hook(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
    mlx_hook(game->win.ref, 2, 1L << 0, ft_keypress_hook, game);
    mlx_hook(game->win.ref, 3, 1L << 1, ft_keyrelease_hook, game);
    mlx_hook(game->win.ref, 17, 0, ft_leave_program, game);
	mlx_loop_hook(game->mlx, ft_game_loop, game);
}