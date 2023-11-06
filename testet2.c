#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// Estrutura para armazenar o endereço
struct endereco {
    char rua[30];
    int num;
    char bairro[30];
    char cidade[40];
    char estado[40];
};
typedef struct endereco Endereco;

// Estrutura para armazenar as matérias
struct materia {
    char nome[30];
    float media;
};
typedef struct materia Materia;

// Estrutura para armazenar informações de um aluno
struct aluno {
    char nome[50];
    int ra;
    char dataNascimento[11];
    int qtdEndereco;
    Endereco *endereco;
    Materia materia[5];
};
typedef struct aluno Aluno;

//Estrutura do Array Dinamico
struct array_dinamico {
    bool ordenado;  // true indica que quer manter o array ordenado.
    int tamanho;    // número máximo de elementos que podemos armazenar no array.
    int quantidade; // quantidade atual de elementos armazenados
    Aluno **ptr_dados;  // array de ponteiros para estruturas Aluno.
};
typedef struct array_dinamico Array_Dinamico;

Array_Dinamico* criar_array_dinamico(int tamanho_array, bool ordenado) {

    Array_Dinamico *array_dinamico = (Array_Dinamico*)malloc(sizeof(Array_Dinamico));

    if (array_dinamico == NULL) {
        
        printf("\nFalha ao alocar memoria para o array");
        return NULL;
    }
    
    array_dinamico->ordenado = ordenado;
    array_dinamico->quantidade = 0;
    array_dinamico->tamanho = tamanho_array;
    array_dinamico->ptr_dados = (Aluno**)calloc(tamanho_array, sizeof(Aluno*));
    
    return array_dinamico;
}

void destruir_array_dinamico(Array_Dinamico **array_dinamico_endereco_de_memoria) {
    
    Array_Dinamico *array_dinamico = *array_dinamico_endereco_de_memoria;
    
    for (int i = 0; i < array_dinamico->quantidade; i++) {
       
        free(array_dinamico->ptr_dados[i]);
    }
    
    free(array_dinamico->ptr_dados);
    free(array_dinamico);
    
    *array_dinamico_endereco_de_memoria = NULL;
}

bool esta_cheio_array_dinamico(Array_Dinamico *array_dinamico) {
   
    return array_dinamico->quantidade >= array_dinamico->tamanho;
}

void aumentar_array_dinamico(Array_Dinamico *array_dinamico) {
  
    int novo_tamanho = array_dinamico->tamanho * 2;
    Aluno **novo_ptr_dados = (Aluno**)calloc(novo_tamanho, sizeof(Aluno*));
   
   //preencher o "novo array" com os dados do array anterior
    for (int i = 0; i < array_dinamico->quantidade; i++) {
   
        novo_ptr_dados[i] = array_dinamico->ptr_dados[i];
    }
   
    free(array_dinamico->ptr_dados);
   
    array_dinamico->ptr_dados = novo_ptr_dados;
    array_dinamico->tamanho = novo_tamanho;
}

void diminuir_array_dinamico(Array_Dinamico *array_dinamico) {
   
   // verificar se a quantidade de alunos preenchida é equivaliente a 1/4 do tamanho do array
    if (array_dinamico->quantidade < array_dinamico->tamanho / 4 && array_dinamico->tamanho >= 4) {
   
   //diminuir pela metade o tamanho do array e passar os dados do "array antigo" para o "novo array"
        int novo_tamanho = array_dinamico->tamanho / 2;
        Aluno **novo_ptr_dados = (Aluno**)calloc(novo_tamanho, sizeof(Aluno*));
   
        for (int i = 0; i < array_dinamico->quantidade; i++) {
   
            novo_ptr_dados[i] = array_dinamico->ptr_dados[i];
        }
   
        free(array_dinamico->ptr_dados);
        array_dinamico->ptr_dados = novo_ptr_dados;
        array_dinamico->tamanho = novo_tamanho;
    }
}


int busca_sequencial_array_dinamico(Array_Dinamico *array_dinamico, int ra) {
   
    for (int i = 0; i < array_dinamico->quantidade; i++) {
   
        if (array_dinamico->ptr_dados[i]->ra == ra) {
            
            return i; // Retornar o índice do aluno encontrado.
        }
    }

    return -1; // Retorna -1 se o aluno não for encontrado.
}

