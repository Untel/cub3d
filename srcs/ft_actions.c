/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 15:28:18 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 18:33:41 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	crouch(t_game *game)
{
	int inc;

	inc = game->win.height / 15;
	if (game->p.crouched == 1 && game->p.view <= (game->win.height / 4))
		game->p.view += inc;
	if (game->p.crouched == 0 && game->p.view > 0)
	{
		if (game->p.view <= inc)
			game->p.view = 0;
		else
			game->p.view -= inc;
	}
}

void
	jump(t_game *game)
{
	int inc;

	inc = game->win.height / 30;
	if (game->p.jumping == 1)
		game->p.view -= inc;
	else if (game->p.jumping == 2)
		game->p.view += inc;
	if (game->p.view <= -(game->win.height / 2))
		game->p.jumping = 2;
	else if (game->p.jumping == 2 && game->p.view >= 0)
	{
		game->p.jumping = 0;
		game->p.view = 0;
	}
}
