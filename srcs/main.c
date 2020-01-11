/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/11 16:59:20 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_inc_speed(t_game *game, double speed)
{
	game->player.ms += speed;
	game->player.rs += (speed / 3);
	if (game->player.ms < 0)
		game->player.ms = 0;
	if (game->player.rs < 0)
		game->player.rs = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!(game.mlx = mlx_init())
		|| ft_args(&game, ac, av) == ERROR
		|| !(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, "Cub3d")))
		return (EXIT_FAILURE);
	ft_generate_renderer(&game);
	ft_generate_minimap(&game);
	ft_generate_megamap(&game);
	if (ac == 3)
		return (ft_strncmp(*(av + 2), "-save", 10) == 0 ?
			ft_snapshot(&game)
			: ERR("Please use -save to save a snapshot"));
	ft_init_hook(&game);
	SUC("RUNNING GAME\n");
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
