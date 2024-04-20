#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// trocar pela quantidade de vertices da sua matriz/grafo
#define tamanho_matriz 3151

void Menu();

int min_e_max(int n, int n1);

int grau_do_maior_vertice(int **matriz);

void mostra_matriz(int **matriz);

void ler_arquivo(char *nome_arquivo, int **matriz);

void escrever_graus_em_arquivo(char *nome_arquivo, int **matriz, int tamanho);

void vertices_isolados(int **matriz, int tamanho);

int main() {
    int **matriz = (int **)malloc(tamanho_matriz * sizeof(int *));

    for (int i = 0; i < tamanho_matriz; i++) {
        matriz[i] = (int *)malloc(tamanho_matriz * sizeof(int));
    }

    ler_arquivo("dados_matriz.txt", matriz);
    //mostra_matriz(matriz);

    int maior_grau; 
    maior_grau = grau_do_maior_vertice(matriz);

    int choice = 0;
    
    do {
        Menu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("\nO vertice com maior grau eh: %i\n", maior_grau);
                break;

            case 2:
                escrever_graus_em_arquivo("dados_grafos_graus.txt", matriz, tamanho_matriz);
                printf("Criado arquivo!\n");
                break;

            case 3:
                vertices_isolados(matriz, tamanho_matriz);
                break;
            case 4:
                printf("Saindo...");
                break;
            default: 
                printf("Erro!\n");
        }
    } while(choice != 4);

    return 0;

}

void Menu() {
    printf("=====================================================================\n");
    printf("     1. Qual(is) o vertice(s) com maior(es) grau?                    \n");
    printf("     2. Numero do vertices seguido pelo seu respectivo grau          \n");
    printf("     3. Se existir, quais sao os vertices isolados?                  \n");
    printf("     4. Sair                                                         \n");
    printf("=====================================================================\n");
} 

void ler_arquivo(char *nome_arquivo, int **matriz) {
    FILE *arch;
    char linha[tamanho_matriz];
    char *token;
    int i = 0, j = 0;
    arch = fopen(nome_arquivo, "r");
    while (fgets(linha, tamanho_matriz, arch)) {
        token = strtok(linha, " ");
        j = 0;
        while (j < tamanho_matriz) {

            matriz[i][j] = atoi(token);
            token = strtok(NULL, " ");
            j++;
        }
        i++;
        if (i >= tamanho_matriz) {
            break;
        }
    }
    
    fclose(arch);
}

void mostra_matriz(int **matriz) {
    int i, j;

    for (i = 0; i < tamanho_matriz; i++) {
        for (j = 0; j < tamanho_matriz; j++) {

            printf(" %i ", matriz[i][j]);
        }

        printf("\n");
    }
}

int grau_do_maior_vertice(int **matriz) {
    int i, j, maior_grau, aux = 0, vertice_com_maior_grau;
    for (i = 0; i < tamanho_matriz; i++) {
        for (j = 0; j < tamanho_matriz; j++) {
            if (matriz[i][j] == 1) {
                aux++;
            }
        }
        if (aux > maior_grau) {
            maior_grau = aux;
            vertice_com_maior_grau = i;
        }
        aux = 0;
    }

    return vertice_com_maior_grau;
}

void escrever_graus_em_arquivo(char *nome_arquivo, int **matriz, int tamanho) {
    FILE *arch;
    arch = fopen(nome_arquivo, "w");
    if (arch == NULL) {
        printf("Erro ao abrir o arquivo para escrita.");
        exit(1);
    }

    int *graus = (int *)malloc(tamanho * sizeof(int));
    for (int i = 0; i < tamanho; i++) {
        int grau = 0;
        for (int j = 0; j < tamanho; j++) {
            if (matriz[i][j] == 1) {
                grau++;
            }
        }
        graus[i] = grau;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arch, "%d %d\n", i, graus[i]);
    }

    fclose(arch);
    free(graus);
}

void vertices_isolados(int **matriz, int tamanho) {
    printf("Vertices isolados:\n");
    for (int i = 0; i < tamanho; i++) {
        int grau = 0;
        for (int j = 0; j < tamanho; j++) {
            grau += matriz[i][j];
        }
        if (grau == 0) {
            printf("%d\n", i);
        }
    }
    printf("\n");
}


