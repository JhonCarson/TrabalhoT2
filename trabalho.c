#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura para armazenar o endereço
struct endereco {
    char rua [30];
    int num;
    char bairro [30];
    char cidade [40];
    char estado [40];
};

struct materia {
    char nome[30];
    float media;
};


// Estrutura para armazenar informações de um aluno
struct Aluno {
    char nome[50];
    int ra;
    char dataNascimento[11]; // Formato: dd/mm/yyyy
    struct endereco endereco[2];
    struct materia materia[5];
};

//Imprimir a Struct

void listarAlunos(struct Aluno aluno, int ra) {

    if (ra != 0) {
    
        printf("\nNome do Aluno: %s", aluno.nome);
        printf("\nRA do Aluno: %d", aluno.ra);
        printf("\nData de Nascimento do Aluno: %s\n", aluno.dataNascimento);
        printf("\nEndereco 1\n   Rua: %s   Numero da casa: %d\n   Bairro: %s   Cidade: %s   Estado: %s", aluno.endereco[0].rua, aluno.endereco[0].num, aluno.endereco[0].bairro, aluno.endereco[0].cidade, aluno.endereco[0].estado);

        if(aluno.endereco[1].num > 0) {
            printf("\nEndereco 2\n   Rua: %s   Numero da casa: %d\n   Bairro: %s   Cidade: %s   Estado: %s", aluno.endereco[1].rua, aluno.endereco[1].num, aluno.endereco[1].bairro, aluno.endereco[1].cidade, aluno.endereco[1].estado);
        }

        for (int i = 0; i < 5; i++) {
        
            printf("\n%s\nMedia %.2f\n", aluno.materia[i].nome, aluno.materia[i].media);
        }

        printf("\n------------------------------------------------------------------------------------\n");
    }
}

// Função para encontrar um aluno pelo RA
int encontrarAluno(struct Aluno alunos[], int ra, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (alunos[i].ra == ra) {
            return i; // Retorna o índice do aluno encontrado
        }
    }
    return -1; // Retorna -1 se o aluno não for encontrado
}

