#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//MatrixCreate ler e criar os elementos
//MatrixDestrÃ³i dar free na memÃ³ria;

struct no {
    int line;
    int column;
    double info;
    struct no *right;
    struct no *below;
};
typedef struct no Matrix;

void tiraNo(Matrix *M, int posicaoi, int posicaoj);

Matrix *CriarN0(int l, int c) {
    Matrix *N = (Matrix *)malloc(sizeof(Matrix));
    N->info = 0;
    N->line = l;
    N->column = c;
    N->right = NULL;
    N->below = NULL;
    return N;
}

Matrix *zeros(int n, int m) {
    Matrix *M;
    M = (Matrix *)malloc(sizeof(Matrix));
    M->line = n;
    M->column = m;
    M->right = M;
    M->below = M;
    int i;
    Matrix *aux;
    for (i = n; i > 0; i--) {
        aux = CriarN0(i, -1);
        aux->below = M->below;
        M->below = aux;
        aux->right = aux;
    }
    for (i = m; i > 0; i--) {
        aux = CriarN0(-1, i);
        aux->right = M->right;
        M->right = aux;
        aux->below = aux;
    }
    return M;
}

//arrumar tratamento de erro se a posicao ja existe
void matrix_setelem(Matrix *M, int posicaoi, int posicaoj, float novo_valor) {
    int k, i, j;
    Matrix *aux2, *aux3;
    Matrix *aux = CriarN0(posicaoi, posicaoj);
    aux->info = novo_valor;

    //apontar o aux para o inicio
    if (posicaoi < 1 || posicaoj < 1 || posicaoi > M->line || posicaoj > M->column) {
        printf("ERRO, posicao invalida!!!\n");
        free(aux);
        return;
    } else if (novo_valor == 0) {
        tiraNo(M, posicaoi, posicaoj);
        free(aux);
        return;
    } else {
        //fazendo ele percorrer atÃ© a posicao que eu quero colocar
        // o valor
        // tratamento de erro se a posicao jÃ¡ conter um valor
        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2->right;
        }
        for (aux3 = aux2, aux2 = aux2->below; aux2->line < posicaoi && aux2->line != -1;
             aux3 = aux2, aux2 = aux2->below)
            ;

        //printf("posicao-> %d %d %lf\n",aux2->line,aux2->column,aux2->info);
        if (aux2->line == posicaoi) {
            aux2->info = aux->info;
            free(aux);
        } else {
            aux->below = aux2;
            aux3->below = aux;
            aux2 = M;
            for (i = 0; i < posicaoi; i++) {
                aux2 = aux2->below;
            }

            for (aux3 = aux2, aux2 = aux2->right; aux2->column < posicaoj &&
                                                  aux2->column != -1;
                 aux3 = aux2, aux2 = aux2->right)
                ;
            aux->right = aux2;
            aux3->right = aux;
        }
    }

    return;
}

//retorna o valor do elemento (x, y) da matriz m.
float matrix_getelem(Matrix *M, int posicaoi, int posicaoj) {
    int k, i, j;
    double valor;
    Matrix *aux2, *aux3;

    //apontar o aux para o inicio
    if (posicaoi < 1 || posicaoj < 1 || posicaoi > M->line || posicaoj > M->column) {
        printf("ERRO, posicao selecionada invalida!!!\n");
        return -999;
    } else {
        //fazendo ele percorrer atÃ© a posicao que eu quero colocar
        // o valor
        // tratamento de erro se a posicao jÃ¡ conter um valor
        aux2 = M;
        for (i = 0; i < posicaoj; i++) {
            aux2 = aux2->right;
        }
        for (aux3 = aux2, aux2 = aux2->below; aux2->line < posicaoi && aux2->line != -1;
             aux3 = aux2, aux2 = aux2->below)
            ;

        if (aux2->line == posicaoi) {  //tirar o no quando for 0 /preencher aleatorio / tempo de execuÃ§Ã£o das funÃ§Ãµes
            valor = aux2->info;
        } else {
            return 0.0;
        }

        //printf("posicao-> %d %d %lf\n", aux2->line, aux2->column, aux2->info);
    }

    return valor;
}

void imprimir(Matrix *M) {
    int i, j;
    Matrix *aux;
    aux = M->below;
    printf("IMPRESSAO!!\n");
    for (aux = M->below; aux != M; aux = aux->below) {
        for (aux = aux->right; aux->column != -1; aux = aux->right) {
            printf("%d %d %lf \n", aux->line, aux->column, aux->info);
        }
    }
}

void imprimirBurra(Matrix *M) {
    int i, j;

    for (i = 0; i < M->line; i++) {
        for (j = 0; j < M->column; j++) {
            printf("%.1lf\t", matrix_getelem(M, i + 1, j + 1));
        }
        printf("\n");
    }
    return;
}

Matrix *criarAleatorio(int posicaoi, int posicaoj) {
    int i, j;
    time_t t;
    Matrix *M;
    M = zeros(posicaoi, posicaoj);
    srand((unsigned int)time(&t));
    for (i = 0; i < M->line; i++) {
        for (j = 0; j < M->column; j++) {
            matrix_setelem(M, i + 1, j + 1, ((float)rand() / (float)(RAND_MAX)) * 5.0);
        }
    }
    return M;
}

