/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aromani <aromani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:03:37 by aromani           #+#    #+#             */
/*   Updated: 2025/05/09 22:35:58 by aromani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"
#include <ctype.h>

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t			i;
// 	unsigned char	*st1;
// 	unsigned char	*st2;

// 	i = 0;
// 	st1 = (unsigned char *)s1;
// 	st2 = (unsigned char *)s2;
// 	while (st1[i] || st2[i])
// 	{
// 		if (st1[i] != st2[i])
// 			return (st1[i] - st2[i]);
// 		i++;
// 	}
// 	return (0);
// }

int sep_exist(char *str, char sep)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == sep)
            return (1);
        i++;
    }
    return (0);
}



// int ft_isalnum(int c)
// {
//     if ()
// }

int export_parser(char *str, t_gc **exec)
{
    int i = 0;
    int e = 0;
    int e_index;
    char *key;

    e_index = get_eqindex(str, '=');
    key = ft_strndup2(str, e_index, exec);
    i = 0;
    if (!ft_isalpha(key[i]) && key[i] != '_')
        return (0);
    while (key[i])
    {
        if (key[i] == '+')
            e++;
        if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '+' && key[i] != '=')
            return (0);
        i++;
    }
    if (e == 1 && sep_exist(str,'=') == 0)
        return (0);
    if (e > 1)
        return (0);
    return (1);
}

size_t len(char *str)
{
    size_t i;

    i = 0;
    if (!str)
        return (i);
    while (str && str[i])
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
	if (!str || (!s1 && !s2))
		return (NULL);
    if (!s1)
        return (ft_strdup2(s2,exec));    
    if(!s2)
        return (ft_strdup2(s1,exec));
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
        if (str && str[i] && str[i] == sep && str[i - 1] != '=' && str[i + 1] == '=')
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
    if (!key)
        return (0);
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
    if (!key)
        return ;
    val = ft_strdup2(key_val + eq_index + 1, exec);
    if (!val)
        return ;
    get = *env;
    eq_index = 0;
    while (get)
    {
        if (ft_strcmp(get->key, key) == 0)
        {
            get->value = ft_strjoinv3(get->value, val, exec);
            eq_index++;
        }
        get = get->next;
    }
    if (eq_index == 0)
    {
            key = ft_strndup2(key_val, (size_t)get_eqindex(key_val, '+') , exec);
            if (!key)
                return ;
            val = ft_strdup2("", exec);
            if (!val)
                return ;
        env_fill(env, &key, &val, exec);
    }
}

void ft_changeval(t_env **env, char *key_val, t_gc **exec)
{
    t_env *get;
    int eq_index;
    char *key;
    char *val;

    eq_index = get_eqindex(key_val, '=');
    if (sep_exist(key_val, '=') == 0)
        return ;
    else
    {
        key = ft_strndup2(key_val, eq_index, exec);
        if (!key)
            return ;
        val = ft_strdup2(key_val + eq_index + 1, exec);
        if (!val)
            return ;
    }
    get = *env;
    while (get)
    {
        if (ft_strcmp(get->key, key) == 0)
            get->value = ft_strdup2(val, exec);
        get = get->next;
    }
}
// env _converter to get path as **
// int ft_sizer(t_env *env)
// {
// 	t_env	*tmp;
// 	size_t	i;

//     i =0;
// 	tmp = env;
// 	while (tmp)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	return (i);
// }

size_t ft_sizer(t_env *env)
{
    size_t count = 0;
    while (env)
    {
        if (env->value != NULL)
            count++;
        env = env->next;
    }
    return count;
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
        if (tmp->value != NULL)
        {
		    new_env[i] = ft_strjoinv3(ft_strjoinv3(tmp->key, "=", exec),tmp->value, exec);
            //new_env[i] = ft_strdup2(tmp->key, exec);
		if (!new_env[i])
			return (NULL);
		i++;
        }
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}


 // ///////////////////////////////////////////////////////////////////////////////////////






int add_varenv(t_env **env, char *key_val, t_gc **exec)
{
    int eq_index;
    char *key;
    char *value;

    eq_index = get_eqindex(key_val, '=');
    if (export_parser(key_val, exec) == 0)
    {
        error_printer(ft_strndup2(key_val, eq_index + 1, exec), ": not a valid identifier\n", "export: ");
        //printf("minishell: export: `%s': not a valid identifier\n",ft_strndup2(key_val, eq_index + 1, exec));
        return (-1);
    }
    if (is_appended(key_val, '+') == 0)
        ft_append(env, key_val, exec);
    else if (is_key(env,key_val, exec) == 0)
            ft_changeval(env, key_val, exec);
    else
    {
        if (sep_exist(key_val, '=') == 0)
        {
            key = ft_strdup2(key_val,exec);
            if (!key)
                return (2);
            value = NULL;
        }
        else
        {
            // if (key_val[eq_index - 1] == '+')
            //     key =ft_strndup2(key_val, eq_index - 1, exec);
            // else
            key =ft_strndup2(key_val, eq_index , exec);
            if (!key)
                return (2);
            value = ft_strdup2(key_val + eq_index + 1, exec);
            if (!value)
                return (2);
        }
        env_fill(env, &key, &value, exec);
    }
    return (0);
}
