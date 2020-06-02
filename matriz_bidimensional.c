#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes tamaño de matriz
const int FILAS = 10;
const int COLUMNAS = 10;

void mostrar_menu();

int numero_aleatorio_entre(int, int);
void llenar_matriz(int[FILAS][COLUMNAS]);
void imprimir_matriz(int[FILAS][COLUMNAS]);
void imprimir_total_filas(int[FILAS][COLUMNAS]);
void imprimir_promedio_columnas(int[FILAS][COLUMNAS]);
void obtener_columna(int[FILAS][COLUMNAS], int[FILAS], int);
int total_fila(int[]);
double promedio_array(int[], int);
void suma_diagonal_principal(int[FILAS][COLUMNAS], int);
void promedio_diagonal_secundaria(int[FILAS][COLUMNAS], int);
void pares_matriz_triangular_superior(int[FILAS][COLUMNAS], int);
void impares_matriz_triangular_inferior(int[FILAS][COLUMNAS], int);
void Pausa();
void limpiarErrores(FILE *);

int main()
{
    mostrar_menu();

    return 0;
}

void mostrar_menu()
{
    int matriz[FILAS][COLUMNAS];
    llenar_matriz(matriz);

    int opcion;

    do
    {
        printf("=============\n");
        printf("==  MENÚ   ==\n");
        printf("=============\n");
        printf("1) -Mostrar la matriz por filas.\n");
        printf("2) -Calcular el total por filas.\n");
        printf("3) -Calcular el promedio por columnas.\n");
        printf("4) -Sumatoria de los valores ubicados en la diagonal principal.\n");
        printf("5) -Promedio de los valores ubicados en la diagonal secundaria.\n");
        printf("6) -Contar números pares están ubicados en la matriz triangular superior.\n");
        printf("7) -Contar números impares están ubicados en la matriz triangular inferior.\n");
        printf("\n0) -SALIR.\n\n");

        do
        {
            printf("Ingrese un número entre 0 y 7.\n");
            if (scanf("%d", &opcion) == 0)
            {
                limpiarErrores(stdin);
                printf("Error, no es un número\n");
                break;
            }

        } while (opcion < 0 || opcion > 7);

        switch (opcion)
        {
        case 1:
            system("clear");
            imprimir_matriz(matriz);
            break;
        case 2:
            system("clear");
            imprimir_total_filas(matriz);
            break;
        case 3:
            system("clear");
            imprimir_promedio_columnas(matriz);
            break;
        case 4:
            system("clear");
            suma_diagonal_principal(matriz, FILAS);
            break;
        case 5:
            system("clear");
            promedio_diagonal_secundaria(matriz, FILAS);
            break;
        case 6:
            system("clear");
            pares_matriz_triangular_superior(matriz, FILAS);
            break;
        case 7:
            system("clear");
            impares_matriz_triangular_inferior(matriz, FILAS);
            break;
        case 0:
            printf("Saliendo...\n");
            break;
        }
        limpiarErrores(stdin);
        Pausa();
        system("clear");

    } while (opcion != 0);
}

void llenar_matriz(int matriz[FILAS][COLUMNAS])
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            matriz[i][j] = numero_aleatorio_entre(1, 50);
        }
    }
}

