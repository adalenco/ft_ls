#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define OP_L (options[0])
# define OP_RR (options[1])
# define OP_A (options[2])
# define OP_R (options[3])
# define OP_T (options[4])

typedef struct s_struct
{
	
}				t_struct;

typedef	struct		s_list
{
	char			mode[11];
	char			*name;
	unsigned int	size;
	void			*next;
}					t_list;

char		*parse_av(char *options, char **av);
void		ft_putstr(char *str);

#endif