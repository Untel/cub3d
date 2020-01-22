/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snapshot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 20:13:21 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 19:29:15 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_filename(void)
{
	char	filename[BUFFER_SIZE];
	int		tries;
	int		fd;

	tries = 1;
	ft_strcpy(filename, "snapshot.bmp");
	while ((fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0666)) == -1
		&& errno == 17 && tries < 20)
		ft_sprintf(filename, "snapshot(%d).bmp", tries++);
	if (fd == -1 && errno != 17)
		return (ft_print_defined_err("Cannot create snapshot file"));
	ft_printf("Generating snapshot on './%s'", filename);
	return (fd);
}

int
	ft_put_octet(int value, int len, int fd)
{
	int		i;
	char	c;

	i = -1;
	while (++i < len)
	{
		c = value / pow(256, i);
		write(fd, &c, 1);
	}
	return (SUCCESS);
}

void
	ft_write_image(t_game *game, int fd)
{
	int size;
	int i;

	i = -1;
	size = game->win.height * game->win.width;
	ft_putstr_fd("BM", fd);
	ft_put_octet(size + 54, 4, fd);
	ft_put_octet(0, 4, fd);
	ft_put_octet(54, 4, fd);
	ft_put_octet(40, 4, fd);
	ft_put_octet(game->win.width, 4, fd);
	ft_put_octet(game->win.height, 4, fd);
	ft_put_octet(1, 2, fd);
	ft_put_octet(game->win.renderer.bits, 2, fd);
	ft_put_octet(0, 4, fd);
	ft_put_octet(size, 4, fd);
	ft_put_octet(11811, 4, fd);
	ft_put_octet(11811, 4, fd);
	ft_put_octet(0, 4, fd);
	ft_put_octet(0, 4, fd);
	while (++i < game->win.height)
		write(fd, &game->win.renderer.data[
			(game->win.height - i) * game->win.renderer.s_line],
			game->win.renderer.s_line);
}

int
	ft_snapshot(t_game *game)
{
	int	fd;

	if ((fd = ft_filename()) == -1)
	{
		ft_print_defined_err("Cannot create snapshot");
		return (EXIT_FAILURE);
	}
	ft_draw_frame(game);
	ft_write_image(game, fd);
	close(fd);
	return (EXIT_SUCCESS);
}
