#include <errno.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	between_quo_extra(char line, int *flag, int *flag2, char s)
{
	if (line != s && *flag2 == 0)
	{
		*flag2 = 1;
	}
	else if (line != s && *flag2 == 1)
	{
		*flag2 = 0;
	}
	else
		*flag = 0;
}

int	create_file_dumb(char *cmd_name, char *cmd, int i)
{
	int	fd;

	if (i > 0 && cmd[i - 1] == '>')
	{
		i--;
		fd = open(cmd_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
		fd = open(cmd_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	close(fd);
	return (i);
}

size_t	ft_strlen(const char *ch)
{
	int	i;

	i = 0;
	while (ch[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	between_quo(char *line, int x)
{
	int		i;
	int		flag;
	int		flag2;
	char	s;

	i = 0;
	flag = 0;
	flag2 = 0;
	while (line[i] != '\0')
	{
		if (flag == 0 && (line[i] == '"' || line[i] == 39))
		{
			s = line[i];
			flag = 1;
		}
		else if (flag == 1 && (line[i] == '"' || line[i] == 39))
		{
			between_quo_extra(line[i], &flag, &flag2, s);
		}
		if (i == x)
			return (flag);
		i++;
	}
	return (0);
}

void	create_dumby_files(char *cmd)
{
	int		i;
	int		j;
	int		x;
	char	*file_name;

	i = ft_strlen(cmd);
	while (i >= 0)
	{
		j = 0;
		if (cmd[i] == '>' && between_quo(cmd, i) == 0)
		{
			x = i + 1;
			file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			while (cmd[x] == ' ')
				x++;
			while (cmd[x] != ' ' && cmd[x] != '\0')
				file_name[j++] = cmd[x++];
			file_name[j] = '\0';
			i = create_file_dumb(file_name, cmd, i);
			free(file_name);
		}
		i--;
	}
}

char	*get_filename_pos(char *cmd, int i)
{
	int		j;
	char	*file_name;

	j = 0;
	while (i >= 0)
	{
		if (cmd[i] == '<' && between_quo(cmd, i) == 0)
		{
			i++;
			file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
			while (cmd[i] == ' ')
				i++;
			while (cmd[i] != ' ' && cmd[i] != '\0')
			{
				file_name[j++] = cmd[i++];
			}
			file_name[j] = '\0';
			return (file_name);
		}
		i--;
	}
	return (NULL);
}

char	**here_maker(char *cmd)
{
	int		i;
	int		j;
	char	**names;

	i = 0;
	j = ft_strlen(cmd) - 1;
	names = malloc(sizeof(char *) * (j + 2));
	while (j >= 0)
	{
		if (cmd[j] == '<' && between_quo(cmd, j) == 0)
		{
			j--;
			if (cmd[j] == '<')
				names[i++] = get_filename_pos(cmd, j + 1);
		}
		j--;
	}
	names[i] = NULL;
	return (names);
}

char	*ft_strdup(const char *src)
{
	char	*st;
	int		i;

	i = 0;
	st = (char *)malloc(ft_strlen(src) + 5);
	if (!st)
		return (NULL);
	while (src[i])
	{
		st[i] = (char)src[i];
		i++;
	}
	st[i] = '\0';
	return ((char *)st);
}

char	*env_key(char *cmd)
{
	int		i;
	int		j;
	char	*file_name;

	i = 0;
	file_name = malloc(sizeof(char) * (ft_strlen(cmd) + 5));
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '=')
		{
			file_name[i] = '\0';
			return (file_name);
		}
		file_name[i] = cmd[i];
		i++;
	}
	file_name[i] = '\0';
	return (file_name);
}

char	*bulid_env(char *key_env, char *path)
{
	int		i;
	int		j;
	char	*env;

	i = 0;
	while (path[i] != '=' && path[i] != '\0')
		i++;
	if (path[i] == '\0' || path[i] == ' ')
	{
		j = ft_strlen(key_env);
		key_env[j++] = '=';
		key_env[j] = '\0';
		return (key_env);
	}
	free(key_env);
	return (ft_strdup(path));
}

int	between_sq(char *cmd, int j)
{
	int	i;
	int	state;
	int	state2;

	i = 0;
	state = 0;
	state2 = 0;
	while (cmd[i] != '\0' && i <= j)
	{
		printf("%d\n", state);
		if (cmd[i] == '\"')
			state++;
		if (cmd[i] == '\'')
		{
			if (state % 2 == 0)
				state2 = 1;
			else
				state2 = 0;
		}
		i++;
	}
	return (state2);
}

int	between_state(int state)
{
	if (state == 0)
		state = 1;
	else
		state = 0;
	return (state);
}

int	between(char *cmd, int j)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	i[3] = 0;
	while (cmd[i[0]] != '\0' && i[0] <= j)
	{
		if (cmd[i[0]] == '\"')
			i[1] = between_state(i[1]);
		if (cmd[i[0]] == '\'')
			i[2] = between_state(i[2]);
		if (cmd[i[0]] == '\'' || cmd[i[0]] == '\"')
			i[3]++;
		if (i[0] == j)
		{
			if (i[3] != 1 && (i[2] == 1 || i[1] == 1))
				return (0);
			return (1);
		}
		if (i[1] == 0 && i[2] == 0)
			i[3] = 0;
		i[0]++;
	}
	return (05);
}

int	between2(char *cmd, int j)
{
	int	i[4];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (cmd[i[0]] != '\0' && i[0] <= j)
	{
		if (cmd[i[0]] == '\"')
			i[1] = between_state(i[1]);
		if (cmd[i[0]] == '\'')
			i[2] = between_state(i[2]);
		if (i[0] == j)
		{
			if ((i[2] == 1 || i[1] == 1))
				return (0);
			return (1);
		}
		i[0]++;
	}
	return (05);
}

int	check_dq(char *cmd)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\"' && between2(cmd, i) == 0)
			counter++;
		i++;
	}
	printf("%d\n", counter);
	if (counter % 2 == 0)
		return (0);
	else
		return (1);
	return (0);
}

int	redir_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '>' && cmd[i + 1] == '>' && cmd[i + 2] == '>')
			return (1);
		if (cmd[i] == '<' && cmd[i + 1] == '<' && cmd[i + 2] == '<')
			return (1);
		i++;
	}
	return (0);
}

int	redir_check2(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '>')
		{
			i++;
			if (cmd[i] == '>')
				i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
				|| cmd[i] == '|')
				return (1);
		}
		if (cmd[i] == '<')
		{
			i++;
			if (cmd[i] == '<')
				i++;
			while (cmd[i] == ' ')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '>' || cmd[i] == '<'
				|| cmd[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	pipe_check(char *cmd)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < ft_strlen(cmd) && cmd[i] != '\0')
	{
		if (cmd[i] != '\0' && cmd[i] != '>' && cmd[i] != '<' && cmd[i] != '|'
			&& cmd[i] != ' ')
			flag = 1;
		if (cmd[i] == '|')
		{
			i++;
			if (flag == 0)
				return (1);
			while (cmd[i] == ' ' || cmd[i] == '>' || cmd[i] == '<')
				i++;
			if (cmd[i] == '\0' || cmd[i] == '|')
				return (1);
			flag = 0;
		}
		i++;
	}
	return (0);
}

int	main(void)
{
	// char *here = ft_strdup("lolgg");
	// char *pth = ft_strdup("lolgg=joke");
	// char *cd = bulid_env(here, pth);
	// // free(here);
	// free(pth);
	// printf("%s\n", cd);
	// free(cd);
	printf("%d\n", pipe_check("ls|ra|<<"));
	return (0);
}