void tiraNo(Matrix *M, int posicaoi, int posicaoj) {
    int i, j;
    Matrix *aux, *aux2;
    aux = M;
    for (i = 0; i != posicaoi; i++) {
        aux = aux->below;
    }
    for (; aux->right->column < posicaoj && aux->right->column != -1; aux = aux->right)
        ;
    if (aux->right->column == posicaoj) {
        aux->right = aux->right->right;
    }
    aux = M;
    for (j = 0; j != posicaoj; j++) {
        aux = aux->right;
    }
    for (; aux->below->line < posicaoi && aux->below->line != -1; aux = aux->below)
        ;
    if (aux->below->line == posicaoi) {
        aux2 = aux->below;
        aux->below = aux->below->below;
        free(aux2);
    }
    return;
}

Matrix *MatrixCreate() {
    int k, i, j, posicaoi, posicaoj;
    double novo_valor;
    Matrix *aux2, *aux3, *M;
    scanf("%d %d", &i, &j);
    if (i < 0 || j < 0) {
        M = NULL;
        return M;
    } else {
        M = zeros(i, j);
    }

    while (1) {
        //apontar o aux para o inicio
        scanf("%d %d %lf", &posicaoi, &posicaoj, &novo_valor);
        Matrix *aux = CriarN0(posicaoi, posicaoj);
        aux->info = novo_valor;

        if (posicaoi == 0 || posicaoj == 0) {
            printf("ExecuÃ§Ã£o encerrada!!!\n");
            break;
        } else {
            //fazendo ele percorrer atÃ© a posicao que eu quero colocar
            // o valor
            // tratamento de erro se a posicao jÃ¡ conter um valor
            matrix_setelem(M, posicaoi, posicaoj, novo_valor);
        }
    }

    return M;
}

void matrix_destroy(Matrix *M) {
    int i, j;
    Matrix *aux, *aux2;
    aux = M->below;
    for (aux2 = M, aux = M->below; aux != M; aux2 = aux, aux = aux->below) {
        for (aux2 = aux2->right, aux = aux->right; aux->column != -1; aux2 = aux) {
            aux = aux->right;
            free(aux2);
        }
        free(aux2);
    }

    free(aux);
    return;
}

Matrix *somaBurra(Matrix *A, Matrix *B) {
    int i, j;
    if (A->line == B->line && A->column == B->column) {
        Matrix *C = zeros(A->line, A->column);
        for (i = 1; i <= A->line; i++) {
            for (j = 1; j <= A->column; j++) {
                matrix_setelem(C, i, j, matrix_getelem(A, i, j) + matrix_getelem(B, i, j));
            }
        }
        return C;
    }
    return NULL;
}

Matrix *soma(Matrix *A, Matrix *B) {
    Matrix *auxA, *auxB;

    if (A->line == B->line && A->column == B->column) {
        Matrix *C;
        C = zeros(B->line, A->column);
        auxA = A->below->right;
        auxB = B->below->right;
        while (auxA->line != -1 && auxB->line != -1) {
            while (auxA->column != -1 && auxB->column != -1) {
                if (auxA->column < auxB->column) {
                    matrix_setelem(C, auxA->line, auxA->column, auxA->info);
                    auxA = auxA->right;
                } else if (auxA->column > auxB->column) {
                    matrix_setelem(C, auxB->line, auxB->column, auxB->info);
                    auxB = auxB->right;
                } else if (auxA->column == auxB->column) {
                    matrix_setelem(C, auxB->line, auxB->column, auxA->info + auxB->info);
                    auxA = auxA->right;
                    auxB = auxB->right;
                }
            }
            auxA = auxA->below->right;
            auxB = auxB->below->right;
        }
        return C;
    }
}

void main() {
    int i, n;
    double valor;
    Matrix *M1, *M2, *M3;
    //M=zeros(3,4);
    //M = MatrixCreate();
    //imprimir(M);
    //matrix_destroy(M);
    //imprimir(M);
    for (n = 200; n < 3000; n = n*2) {

        M1 = criarAleatorio(n,n);
        M2 = criarAleatorio(n,n);


        clock_t Ticks1[2];
        Ticks1[0] = clock();
        M3 = somaBurra(M1, M2);
        Ticks1[1] = clock();
        double Tempo1 = (Ticks1[1] - Ticks1[0]) * 1000.0 / CLOCKS_PER_SEC;

        clock_t Ticks2[2];
        Ticks2[0] = clock();
        M3 = soma(M1, M2);
        Ticks2[1] = clock();
        double Tempo2 = (Ticks2[1] - Ticks2[0]) * 1000.0 / CLOCKS_PER_SEC;
        printf("%d %g %g\n", n, Tempo1, Tempo2);

        matrix_destroy(M1);
        matrix_destroy(M2);
        matrix_destroy(M3);
    }
    //matrix_setelem(M,1,1,50.0);
    //matrix_setelem(M,1,2,255.0);
    //matrix_setelem(M,2,1,255.0);
    //matrix_setelem(M,1,1,455.0);

    //valor= matrix_getelem(M, 1, 1);

    //imprimir(M);
    //printf("O valor retornado Ã© %lf\n",valor);

    return;
}