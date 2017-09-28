/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:59:56 by adalenco          #+#    #+#             */
/*   Updated: 2017/09/28 18:59:57 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_option(char *op, char options[6])
{
	int		i;

	i = 1;
	while (op[i])
	{
		if (op[i] == 'l')
			OP_L = 1;
		else if (op[i] == 'R')
			OP_RR = 1;
		else if (op[i] == 'a')
			OP_A = 1;
		else if (op[i] == 'r')
			OP_R = 1;
		else if (op[i] == 't')
			OP_T = 1;
		else
		{
			ft_putstr("ls: illegal option -- ");
			write(1, &op[i], 1);
			ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
			exit(0);
		}
		i++;
	}
}

int			parse_av(char options[6], char **av, char *path)
{
	DIR     *dirp;
	char	*npath;
	int		i;
	int		arg;

	arg = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-' && i == 1)
			;
		else
		{
			npath = ft_strjoin3(path, "/", av[i]);
			if ((dirp = opendir(npath)) == NULL)
				; // recuperer errno -> ENOTDIR
			ft_parse_ls(dirp, options, npath);
			closedir(dirp);
			free(npath);
			arg++;
		}
		i++;
	}
	return (arg);
}
