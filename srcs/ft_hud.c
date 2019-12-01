/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hud.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:47:19 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 19:52:00 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_draw_health(t_game *game, t_ipos pos)
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
		color = ratio > .75 ? GREEN : YELLOW;
	else
		color = ratio > 0.25 ? ORANGE : RED;
	while (draw.x++ < pos.x + hp && (draw.y = pos.y))
		while (draw.y++ < pos.y + HEALTHBAR_HEIGHT - 1)
			ft_draw_renderer(game, draw, color);
	ft_sprintf(txt, "%d/%d - %d%%", game->player.hp,
		game->player.max_hp, (int)(ratio * 100));
	ft_render(game);
	mlx_string_put(game->mlx, game->win.ref, pos.x + 5,
		pos.y + (HEALTHBAR_HEIGHT / 2 - 11), 0x0, txt);
}

int
	ft_healthbar(t_game *game)
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

int
	ft_weapon(t_game *game)
{
	t_ipos start_draw;
	t_ipos draw;
	t_dpos draw_tex_step;
	t_dpos draw_tex;
	int pad = ((double)game->win.width / 3);
	draw = (t_ipos) { .x = game->win.width - pad + (pad / 15), .y = game->win.height - pad + (pad / 7) };
	start_draw = (t_ipos) { .x = draw.x + pad, .y = draw.y + pad};
	draw_tex_step = (t_dpos) {
		.x = (1 / (double)(start_draw.x - draw.x)),
		.y = (1 / (double)(start_draw.y - draw.y))
	};
	draw_tex = (t_dpos) { 0, 0 };
	while (draw.x < (start_draw.x))
	{
		(draw.y = game->win.height - pad + (pad / 7));
		draw_tex.y = 0;
		while (draw.y < (start_draw.y))
		{
			ft_draw_sprite(game, &(game->weapon), draw, draw_tex);
			draw_tex.y += draw_tex_step.y;
			draw.y++;
		}
		draw.x++;
		draw_tex.x += draw_tex_step.x;
	}
	// printf("Weapon drawed");
}

int	ft_draw_crosshair(t_game *game)
{
	t_ipos pos;
	int i;

	i = -1;
	pos.x = game->win.width / 2 - CH_RADIAN;
	pos.y = game->win.height / 2;
	while (pos.x++ < game->win.width / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
	pos.x = game->win.width / 2;
	pos.y = game->win.height / 2 - CH_RADIAN;	
	while (pos.y++ < game->win.height / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
}

int
	ft_hud(t_game *game)
{
	// printf("weapon is %d  /  %d", game->weapon.frame_size.x, game->weapon.frame_size.y);
	ft_weapon(game);
	ft_draw_crosshair(game);
	ft_draw_minimap(game);
	ft_healthbar(game);
}
