#include "../../includes/minishell.h"

void	wait_all_processes(t_process *head)
{
	t_process *cur;

    cur = head;
	while (cur)
	{
		waitpid(cur->pid, &cur->status, 0);
		if (WIFEXITED(cur->status))
			cur->exit_signal = WEXITSTATUS(cur->status);
		else if (WIFSIGNALED(cur->status))
			cur->exit_signal = 128 + WTERMSIG(cur->status);
		else
			cur->exit_signal = -1;
		cur = cur->next;
	}
}

void execute_command(t_minishell *mini)
{
    t_exec_vars e;
    t_process   *p;

    ft_memset(&e, -1, sizeof(t_exec_vars));
    
    // 1. Salvar stdin e stdout
    e.tmpin = dup(0);    // salva stdin
    e.tmpout = dup(1);   // salva stdout
    p = mini->process_list;
    mini->exec_vars = e;
    while (p)
    {
        mini->current_process = p;
    
        // 2. Redirecionar a entrada inicial (inputFile ou stdin)
        if (p->fdin == -1)
        {
            if (p->input_file)
                p->fdin = open(p->input_file, O_RDONLY);
            else
                p->fdin = dup(e.tmpin); // entrada padrão
        }

        if (p->output_file)
        {   
            if (p->append_flag)
                p->fdout = open(p->output_file, O_WRONLY | O_CREAT | O_APPEND, 0666);
            else if (p->redirect_out_flag)
                p->fdout = open(p->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        }
        else if (p->next)
        {
            // 3. Criar pipe para o próximo comando
            if (pipe(e.fdpipe) == -1)
            {
                perror("pipe");
                safe_exit(mini);
            }
            if (!p->output_file)
                p->fdout = e.fdpipe[1]; // escrever na saída do pipe
            if (p->next->fdin == -1 && !p->next->input_file)
                p->next->fdin = e.fdpipe[0]; // o próximo comando vai ler daqui
            else
                close(e.fdpipe[0]); // fecha leitura do pipe no pai
        }
        else
            p->fdout = dup(e.tmpout); // saída padrão
        p->pid = fork();
        if (p->pid == 0)
        {
            // 4. Redirecionar entrada e saída
            if (p->fdin != 0)
            {
                dup2(p->fdin, 0); // redireciona stdin
                close(p->fdin);
            }
            if (p->fdout != 1)
            {
                dup2(p->fdout, 1); // redireciona stdout
                close(p->fdout);
            }
            // Processo filho: executar comando
            execve(p->path, p->args, mini->envp_copy);
            perror("execvp");
            exit(1);
        }
        if (p->fdin != -1)
            close(p->fdin); // fecha fdin no pai
        if (p->fdout != -1)
            close(p->fdout); // fecha fdout no pai
        if (p->next && !p->output_file)    
            close(e.fdpipe[1]);

        p = p->next;
    }
    // 8. Restaurar entrada e saída originais
    dup2(e.tmpin, 0);
    dup2(e.tmpout, 1);
    close(e.tmpin);
    close(e.tmpout);

    // 9. Se não for em background, espera o último comando
    wait_all_processes(mini->process_list);
}

void    executor(t_minishell *minishell)
{
    //handle_heredoc(minishell);
    if (minishell->envp_copy)
        free_env(minishell->envp_copy);
    minishell->envp_copy = copy_envp(minishell->env_list);
    if (!get_args(minishell->process_list))
        return ;
    //execute_command(minishell);
    unlink_heredoc_files(minishell);
}