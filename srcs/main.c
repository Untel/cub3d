/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 11:07:24 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_read_events(t_game *game)
{
	if (game->event[FORWARD] == 1)
		move_forward(game);
	if (game->event[BACKWARD] == 1)
		move_backward(game);
	if (game->event[STR_LEFT] == 1)
		strafe_left(game);
	if (game->event[STR_RIGHT] == 1)
		strafe_right(game);
	if (game->event[ROT_LEFT] == 1)
		rotate_left(game);
	if (game->event[ROT_RIGHT] == 1)
		rotate_right(game);
	if (game->event[ROT_UP] == 1)
		rotate_up(game);
	if (game->event[ROT_DOWN] == 1)
		rotate_down(game);
	if (game->event[INC_SPEED] == 1)
		ft_inc_speed(game, 0.01);
	if (game->event[DEC_SPEED] == 1)
		ft_inc_speed(game, -0.01);
	game->map.show_mega = game->event[TOGGLE_MAP];
	game->collision = !game->event[TOGGLE_COLLISION];
}

int ft_inc_speed(t_game *game, double speed)
{
	game->player.ms += speed;
	game->player.rs += (speed / 3);
	if (game->player.ms < 0)
		game->player.ms = 0;
	if (game->player.rs < 0)
		game->player.rs = 0;
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
	system("leaks a.out");
	exit(EXIT_SUCCESS);
}

int toggle_key(t_game *game, int keycode, int value)
{
	if (keycode == KEY_W)
		game->event[FORWARD] = value;
	else if (keycode == KEY_S)
		game->event[BACKWARD] = value;
	else if (keycode == KEY_A)
		game->event[STR_LEFT] = value;
	else if (keycode == KEY_D)
		game->event[STR_RIGHT] = value;
	else if (keycode == KEY_Q || keycode == KEY_RIGHT)
		game->event[ROT_LEFT] = value;
	else if (keycode == KEY_E || keycode == KEY_LEFT)
		game->event[ROT_RIGHT] = value;
	else if (keycode == KEY_UP)
		game->event[ROT_UP] = value;
	else if (keycode == KEY_DOWN)
		game->event[ROT_DOWN] = value;
	else if (keycode == KEY_PLUS)
		game->event[INC_SPEED] = value;
	else if (keycode == KEY_MINUS)
		game->event[DEC_SPEED] = value;
	else if (keycode == KEY_M)
		game->event[TOGGLE_MAP] = value;
	else if (keycode == KEY_TAB)
		game->event[TOGGLE_COLLISION] = value;
}

int	ft_keypress_hook(int keycode, t_game *game)
{
	printf("Key %d press\n", keycode);
	toggle_key(game, keycode, 1);
	return (1);
}
int	ft_keyrelease_hook(int keycode, t_game *game)
{
	printf("Key %d release\n", keycode);
	if (keycode == KEY_ESC)
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
