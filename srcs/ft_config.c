/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 04:10:39 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 09:05:37 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_next_number(char **str)
{
	int nb;

	while (!ft_isdigit(**str))
		(*str)++;
	if (!*str)
		return (-1);
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
	if (!(0 <= r <= 255 && 0 <= g <= 255 && 0 <= b <= 255))
		return (!ft_printf("Error setting RGB color for %s\n", key));
	*color = (b << 16) + (g << 8) + r;
	ft_printf("- %s set to %d %d %d (%d)\n", key, r, g, b, *color);
	return (1);
}

int	ft_set_path(char *key, char *buffer, char *str)
{
	if (ft_strlen(str) >= PATH_URL_SIZE)
		return (0);
	ft_strcpy(buffer, str);
	ft_printf("- %s path : \"%s\"\n", key, buffer);
	return (1);
}

int	ft_set_window_size(char *str)
{
	game.win.width = ft_get_next_number(&str);
	game.win.height = ft_get_next_number(&str);
	if (game.win.width == -1 || game.win.height == -1)
		return (!ft_printf("Error setting Win Size\n"));
	ft_printf("- Win Size %d/%d\n", game.win.width, game.win.height);
	return (1);
}

int	ft_fill_map(char *str)
{
	static int	line = 0;
	char		*ptr;
	int			i;

	i = 0;
	while (*str)
		if (!(0 <= (game.map.grid[line][i++] = (*str++ - '0')) <= 2))
			return (!ft_printf("Error filling map at idx %d,%d", line, i));
	if (line == 0)
		game.map.width = i;
	return (1);
}

int	ft_readline(char *line)
{
	int ret;

	if (!ft_strncmp("R ", line, 2))
		ret = ft_set_window_size(&line[2]);
	else if (!ft_strncmp("NO ", line, 3))
		ret = ft_set_path("NO", game.env.NO, &line[3]);
	else if (!ft_strncmp("SO ", line, 3))
		ret = ft_set_path("SO", game.env.SO, &line[3]);
	else if (!ft_strncmp("WE ", line, 3))
		ret = ft_set_path("WE", game.env.WE, &line[3]);
	else if (!ft_strncmp("EA ", line, 3))
		ret = ft_set_path("EA", game.env.EA, &line[3]);
	else if (!ft_strncmp("S ", line, 2))
		ret = ft_set_path("SPRITE", game.env.SPRITE, &line[2]);
	else if (!ft_strncmp("F ", line, 2))
		ret = ft_set_color("FLOOR", &game.env.FLOOR, &line[2]);
	else if (!ft_strncmp("C ", line, 2))
		ret = ft_set_color("CEIL", &game.env.CEIL, &line[2]);
	else if (*line == '1')
		ret = ft_fill_map(line);
	else if (!*line)
		ret = (1);
	else
		ret = -1;
	return (ret);
}

int	ft_configure(char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(filename, O_RDONLY);
	ft_printf("===========================================\n");
	ft_printf("Configuring from %s\n", filename);
	ft_printf("===========================================\n");
	while ((ret = get_next_line(fd, &line)) == 1)
		ret = ft_f(line, ft_readline(line));
	if (ret == 0)
		ft_f(line, ft_readline(line));
	else
		exit(0);
	ft_printf("===========================================\n");
}

int	ft_args(int ac, char **argv)
{
	int has_err;

	has_err = 0;
	if (ac > 1)
		has_err &= !ft_configure(*++argv);
	return (has_err);
}