void imprimir_array_dinamico(const Array_Dinamico *array_dinamico) {
   
   system("cls");

   printf("\n                #### Listagem de Aluno ####");

    for (int i = 0; i < array_dinamico->quantidade; i++) {
        
        printf("\n==============================================================\n");
        printf("\n# - Aluno %d - #\n", i + 1);
        printf("\n    Nome: %s\n", array_dinamico->ptr_dados[i]->nome);
        printf("    RA: %d\n", array_dinamico->ptr_dados[i]->ra);
        printf("    Data de Nascimento: %s\n", array_dinamico->ptr_dados[i]->dataNascimento);
        printf("\n    Endereco 1: \n");
        printf("    R. %s, %d, %s, %s - %s", array_dinamico->ptr_dados[i]->endereco[0].rua, 
        array_dinamico->ptr_dados[i]->endereco[0].num, array_dinamico->ptr_dados[i]->endereco[0].bairro, 
        array_dinamico->ptr_dados[i]->endereco[0].cidade, array_dinamico->ptr_dados[i]->endereco[0].estado);
        
        if (array_dinamico->ptr_dados[i]->qtdEndereco == 2) {
            
            printf("\n\n    Endereco 2:\n");
            printf("    R. %s, %d, %s, %s - %s", array_dinamico->ptr_dados[i]->endereco[1].rua, 
            array_dinamico->ptr_dados[i]->endereco[1].num, array_dinamico->ptr_dados[i]->endereco[1].bairro, 
            array_dinamico->ptr_dados[i]->endereco[1].cidade, array_dinamico->ptr_dados[i]->endereco[1].estado);
        }

        printf("\n\n    Notas:\n\n");
        
        for (int j = 1; j < 5; j++) {
        
            printf("    Materia de %s: | Media: %.2f\n", array_dinamico->ptr_dados[i]->materia[j].nome, array_dinamico->ptr_dados[i]->materia[j].media);
        }   
        printf("\n");
    }
    printf("==============================================================\n");
}

void adicionar_array_dinamico(Array_Dinamico *array_dinamico, Aluno *aluno) {
    
    if (esta_cheio_array_dinamico(array_dinamico)) {
       
        aumentar_array_dinamico(array_dinamico);
    }
    
    array_dinamico->ptr_dados[array_dinamico->quantidade] = aluno;
    
    array_dinamico->quantidade++;
}


//ajusrar string para adicionar o "\0" no final
char *ajustarString (char * str) {

    int tamanho = strlen(str);

    if (str[tamanho - 1] == '\n') {
        
        str[tamanho - 1] = '\0';
    }

    return str;
}

