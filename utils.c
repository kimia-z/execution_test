#include "mini.h"

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
