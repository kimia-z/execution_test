#include "mini.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	if (s1p == 0 && s2p == 0)
		return (0);
	while (n > 0 && *s1p && *s2p && (*s1p == *s2p))
	{
		s1p++;
		s2p++;
		n--;
	}
	if (n == 0 || (*s1p == '\0' && *s2p == '\0'))
		return (0);
	else
		return (*s1p - *s2p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;
	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s == 0)
		return ;
	while (s[i] != 0)
		i++;
	write(fd, s, i);
	write(fd, "\n", 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == 0 || *s == 0)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

