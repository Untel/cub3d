/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/24 20:34:40 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_read_events(t_game *game)
{
	if (game->event[FORWARD] == 1)
		move_forward(game);
	if (game->event[BACKWARD] == 1)
		move_backward(game);
	if (game->event[STRAFE_LEFT] == 1)
		strafe_left(game);
	if (game->event[STRAFE_RIGHT] == 1)
		strafe_right(game);
	if (game->event[ROTATE_LEFT] == 1)
		rotate_left(game);
		// rotate(game, (game->player.rs));
	if (game->event[ROTATE_RIGHT] == 1)
		rotate_right(game);
	game->map.show_mega = game->event[TAB];
		// rotate(game, -(game->player.rs));
}

int	ft_destroy_window(t_game *game)
{
	SUC("Destroying\n");
	mlx_destroy_window(game->mlx, game->win.ref);
	ft_leave_program(game);
}

int	ft_leave_program(t_game *game)
{
	SUC("Good bye\n");
	exit(EXIT_SUCCESS);
}

int	ft_keypress_hook(int keycode, t_game *game)
{
	printf("Key %d press\n", keycode);
	game->event[keycode] = 1;
	return (1);
}
int	ft_keyrelease_hook(int keycode, t_game *game)
{
	printf("Key %d release\n", keycode);
 	// if (keycode == TAB)
	// 	SUC("Collision set to %d", (game->collision = !game->collision));
	if (keycode == ESCAPE)
		ft_destroy_window(game);
	else
		game->event[keycode] = 0;
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

int ft_snapshot(t_game *game)
{
	draw_frame(game);
	ft_render(game);
	ft_draw_minimap(game);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (!(game.mlx = mlx_init())
		|| ft_args(&game, ac, av) == ERROR
		|| !(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, "Cub3d")))
		return (EXIT_FAILURE);
	ft_generate_minimap(&game);
	ft_generate_megamap(&game);
	ft_generate_renderer(&game);
	// if (ac == 3 && 0)
	// 	return (ft_snapshot(&game));
	ft_init_hook(&game);
	SUC("RUNNING GAME\n");
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}
