/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:57:28 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/11 21:17:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_read_events(t_game *game)
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
	if (game->event[FIRE] == 1)
		ft_increment_sprite_index(&game->weapon);
	else
		game->weapon.index = (t_ipos) { 0, 0 };
	return (ft_read_events2(game));
}

int
	ft_read_events2(t_game *game)
{
	if (game->event[JUMP] == 1 && !game->player.jumping)
		game->player.jumping = 1;
	game->player.crouched = game->event[CROUCH];
	game->map.show_mega = game->event[TOGGLE_MAP];
	game->collision = !game->event[TOGGLE_COLLISION];
	return (SUCCESS);
}

void
	ft_toggle_key2(t_game *game, int keycode, int value)
{
	if (keycode == KEY_TAB)
		game->event[TOGGLE_COLLISION] = value;
	else if (keycode == KEY_F)
		game->event[FIRE] = value;
	else if (keycode == KEY_CTRL)
		game->event[CROUCH] = value;
	else if (keycode == KEY_SPACE)
		game->event[JUMP] = value;
}

void
	ft_toggle_key(t_game *game, int keycode, int value)
{
	if (keycode == KEY_W)
		game->event[FORWARD] = value;
	else if (keycode == KEY_S)
		game->event[BACKWARD] = value;
	else if (keycode == KEY_A)
		game->event[STR_LEFT] = value;
	else if (keycode == KEY_D)
		game->event[STR_RIGHT] = value;
	else if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->event[ROT_LEFT] = value;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
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
	else
		ft_toggle_key2(game, keycode, value);
}
