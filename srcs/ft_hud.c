/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hud.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:47:19 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 05:34:21 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define HEALTHBAR_WIDTH 150
#define HEALTHBAR_HEIGHT 20
#define HEALTHBAR_PADDING 5
#define HEALTHBAR_BORDER 0x00FFFFFF

int	ft_draw_health(t_game *game, t_ipos pos)
{
	t_ipos			draw;
	double			ratio;
	unsigned int	color;
	int				hp;
	char			txt[300];
	
	ratio = (double)game->player.hp / (double)(game->player.max_hp);
	hp = HEALTHBAR_WIDTH * ratio - 1;
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	if (ratio > .5)
		color = ratio > .75 ? 0x0000ff00 : 0x00ffff00;
	else
		color = ratio > 0.25 ? 0x00ffA500 : 0x00ff0000;
	while (draw.x++ < pos.x + hp && (draw.y = pos.y))
		while (draw.y++ < pos.y + HEALTHBAR_HEIGHT - 1)
			ft_draw_renderer(game, draw, color);
	ft_sprintf(txt, "%d/%d - %d%%", game->player.hp, game->player.max_hp, (int)(ratio * 100));
	ft_render(game);
	mlx_string_put(game->mlx, game->win.ref, pos.x + 5, pos.y + (HEALTHBAR_HEIGHT / 2 - 11), 0x0, txt);
}

int	ft_healthbar(t_game *game)
{
	t_ipos	pos;
	t_ipos	draw;

	pos = (t_ipos){ .x = HEALTHBAR_PADDING, .y = game->map.mini.height + HEALTHBAR_PADDING };
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	while (draw.x++ < pos.x + HEALTHBAR_WIDTH)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x, .y = pos.y + HEALTHBAR_HEIGHT };
	while (draw.x++ < pos.x + HEALTHBAR_WIDTH)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	while (draw.y++ < pos.y + HEALTHBAR_HEIGHT)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x + HEALTHBAR_WIDTH, .y = pos.y };
	while (draw.y++ < pos.y + HEALTHBAR_HEIGHT)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	ft_draw_health(game, pos);
}

int	ft_hud(t_game *game)
{
	ft_healthbar(game);
}
