/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/17 19:50:46 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_next_number(char **str)
{
	int nb;

	while (!ft_isdigit(**str))
		(*str)++;
	if (!*str)
		return (ERROR);
	nb = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (nb);
}

int	ft_set_color(char *key, int *color, char *str)
{
	int r;
	int g;
	int b;

	r = ft_get_next_number(&str);
	g = ft_get_next_number(&str);
	b = ft_get_next_number(&str);
	if (!(r >= 0 && r <= 255
		&& g >= 0 && g <= 255
		&& b >= 0 && b <= 255))
		return (ERR("setting RGB color for %s", key));
	*color = (b << 16) + (g << 8) + r;
	return (SUC("%s set to %d %d %d (%#X)", key, r, g, b, *color));
}

int	ft_set_path(char *key, char *buffer, char *str)
{
	if (ft_strlen(str) >= PATH_URL_SIZE)
		return (0);
	ft_strcpy(buffer, str);
	return (SUC("%s path: \"%s\"", key, buffer));
}

int	ft_set_window_size(char *str)
{
	game.win.width = ft_get_next_number(&str);
	game.win.height = ft_get_next_number(&str);
	if (game.win.width == -1 || game.win.height == -1)
		return (ERR("Error setting Win Size\n"));
	return (SUC("Win Size %d/%d", game.win.width, game.win.height));
}

int	ft_set_player_position(char dir, int x, int y)
{
	game.player.pos.x = (double)x + .5;
	game.player.pos.y = (double)y + .5;
	game.map.grid[x][y] = 0;
	return (SUC("Player start at x%d, y%d", x, y));
}

int	ft_fill_map(char *str)
{
	static int	line = 0;
	char		*ptr;
	int			i;
	int			x;

	i = -1;
	while (*str)
		if (*str == ' ')
			str++;
		else if (ft_strchr("NSWE", *str))
			ft_set_player_position(*str++, line, ++i);
		else
		{
			x = (*str - '0');
			if (x < 0 || x > 4)
				return (ERR("filling map %d,%d (%d)", line, i, x));
			game.map.grid[line][++i] = x;
			str++;
		}
	if (line == 0)
		game.map.width = i;
	else if (game.map.width != i)
		return (ERR("filling map, not same width at line %d", line + 1));
	line++;
	return (SUCCESS);
}

int	ft_verify_map(void)
{
	int	i;

	i = -1;
	while (++i < game.map.width)
		if (game.map.grid[0][i] != WALL
			&& game.map.grid[game.map.height - 1][i] != WALL)
			return (ERROR);
	i = -1;
	while (++i < game.map.height)
		if (game.map.grid[i][0] != WALL
			&& game.map.grid[i][game.map.width - 1] != WALL)
			return (ERROR);
	return (SUCCESS);
}

int	ft_readline(char *line)
{
	int ret;

	if (!ft_strncmp("R ", line, 2))
		ret = ft_set_window_size(&line[2]);
	else if (!ft_strncmp("NO ", line, 3))
		ret = ft_set_path("North texture", game.env.NO, &line[3]);
	else if (!ft_strncmp("SO ", line, 3))
		ret = ft_set_path("South texture", game.env.SO, &line[3]);
	else if (!ft_strncmp("WE ", line, 3))
		ret = ft_set_path("West texture", game.env.WE, &line[3]);
	else if (!ft_strncmp("EA ", line, 3))
		ret = ft_set_path("East texture", game.env.EA, &line[3]);
	else if (!ft_strncmp("S ", line, 2))
		ret = ft_set_path("Sprite texture", game.env.SPRITE, &line[2]);
	else if (!ft_strncmp("F ", line, 2))
		ret = ft_set_color("Floor color", &game.env.FLOOR, &line[2]);
	else if (!ft_strncmp("C ", line, 2))
		ret = ft_set_color("Ceil color", &game.env.CEIL, &line[2]);
	else if (*line == '1')
		ret = ft_fill_map(line);
	else
		ret = !*line ? SUCCESS : ERROR;
	return (ret);
}

int	ft_configure(char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	if ((fd = open(filename, O_RDONLY)) == ERROR)
		return (ERROR);
	ret = SUCCESS;
	ft_printf("===========================================\n");
	ft_printf("Configuring from %s\n", filename);
	ft_printf("===========================================\n");
	while (ret == SUCCESS && (ret = get_next_line(fd, &line)) == SUCCESS)
		ret = ft_f(line, ft_readline(line));
	if (ret == 0)
		ret = ft_f(line, ft_readline(line));
	ft_printf("===========================================\n");
	return (ret);
}

int	ft_args(int ac, char **argv)
{
	int ret;

	if (ac > 1)
		ret = ft_configure(*++argv);
	game.player.ms = 1;
	game.player.rs = 1;
	game.player.dir.x = -1;
	game.player.dir.y = 0;
	game.player.plane.x = 0;
	game.player.plane.y = 0.66;
	game.time = 0;
	return (ret);
}
