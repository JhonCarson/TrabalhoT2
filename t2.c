/*A atividade consiste em desenvolver uma aplicação em linguagem C que armazene dados dos
alunos em memória e depois em um arquivo binário e que atenda os requisitos abaixo. Faça um
comentário no início do código explicando o que você fez e também em partes do código que seja
necessário para o entendimento.
1) Armazenamento das dados em memória de forma dinâmica.
2) Gravar e Carregar os dados de um arquivo binário.
3) Deve conter um menu de operações para manipular os dados.
4) Informações que devem ser armazenadas: Nome, RA, data de nascimento, 2 endereços
(rua, número, bairro, cidade e estado), nomes e médias de 5 disciplinas.
5) A estrutura da aplicação disponibilizada no Github no endereço
https://github.com/edersonschmeing/algoritmos-e-logica-de-programacao-em-c/tree/main/
2023-2/12-trabalho-2
6) Demais orientações serão passadas em sala no dia 16/10/2023, 20/10/2023 e 27/10/2023*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>  
#include <string.h>  


//Estrutura para armazenar o endereço
struct endereco {
    char rua [30];
    int num;
    char bairro [30];
    char cidade [40];
    char estado [40];
} 
typedef Endereco;

//Estrutura para armazenar as materias
struct materia {
    char nome[30];
    float media;
} 
typedef Materia;


// Estrutura para armazenar informações de um aluno
struct aluno {
    char nome[50];
    int ra;
    char dataNascimento[11];
    Endereco endereco[2];
    Materia materia[5];
} 
typedef Aluno;

struct array_dinamico {
    bool ordenado;  // true indica que quer manter o array ordenado. 
    int tamanho;    // número máximo de elementos que podemos armazenados no array.
    int quantidade; // quantidade atual de elementos armazenados
    Aluno **ptr_dados;     // array de int que representa nossos dados. 
} 
typedef Array_Dinamico;


Array_Dinamico* criar_array_dinamico(int tamanho_array, bool ordenado) {

    Array_Dinamico *array_dinamico = (Array_Dinamico*) malloc(sizeof(Array_Dinamico));
    array_dinamico->ordenado = ordenado;
    array_dinamico->quantidade = 0;
    array_dinamico->tamanho = tamanho_array;
    array_dinamico->ptr_dados = (Aluno**) calloc(tamanho_array, sizeof(Aluno**));
    
    return array_dinamico;

}

void destruir_array_dinamico(Array_Dinamico **array_dinamico_endereco_de_memoria) {

    Array_Dinamico *array_dinamico = *array_dinamico_endereco_de_memoria;
    free(array_dinamico->quantidade);
    free(array_dinamico);
    *array_dinamico_endereco_de_memoria = NULL;

}

bool esta_cheio_array_dinamico(Array_Dinamico* array_dinamico, int tamanho_array) {
   

    return 0;
}

//se array estiver cheio, aumentamos 2 vezes o seu tamanho.
void aumentar_array_dinamico(Array_Dinamico *array_dinamico) {
    
    printf("Aumentando 2 vezes o tamanho atual do array( 2 * %d )\n", array_dinamico->tamanho);

    int *temp = array_dinamico->ptr_dados; 
    array_dinamico->tamanho *= 2;

    array_dinamico->tamanho = (Aluno**)calloc(array_dinamico->tamanho, sizeof(Aluno**)); 

    for (int i = 0; i < array_dinamico->tamanho; i++ ) { 
        array_dinamico->ptr_dados[i] = temp[i];
    }

    free(temp);
}

//diminuir o tamanho do array pela metade quando tiver 1/4 ou 25% cheio   
void diminuir_array_dinamico(Array_Dinamico *array_dinamico) {

    if ((array_dinamico->quantidade < array_dinamico->tamanho / 4) && 
        (array_dinamico->tamanho >= 4)) { 
       
        //printf("Diminuindo o tamanho atual do array pela metade ( %d / 2 )\n", array_dinamico->tamanho); 
 
        int *temp = array_dinamico->ptr_dados; 
        array_dinamico->tamanho /= 2;
    
        array_dinamico->ptr_dados = (int*)calloc(array_dinamico->tamanho, sizeof(int)); 

        for (int j = 0; j < array_dinamico->tamanho; j++ ) { 
            array_dinamico->ptr_dados[j] = temp[j];
        }
        free(temp);
    }
}

int busca_binaria_iterativa_array_dinamico(int *dados, int quantidade, int valor) {
    
    int inicio = 0, fim = quantidade - 1, index_meio;

    while (inicio <= fim) { // enquanto o array tiver pelo menos 1 elemento.

        index_meio = (inicio + fim) / 2;
        if (dados[index_meio] == valor) 
           return index_meio;
        
        else if (dados[index_meio] > valor)
            fim = index_meio - 1;
        
        else 
            inicio = index_meio + 1;
    } 
    return -1;
}    

int busca_binaria_recursiva_array_dinamico(int *dados, int limite_esquerda, int limite_direita, int valor) {    
    
    int index_meio = (limite_esquerda + limite_direita) / 2;

    printf("%d\n", index_meio);

    if (limite_esquerda > limite_direita) //caso base 1
       return -1;
    
    if (dados[index_meio] == valor) //caso base 2
       return index_meio; 

    else if (dados[index_meio] < valor)   
       return busca_binaria_recursiva_array_dinamico(dados, index_meio + 1, limite_direita, valor);

    else 
       return busca_binaria_recursiva_array_dinamico(dados, limite_esquerda, index_meio - 1, valor);

    return -1;
}

int busca_sequencial_array_dinamico(Array_Dinamico *array_dinamico, int valor) {    
    
    for (int i = 0; i < array_dinamico->quantidade; i++) {
        if (array_dinamico->dados[i] == valor) 
            return i; //retorna o index do elemento.
    }    
    return -1; //caso não encontre o elemente, retorna -1 com index.
}

int busca_sequencial_ordenada_array_dinamico(Array_Dinamico *array_dinamico, int valor) {    
    
    for (int i = 0; i < array_dinamico->quantidade; i++) {
        if (array_dinamico->dados[i] == valor){ 
            return i; //retorna o index do elemento.
        }else { 
            if (array_dinamico->dados[i] > valor)
                return -1; //para a busca
        } 
    }    
    return -1; //caso não encontre o elemente, retorna -1 com index.
}

void imprimir_array_dinamico(const Array_Dinamico *array_dinamico) {
   
   //Implemente

}

void ordenar_array_dinamico(const Array_Dinamico *array_dinamico) {
   
   //Implemente

}
  
  
void adicionar_array_dinamico(Array_Dinamico *array_dinamico, int valor) {    
   
   //implemente

}


int busca_array_dinamico(Array_Dinamico *array_dinamico, int valor) { 
    
    //implemente

    return 0;
}

void remover_array_dinamico(Array_Dinamico *array_dinamico, int index) { 
   
   //implemente
   
}

int acessar_array_dinamico(const Array_Dinamico *array_dinamico, int index) {

    // implemente
    return 0;

} 

int acessar_verificado_array_dinamico(const Array_Dinamico *array_dinamico, int index) { // verifica se tem elemento

    // implemente
    
    return 0;

}

int tamanho_array_dinamico(const Array_Dinamico *array_dinamico) {
    
    // implemente
    return 0;

}

int quantidade_array_dinamico(const Array_Dinamico *array_dinamico) {
 
    return 0;

}

void carregar_arquivo_array_dinamico(Array_Dinamico *array_dinamico, char *caminho_arquivo) { 

   //ler o arquivo

}

void gravar_arquivo_array_dinamico(Array_Dinamico *array_dinamico, char *caminho_arquivo) { 

   //se arquivo já existir remove tudo e cria novamente
   //gravar no arquivo no disco

}

void menu() { 

   int tamanho = 4; //vamos começar com um tamanho fixo e depois vamos dobrando o seu tamanho.  

   bool ordenado = false; 
  
   Array_Dinamico *array_dinamico = criar_array_dinamico(tamanho, ordenado);
   
   Aluno *aluno01 = (Aluno*) malloc(1 * sizeof(Aluno*));
    
   void adicionar_array_dinamico(array_dinamico, aluno01);   
    
   //Aluno *aluno_do_array = array_dinamico->ptr_dados[0]; 

   //printf("%d %s\n", aluno01->ra, aluno_do_array->nome ); 

   free(aluno01);
   destruir_array_dinamico(&array_dinamico);

}

int main(int argc, char *argv[]) {

    menu();

}