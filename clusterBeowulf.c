// Criado em: 04/07/2023
// Última modificação: 06/07/2023
// Autores: - Nome (matrícula)
//     - Glauber Gouveia (218116362)
//     - Guilherme Guimarães (220116170)
//     - Hiosery Gabriel (218116355)
//     - Larissa Hora (219216411)
// Disciplina: Sistemas Operacionais
// Professor: Robespierre Dantas da Rocha Pita
// Universidade Federal do Bahia - UFBA
// GCC (Ubuntu 11.3.0-1ubuntu1~22.04.1) 11.3.0
// Linux 5.11.0-22-generic x86_64 GNU/Linux
// Descrição:
//     Aplicação que simula um terminal de comandos com algumas funcionalidades básicas. O programa deve ser executado com o nome do outro nó como
//     argumento. O programa executa os comandos localmente e remotamente no outro nó.
//     Comandos disponíveis:
//         - ls: lista os arquivos e diretórios do diretório atual
//         - ls -l: lista os arquivos e diretórios do diretório atual com detalhes
//         - cp <arquivo>: copia o arquivo para o diretório atual
//         - mv <arquivo>: move o arquivo para o diretório atual
//         - mkdir <diretório>: cria o diretório no diretório atual
//         - rm <arquivo>: remove o arquivo do diretório atual
//         - rm -r: remove o diretório atual e todo o seu conteúdo
//         - sair: encerra o programa
//     O programa deve ser encerrado com o comando sair.
//     O programa deve ser compilado com o comando:
//         gcc -o app app.c
//     O programa deve ser executado com o comando:
//         ./app <nome do outro nó>
//     Exemplo:
//         ./app node1
//     O programa deve ser executado em dois terminais diferentes para simular dois nós. 

#include <stdlib.h>   //biblioteca padrão
#include <stdio.h>    //biblioteca padrão de entrada e saída
#include <string.h>   //biblioteca para manipulação de strings
#include <unistd.h>   //biblioteca para chamadas de sistema
#include <sys/wait.h> //biblioteca para chamadas de sistema

#define COMMAND_SIZE 100 // tamanho máximo da linha de comando

