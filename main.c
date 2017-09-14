#include "ft_ls.h"

void		ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

void		b_zero(char *str, int n)
{
	int		i = 0;

	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

void		ft_print_ls(DIR *dirp, char options[6])
{
	struct dirent *entry;
	struct stat buf;
	int			dir;
	
	dir = 0;
	printf("%-15s      name\n%-15s%s\n\n", "size", "----", "      ----");
	while ((entry = readdir(dirp))  != NULL)
	{
		if (entry->d_name[0] == '.' && OP_A == 0)
			;
		else
		{
			stat(entry->d_name, &buf);
			printf("%-15u", (unsigned int)buf.st_size);
			if (S_ISDIR(buf.st_mode))
			{
				dir++;
				printf("d     ");
			}
			else
				printf("      ");
			printf(entry->d_name);
			printf("\n");
		}
	}
}

int			main(int ac, char **av)
{
	DIR *dirp;

	int		i;
	char	options[6];
	char		*path;
	char		mode[11];

	path = "./";
	b_zero(options, 6);
	b_zero(mode, 11);
	i = 0;
	if (ac > 1)
		parse_av(options, av);
	dirp = opendir(path);
	ft_print_ls(dirp, options);
	
	closedir(dirp);
	return (0);
}