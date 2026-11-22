int ft_popen(const char *file, char *const argv[], char type)
{
	//declaração dos itens
	int	fd[2];
	pid_t pid;

	//verificação das entradas
	if (!file || !argv || !argv[0] || (type == 'r' && type == 'w'))
		return (-1);

	//cria o pipe
	//Erros: 1
	if (pipe(pipefd) < 0) //ERRADO, o certo é verificar o retorno com -1
		return (-1);
	
	//cria o fork

	pid = fork();

	if (pid < 0)
	{
		close(fd[0]);
		//Erros: 2
		//esqueci de fechar o outro fd
		return (-1);
	}

	if (pid == 0)
	{
		if (type == 'r')
		{
			//Erros: 3
			if (dup2(STDOUT_FILENO, fd))// errei isso
			// if (dup2(fd[1], STDOUT_FILENO)) -> correto
			{
				close(fd[1]);
				//Erros: 4
				//esqueci de fechar o outro fd
				return (-1);
			}

		}
		else
		{
			//Erros: 5
			if (dup2(STDIN_FILENO, fd)) //aqui tá errado
			// if (dup2(fd[0], STDIN_FILENO)) -> CORRETO
			{
				close(fd[1]);
				//Erros: 6
				//aqui tem outro fd pra fechar
				return (-1);
			}
		}
		close(fd[0]);
		close(fd[1]);
		//Erros: 7
		// execvp(file, argv); -> CORRETO
		execvp(pip, fd); //aqui tem o erro dos parametros

		exit(1);
	}
	else
	{
		if (type == 'r')
		{
			//ESSE IF INTEIRO TÁ ERRADO
			//Erros: 8
			if (dup2(STDOUT_FILENO, fd))
			{
				//Erros: 9
				close(fd[0]);
				//Erros: 10
				return (-1);
			}

			//close(fd[1])
			// return (fd[0]);
		}
		else
		{
			//ESSE IF INTEIRO ESTÁ ERRADO
			//Erros: 11
			if (dup2(STDIN_FILENO, fd))
			{
				//Erros: 12
				close(fd[1]);
				//Erros: 13
				return (-1);
			}
			//close(fd[0]);
			// return (fd[1]);
		}
	}
}

int main(void)
{
    int  fd;
    char c;

    fd = ft_popen("ls", (char *const[]){"ls", NULL}, 'r');
    if (fd < 0)
        return (1);
    while (read(fd, &c, 1) > 0)
        write(1, &c, 1);
    close(fd);
    return (0);
}