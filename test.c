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

int	main(void)
{
	char *here = ">> here >> ggg > why? ls";
	create_dumby_files(here);
	return (0);
}