#include "mini_parser.h"

char	*env_test(char *str, int i, int end)
{
	char *tmp;

	tmp = ft_substr(str, i, end - i + 1);
	if ((ft_strncmp(tmp, "ENV", ft_strlen(tmp)) == 0)
			&& (ft_strlen(tmp) == ft_strlen("ENV")))
	{
		free(tmp);
		return (ft_strdup("enviroment"));
	}
	free(tmp);
	return (NULL);
}

/* int		main(void)
{
	char *str;
	int i;
	char *tmp, *tmp2, *env, *old;
	int j, end, st;

	str = ft_strdup("eto 21 detka $ENV\"Testing $ENV to str\" neujele $ENV");
	i = 0;
	st = 0;
	printf("before - [%s]\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			i++;
			j = i;
			old = ft_substr(str, 0, i - 1);
			printf("old - %s\n", old);
			while (str[i] != '\"')
			{
				if (str[i] == '$')
				{
					end = i;
					tmp = ft_substr(str, j, end - 1);
					i++;
					while (str[i] != ' ' && str[i] != '\'' && str[i] != '\"'
							&& str[i] != '\\' && str[i] != '$')
							i++;
					//printf("[%c] & [%c]\n", str[end], str[i]);
					tmp2 = ft_substr(str, i, ft_strlen(str) - i - 1);
					env = env_test(str, end + 1, i - 1);
					//printf("tmp - [%s]\nenv - [%s]\ntmp2 - [%s]\n", tmp, env, tmp2);
					tmp = ft_strjoin(tmp, env);
					tmp = ft_strjoin(tmp, tmp2);
					printf("new \" - [%s]\n", tmp);
					free(env);
					//free(tmp);
					free(tmp2);
					//free(str);
					//return (0);
				}
				i++;
			}
			end = i;
		}
		i++;
	}
	//tmp2 = ft_substr(str, end, ft_strlen(str) - end);
	//str = ft_strjoin(old, tmp);
	str = ft_strjoin(old, tmp); 
	free(tmp);
	free(old);
	free(tmp2);
	printf("after - [%s]\n", str);
	free(str);
	return (0);
} */

int		main(void)
{
	char *str;
	int i;
	char *tmp, *tmp2, *env, *old;
	int j, end, st;

	str = ft_strdup("eto 21 detka $ENV\"Testing $ENV to str\" neujele $ENV");
	i = 0;
	st = 0;
	printf("before - [%s]\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
		{
			j = i;
			old = ft_substr(str, 0, i);
			printf("old - %s\n", old);
			while (str[++i] != '\"')
			{
				if (str[i] == '$')
					st = 1;
			}
			tmp = ft_substr(str, j, i - j + 1);
			printf("tmp - %s\n", tmp);
		}
		i++;
	}
	//tmp2 = ft_substr(str, end, ft_strlen(str) - end);
	//str = ft_strjoin(old, tmp);
	////str = ft_strjoin(old, tmp); 
	free(tmp);
	free(old);
	//free(tmp2);
	//printf("after - [%s]\n", str);
	free(str);
	return (0);
}