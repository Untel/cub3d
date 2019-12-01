/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snapshot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 20:13:21 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/01 10:29:24 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_filename(char *buffer)
{
	ft_strcpy(buffer, "snapshot.bmp");
	return (SUCCESS);
}

int	ft_put_octet(int value, int len, int fd)
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

int ft_write_image(t_game *game, int fd)
{
	int size;
	int i = -1;

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
	return (SUCCESS);
}

int ft_snapshot(t_game *game)
{
	char	filename[300];
	int		fd;

	printf("Generate snapshot\n");
	ft_filename(filename);
	ft_draw_frame(game);
	fd = open(filename, O_RDWR|O_CREAT, 0666);
	ft_write_image(game, fd);
	close(fd);
	return (EXIT_SUCCESS);
}
