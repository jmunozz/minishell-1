#include "libft.h"

size_t	ft_strtabtotallen(char	**tab)
{
	size_t len;

	len = 0;
	while (*tab)
	{
		len += ft_strlen(*tab);
		++tab;
	}
	return (len);
}

char	*ft_strtabchrjoin(char **tab, char c)
{
	size_t	len;
	char	*result;

	if (!(len = ft_strtabtotallen(tab))
		|| !(result = ft_memalloc(len + (c ? ft_strtablen(tab) : 0) + 1)))
		return (NULL);
	len = 0;
	while (*tab)
	{
		ft_strcpy(result + len, *tab);
		len += ft_strlen(*tab);
		if (c)
		{
			result[len] = c;
			++len;
		}
		++tab;
	}
	return (result);
}
