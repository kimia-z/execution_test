#include "mini.h"

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int	ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d_len;
	size_t	s_len;

	d_len = 0;
	while (d_len < size && dst[d_len] != 0)
		d_len++;
	if (d_len == size)
		return (size + ft_strlen(src));
	s_len = ft_strlcpy(dst + d_len, src, size - d_len);
	return (d_len + s_len);
}

static unsigned int	num_of_substrings(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
	}
	return (i);
}

static char	*create_substrings(char const *s, char c)
{
	char	*string;
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[len] && s[len] != c)
		len++;
	string = malloc (len + 1);
	if (!string)
		return (NULL);
	while (i < len)
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static void	free_things(char **ptr)
{
	unsigned int	i;

	i = 0;
	if (ptr)
	{
		while (ptr[i])
		{
			free(ptr[i]);
			i++;
		}
	}
	free(ptr);
}

char	**fill_substrings(char const *s, char **str, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			str[i] = create_substrings(s, c);
			if (str[i] == NULL)
			{
				free_things(str);
				return (NULL);
			}
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char		**ptr;

	ptr = ft_calloc(sizeof(char *), (num_of_substrings(s, c)) + 1);
	if (!ptr)
		return (NULL);
	return (fill_substrings(s, ptr, c));
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	size_t	total_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, total_len + 1);
	ft_strlcat(result, s2, total_len + 1);
	return (result);
}

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;
	size_t	total;

	total = nmemb * size;
	if (nmemb && (total / nmemb) != size)
	{
		return (NULL);
	}
	if ((long) nmemb < 0 || (long) size < 0)
		return (0);
	new = malloc(nmemb * size);
	if (new == NULL)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		((unsigned char *)s)[n - 1] = '\0';
		n--;
	}
}

char	*ft_strchr(const char *s, int c)
{
	char			*string;
	unsigned char	value;
	if (!s)
		return (NULL);
	string = (char *)s;
	value = c;
	while (*string != value && *string != '\0')
		string++;
	if (*string == value)
		return (string);
	else
		return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;

	new_s = malloc(ft_strlen(s) + 1);
	if (new_s == NULL)
		return (NULL);
	ft_strlcpy(new_s, s, ft_strlen(s) + 1);
	return (new_s);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i + 1 < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (i < size)
	{
		dst[i] = '\0';
	}
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strtrim_beginning(char const *s1, char const *set)
{
	char	*new_s1;
	int		start;
	int		end;
	int		new_len;

	start = 0;
	end = ft_strlen(s1) -1;
	while ((s1[start] != '\0' && s1[start] == set[start])
		|| s1[start] == ' ')
		start++;
	start++;
	new_len = end - start + 2;
	new_s1 = (char *)malloc(sizeof(char) * new_len);
	if (new_s1 == NULL)
		return (NULL);
	ft_strlcpy(new_s1, s1 + start, new_len);
	return (new_s1);
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

static t_env	*new_env(char *env)
{
	t_env	*env_list;
	char	*temp;
	int		i;

	env_list = malloc(sizeof(t_env));
	if (env_list == NULL)
		return (ft_putstr_fd("Erro to create env node\n", 2), NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	env_list->key = ft_calloc(sizeof(char), i + 1);
	if (env_list->key == NULL)
		return (free(env_list), NULL);
	ft_strlcpy(env_list->key, env, (i + 1));
	temp = ft_strtrim_beginning(env, env_list->key);
	env_list->value = ft_strdup(temp);
	free(temp);
	env_list->next = NULL;
	return (env_list);
}

static void	add_env_back(t_env **head, void *content)
{
	t_env	*current_node;
	t_env	*new_node;

	current_node = *head;
	while (current_node->next != NULL)
	{
		current_node = current_node->next;
	}
	new_node = new_env(content);
	current_node->next = new_node;
}

t_env	*initial_env(char **env)
{
	t_env	*env_list;
	int		i;

	env_list = new_env(env[0]);
	if (env_list == NULL)
		return (NULL);
	i = 1;
	while (env[i] != NULL)
	{
		add_env_back(&env_list, env[i]);
		i++;
	}
	return (env_list);
}

void	free_env_list(t_env *head)
{
	t_env	*temp;
	t_env	*change;

	temp = head;
	if (head == NULL)
		return ;
	while (temp != NULL)
	{
		free(temp->key);
		free(temp->value);
		change = temp->next;
		free(temp);
		temp = change;
	}
}

int	ft_strchr_pos(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != (unsigned char)c)
		i++;
	if (s[i] == (unsigned char)c)
		return (i);
	return (0);
}

char	*ft_strcharjoin(char *s1, char s2)
{
	char	*s;
	size_t	len;

	len = 3;
	if (s1 != NULL)
		len += ft_strlen(s1);
	s = ft_calloc(sizeof(char), len);
	if (s == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_strcat(s, s1);
	ft_strcharcat(s, s2);
	return (s);
}


void	free_2arr(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

char	*ft_strcharcat(char *dest, const char src)
{
	int	i;

	i = 0;
	while (dest[i] != '\0')
		i++;
	dest[i] = src;
	dest[i + 1] = '\0';
	return (dest);
}
