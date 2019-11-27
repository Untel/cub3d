/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 18:21:30 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/27 01:15:23 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	move(t_game *game, int dir)
{
	double	next_x;
	double	next_y;

	next_x = game->player.pos.x + (game->player.dir.x * game->player.ms * dir);
	next_y = game->player.pos.y + (game->player.dir.y * game->player.ms * dir);
	if (next_x < 1.0001 || next_x > ((double)(game->map.width) - 1.0001)
		|| next_y < 1.0001 || next_y > ((double)(game->map.width) - 1.0001))
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
	if (!game->collision ||
		game->map.grid[(int)(game->player.pos.x)]
		[(int)(game->player.pos.y + game->player.dir.y * game->player.ms)] == EMPTY)
		game->player.pos.y += (game->player.dir.y * game->player.ms);
	// printf("Stafe left %.2f\n", game->player.dir.y);
	return (1);
}
// if(game->map.grid[(int)game->player.pos.x][(int)(game->player.pos.y - game->player.dir.y * game->player.ms)] == EMPTY) game->player.pos.y -= game->player.dir.y * game->player.ms;
// if(game->map.grid[(int)game->player.pos.x][(int)(game->player.pos.y - game->player.dir.y * game->player.ms)] == EMPTY) game->player.pos.y += game->player.dir.y * game->player.ms;
int
	strafe_right(t_game *game)
{
	if (!game->collision ||
		game->map.grid[
		(int)(game->player.pos.x - game->player.dir.x * game->player.ms)]
		[(int)game->player.pos.y] == EMPTY)
		game->player.pos.x -= (game->player.dir.x * game->player.ms);
	// printf("Stafe right %.2f\n", game->player.pos.x);
	return (1);
}

int
	move_forward(t_game *game)
{
	// printf("Moving forward\n");
	return (move(game, 1));
}

int
	move_backward(t_game *game)
{
	// printf("Moving backward\n");
	return (move(game, -1));
}

int
	rotate(t_game *game, double deg)
{
	double old_dir_x;
	double old_plane_x;
	double acc;

	acc = 1;
	// printf("Rotating %.2f %.2f\n", game->player.plane.x, game->player.plane.y);
	old_dir_x = game->player.dir.x;
	game->player.dir.x = ((game->player.dir.x * cos(deg)
		- game->player.dir.y * sin(deg)) * acc);
	game->player.dir.y = (
		(old_dir_x * sin(deg) + game->player.dir.y * cos(deg)) * acc);

	old_plane_x = game->player.plane.x;
	game->player.plane.x = ((game->player.plane.x
		* cos(deg) - game->player.plane.y * sin(deg)));
	game->player.plane.y = (
		(old_plane_x * sin(deg) + game->player.plane.y * cos(deg)));
}

void    update_orientation(t_game *game)
{
    game->player.dir.x = cos(game->player.angle);
    game->player.dir.y = sin(game->player.angle);
}

void    rotate_right(t_game *game)
{
    game->player.angle -= game->player.rs;
    update_orientation(game);
}

void    rotate_left(t_game *game)
{
    game->player.angle += game->player.rs;
    update_orientation(game);
}
