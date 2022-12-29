/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:59:16 by adda-sil          #+#    #+#             */
/*   Updated: 2022/12/29 13:54:25 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstprint(t_list *lst, char *cmt)
{
	int i;

	i = 0;
	printf("--- %d nodes ---\n", ft_lstsize(lst));
	if (cmt)
		printf("| %s\n", cmt);
	while (lst)
	{
		printf("| %d | \"%s\" (%lu)\n", i++, (char *)lst->content, lst->size);
		lst = lst->next;
	}
	printf("---------------\n\n");
}
