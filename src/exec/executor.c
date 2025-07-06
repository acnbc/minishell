#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// Suponha que essas variáveis estejam globais ou passadas por parâmetro:
char *inputFile = NULL;
char *outputFile = NULL;
int background = 0;

typedef struct {
    char **args; // argumentos do comando, começando com o nome
} SimpleCommand;

SimpleCommand **simpleCommands;
int numSimpleCommands;

void execute_command() {
    // 1. Salvar stdin e stdout
    int tmpin = dup(0);    // salva stdin
    int tmpout = dup(1);   // salva stdout

    // 2. Redirecionar a entrada inicial (inputFile ou stdin)
    int fdin;
    if (inputFile) {
        fdin = open(inputFile, O_RDONLY);
    } else {
        fdin = dup(tmpin); // entrada padrão
    }

    int fdout;
    int ret;
    int i;

    for (i = 0; i < numSimpleCommands; i++) {
        // 3. Redirecionar entrada para o comando atual
        dup2(fdin, 0);
        close(fdin);

        // 4. Verificar se é o último comando da sequência
        if (i == numSimpleCommands - 1) {
            // Último comando
            if (outputFile) {
                fdout = open(outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            } else {
                fdout = dup(tmpout); // saída padrão
            }
        } else {
            // 5. Criar pipe para conectar ao próximo comando
            int fdpipe[2];
            pipe(fdpipe);
            fdout = fdpipe[1]; // escrever na saída do pipe
            fdin  = fdpipe[0]; // o próximo comando vai ler daqui
        }

        // 6. Redirecionar a saída do processo atual
        dup2(fdout, 1);
        close(fdout);

        // 7. Criar processo filho
        ret = fork();
        if (ret == 0) {
            // Processo filho: executar comando
            execvp(simpleCommands[i]->args[0], simpleCommands[i]->args);
            perror("execvp");
            exit(1);
        }

        // pai continua o loop para o próximo comando
    }

    // 8. Restaurar entrada e saída originais
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);

    // 9. Se não for em background, espera o último comando
    if (!background) {
        waitpid(ret, NULL, 0);
    }
}
