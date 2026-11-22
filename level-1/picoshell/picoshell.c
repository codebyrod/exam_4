#include <unistd.h>     // fork, execvp, pipe, dup2, close
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // wait, WIFEXITED, WEXITSTATUS
#include <stdlib.h>     // exit

int picoshell(char **cmds[])
{
    int     prev_fd = -1;   // read end of the previous pipe
    int     pipefd[2];
    int     i = 0;
    int     ret = 0;        // 0 = success, 1 = error
    int     status;

    // validação dos parâmeros
    if (cmds == NULL || cmds[0] == NULL)
        return (0);

    while (cmds[i] != NULL)
    {
        // se houver um próximo comando, precisamos de um pipe
        if (cmds[i + 1] != NULL)
        {
            if (pipe(pipefd) == -1)
            {
                ret = 1;
                break;
            }
        }
        else // último comando: nenhum pipe é criado
        {
            pipefd[0] = -1;
            pipefd[1] = -1;
        }

        pid_t pid = fork();
        if (pid < 0) // verifica se o fork falhou
        {
            if (pipefd[0] != -1)
                close(pipefd[0]);
            if (pipefd[1] != -1)
                close(pipefd[1]);
            ret = 1;
            break;
        }
        if (pid == 0) // processo filho
        {
            // conecte o stdin ao pipe anterior, caso ele exista
            if (prev_fd != -1)
            {
                if (dup2(prev_fd, STDIN_FILENO) == -1)
                    exit(1);
            }

            // connect stdout to current pipe if there is a next command
			//conecte o stdout ao pipe atual, caso exista um próximo comando
            if (cmds[i + 1] != NULL)
            {
                if (dup2(pipefd[1], STDOUT_FILENO) == -1)
                    exit(1);
            }

            // close unused file descriptors in the child
			// fechar descritores de arquivo não utilizados no filho
            if (prev_fd != -1)
                close(prev_fd);
            if (cmds[i + 1] != NULL)
            {
                close(pipefd[0]);
                close(pipefd[1]);
            }

            execvp(cmds[i][0], cmds[i]);
            exit(1); // se execvp falhou
        }
        // processo pai

        // previous read end is no longer needed by the parent
		// o final da leitura anterior não é mais necessário para o elemento pai
        if (prev_fd != -1)
            close(prev_fd);

        if (cmds[i + 1] != NULL)
        {
            // parent keeps read end for the next command
			// o processo pai mantém a extremidade de leitura aberta para o próximo comando

			// A escrita final só é necessária no filho
            close(pipefd[1]);      // write end is only needed in the child

			// a extremidade de leitura torna-se prev_fd
            prev_fd = pipefd[0];   // read end becomes prev_fd
        }
        else
        {
            prev_fd = -1;
        }
        i++;
    }

    // close last prev_fd if still open
	// fecha o último prev_fd, caso ainda esteja aberto
    if (prev_fd != -1)
        close(prev_fd);

	// aguardar todos os filhos
    while (wait(&status) > 0) // wait for all children
    {
        if (WIFEXITED(status) == 0 || WEXITSTATUS(status) != 0)
            ret = 1;
    }
    return ret;
}


#pragma region Test code

#include <stdio.h>
int main(void)
{
    char *cmd1[] = {"/bin/ls", "level-1", NULL};
    // char *cmd1[] = {"/bin/ls", NULL};
    char *cmd2[] = {"/usr/bin/grep", "picoshell", NULL};
    char **cmds[] = {cmd1, cmd2, NULL};

    int result = picoshell(cmds);
    printf("picoshell returned %d\n", result);

    return 0;
}
#pragma endregion
