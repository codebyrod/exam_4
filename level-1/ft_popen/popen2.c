int ft_popen(const char *file, char *const argv[], char type)
{
	
	int		fd[2];
	pid_t	pid;

	//Erro 1. O certo é verificar se o type é diferente de r e w
	if (!file || !argv || !argv[0] || (type == 'r' && type == 'w'))
		return (-1);

	if (pipe(fd) == -1)
		return (-1);

	pid = fork();

	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
		{
			//2. Errei o fd[0], o correto seria o fd[1]
			if (dup2(fd[0], STDOUT_FILENO))
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
		}
		else
		{
			//3. Errei o fd[1], na vdd é o fd[0]
			if (dup2(fd[1], STDIN_FILENO))
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
		}
	close(fd[0]);
	close(fd[1]);
	execvp(file, argv);
	exit(1);

	}
	else
	{
		if (type == 'r')
		{
			close(fd[1]);
			//4. Errei  retorno, o certo é fd[0]
			return (-1);
		}
		else
		{
			close(fd[0]);
			//5. Errei o retorno, o certo é fd[1]
			return (-1);
		}
	}

}