void imprimir_matriz(int matriz[FILAS][COLUMNAS])
{
    printf("Columnas:");
    for (int x = 0; x < COLUMNAS; x++)
    {
        printf(" %02d ", x + 1);
    }
    printf("\n");
    printf("\n");

    for (int i = 0; i < FILAS; i++)
    {
        printf("Fila %02d: ", i + 1);
        for (int j = 0; j < COLUMNAS; j++)
        {
            printf(" %02d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void imprimir_total_filas(int matriz[FILAS][COLUMNAS])
{
    int mayor_suma = 0;
    int numero_fila = 0;

    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            printf("%02d", matriz[i][j]);
            if (j < COLUMNAS - 1)
            {
                printf(" + ");
            }
        }
        int total_f = total_fila(matriz[i]);
        if (total_f > mayor_suma)
        {
            mayor_suma = total_f;
            numero_fila = i + 1;
        }

        printf("  =  %d", total_f);
        printf("\n");
    }
    printf("\n");
    printf("Fila con mayor total: ");
    printf("Fila %d\n", numero_fila);
    printf("Total: %d\n", mayor_suma);
}

void imprimir_promedio_columnas(int matriz[FILAS][COLUMNAS])
{
    double menorPromedio = 100000000;
    int menorColumna = 0;
    printf("Columnas:");
    for (int x = 0; x < COLUMNAS; x++)
    {
        printf("  %02d  ", x + 1);
    }
    printf("\n");
    printf("\n");

    for (int i = 0; i < FILAS; i++)
    {
        printf("Fila %02d: ", i + 1);
        for (int j = 0; j < COLUMNAS; j++)
        {
            printf("  %02d  ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------------------------\n");
    printf("Promed: ");
    for (int i = 0; i < COLUMNAS; i++)
    {
        int columna[FILAS];
        double promedio = 0;

        obtener_columna(matriz, columna, i);
        promedio = promedio_array(columna, FILAS);
        printf(" %.1f ", promedio);

        if (promedio < menorPromedio)
        {
            menorColumna = i + 1;
            menorPromedio = promedio;
        }
    }
    printf("\n\n");
    printf("Menor promedio: %.1f\n", menorPromedio);
    printf("Columna: %d\n", menorColumna);
}

int total_fila(int fila[])
{
    int total = 0;
    for (int i = 0; i < COLUMNAS; i++)
    {
        total = total + fila[i];
    }

    return total;
}

void obtener_columna(int matriz[FILAS][COLUMNAS], int columna[FILAS], int num_columna)
{
    for (int i = 0; i < FILAS; i++)
    {
        columna[i] = matriz[i][num_columna];
    }
}

double promedio_array(int vector[], int tamanos)
{
    int sumatoria = 0;
    double promedio = 0;
    for (int i = 0; i < tamanos; i++)
    {
        sumatoria = sumatoria + vector[i];
    }

    promedio = (double)sumatoria / (double)tamanos;

    return promedio;
}

void suma_diagonal_principal(int matriz[FILAS][COLUMNAS], int tamano)
{
    int sumatoria = 0;
    for (int i = 0; i < tamano; i++)
    {
        for (int j = 0; j < tamano; j++)
        {
            if (j == i)
            {
                printf(" %02d ", matriz[i][j]);
                sumatoria = sumatoria + matriz[i][i];
            }
            else
            {
                printf(" -- ");
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Sumatoria: %d\n", sumatoria);
}

void promedio_diagonal_secundaria(int matriz[FILAS][COLUMNAS], int tamano)
{
    int sumatoria = 0;
    for (int i = 0; i < tamano; i++)
    {
        for (int j = 0; j < tamano; j++)
        {
            if (i == ((tamano - 1) - j))
            {
                printf(" %02d ", matriz[i][j]);
                sumatoria = sumatoria + matriz[i][i];
            }
            else
            {
                printf(" -- ");
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Promedio: %.1f\n", (double)sumatoria / (double)tamano);
}

void pares_matriz_triangular_superior(int matriz[FILAS][COLUMNAS], int tamano)
{
    int contadorPares = 0;
    for (int i = 0; i < tamano; i++)
    {
        for (int j = 0; j < tamano; j++)
        {
            if (j >= i + 1)
            {
                if (matriz[i][j] % 2 == 0)
                {
                    printf(" %02d*", matriz[i][j]);
                    contadorPares++;
                }
                else
                {

                    printf(" %02d ", matriz[i][j]);
                }
            }
            else
            {
                printf(" -- ");
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Total pares: %d\n\n", contadorPares);
}

void impares_matriz_triangular_inferior(int matriz[FILAS][COLUMNAS], int tamano)
{
    int contadorImpares = 0;
    for (int i = 0; i < tamano; i++)
    {
        for (int j = 0; j < tamano; j++)
        {
            if (j <= i - 1)
            {
                if (matriz[i][j] % 2 != 0)
                {
                    printf(" %02d*", matriz[i][j]);
                    contadorImpares++;
                }
                else
                {

                    printf(" %02d ", matriz[i][j]);
                }
            }
            else
            {
                printf(" -- ");
            }
        }
        printf("\n");
    }
    printf("\n");
    printf("Total impares: %d\n\n", contadorImpares);
}

int numero_aleatorio_entre(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void Pausa()
{
    printf("\n\nPresione una tecla para continuar...\n");
    fflush(stdout);
    getchar();
}

void limpiarErrores(FILE *in)
{
    int ch;
    do
        ch = fgetc(in);
    while (ch != EOF && ch != '\n');
    clearerr(in);
}