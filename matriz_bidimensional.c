#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constantes tamaño de matriz
// El tamaño es de 10 x 10
const int FILAS = 10;
const int COLUMNAS = 10;


// AQUÍ SE DECLARAN LOS PROTOTIPOS DE FUNCIONES Y MÉTODOS
// LAS CUALES SE ESPECIFICAN DESPUÉS DEL MÉTDO MAIN
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

// Metodo Principal
int main()
{
    // Llamar al método mostrar menú
    mostrar_menu();
    return 0;
}

// Metodo para mostrar menú
void mostrar_menu()
{
    // Definir el array para la matriz
    // es un array de enteros con tamaño 10 x 10
    int matriz[FILAS][COLUMNAS];
    // llenar la matriz de números
    llenar_matriz(matriz);

    // Variable que almacena la opcion ingresada
    int opcion;

    // Ciclo para mostrar el menú
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

        // Ciclo para asegurarse que se ingresa un numero
        do
        {
            printf("Ingrese un número entre 0 y 7.\n");
            
            // scanf devuelve el número de elementos leídos con éxito, 
            // por lo que en este caso debe devolver 1 para valores válidos
            // %d indica a scanf que se espera un entero
            if (scanf("%d", &opcion) == 0)
            {
                // Limpiar las entradas en el Buffer
                limpiarErrores(stdin);
                printf("Error, no es un número\n");
                break;
            }

        } while (opcion < 0 || opcion > 7);

        // Condicional switch para lanzar ejercicio según variable opcion
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

// Llenar la matriz pasada para llenarla con números aleatorios
void llenar_matriz(int matriz[FILAS][COLUMNAS])
{
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            matriz[i][j] = numero_aleatorio_entre(1, 50);
        }
    }
}

// Imprimir la matriz pasada como parametro
void imprimir_matriz(int matriz[FILAS][COLUMNAS])
{
    // imprimir linea "columnas"
    printf("Columnas:");
    for (int x = 0; x < COLUMNAS; x++)
    {
        printf(" %02d ", x + 1);
    }
    printf("\n");
    printf("\n");

    // imprimir matriz con numero de fila
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

// Imprimir sumatoria de filas de la matriz
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

// Imprimir promedio de columnas de la matriz
void imprimir_promedio_columnas(int matriz[FILAS][COLUMNAS])
{
    // Estableces un numero muy alto
    // Para poder comparar si los promedios calculados son menores que este
    double menorPromedio = 100000000;
    // Aquí se guardará el numero de columna que tiene el menor promedio
    int menorColumna = 0;
    
    // IMPRIMIR MATRIZ
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

    // Calcular promedios
    for (int i = 0; i < COLUMNAS; i++)
    {
        // Vector o array unidimensional que 
        // guardara los valores de una columna
        int columna[FILAS];

        // La funcion obtener columna devuelve 
        // un vector de con los valores de la columna dada
        // de una matriz
        obtener_columna(matriz, columna, i);
        
        // Variable para guardar el primedio actual
        double promedio = 0;
        
        // La función promedio_array devuelve un valor numerico
        // del promedio de un vector dado (columna)
        promedio = promedio_array(columna, FILAS);
        // imprimir el promedio obtenido
        printf(" %.1f ", promedio);

        // Si el promedio obtenido es menor a menorPromedio
        // asignar ese valor a menorPromedio y el numero de columna
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

// Obtener la sumatoria de un vector o array aunidimensional (fila)
int total_fila(int fila[])
{
    int total = 0;
    for (int i = 0; i < COLUMNAS; i++)
    {
        total = total + fila[i];
    }

    return total;
}

// Obtener de una matriz una columna especificada como vector
void obtener_columna(int matriz[FILAS][COLUMNAS], int columna[FILAS], int num_columna)
{
    for (int i = 0; i < FILAS; i++)
    {
        columna[i] = matriz[i][num_columna];
    }
}

// Calcular promedio de valores en un vector
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

// Calcular suma de diagonal principal de una matriz CUADRADA
void suma_diagonal_principal(int matriz[FILAS][COLUMNAS], int tamano)
{
    int sumatoria = 0;
    // recorrer matriz por filas
    for (int i = 0; i < tamano; i++)
    {
        // recorrer matriz por columnas
        for (int j = 0; j < tamano; j++)
        {
            // Si el numero de columna j es igual al numero de fila
            // entonces es un elemento de la diagonal y se suma
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

// Calcular suma de diagonal SECUNDARIA de una matriz CUADRADA
void promedio_diagonal_secundaria(int matriz[FILAS][COLUMNAS], int tamano)
{
    int sumatoria = 0;
    // recorrer matriz por filas de mayor a menor (de 9 a 0)
    for (int i = 0; i < tamano; i++)
    {
        // recorrer matriz por columna de menos a mayor
        for (int j = 0; j < tamano; j++)
        {
            // Si el numero de columna i es igual a 
            // el tamaño de un lado (10 -1 = 9) menos el numero de columna j
            // entonces es un elemento de la diagonal secundaria
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

// Calcular pares de la matriz triangular superior de una matriz cuadrada 
void pares_matriz_triangular_superior(int matriz[FILAS][COLUMNAS], int tamano)
{
    // variable contador de pares
    int contadorPares = 0;
    // recorrer matriz por filas (i)
    for (int i = 0; i < tamano; i++)
    {
        // recorrer matriz por columnas (j)
        for (int j = 0; j < tamano; j++)
        {
            // Si el numero de columna j es mayor o igual al numero de fila+1 (i+1)
            // Es un elemento dentro del triangulo y se imprime
            if (j >= i + 1)
            {
                // Si es par se imprime con un *
                if (matriz[i][j] % 2 == 0)
                {
                    printf(" %02d*", matriz[i][j]);
                    // sumar 1 al contador de pares
                    contadorPares++;
                }
                // si no se imprime normalmente
                else
                {

                    printf(" %02d ", matriz[i][j]);
                }
            }
            // Si no es elemento del triangulo
            // se reemplaza con --
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

// Calcular pares de la matriz triangular inferior de una matriz cuadrada 
void impares_matriz_triangular_inferior(int matriz[FILAS][COLUMNAS], int tamano)
{
    // variable contador de pares
    int contadorImpares = 0;
    // recorrer matriz por filas (i)
    for (int i = 0; i < tamano; i++)
    {
        // recorrer matriz por columnas (j)
        for (int j = 0; j < tamano; j++)
        {
            // Si el numero de columna j es menor o igual al numero de fila-1 (i-1)
            // Es un elemento dentro del triangulo y se imprime
            if (j <= i - 1)
            {
                // Ya saben cual es la idea
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
            // Si no es elemento del triangulo
            // se reemplaza con --
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

// Funcion para devolver un numero aleatorio entre dos numeros dados
int numero_aleatorio_entre(int min, int max)
{
    // Se usa la funcion rand()
    return (rand() % (max - min + 1)) + min;
}

// Funcion para introducir una pausa y un texto "Presione una tecla para continuar..."
void Pausa()
{
    printf("\n\nPresione una tecla para continuar...\n");
    fflush(stdout);
    getchar();
}

// Limpiar entradas en buffer de scanf
void limpiarErrores(FILE *in)
{
    int ch;
    do
        ch = fgetc(in);
    while (ch != EOF && ch != '\n');
    clearerr(in);
}