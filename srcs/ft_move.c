/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:21:30 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/20 18:07:06 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	can_go(t_game *game, int x, int y)
{
	if (game->map.grid[y][x] == WALL && game->collision)
		return (0);
	if (game->map.grid[y][x] == OBJECT && game->env.s.collision)
		return (0);
	return (1);
}

int
	move(t_game *game, t_dpos dir)
{
	double	next_x;
	double	next_y;

	next_x = game->p.pos.x + (dir.x * game->p.ms);
	next_y = game->p.pos.y + (dir.y * game->p.ms);
	if (next_x < 1.01)
		next_x = 1.01;
	else if (next_x > ((double)game->map.width - 1.01))
		next_x = (double)game->map.width - 1.01;
	if (next_y < 1.01)
		next_y = 1.01;
	else if (next_y > ((double)game->map.height - 1.01))
		next_y = (double)game->map.height - 1.01;
	if (can_go(game, (int)game->p.pos.x, (int)(next_y)))
		game->p.pos.y = next_y;
	if (can_go(game, (int)(next_x), (int)game->p.pos.y))
		game->p.pos.x = next_x;
	return (SUCCESS);
}

int
	strafe_left(t_game *game)
{
	t_dpos dir;

	update_orientation(game->p.angle + M_PI_2, &dir);
	move(game, dir);
	return (1);
}

int
	strafe_right(t_game *game)
{
	t_dpos dir;

	update_orientation(game->p.angle - M_PI_2, &dir);
	return (move(game, dir));
}

int
	move_backward(t_game *game)
{
	t_dpos dir;

	update_orientation(game->p.angle - M_PI, &dir);
	return (move(game, dir));
}
