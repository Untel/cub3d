/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:21:30 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 04:18:40 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	move(t_game *game, t_dpos dir)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos.x + (dir.x * game->player.ms);
	next_y = game->player.pos.y + (dir.y * game->player.ms);
	if (next_x < 1.01)
		next_x = 1.01;
	else if (next_x > ((double)game->map.width - .01))
		next_x = (double)game->map.width - .01;
	if (next_y < 1.01)
		next_y = 1.01;
	else if (next_y > ((double)game->map.height - .01))
		next_y = (double)game->map.height - .01;

	if (!game->collision ||
		game->map.grid[(int)(next_y)][(int)game->player.pos.x] != WALL)
		game->player.pos.y = next_y;
	if (!game->collision ||
		game->map.grid[(int)game->player.pos.y][(int)(next_x)] != WALL)
		game->player.pos.x = next_x;
	return (1);

}

int
	strafe_left(t_game *game)
{
	t_dpos dir;

	update_orientation(game->player.angle + M_PI_2, &dir);
	move(game, dir);
	return (1);
}

int
	strafe_right(t_game *game)
{
	t_dpos dir;

	update_orientation(game->player.angle - M_PI_2, &dir);
	return (move(game, dir));
}

int
	move_forward(t_game *game)
{
	return (move(game, game->player.dir));
}

int
	move_backward(t_game *game)
{
	t_dpos dir;

	update_orientation(game->player.angle - M_PI, &dir);
	return (move(game, dir));
}

void    update_orientation(double angle, t_dpos *dir)
{
    dir->x = cos(angle);
    dir->y = sin(angle);
}

void    rotate_right(t_game *game)
{
    game->player.angle -= game->player.rs;
    update_orientation(game->player.angle, &(game->player.dir));
}

void    rotate_left(t_game *game)
{
    game->player.angle += game->player.rs;
    update_orientation(game->player.angle, &(game->player.dir));
}

void    rotate_up(t_game *game)
{
    game->player.view -= game->player.rs;
	if (game->player.view < 0.5)
		game->player.view = 0.5;
}

void    rotate_down(t_game *game)
{
    game->player.view += game->player.rs;
	if (game->player.view > 3)
		game->player.view = 3;
}