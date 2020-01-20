/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 21:45:23 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_destroy_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win.ref);
	ft_leave_program(game);
	return (SUCCESS);
}

int
	ft_leave_program(t_game *game)
{
	free(game->win.sky_dist);
	free(game->win.floor_dist);
	free(game->win.cos);
	free(game->win.sin);
	mlx_destroy_image(game->mlx, game->env.ea.ref);
	mlx_destroy_image(game->mlx, game->env.we.ref);
	mlx_destroy_image(game->mlx, game->env.no.ref);
	mlx_destroy_image(game->mlx, game->env.so.ref);
	mlx_destroy_image(game->mlx, game->env.s.img.ref);
	mlx_destroy_image(game->mlx, game->weapon.img.ref);
	exit(EXIT_SUCCESS);
	return (1);
}

void
	ft_inc_speed(t_game *game, double speed)
{
	game->p.ms += speed;
	game->p.rs += (speed / 3);
	if (game->p.ms < 0)
		game->p.ms = 0;
	if (game->p.rs < 0)
		game->p.rs = 0;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!(game.mlx = mlx_init()))
		return (ft_print_defined_err("Cannot init minilibx") || EXIT_FAILURE);
	if (ft_args(&game, ac, av) == ERROR)
		return (EXIT_SUCCESS);
	if (!(game.win.ref = mlx_new_window(game.mlx,
			game.win.width, game.win.height, "Cub3d")))
		return (ft_print_defined_err("Cannot generate window") || EXIT_FAILURE);
	ft_generate_renderer(&game);
	ft_generate_minimap(&game);
	ft_generate_megamap(&game);
	if (ac > 2 && ft_strncmp(*(av + 2), "-save", 10) == 0)
		return (ft_snapshot(&game));
	ft_init_hook(&game);
	mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
