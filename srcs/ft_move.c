/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:21:30 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/27 19:49:35 by adda-sil         ###   ########.fr       */
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
	if (next_x < 1.0001 || next_x > ((double)(game->map.width))
		|| next_y < 1.0001 || next_y > ((double)(game->map.width)))
		return (0);

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
	double angle;

	angle = game->player.angle + M_PI_2;
	update_orientation(angle, &dir);
	move(game, dir);
	return (1);
}
// if(game->map.grid[(int)game->player.pos.x][(int)(game->player.pos.y - game->player.dir.y * game->player.ms)] == EMPTY) game->player.pos.y -= game->player.dir.y * game->player.ms;
// if(game->map.grid[(int)game->player.pos.x][(int)(game->player.pos.y - game->player.dir.y * game->player.ms)] == EMPTY) game->player.pos.y += game->player.dir.y * game->player.ms;
int
	strafe_right(t_game *game)
{
	t_dpos dir;
	double angle;

	angle = game->player.angle - M_PI_2;
	update_orientation(angle, &dir);
	move(game, dir);
	return (1);
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
	double angle;

	angle = game->player.angle - M_PI;
	update_orientation(angle, &dir);
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
