#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define OP_L options[0]
# define OP_RR options[1]
# define OP_A options[2]
# define OP_R options[3]
# define OP_T options[4]

typedef struct s_struct
{
	char		options[6];
	char		*path;
}				t_struct;

typedef	struct		s_list
{
	char			mode[11];
	char			*name;
	unsigned int	size;
	void			*next;
}					t_list;

int			parse_av(char *options, char **av);
void		get_option(char *op, char options[6]);
void		ft_putstr(char *str);
int			ft_parse_ls(DIR *dirp, char options[6], char *path);
void		ft_bzero(char *str, int n);
char		*ft_strjoin(char *s1, char *s2);
size_t		ft_strlen(char *s);
char		*ft_strjoin3(char *s1, char *s2, char *s3);

#endif