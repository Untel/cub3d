/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:28:50 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/20 17:20:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	update_orientation(double angle, t_dpos *dir)
{
	dir->x = sin(angle);
	dir->y = cos(angle);
}

void
	rotate_right(t_game *game)
{
	game->p.angle -= game->p.rs;
	update_orientation(game->p.angle, &(game->p.dir));
}

void
	rotate_left(t_game *game)
{
	game->p.angle += game->p.rs;
	update_orientation(game->p.angle, &(game->p.dir));
}

void
	rotate_up(t_game *game)
{
	game->p.view2 -= game->win.height / 30;
	if (game->p.view2 <= -(game->win.height / 1.5))
		game->p.view2 = -(game->win.height / 1.5);
}

void
	rotate_down(t_game *game)
{
	game->p.view2 += game->win.height / 30;
	if (game->p.view2 >= (game->win.height / 1.5))
		game->p.view2 = (game->win.height / 1.5);
}