int main() {
    struct Aluno alunos[20];
    int numRegistrosFeitos = 2, qtdEndereco = 0, qtdAlunosTotal = 2; // Contador do número de alunos armazenados e Quantidade de Endereços
    int ra, indice = 0; //Localizador de alunos.


//informações para testar as requisições

//info do aluno 1
    strcpy(alunos[0].nome, "Joao\n");
    alunos[0].ra = 111;
    strcpy(alunos[0].dataNascimento, "01/01/2000\n");

//info de endereço
    strcpy(alunos[0].endereco[0].rua, "Rua A\n");
    alunos[0].endereco[0].num = 123;
    strcpy(alunos[0].endereco[0].bairro, "Bairro X\n");
    strcpy(alunos[0].endereco[0].cidade, "Cidade Y\n");
    strcpy(alunos[0].endereco[0].estado, "SP\n");

//info endereço 2
    strcpy(alunos[0].endereco[1].rua, "Rua B\n");
    alunos[0].endereco[1].num = 456;
    strcpy(alunos[0].endereco[1].bairro, "Bairro Z\n");
    strcpy(alunos[0].endereco[1].cidade, "Cidade W\n");
    strcpy(alunos[0].endereco[1].estado, "RJ\n");

//materias e nota
    for (int i = 0; i < 5; i++) {
        strcpy(alunos[0].materia[i].nome, "Materia A");
        alunos[0].materia[i].media = 10.0;
    }

//info do aluno 1
    strcpy(alunos[1].nome, "Maria\n");
    alunos[1].ra = 222;
    strcpy(alunos[1].dataNascimento, "15/03/2001\n");

//info de endereço
    strcpy(alunos[1].endereco[0].rua, "Rua C\n");
    alunos[1].endereco[0].num = 789;
    strcpy(alunos[1].endereco[0].bairro, "Bairro P\n");
    strcpy(alunos[1].endereco[0].cidade, "Cidade Q\n");
    strcpy(alunos[1].endereco[0].estado, "MG\n");

//info de endereço 2
    strcpy(alunos[1].endereco[1].rua, "Rua D\n");
    alunos[1].endereco[1].num = 101;
    strcpy(alunos[1].endereco[1].bairro, "Bairro R\n");
    strcpy(alunos[1].endereco[1].cidade, "Cidade S\n");
    strcpy(alunos[1].endereco[1].estado, "RS\n");

//materias e nota 
    for (int i = 0; i < 5; i++) {
        strcpy(alunos[1].materia[i].nome, "Materia B");
        alunos[1].materia[i].media = 10.0;
    }

    int opcao;
    do {
        printf("\nMenu de Operacoes:\n");
        printf("1. Adicionar novo aluno\n");
        printf("2. Apagar informacoes de um aluno\n");
        printf("3. Mostrar informacoes de um aluno pelo RA\n");
        printf("4. Mostrar informacoes de todos os alunos\n");
        printf("5. Sair\n");
        printf("\nEscolha a operacao (1-5): ");
        scanf("%d", &opcao);
        printf("\n ");

        switch (opcao) {
            case 1:
                if (qtdAlunosTotal < 20) {
                    
                    struct Aluno novoAluno;

                    printf("\nInforme o nome do aluno: ");
                    setbuf(stdin, NULL); // Limpar o buffer de entrada
                    fgets(novoAluno.nome, sizeof(novoAluno.nome), stdin);
                    
                    do {

                        printf("\nInforme o RA do aluno: ");
                        scanf("%d", &novoAluno.ra);

                        if (novoAluno.ra == 0) {
                            
                            printf("\n**--- Por favor, digite um RA valido! ---**\n");
                        }
                    }
                    while (novoAluno.ra == 0);   

                // Verifica se o RA já está armazenado
                    if (encontrarAluno(alunos, novoAluno.ra, numRegistrosFeitos) == -1) {
 
                            printf("\nInforme a data de nascimento (dd/mm/yyyy): ");
                            scanf("%s", &novoAluno.dataNascimento);
                        
                        do{
            
                            printf("\nDigite o numero da opcao que deseja: \n\n1 - Cadastrar apenas 1 endereco.\n2 - Cadastrar 2 enderecos. \n\nDigite 1 ou 2: ");
                            scanf(" %d", &qtdEndereco);

                            if(qtdEndereco != 1 && qtdEndereco != 2){

                                printf("\nDigite um valor valido sendo 1 ou 2.");
                            }

                        }
                        while (qtdEndereco != 1 && qtdEndereco != 2);

                        if (qtdEndereco == 1) {
                            
                            novoAluno.endereco[1].num = 0;
                        }
                        

                    //Preencher Endereços
                        for (int i = 0; i < qtdEndereco; i++) {
                                
                            setbuf(stdin, NULL);

                            printf("\nInforme a rua do endereco %d: ", i+1);
                            fgets(novoAluno.endereco[i].rua, sizeof(novoAluno.endereco[i].rua), stdin);
                            
                            printf("\nInforme o numero do endereco %d: ", i+1);
                            scanf("%d", &novoAluno.endereco[i].num);

                            setbuf(stdin, NULL);

                            printf("\nInforme o bairro do endereco %d: ", i+1);
                            fgets(novoAluno.endereco[i].bairro, sizeof(novoAluno.endereco[i].bairro), stdin);

                            setbuf(stdin, NULL);
                            
                            printf("\nInforme a cidade do endereco %d: ", i+1);
                            fgets(novoAluno.endereco[i].cidade, sizeof(novoAluno.endereco[i].cidade), stdin);   

                            setbuf(stdin, NULL);                   

                            printf("\nInforme o estado do endereco %d: ", i+1);
                            fgets(novoAluno.endereco[i].estado, sizeof(novoAluno.endereco[i].estado), stdin);      
                        }                                    
                    //Preencher as diciplinas

                        strcpy(novoAluno.materia[0].nome, "Algoritmos e Logica");
                        strcpy(novoAluno.materia[1].nome, "Estrutura de Dados");
                        strcpy(novoAluno.materia[2].nome, "Banco de Dados");
                        strcpy(novoAluno.materia[3].nome, "Programacao Orientada a Objeto");
                        strcpy(novoAluno.materia[4].nome, "Marketing Digital");
                            
                        for (int i = 0; i < 5; i++) {
                                
                            setbuf(stdin, NULL);   

                            printf("\nInforme a media da disciplina %s: ", novoAluno.materia[i].nome);
                            scanf(" %f", &novoAluno.materia[i].media);
                        }
                            
                       //atribuindo 0 ao RA para caso haja uma exclusão, armazenar na posição do aluno excluido que por sua vez tem o ra = 0
                        ra = 0; 

                    //Valida se ha algum aluno com informação deletada para usar o seu indice como um novo repositorio de registro
                        if (encontrarAluno(alunos, ra, numRegistrosFeitos) >= 0){
                                
                            indice = encontrarAluno(alunos, ra, numRegistrosFeitos);
                            alunos[indice] = novoAluno;
                                
                            qtdAlunosTotal++;

                            printf("\nAluno adicionado com sucesso!\n");

                        } 
                        else {

                            alunos[numRegistrosFeitos] = novoAluno;
                            numRegistrosFeitos++;
                            qtdAlunosTotal++;

                            printf("\nAluno adicionado com sucesso!\n");
                        } 
                    }
                    else{

                    printf("\nO RA ja esta armazenado. Nao foi possivel adicionar o aluno.\n");
                    }
                } 
                else {
                    
                    printf("\nNao ha espaco para adicionar mais alunos.\n");
                }
                break;

            case 2:

            //2. Apagar informacoes de um aluno

                printf("Digite o RA do aluno que deseja apagar as informacoes: ");
                scanf(" %d", &ra);
                
                if (encontrarAluno(alunos, ra, numRegistrosFeitos) >= 0) {
                    
                    indice = encontrarAluno(alunos, ra, numRegistrosFeitos);

                    strcpy(alunos[indice].nome, "null");
                    alunos[indice].ra = 0;
                    strcpy(alunos[indice].dataNascimento, "null");
                    strcpy(alunos[indice].endereco[0].rua, "null");
                    
                    //Limpar Endereço 1
                    alunos[indice].endereco[0].num = 0;
                    strcpy(alunos[indice].endereco[0].bairro, "null");
                    strcpy(alunos[indice].endereco[0].cidade, "null");
                    strcpy(alunos[indice].endereco[0].estado, "null");
                    
                    //Limpar Endereço 2
                    alunos[indice].endereco[1].num = 0;
                    strcpy(alunos[indice].endereco[1].bairro, "null");
                    strcpy(alunos[indice].endereco[1].cidade, "null");
                    strcpy(alunos[indice].endereco[1].estado, "null");
                   
                    for (int i = 0; i < 5; i++) {
                       
                        alunos[indice].materia[i].media = 00.0;
                    }
                }
                printf("\n  ----------------------\n");
                printf("\nDados removidos com sucesso!\n");
                printf("\n  ----------------------\n");

                qtdAlunosTotal--;
                    
                break;

            case 3:
                //3. Mostrar informacoes de um aluno pelo RA

                printf("Digite o RA do aluno que deseja localizar: ");
                scanf(" %d", &ra);

                indice = encontrarAluno(alunos, ra, numRegistrosFeitos);

                if (encontrarAluno(alunos, ra, numRegistrosFeitos) >= 0) {
                    
                    printf("\nSegue as informacoes do aluno correspondente a esse RA: \n");
                    printf("------------------------------------------------------------------------------------\n");
                    listarAlunos(alunos[indice], alunos[indice].ra);
                }
                else {

                    printf("\nNão encontramos nenhum aluno com esse RA.\n");
                }
                break;

            case 4:
                //4. Mostrar informacoes de todos os alunos

                printf("\n--------------------------------------Regitros de %d Alunos----------------------------------------------\n", qtdAlunosTotal);
                for (int i = 0; i < numRegistrosFeitos; i++) {
                
                    listarAlunos(alunos[i], alunos[i].ra);
                }

                break;

            case 5:
                printf("\nSaindo da aplicacao. Ate logo!\n");
                printf("\n ");

                break;

            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}