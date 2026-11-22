int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	//Erro 1
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
			if (dup2(fd[1], STDOUT_FILENO) == -1)
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
		}
		else
		{
			if (dup2(fd[0], STDIN_FILENO) == -1)
			{
				close(fd[0]);
				close(fd[1]);
				return (-1);
			}
		}
		close(fd[0]);
		close(fd[1]);
		execvp(file, argv);
		exit(1)
	}
	else
	{
		if (type == 'r')
		{
			//2. Erro
			close(fd[0]);
			return (fd[1]);
		}
		else
		{
			// 3. Erro
			close(fd[1]);
			return (fd[0]);
		}
	}
}