/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/17 21:33:44 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	game_loop()
{
	char	txt[300];
	int		fps;

	*txt = 0;
	fps = 0;
	draw_frame();
	ft_sprintf(txt, "Fps:%d X:%d Y:%d -", fps, (int)game.player.pos.x, (int)game.player.pos.y);
	mlx_string_put(game.mlx, game.win.ref, 50, 50, 0xffffff, txt);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == FORWARD)
		move_forward();
	else if (keycode == BACKWARD)
		move_backward();
	else if (keycode == STRAFE_LEFT)
		strafe_left();
	else if (keycode == STRAFE_RIGHT)
		strafe_right();
	else if (keycode == ROTATE_LEFT)
		rotate((game.player.rs));
	else if (keycode == ROTATE_RIGHT)
		rotate(-(game.player.rs));
	if (keycode == ESCAPE)
	{
		printf("destroying\n");
		mlx_clear_window(game.mlx, game.win.ref);
		mlx_destroy_window(game.mlx, game.win.ref);
		exit(0);
	}
	// SUC("Press %d\n", keycode);
	printf("Key %d, POS(%.2f, %.2f)\n", keycode, game.player.pos.x, game.player.pos.y);
	return (1);
}

int	keypress_hook()
{
	SUC("PRESS");
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	if (ft_args(ac, av) == ERROR)
		return (EXIT_FAILURE);
	system("leaks a.out");
	// return (0);
	if (!(game.mlx = mlx_init()))
		return (EXIT_FAILURE);
	if (!(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, "Cub3d")))
		return (EXIT_FAILURE);
	SUC("RUNNING GAME\n");
	// mlx_do_key_autorepeatoff(game.mlx);
	
	mlx_hook(game.win.ref, 1, 4, keypress_hook, NULL);
	mlx_key_hook(game.win.ref, key_hook, NULL);
	// mlx_mouse_hook(game.win.ref, mouse_hook, NULL);
	// mlx_expose_hook(game.mlx, game, NULL);
	// mlx_mouse_get_pos(game.mlx);
	// draw_frame();
	mlx_loop_hook(game.mlx, game_loop, NULL);
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}