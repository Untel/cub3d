/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/19 17:31:10 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_events(game_t *game)
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
		rotate(game, (game->player.rs));
	if (game->event[ROTATE_RIGHT] == 1)
		rotate(game, -(game->player.rs));
}

int	game_loop(game_t *game)
{
	char	txt[300];
	int		fps;

	*txt = 0;
	fps = 0;
	read_events(game);
	draw_frame(game);
	ft_sprintf(txt, "Fps:%d X:%d Y:%d -", fps, (int)game->player.pos.x, (int)game->player.pos.y);
	mlx_string_put(game->mlx, game->win.ref, 50, 50, 0xffffff, txt);
}

int	destroy_window(game_t *game)
{
	SUC("Destroying\n");
	mlx_clear_window(game->mlx, game->win.ref);
	mlx_destroy_window(game->mlx, game->win.ref);
	exit(0);
}

int	keypress_hook(int keycode, game_t *game)
{
	if (game->event[keycode] == 0)
		printf("Key %d press\n", keycode);
	game->event[keycode] = 1;
	return (1);
}
int	keyrelease_hook(int keycode, game_t *game)
{
	printf("Key %d released\n", keycode);
 	if (keycode == TAB)
		SUC("Collision set to %d", (game->collision = !game->collision));
	else if (keycode == ESCAPE)
		destroy_window(game);
	else
		game->event[keycode] = 0;
	return (1);
}

int	test(int keycode, game_t *game)
{
	printf("TEST FN %d\n\n", keycode);
}

int	main(int ac, char **av)
{
	game_t	game;

	if (ft_args(&game, ac, av) == ERROR)
		return (EXIT_FAILURE);
	system("leaks a.out");
	// return (0);
	if (!(game.mlx = mlx_init()))
		return (EXIT_FAILURE);
	if (!(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, "Cub3d")))
		return (EXIT_FAILURE);
	SUC("RUNNING GAME\n");
	// mlx_do_key_autorepeatoff(game->mlx);
	
    mlx_hook(game.win.ref, 2, 1L << 0, keypress_hook, &game);
    mlx_hook(game.win.ref, 3, 1L << 1, keyrelease_hook, &game);
    mlx_hook(game.win.ref, 17, 0, test, &game);
	// mlx_mouse_hook(game->win.ref, mouse_hook, NULL);
	// mlx_expose_hook(game->mlx, game, NULL);
	// mlx_mouse_get_pos(game->mlx);
	// draw_frame();
	mlx_loop_hook(game.mlx, game_loop, &game);
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}