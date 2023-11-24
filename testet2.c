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
    free(array_dinamico->ptr_dados);
    
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

void trocar(void **array, int pos1, int pos2){

	void * temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;

}

int compare_strucs_pessoa_nome(const void *pessoa1, const void *pessoa2) { 
   
   return strcmp((*(Aluno*)pessoa1).nome, (*(Aluno*)pessoa2).nome);
}

int particionar(void **array, int p, int r, int (*compare)(const void*, const void*)) { 

	void *value = array[r];	// elemento pivô
	int i = p - 1;

	for(int j = p;j < r; j++){		// com este loop, os valores são separados em 2 partições, as maiores e as menores do pivô
		if(compare(array[j], value) <= 0) {
			i = i + 1;
			trocar(array, i, j);	// alterar as posições dos elementos antes e depois do elemento ordenado
        }
	}
	trocar(array, i + 1, r);		// mova o elemento inicial para sua posição final

	return i + 1;
}

void quick_sort(void **array, int p, int r, int (*compare)(const void*, const void*)){

	if(p < r){
		int q = particionar(array, p, r, compare);	/* pivô */
		quick_sort(array, p, q - 1, compare);
		quick_sort(array, q + 1, r, compare);
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

void imprimir_aluno(int i, const Array_Dinamico *array_dinamico) {

    system("cls");

    printf("\n                #### Listagem de Aluno ####");
       
    printf("\n==============================================================\n");
    printf("\n# - Aluno %d - #\n", array_dinamico->ptr_dados[i]->ra);
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

    printf("==============================================================\n");
}

void remover_aluno (int ra, Array_Dinamico * array_dinamico) {

    int indice = busca_sequencial_array_dinamico(array_dinamico, ra);

    array_dinamico->ptr_dados[indice] = array_dinamico->ptr_dados[array_dinamico->quantidade - 1];
    array_dinamico->ptr_dados[array_dinamico->quantidade - 1] = NULL;
    array_dinamico->quantidade = array_dinamico->quantidade - 1;

    diminuir_array_dinamico(array_dinamico);
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

int salvarBinario(Array_Dinamico *array_dinamico, char *caminho_arquivo) { 
   
    FILE *arquivo;
    arquivo = fopen(caminho_arquivo, "wb");

    if (!arquivo) { 
       
        printf("\n\nErro ao abrir o arquivo!\n\n");     
        return 1;
    }

    //fwrite(&array_dinamico->quantidade, sizeof(int), 1, arquivo);

    for (int i = 0; i < array_dinamico->quantidade; i++) { 
       
        fwrite(array_dinamico->ptr_dados[i]->nome, sizeof(array_dinamico->ptr_dados[i]->nome), 1, arquivo);
        fwrite(&array_dinamico->ptr_dados[i]->ra, sizeof(int), 1, arquivo);
        fwrite(array_dinamico->ptr_dados[i]->dataNascimento, sizeof(array_dinamico->ptr_dados[i]->dataNascimento), 1, arquivo);

        fwrite(&array_dinamico->ptr_dados[i]->qtdEndereco, sizeof(int), 1, arquivo);

        for (int j = 0; j < array_dinamico->ptr_dados[i]->qtdEndereco; j++) {
           
            fwrite(&array_dinamico->ptr_dados[i]->endereco[j], sizeof(Endereco), 1, arquivo);
        }
    }

    fclose(arquivo);
    return 0;
}


int carregarBinario(Array_Dinamico *array_dinamico, char *caminho_arquivo) {
   
    FILE *arquivo;
    arquivo = fopen(caminho_arquivo, "rb");

    if (!arquivo) {
   
        printf("\n\nErro ao abrir o arquivo!\n\n");
        return 1;
    }

    fseek(arquivo, 0, SEEK_END); // Move o cursor para o final do arquivo
    long tamanho_arquivo = ftell(arquivo);

    if (tamanho_arquivo == 0) {
   
        fclose(arquivo);
        return 2;
    }

    fseek(arquivo, 0, SEEK_SET); // Move o cursor de volta para o início do arquivo

    //int quantidade_alunos;
   
    //fread(&quantidade_alunos, sizeof(int), 1, arquivo);

    //printf("quantidade2 -> %d", quantidade_alunos);

    while (1) { 

        if (feof(arquivo)) {

            break; 
        }
        
        Aluno *aluno = (Aluno *)malloc(sizeof(Aluno));

        fread(aluno->nome, sizeof(aluno->nome), 1, arquivo);
        fread(&aluno->ra, sizeof(int), 1, arquivo);
        fread(aluno->dataNascimento, sizeof(aluno->dataNascimento), 1, arquivo);

        fread(&aluno->qtdEndereco, sizeof(int), 1, arquivo);

        aluno->endereco = (Endereco *)malloc(aluno->qtdEndereco * sizeof(Endereco));

        for (int j = 0; j < aluno->qtdEndereco; j++) {
   
            fread(&aluno->endereco[j], sizeof(Endereco), 1, arquivo);
        }

        adicionar_array_dinamico(array_dinamico, aluno);
    }

    fclose(arquivo);
    return 0;
}



int main (int argc, char *argv[]) {
    
    if (argc < 2) {

        printf("Uso: %s <caminho_do_arquivo>\n", argv[0]);

        return 0;
    }

    char *dados_alunos = argv[1];

    printf("\n\nSegundo Parametro %s", dados_alunos);

    int ra, indice, res;
    int tamanho = 4;
    int qtdEndereco = 2;

    Array_Dinamico *array_dinamico = criar_array_dinamico(tamanho, false);
    
    if(carregarBinario(array_dinamico, dados_alunos) != 2 ) {
       
        carregarBinario(array_dinamico, dados_alunos); 
    } 

    Aluno *novoAluno = (Aluno*)malloc(sizeof(Aluno));

    novoAluno->endereco = (Endereco *) malloc(qtdEndereco * sizeof(Endereco));

    if (novoAluno == NULL || novoAluno->endereco == NULL) {
        
        printf("\nFalha ao alocar memoria dinamicamente");
        exit(1);
    }
    
    int opcao;

    do {

        menu: 

        printf("\n\n\n ========= Menu de Operacoes: =========\n\n");
        printf("## QTD. Alunos: %d   ||   Tamanho do Vetor: %d ##\n\n", array_dinamico->quantidade, array_dinamico->tamanho);
        printf("1. Adicionar novo aluno\n");
        printf("2. Apagar informacoes de um aluno\n");
        printf("3. Mostrar informacoes de um aluno pelo RA\n");
        printf("4. Mostrar informacoes de todos os alunos\n");
        printf("5. Sair\n");
        printf("\nEscolha a operacao (1-5): ");
        
        
        scanf(" %d", &opcao);

        switch (opcao) {
            
            case 1:  

                //adicionar Aluno                                 
                
                novoAluno = (Aluno*)malloc(sizeof(Aluno));

                informar_ra: 

                do {

                    printf("\nInforme o RA do aluno: ");
                    scanf(" %d", &novoAluno->ra);
                    
                    if (novoAluno->ra == 0) {
                            
                        printf("\n**--- Por favor, digite um RA valido! ---**\n");
                    }

                }while (novoAluno->ra == 0);   

                // Verifica se o RA já está armazenado
                if (busca_sequencial_array_dinamico(array_dinamico, novoAluno->ra) != -1) {

                    res = 0;
                        
                    do {
                        printf("\nAluno ja cadastrado!\n");
                        printf("\nDeseja inserir um novo RA?\n\n1 - Sim\n2 - Nao");
                        printf("\n\nDigite 1 para sim ou 2 para nao: ");
                        scanf(" %d", &res);
                                
                        if (res == 1) {
                       
                            goto informar_ra;
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
                    
                    system("cls");

                    printf("\n\nAluno adicionado com sucesso!\n\n");
                    sleep(2);
                    system("cls");

                }

                break;
            case 2:

                //remover aluno

                removerAluno:

                system("cls");

                printf("\nDigite o RA do aluno que voce deseja remover: ");
                scanf(" %d", &ra);

                if(indice = busca_sequencial_array_dinamico(array_dinamico, ra) != -1) {

                    do {

                        system("cls");
                        printf("\nTem certeza que deseja remover o aluno %s?\n\n1 - Sim\n2 - Nao\n\nDigite o numero de acordo com a sua escolha: ", array_dinamico->ptr_dados[indice]->nome);
                        scanf(" %d", &res);

                        if (res != 1 && res != 2) {

                            system("cls");
                            printf("\nPor favor, digite uma opcao valida! ");
                        }
                    } while (res != 1 && res != 2);

                    if (res == 1) {
                        
                        remover_aluno(ra, array_dinamico);
                        system("cls");
                        printf("\n\n ##  Aluno removido com sucesso!!  ## \n\n");

                        sleep(2);

                        system("cls");
                    }
                    else{
                        
                        system("cls");
                        goto removerAluno;
                    }
                }
                else {
                    
                    system("cls");
                    printf("\n\n##  Aluno nao encontrado!  ##\n");

                    do {

                        
                        printf("\nGostaria de informar um novo RA?\n\n1 - Sim\n2 - Nao\n\nDigite o numero de acordo com a sua escolha: ", array_dinamico->ptr_dados[indice]->nome);
                        scanf(" %d", &res);

                        if (res != 1 && res != 2) {

                            system("cls");
                            printf("\nPor favor, digite uma opcao valida! ");
                        }
                    } while (res != 1 && res != 2);

                    if (res == 1) {
                        
                        goto removerAluno;
                    }
                    else {
                        
                        system("cls");
                        goto menu;
                    }
                }
                
                    
                break;
            case 3:
                
                //mostrar aluno pelo RA

                mostrarAluno:

                system("cls");

                printf("\nDigite o RA que deseja buscar: ");
                scanf(" %d", &ra);

                indice = busca_sequencial_array_dinamico(array_dinamico, ra);

                if (indice != -1) {
                    imprimir_aluno(indice, array_dinamico);
                }
                else {
                    
                    system("cls");
                    printf("\n\n##  Aluno nao encontrado!  ##\n");

                    do {

                        
                        printf("\nGostaria de informar um novo RA?\n\n1 - Sim\n2 - Nao\n\nDigite o numero de acordo com a sua escolha: ", array_dinamico->ptr_dados[indice]->nome);
                        scanf(" %d", &res);

                        if (res != 1 && res != 2) {

                            system("cls");
                            printf("\nPor favor, digite uma opcao valida! ");
                        }
                    } while (res != 1 && res != 2);

                    if (res == 1) {
                        
                        goto mostrarAluno;
                    }
                    else {
                        
                        system("cls");
                        goto menu;
                    }
                }
                break;
            case 4:
                
                //imprimir todos os alunos
                if(array_dinamico->quantidade == 0) {
                    
                    system("cls");
                    printf("\n\nNao a alunos cadastrados!...");
                    sleep(1);

                    printf("\n\nRetornando ao \"Menu Principal\"");
                    sleep(2);

                    system("cls");
                    goto menu;

                }
                else {

                    quick_sort((void**)array_dinamico->ptr_dados, 0, array_dinamico->quantidade - 1, compare_strucs_pessoa_nome); 
                    
                    //printf("Nome: %s", array_dinamico->ptr_dados[0]->nome);

                    imprimir_array_dinamico(array_dinamico);
                }

                break;
            case 5:

                //encerrar programa

                system("cls");
                printf("Encerrando o programa...\n");

                break;
            default:
               
                printf("\nOpcao invalida. Tente novamente.\n");
        }

    } while (opcao != 5);

    salvarBinario(array_dinamico, dados_alunos);
    
    destruir_array_dinamico(&array_dinamico);
    
    //fim de codigo
    return 0;
}