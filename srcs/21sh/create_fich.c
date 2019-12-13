/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_fich.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 13:24:49 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 03:48:38 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void		restore_fd(void)
{
	dup2(10, 0);
	close(10);
	dup2(11, 1);
	close(11);
	dup2(12, 2);
	close(12);
}

void		save_fd(void)
{
	dup2(0, 10);
	dup2(1, 11);
	dup2(2, 12);
}

int			ft_error_descr(int descr)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(ft_itoa(descr), 2);
	ft_putendl_fd(": bad file descriptor", 2);
	return (-1);
}

int			create_fich(char **tab_reddir, int i)
{
	int		fd_in;
	int		fd_out;

	fd_in = search_in(tab_reddir[i], 1);
	if (!its_double_reddir(tab_reddir[i]))
	{
		if (ft_strlen(tab_reddir[i + 1]) == 1 && tab_reddir[i + 1][0] >= '0'
				&& tab_reddir[i + 1][0] <= '9')
		{
			fd_out = tab_reddir[i + 1][0] - '0';
			if (write(fd_out, "0", 0) == -1)
				return (ft_error_descr(fd_out));
		}
		else if (!ft_strcmp(tab_reddir[i + 1], "-"))
			fd_out = open("/dev/null", O_RDONLY);
		else
			fd_out = open(tab_reddir[i + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	else
		fd_out = open(tab_reddir[i + 1], O_CREAT | O_APPEND | O_RDWR, 0644);
	dup2(fd_out, fd_in);
	return (0);
}
