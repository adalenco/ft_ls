#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void		ft_putstr(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	write(1, str, i);
}

void		ft_bzero(char *str, int n)
{
	int		i = 0;

	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

size_t		ft_strlen(char *s)
{
	size_t i;

	i = 0;
	while(s[i])
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if ((dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))) == NULL)
		return (NULL);
	while (s1[j])
	{
		dest[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char		*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	if ((dest = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1))) == NULL)
		return (NULL);
	while (s1[j])
	{
		dest[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[j])
	{
		dest[i] = s3[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}