int main() {
    
   int tamanho = 4;
   int qtdEndereco = 2;

    Array_Dinamico *array_dinamico = criar_array_dinamico(tamanho, false);
    Aluno *novoAluno = (Aluno*)malloc(sizeof(Aluno));

    novoAluno->endereco = (Endereco *) malloc(qtdEndereco * sizeof(Endereco));

    if (novoAluno == NULL || novoAluno->endereco == NULL) {
        
        printf("\nFalha ao alocar memoria dinamicamente");
        exit(1);
    }
    
    //info do aluno

    strcpy(novoAluno->nome, "Aluno 1");
    novoAluno->ra = 12345;
    strcpy(novoAluno->dataNascimento, "01/01/2000");

    //info de endereço

    strcpy(novoAluno->endereco[0].rua, "Rua A");
    novoAluno->endereco[0].num = 789;
    strcpy(novoAluno->endereco[0].bairro, "Bairro A");
    strcpy(novoAluno->endereco[0].cidade, "Cidade A");
    strcpy(novoAluno->endereco[0].estado, "PR");

    //info de endereço 2

    strcpy(novoAluno->endereco[1].rua, "Rua B");
    novoAluno->endereco[1].num = 101;
    strcpy(novoAluno->endereco[1].bairro, "Bairro B");
    strcpy(novoAluno->endereco[1].cidade, "Cidade B");
    strcpy(novoAluno->endereco[1].estado, "MG");

    //materias e nota 

    for (int i = 0; i < 5; i++) {
        strcpy(novoAluno->materia[i].nome, "Materia B");
        novoAluno->materia[i].media = 10.0;
    }

    adicionar_array_dinamico(array_dinamico, novoAluno);

    novoAluno = NULL;

    menu: 

    int opcao;

    do {

        printf("\nMenu de Operacoes:\n");
        printf("1. Adicionar novo aluno\n");
        printf("2. Apagar informacoes de um aluno\n");
        printf("3. Mostrar informacoes de um aluno pelo RA\n");
        printf("4. Mostrar informacoes de todos os alunos\n");
        printf("5. Sair\n");
        printf("\nEscolha a operacao (1-5): ");
        
        scanf(" %d", &opcao);

        switch (opcao) {
            
            case 1:                                   
                
                novoAluno = (Aluno*)malloc(sizeof(Aluno));

                ra: 

                do {

                    printf("\nInforme o RA do aluno: ");
                    scanf(" %d", &novoAluno->ra);
                    
                    if (novoAluno->ra == 0) {
                            
                        printf("\n**--- Por favor, digite um RA valido! ---**\n");
                    }

                }while (novoAluno->ra == 0);   

                // Verifica se o RA já está armazenado
                if (busca_sequencial_array_dinamico(array_dinamico, novoAluno->ra) != -1) {

                    int res = 0; 
                        
                    do {
                        printf("\nAluno ja cadastrado!\n");
                        printf("\nDeseja inserir um novo RA?\n\n1 - Sim\n2 - Nao");
                        printf("\n\nDigite 1 para sim ou 2 para nao: ");
                        scanf(" %d", &res);
                                
                        if (res == 1) {
                       
                            goto ra;
                        } 
                        else if (res == 2) {

                            system("cls");
                            printf("Entendido, voltando ao menu principal...");
                            sleep(2);

                            goto menu;
                        } 
                        else {

                            printf("Valor inváido!");
                        }
                    } while (res != 1 && res != 2);
                }
                else {

                    printf("\nInforme o nome do aluno: ");
                    setbuf(stdin, NULL); 
                    fgets(novoAluno->nome, sizeof(novoAluno->nome), stdin);
                    strcpy(novoAluno->nome, ajustarString(novoAluno->nome));
                        
                    printf("\nInforme a data de nascimento (dd/mm/yyyy): ");
                    scanf(" %s", &novoAluno->dataNascimento);
                
                    do{
        
                        printf("\nDigite o numero da opcao que deseja: \n\n1 - Cadastrar apenas 1 endereco\n2 - Cadastrar 2 enderecos\n\nDigite 1 ou 2: ");
                        scanf(" %d", &qtdEndereco);
                        
                        if(qtdEndereco != 1 && qtdEndereco != 2){
                            
                            printf("\nDigite um valor valido sendo 1 ou 2");
                        }

                    } while (qtdEndereco != 1 && qtdEndereco != 2);
                       
                    novoAluno->endereco = (Endereco *) malloc(2 * sizeof(Endereco));

                    if (qtdEndereco == 1) {
                        
                        novoAluno->qtdEndereco = 1;
                    }
                    else {

                        novoAluno->qtdEndereco = 2;
                    }
                    

                    //Preencher Endereços
                    for (int i = 0; i < qtdEndereco; i++) {
                            
                        setbuf(stdin, NULL);

                        printf("\nInforme a rua do endereco %d: ", i+1);
                        fgets(novoAluno->endereco[i].rua, sizeof(novoAluno->endereco[i].rua), stdin);
                        strcpy(novoAluno->endereco[i].rua, ajustarString(novoAluno->endereco[i].rua));
                        
                        printf("\nInforme o numero do endereco %d: ", i+1);
                        scanf("%d", &novoAluno->endereco[i].num);
                        
                        setbuf(stdin, NULL);
                        
                        printf("\nInforme o bairro do endereco %d: ", i+1);
                        fgets(novoAluno->endereco[i].bairro, sizeof(novoAluno->endereco[i].bairro), stdin);
                        strcpy(novoAluno->endereco[i].bairro, ajustarString(novoAluno->endereco[i].bairro));
                        
                        setbuf(stdin, NULL);
                        
                        printf("\nInforme a cidade do endereco %d: ", i+1);
                        fgets(novoAluno->endereco[i].cidade, sizeof(novoAluno->endereco[i].cidade), stdin);   
                        strcpy(novoAluno->endereco[i].cidade, ajustarString(novoAluno->endereco[i].cidade));
                        
                        setbuf(stdin, NULL);                   
                        
                        printf("\nInforme o estado do endereco %d: ", i+1);
                        fgets(novoAluno->endereco[i].estado, sizeof(novoAluno->endereco[i].estado), stdin);     
                        strcpy(novoAluno->endereco[i].estado, ajustarString(novoAluno->endereco[i].estado)); 
                    }           

                    //Preencher as diciplinas
                    strcpy(novoAluno->materia[0].nome, "Algoritmos e Logica");
                    strcpy(novoAluno->materia[1].nome, "Estrutura de Dados");
                    strcpy(novoAluno->materia[2].nome, "Banco de Dados");
                    strcpy(novoAluno->materia[3].nome, "Programacao Orientada a Objeto");
                    strcpy(novoAluno->materia[4].nome, "Marketing Digital");
                            
                    for (int i = 0; i < 5; i++) {
                            
                        setbuf(stdin, NULL);   
                        printf("\nInforme a media da disciplina %s: ", novoAluno->materia[i].nome);
                        scanf(" %f", &novoAluno->materia[i].media);
                    }
                            
                    adicionar_array_dinamico(array_dinamico, novoAluno);

                    novoAluno = NULL;

                    printf("\nAluno adicionado com sucesso!\n");
                        
                }

                break;
            case 2:

                //apagar info de aluno
                break;
            case 3:
                //mostrar informações de um aluno por RA
                break;
            case 4:
                
                imprimir_array_dinamico(array_dinamico);

                break;
            case 5:
                printf("Encerrando o programa...\n");
                break;
            default:
               
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5);
    // Buscar Aluno 
    /*
    int ra_a_buscar = 12345;
    int indice_encontrado = busca_sequencial_array_dinamico(array_dinamico, ra_a_buscar);
   
    if (indice_encontrado != -1) {
   
        printf("Aluno encontrado no índice %d.\n", indice_encontrado);
    }
    else {
    
        printf("Aluno não encontrado.\n");
    }

    imprimir_array_dinamico(array_dinamico);
    
 */
    
    //fim de codigo
    for (int i = 0; i < array_dinamico->quantidade; i++) {
        
        free(array_dinamico->ptr_dados[i]);
    }
    destruir_array_dinamico(&array_dinamico);

    return 0;
}
