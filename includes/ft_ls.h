#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"
# include "ft_printf.h"
# define OP_L options[0]
# define OP_RR options[1]
# define OP_A options[2]
# define OP_R options[3]
# define OP_T options[4]

typedef	struct			s_data
{
	char				mode[11];
	char				*name;
	char				*usr;
	size_t				usrlen;
	char				*grp;
	size_t				grplen;
	unsigned int		bytes;
	size_t				byteslen;
	unsigned long int	links;
	size_t				lklen;
	unsigned long int	blocks;
	void				*next;
}						t_data;

typedef struct			s_fol
{
	size_t				usrlen;
	size_t				grplen;
	size_t				byteslen;
	size_t				lklen;
	char				*path;
	unsigned long int	tblocks;
	t_data				*start;
}						t_fol;

int						parse_av(char *options, char **av, char *path);
void					get_option(char *op, char options[6]);
int						ft_parse_ls(DIR *dirp, char options[6], char *path);
char					*ft_strjoin3(char *s1, char *s2, char *s3);

#endif
