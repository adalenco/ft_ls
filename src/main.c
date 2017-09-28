/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 19:00:02 by adalenco          #+#    #+#             */
/*   Updated: 2017/09/28 22:05:45 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				get_info(t_data *list, struct stat *buf)
{
	struct passwd	*pass;
	struct group	*grp;

	pass = getpwuid(buf->st_uid);
	grp = getgrgid(buf->st_gid);
	list->usrlen = ft_strlen(list->usr = ft_strdup(pass->pw_name));
	list->grplen = ft_strlen(list->grp = ft_strdup(grp->gr_name));
	list->byteslen = ft_unblen(list->bytes = (unsigned int)buf->st_size);
	list->lklen = ft_unblen(list->links = (unsigned long int)buf->st_nlink);
	list->blocks = (unsigned long int)buf->st_blocks;
}

int					ft_rec_mode(t_data *list, struct dirent *entry, char *path, char options[6])
{
	struct stat		buf;
	int				dir;
	char			*file;

	file = ft_strjoin3(path, "/", entry->d_name);
	dir = 0;
	stat(file, &buf);
	if (buf.st_mode & S_IFDIR)
	{
		list->mode[0] = 'd';
		dir++;
	}
	list->name = strdup(entry->d_name);
	if (buf.st_mode & S_IRUSR)
		list->mode[1] = 'r';
	if (buf.st_mode & S_IWUSR)
		list->mode[2] = 'w';
	if (buf.st_mode & S_IXUSR)
		list->mode[3] = 'x';
	if (buf.st_mode & S_IRGRP)
		list->mode[4] = 'r';
	if (buf.st_mode & S_IWGRP)
		list->mode[5] = 'w';
	if (buf.st_mode & S_IXGRP)
		list->mode[6] = 'x';
	if (buf.st_mode & S_IROTH)
		list->mode[7] = 'r';
	if (buf.st_mode & S_IWOTH)
		list->mode[8] = 'w';
	if (buf.st_mode & S_IXOTH)
		list->mode[9] = 'x';
	if (OP_L == 1)
		get_info(list, &buf);
	free(file);
	return (dir);
}

void				ft_print_ls(t_data *list, t_fol fol)
{
	while (list->next != NULL)
	{
		ft_printf("%s ", list->mode);
		while(list->lklen++ <= fol.lklen + 1)
			write(1, " ", 1);
		ft_printf("%lu ", list->links);
		while (++list->usrlen <= fol.usrlen + 1)
			write(1, " ", 1);
		ft_printf("%s ", list->usr);
		while (++list->grplen <= fol.grplen + 1)
			write(1, " ", 1);
		ft_printf("%s ", list->grp);
		while(++list->byteslen <= fol.byteslen + 1)
			write(1, " ", 1);
		ft_printf("%u %s\n", list->bytes, list->name);
		list = list->next;
	}
}

void				ft_recursive(t_data *list, char options[6], char *path)
{
	DIR *dirp;
	char *npath;

	while (list)
	{
		if (list->mode[0] == 'd' && !(list->name[0] == '.' && (list->name[1] == '.' || list->name[1] == 0)))
		{
			write(1, "\n", 1);
			npath = ft_strjoin3(path, "/", list->name);
			dirp = opendir(npath);
			ft_parse_ls(dirp, options, npath);
			closedir(dirp);
			free(npath);
		}
		list = list->next;
	}
}

void				freelist(t_data *list, char options[6])
{
	t_data *tmp;

	while (list->next)
	{
		if (OP_L == 1)
		{
			free(list->usr);
			free(list->grp);
		}
		free(list->name);
		tmp = list;
		list = list->next;
		free(tmp);
	}
	free(list);
}

int					ft_parse_ls(DIR *dirp, char options[6], char *path)
{
	struct dirent	*entry;
	int				dir;
	t_data			*list;
	t_fol			fol;
	
	dir = 0;
	fol.tblocks = 0;
	if ((list = (t_data *)malloc(sizeof(t_data))) == NULL)
			return (-1);
	list->next = NULL;
	fol.start = list;
	ft_printf("%s :\n", path);
	while ((entry = readdir(dirp)) != NULL)
	{
		ft_bzero(list->mode, 11);
		memset(list->mode, '-', 10);
		if (entry->d_name[0] == '.' && OP_A == 0)
			;
		else
		{
			dir += ft_rec_mode(list, entry, path, options);
			fol.tblocks += list->blocks;
			if ((list->next = (t_data *)malloc(sizeof(t_data))) == NULL)
				return (-1);
			list = list->next;
			list->next = NULL;
		}
	}
	ft_printf("total %lu\n", fol.tblocks);
	//ft_sort_data(list);
	ft_print_ls(fol.start, fol);
	if (dir != 0 && fol.start != NULL && OP_RR == 1)
		ft_recursive(fol.start, options, path);
	freelist(fol.start, options);
	return (0);
}

int				main(int ac, char **av)
{
	DIR			*dirp;
	char		*path;
	char		options[6];
	int			arg;

	arg = 0;
	ft_bzero(options, 6);
	if ((path = (char *)malloc(2)) == NULL)
		return (1);
	strcpy(path, ".");
	if (ac > 1 && av[1][0] == '-')
		get_option(av[1], options);
	if (ac > 1)
		arg = parse_av(options, av, path);
	if (arg == 0)
	{
		dirp = opendir(path);
		ft_parse_ls(dirp, options, path);
		closedir(dirp);
	}
	free(path);
	return (0);
}
