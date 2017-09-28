#include "libft.h"

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