int main(int argc, char *argv[])
{ // chamada da função main com argumentos
    if (argc != 2)
    {                                                             // verifica se o número de argumentos é diferente de 2
        fprintf(stderr, "Uso: %s <nome do outro nó>\n", argv[0]); // imprime mensagem de erro caso o número de argumentos seja diferente de 2
        return 1;
    }

    char *otherNode = argv[1]; // nome do outro nó

    char command[COMMAND_SIZE];    // linha de comando
    char currentDir[COMMAND_SIZE]; // diretório atual

    // Obtém o diretório atual
    if (getcwd(currentDir, sizeof(currentDir)) == NULL)
    {                                              // verifica se o diretório atual é nulo
        perror("Erro ao obter o diretório atual"); // imprime mensagem de erro
        return 1;
    }

    while (1)
    {
        printf("Diretório atual: %s\n", currentDir);                   // imprime o diretório atual
        printf("Digite o comando desejado ou 'sair' para encerrar: "); // imprime mensagem para o usuário digitar o comando desejado
        fgets(command, sizeof(command), stdin);                        // lê a linha de comando

        command[strcspn(command, "\n")] = '\0'; // remove a quebra de linha do final do comando

        if (strcmp(command, "sair") == 0)
        {          // verifica se o comando é sair
            break; // encerra o programa
        }
        else if (strcmp(command, "ls") == 0)
        {                                                                     // verifica se o comando é ls
            char sshCommand[COMMAND_SIZE + strlen(otherNode)];                // linha de comando para o ssh
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s ls", otherNode); // concatena o comando ssh com o comando ls e o nome do outro nó
            system(sshCommand);                                               // executa o comando ssh
            system("ls");                                                     // executa o comando ls
        }
        else if (strcmp(command, "ls -l") == 0)
        { // verifica se o comando é ls -l
            // linhas de comando idênticas ao if anterior
            char sshCommand[COMMAND_SIZE + strlen(otherNode)];
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s ls -l", otherNode);
            system(sshCommand);
            system("ls -l");
        }
        else if (strncmp(command, "cp ", 3) == 0)
        {                                                                                  // verifica se o comando é cp
            char fullCommand[COMMAND_SIZE + strlen(command)];                              // linha de comando completa
            snprintf(fullCommand, sizeof(fullCommand), "cp %s", command + 3);              // concatena o comando cp com o nome do arquivo
            char sshCommand[COMMAND_SIZE + strlen(otherNode) + strlen(fullCommand)];       // linha de comando para o ssh
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s %s", otherNode, fullCommand); // concatena o comando ssh com o comando cp e o nome do outro nó
            system(sshCommand);                                                            // executa o comando ssh
            system(fullCommand);                                                           // executa o comando cp
        }
        else if (strncmp(command, "mv ", 3) == 0)
        { // verifica se o comando é mv
            // linhas de comando idênticas ao if anterior
            char fullCommand[COMMAND_SIZE + strlen(command)];
            snprintf(fullCommand, sizeof(fullCommand), "mv %s", command + 3);
            char sshCommand[COMMAND_SIZE + strlen(otherNode) + strlen(fullCommand)];
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s %s", otherNode, fullCommand);
            system(sshCommand);
            system(fullCommand);
        }
        else if (strncmp(command, "mkdir ", 6) == 0)
        {                                                                                  // verifica se o comando é mkdir
            char fullCommand[COMMAND_SIZE + strlen(command)];                              // linha de comando completa
            snprintf(fullCommand, sizeof(fullCommand), "mkdir %s", command + 6);           // concatena o comando mkdir com o nome do diretório
            char sshCommand[COMMAND_SIZE + strlen(otherNode) + strlen(fullCommand)];       // linha de comando para o ssh
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s %s", otherNode, fullCommand); // concatena o comando ssh com o comando mkdir e o nome do outro nó
            system(sshCommand);                                                            // executa o comando ssh
            system(fullCommand);                                                           // executa o comando mkdir
        }
        else if (strncmp(command, "rm ", 3) == 0)
        {                                                                            // verifica se o comando é rm
            char fullCommand[COMMAND_SIZE + strlen(command)];                        // linha de comando completa
            snprintf(fullCommand, sizeof(fullCommand), "rm %s", command + 3);        // concatena o comando rm com o nome do arquivo
            char sshCommand[COMMAND_SIZE + strlen(otherNode) + strlen(fullCommand)]; // linha de comando para o ssh
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s %s", otherNode, fullCommand);
            system(sshCommand);
            system(fullCommand);
        }
        else if (strcmp(command, "rm -r") == 0)
        { // verifica se o comando é rm -r
            // linhas de comando idênticas ao if anterior
            char sshCommand[COMMAND_SIZE + strlen(otherNode)];
            snprintf(sshCommand, sizeof(sshCommand), "ssh %s rm -r", otherNode);
            system(sshCommand);
            system("rm -r");
        }
        else if (strcmp(command, "useradd") == 0)
        { // verifica se o comando é criar usuário
            printf("Digite o nome do usuário: ");
            fgets(command, sizeof(command), stdin); // lê o nome do usuário
            command[strcspn(command, "\n")] = '\0'; // remove a quebra de linha

            char createUserCommand[COMMAND_SIZE + strlen(command)];
            snprintf(createUserCommand, sizeof(createUserCommand), "ssh %s sudo useradd %s", otherNode, command);
            system(createUserCommand);

            // printf("Digite a senha do usuário: ");
            // fgets(command, sizeof(command), stdin); // lê a senha do usuário
            // command[strcspn(command, "\n")] = '\0'; // remove a quebra de linha

            // char passwdCommand[COMMAND_SIZE + strlen(command)];
            // snprintf(passwdCommand, sizeof(passwdCommand), "ssh %s passwd %s", otherNode, command);
            // system(passwdCommand);
        }
        // else if (strcmp(command, "createuser") == 0)
        // { // verifica se o comando é createuser
        //     char username[COMMAND_SIZE];
        //     printf("Digite o nome de usuário: ");
        //     scanf("%s", username);

        //     char createUserCommand[COMMAND_SIZE];
        //     snprintf(createUserCommand, sizeof(createUserCommand), "sudo useradd %s", username);
        //     system("createUserCommand");
        // }

        else
        {                                 // caso o comando não seja nenhum dos anteriores
            printf("Comando inválido\n"); // imprime mensagem de comando inválido
        }
    }

    return 0; // retorna 0 para a função main
}
