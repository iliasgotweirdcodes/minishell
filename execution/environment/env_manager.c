/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:03:37 by aromani           #+#    #+#             */
/*   Updated: 2025/04/24 13:13:16 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while (st1[i] || st2[i])
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
	}
	return (0);
}

int export_parcer(char *str, t_gc **exec)
{
    int i = 0;
    int j = 0;
    int e = 0;
    int e_index;
    char *key;

    e_index = get_eqindex(str, '=');
    key = ft_strndup2(str, e_index , exec);
    i = 0;
    while (key[i])
    {
        if (key[i] == '+')
            e++;
        else if (!(key[i] >= 0 && key[i] <= 9) && !(key[i] >= 'a' && str[i] <= 'z') && !(key[i] >= 'A' && str[i] <= 'Z') && str[i] != '+')
            j++;
        i++;
    }
    if (j != 0 || e > 1)
        return (0);
    return (1);
}

size_t len(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (i);
    while (str[i])
        i++;
    return (i);
}

char	*ft_strjoinv3(char *s1, char*s2,t_gc **exec)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_malloc(len(s1) + len(s2) + 1, exec);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

int is_appended(char *str, char sep)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            return (0);
        i++;
    }
    return (1);
}

int is_key(t_env **env, char *key_val, t_gc **exec)
{
    t_env *get;
    int eq_index;
    char *key;

    eq_index = get_eqindex(key_val, '=');
    key = ft_strndup2(key_val, eq_index , exec);
    get = *env;
    while (get)
    {
        if (ft_strcmp(get->key, key) == 0)
            return (0);
        get = get->next;
    }
    return (1);
}

void ft_append(t_env **env, char *key_val,t_gc **exec)
{
    t_env *get;
    int eq_index;
    char *key;
    char *val;

    eq_index = get_eqindex(key_val, '=');
    key = ft_strndup2(key_val, eq_index - 1, exec);
    val = ft_strdup2(key_val + eq_index + 1, exec);
    get = *env;
    while (get)
    {
        if (ft_strcmp(get->key, key) == 0)
            get->value = ft_strjoinv3(get->value, val, exec);
        get = get->next;
    }
}

void ft_changeval(t_env **env, char *key_val, t_gc **exec)
{
    t_env *get;
    int eq_index;
    char *key;
    char *val;

    eq_index = get_eqindex(key_val, '=');
    key = ft_strndup2(key_val, eq_index, exec);
    val = ft_strdup2(key_val + eq_index + 1, exec);
    get = *env;
    while (get)
    {
        if (ft_strcmp(get->key, key) == 0)
            get->value = ft_strdup2(val, exec);
        get = get->next;
    }
}
// env _converter to get path as **
int ft_sizer(t_env *env)
{
	t_env	*tmp;
	size_t	i;

    i =0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
char **env_converter(t_env **env,t_gc **exec)
{
	char	**new_env;
	t_env	*tmp;
	int		i;
	
	new_env = ft_malloc((ft_sizer(*env) + 1) * sizeof(char *), exec);
	if (!new_env)
		return (NULL);
	i = 0;
	tmp = *env;
	while (tmp)
	{
		new_env[i] = ft_strjoinv3(ft_strjoinv3(tmp->key, "=", exec),tmp->value, exec);
		if (!new_env[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}
 // ///////////////////////////////////////////////////////////////////////////////////////
void add_varenv(t_env **env, char *key_val, t_gc **exec)
{
    int eq_index;
    char *key;
    char *value;

    if (export_parcer(key_val, exec) == 0)
    {
        write (1,"error\n",6);
        return ;
    }
    if (is_appended(key_val, '+') == 0)
        ft_append(env, key_val, exec);
    else if (is_key(env,key_val, exec) == 0)
            ft_changeval(env, key_val, exec);
    else
    {
            eq_index = get_eqindex(key_val, '=');
            key =ft_strndup2(key_val, eq_index, exec);
            value = ft_strdup2(key_val + eq_index + 1, exec);
            env_fill(env, &key, &value, exec);
    }
}
