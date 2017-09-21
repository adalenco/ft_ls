#include "ft_ls.h"



int	ft_rec_mode(t_list *list, struct dirent *entry)
{
	struct stat  buf;
	int   dir;

	dir = 0;
	stat(entry->d_name, &buf);
	list->size = (unsigned int)buf.st_size;
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
	/*if (buf.st_mode & S_IRGRP)
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
		list->mode[9] = 'x';*/
	return (dir);
}

void	ft_print_ls(t_list *list)
{
	while (list->next != NULL)
	{
		printf("%-15s%-20u%s\n", list->mode, list->size, list->name);
		list = list->next;
	}
}

void	ft_recursive(t_list *start, char options[6], char *path)
{
	DIR *dirp;
	char *npath;

	while (start)
	{
		if (start->mode[0] == 'd')
		{
			if (npath)
				free(npath);
			npath = ft_strjoin3(path, "/", start->name);
			dirp = opendir(npath);
			ft_parse_ls(dirp, options, npath);
			closedir(dirp);
		}
		start = start->next;
	}
}

int		ft_parse_ls(DIR *dirp, char options[6], char *path)
{
	struct dirent *entry;
	int			dir;
	t_list		*list;
	t_list		*start;
	t_list		*tmp;
	
	dir = 0;
	if ((list = (t_list *)malloc(sizeof(t_list))) == NULL)
			return (-1);
	list->next = NULL;
	start = list;
	printf("%s :\n", path);
	while ((entry = readdir(dirp)) != NULL)
	{
		ft_bzero(list->mode, 11);
		memset(list->mode, '-', 10);
		if (entry->d_name[0] == '.' && OP_A == 0)
			;
		else
		{
			dir += ft_rec_mode(list, entry);
			if ((list->next = (t_list *)malloc(sizeof(t_list))) == NULL)
				return (-1);
			list = list->next;
			list->next = NULL;
		}
	}
	//ft_sort_list(list);
	ft_print_ls(start);
	if (dir != 0 && start != NULL && OP_RR == 1)
		ft_recursive(start, options, path);
	while (start)
	{
		tmp = start;
		start = start->next;
		free(tmp);
	}
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
	if (ac > 1 && av[1][0] == '-')
		get_option(av[1], options);
	if (ac > 1)
		arg = parse_av(options, av);
	if (arg == 0)
	{
		if ((path = (char *)malloc(2)) == NULL)
			return (1);
		strcpy(path, ".");
		dirp = opendir(path);
		ft_parse_ls(dirp, options, path);
		closedir(dirp);
	}
	return (0);
}