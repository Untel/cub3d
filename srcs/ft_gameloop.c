/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gameloop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 21:18:59 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 19:12:07 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ft_trigger_hp_losing(t_game *game)
{
	if (game->map.grid[(int)game->player.pos.y]
		[(int)game->player.pos.x] == OBJECT)
	{
		game->player.hp -= 10;
		if (game->player.hp <= 0)
		{
			ft_printf("YOU DIED\n");
			ft_destroy_window(game);
		}
	}
	else if (game->player.hp < game->player.max_hp)
		game->player.hp++;
}

void
	ft_increment_sprite_index(t_sprite *spr)
{
	if (spr->frame_size.x > 0)
	{
		spr->index.x++;
		if (spr->index.x >= (spr->img.width / spr->frame_size.x))
		{
			spr->index.x = 0;
			spr->index.y++;
		}
		if (spr->index.y >= (spr->img.height / spr->frame_size.y))
		{
			spr->index.x = 0;
			spr->index.y = 0;
		}
	}
}

void
	ft_game_loop(t_game *game)
{
	char		txt[300];

	ft_read_events(game);
	ft_trigger_hp_losing(game);
	if (game->player.jumping > 0)
		jump(game);
	crouch(game);
	if (game->map.show_mega)
		ft_draw_megamap(game);
	ft_draw_frame(game);
	if (game->map.show_mega)
	{
		ft_render_megamap(game);
		ft_sprintf(txt, "Pos: x%.2f/y%.2f | Dir x%.2f/y%.2f | Angle %.2f",
			game->player.pos.x, game->player.pos.y,
			game->player.dir.x, game->player.dir.y,
			game->player.angle);
		mlx_string_put(game->mlx, game->win.ref, 10,
			game->win.height - 20, 0xffffff, txt);
	}
	ft_increment_sprite_index(&(game->env.S));
}
