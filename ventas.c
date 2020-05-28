#include <stdio.h>
#include <stdlib.h>

// Estructura tipo vendedor
struct Vendedor
{
    int id;
    char nombre[50];
};
// Estructura tipo producto
struct Producto
{
    int id;
    char tipo[1];
    double valor;
    double comision;
};
// Estructura tipo venta
struct Venta
{
    struct Vendedor vendedor;
    struct Producto producto;
    int cantidad;
};
// Estructura tipo semana
struct Semana
{
    struct Venta ventas[6];
};

// Definir vendedores
struct Vendedor juan = {.id = 1, .nombre = "Juan"};
struct Vendedor maria = {.id = 2, .nombre = "María"};
struct Vendedor luis = {.id = 3, .nombre = "Luis"};

// Definir productos
struct Producto productoA = {.id = 1, .tipo = "A", .valor = 150, .comision = 0.09};
struct Producto productoB = {.id = 2, .tipo = "B", .valor = 90, .comision = 0.06};

//
void imprimir_resumen_semanal_vendedor(struct Semana *, int);
void imprimir_resumen_semanal_productos(struct Semana *, int);
void imprimir_valor_semanal_productos(struct Semana *, int);
void imprimir_valor_mensual_productos(struct Semana *, int);
void imprimir_comision_semanal_vendedor(struct Semana *, int);
void imprimir_comision_mensual_vendedor(struct Semana *, int);
void imprimir_total_comision(struct Semana *, int);
void imprimir_semana_mas_vendida_producto(struct Semana *, int, struct Producto);
void imprimir_vendedor_mas_ventas(struct Semana *, int);
//
double venta_total_vendido_producto(struct Venta *, int, struct Producto);

//
double comision_vendido_vendedor(struct Venta *, int, struct Vendedor);

//
double comision_vendido_vendedor_producto(struct Venta *, int, struct Vendedor, struct Producto);

// Imprimir venta por vendedor
void imprimir_venta_por_vendedor(struct Venta *, int, struct Producto);

// Imprimir venta por producto
void imprimir_venta_por_producto(struct Venta *, int, struct Producto);

// prototipo de funcion filtrar por vendedor
struct Venta *filtrar_por_vendedor(struct Vendedor, struct Venta *, int, int *);

// prototipo de funcion filtrar por producto
struct Venta *filtrar_por_producto(struct Producto, struct Venta *, int, int *);

// Funcion principal Main()
int main()
{
    // Array de semanas (4 semanas)
    struct Semana semanas[] = {
        // Ventas Semana 1
        {
            .ventas[0] = {.vendedor = juan, .producto = productoA, .cantidad = 50},
            .ventas[1] = {.vendedor = maria, .producto = productoA, .cantidad = 30},
            .ventas[2] = {.vendedor = luis, .producto = productoA, .cantidad = 4},
            .ventas[3] = {.vendedor = juan, .producto = productoB, .cantidad = 60},
            .ventas[4] = {.vendedor = maria, .producto = productoB, .cantidad = 50},
            .ventas[5] = {.vendedor = luis, .producto = productoB, .cantidad = 4}},
        // Ventas Semana 2
        {
            .ventas[0] = {.vendedor = juan, .producto = productoA, .cantidad = 20},
            .ventas[1] = {.vendedor = maria, .producto = productoA, .cantidad = 35},
            .ventas[2] = {.vendedor = luis, .producto = productoA, .cantidad = 25},
            .ventas[3] = {.vendedor = juan, .producto = productoB, .cantidad = 40},
            .ventas[4] = {.vendedor = maria, .producto = productoB, .cantidad = 50},
            .ventas[5] = {.vendedor = luis, .producto = productoB, .cantidad = 45}},
        // Ventas Semana 3
        {
            .ventas[0] = {.vendedor = juan, .producto = productoA, .cantidad = 30},
            .ventas[1] = {.vendedor = maria, .producto = productoA, .cantidad = 18},
            .ventas[2] = {.vendedor = luis, .producto = productoA, .cantidad = 15},
            .ventas[3] = {.vendedor = juan, .producto = productoB, .cantidad = 10},
            .ventas[4] = {.vendedor = maria, .producto = productoB, .cantidad = 15},
            .ventas[5] = {.vendedor = luis, .producto = productoB, .cantidad = 20}},
        // Ventas Semana 4
        {
            .ventas[0] = {.vendedor = juan, .producto = productoA, .cantidad = 25},
            .ventas[1] = {.vendedor = maria, .producto = productoA, .cantidad = 35},
            .ventas[2] = {.vendedor = luis, .producto = productoA, .cantidad = 15},
            .ventas[3] = {.vendedor = juan, .producto = productoB, .cantidad = 18},
            .ventas[4] = {.vendedor = maria, .producto = productoB, .cantidad = 21},
            .ventas[5] = {.vendedor = luis, .producto = productoB, .cantidad = 20}},
    };

    imprimir_resumen_semanal_vendedor(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_resumen_semanal_productos(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_valor_semanal_productos(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_valor_mensual_productos(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_comision_semanal_vendedor(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_comision_mensual_vendedor(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_total_comision(semanas, sizeof(semanas) / sizeof(struct Semana));
    imprimir_semana_mas_vendida_producto(semanas, sizeof(semanas) / sizeof(struct Semana), productoA);
    imprimir_semana_mas_vendida_producto(semanas, sizeof(semanas) / sizeof(struct Semana), productoB);
    imprimir_vendedor_mas_ventas(semanas, sizeof(semanas) / sizeof(struct Semana));

    return 0;
}

// Funciones para imprimir

void imprimir_resumen_semanal_vendedor(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("============================\n");
    printf("RESUMEN SEMANAL POR VENDEDOR\n");
    printf("============================\n");

    for (int i = 0; i < tamano; i++)
    {
        printf("\n=========\n");
        printf("Semana %d: \n", (i + 1));
        printf("=========\n");

        // Tamaño de array ventas
        int tamano = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        // Tamaño de array de ventas filtrado
        // int nuevoTamano = 0;
        // struct Venta *ventasX = filtrar_por_vendedor(juan, semanas[i].ventas, tamano, &nuevoTamano);

        imprimir_venta_por_vendedor(semanas[i].ventas, tamano, productoA);
        imprimir_venta_por_vendedor(semanas[i].ventas, tamano, productoB);
    }
}

void imprimir_resumen_semanal_productos(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("=============================\n");
    printf("RESUMEN SEMANAL POR PRODUCTOS\n");
    printf("=============================\n");

    for (int i = 0; i < tamano; i++)
    {
        printf("\n=========\n");
        printf("Semana %d: \n", (i + 1));
        printf("=========\n");

        // Tamaño de array ventas
        int tamano = sizeof(semanas[i].ventas) / sizeof(struct Venta);
        // Tamaño de array de ventas filtrado
        int nuevoTamano = 0;
        struct Venta *ventasX = filtrar_por_vendedor(juan, semanas[i].ventas, tamano, &nuevoTamano);

        imprimir_venta_por_producto(semanas[i].ventas, tamano, productoA);
        imprimir_venta_por_producto(semanas[i].ventas, tamano, productoB);
    }
}

void imprimir_valor_semanal_productos(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("==================================\n");
    printf("VALOR VENDIDO SEMANAL POR PRODUCTO\n");
    printf("==================================\n");

    for (int i = 0; i < tamano; i++)
    {
        printf("\n=========\n");
        printf("Semana %d: \n", (i + 1));
        printf("=========\n");

        // Tamaño de array ventas
        int tamanoVentas = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        double venta_productoA = venta_total_vendido_producto(semanas[i].ventas, tamanoVentas, productoA);
        printf("Producto A: $ %.2f\n", venta_productoA);

        double venta_productoB = venta_total_vendido_producto(semanas[i].ventas, tamanoVentas, productoB);
        printf("Producto B: $ %.2f\n", venta_productoB);
    }
}

void imprimir_valor_mensual_productos(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("==================================\n");
    printf("VALOR VENDIDO MENSUAL POR PRODUCTO\n");
    printf("==================================\n");

    printf("\n============\n");
    printf("Mes de Marzo\n");
    printf("============\n");

    double sumatoriaA = 0;
    double sumatoriaB = 0;

    for (int i = 0; i < tamano; i++)
    {
        // Tamaño de array ventas
        int tamano = sizeof(semanas[i].ventas) / sizeof(struct Venta);
        // Tamaño de array de ventas filtrado
        int nuevoTamano = 0;
        struct Venta *ventasX = filtrar_por_vendedor(juan, semanas[i].ventas, tamano, &nuevoTamano);

        double venta_productoA = venta_total_vendido_producto(semanas[i].ventas, tamano, productoA);
        sumatoriaA = sumatoriaA + venta_productoA;

        double venta_productoB = venta_total_vendido_producto(semanas[i].ventas, tamano, productoB);
        sumatoriaB = sumatoriaB + venta_productoB;
    }

    printf("Producto A: $ %.2f\n", sumatoriaA);
    printf("Producto B: $ %.2f\n", sumatoriaB);
}

void imprimir_comision_semanal_vendedor(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("======================================\n");
    printf("COMISION SEMANAL PRODUCTO POR VENDEDOR\n");
    printf("======================================\n");

    for (int i = 0; i < tamano; i++)
    {
        printf("\n=========\n");
        printf("Semana %d: \n", (i + 1));
        printf("=========\n");

        // Tamaño de array ventas
        int tamano = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        struct Producto p[] = {productoA, productoB};
        struct Vendedor v[] = {juan, maria, luis};

        for (int j = 0; j < 2; j++)
        {
            printf("Producto %s:\n", p[j].tipo);
            printf("-----------\n");
            for (int k = 0; k < 3; k++)
            {
                double comision = comision_vendido_vendedor_producto(semanas[i].ventas, tamano, v[k], p[j]);
                printf("%s: $ %.2f\n", v[k].nombre, comision);
            }
            printf("\n");
        }
    }
}

void imprimir_comision_mensual_vendedor(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("=============================\n");
    printf("COMISION MENSUAL POR VENDEDOR\n");
    printf("=============================\n");

    printf("Marzo:\n");
    printf("------\n");

    double sumComisionJuan = 0;
    double sumComisionMaria = 0;
    double sumComisionLuis = 0;

    for (int i = 0; i < tamano; i++)
    {
        // Tamaño de array ventas
        int tamanoVentas = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        sumComisionJuan = sumComisionJuan + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, juan);
        sumComisionMaria = sumComisionMaria + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, maria);
        sumComisionLuis = sumComisionLuis + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, luis);
    }

    printf("%s: $ %.2f\n", juan.nombre, sumComisionJuan);
    printf("%s: $ %.2f\n", maria.nombre, sumComisionMaria);
    printf("%s: $ %.2f\n", luis.nombre, sumComisionLuis);
}

void imprimir_total_comision(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("============================\n");
    printf("TOTAL A PAGAR POR COMISIONES\n");
    printf("============================\n");

    printf("Marzo:\n");
    printf("------\n");

    double sumComision = 0;

    for (int i = 0; i < tamano; i++)
    {
        // Tamaño de array ventas
        int tamanoVentas = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        sumComision = sumComision + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, juan);
        sumComision = sumComision + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, maria);
        sumComision = sumComision + comision_vendido_vendedor(semanas[i].ventas, tamanoVentas, luis);
    }

    printf("TOTAL COMISIONES: $ %.2f\n", sumComision);
}

void imprimir_semana_mas_vendida_producto(struct Semana *semanas, int tamano, struct Producto producto)
{
    printf("\n\n");
    printf("=============================\n");
    printf("PRODUCTO %s SEMANA MÁS VENDIDO\n", producto.tipo);
    printf("=============================\n");

    int semana;
    int unidades = 0;

    for (int i = 0; i < tamano; i++)
    {
        // Tamaño de array ventas
        int tamanoVentas = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        // Tamaño de array de ventas filtrado
        int nuevoTamano = 0;
        struct Venta *ventasX = filtrar_por_producto(producto, semanas[i].ventas, tamanoVentas, &nuevoTamano);

        for (int j = 0; j < nuevoTamano; j++)
        {
            if (ventasX[j].cantidad > unidades)
            {
                semana = (i + 1);
                unidades = ventasX[j].cantidad;
            }
        }
    }

    printf("La semana %d se vendieron más unidades del Producto %s\n", semana, producto.tipo);
}

void imprimir_vendedor_mas_ventas(struct Semana *semanas, int tamano)
{
    printf("\n\n");
    printf("=================================\n");
    printf("VENDEDOR CON MÁS VENTAS EN EL MES\n");
    printf("=================================\n");

    struct Venta mayorVenta;
    int semana = 0;

    for (int i = 0; i < tamano; i++)
    {
        // Tamaño de array ventas
        int tamanoVentas = sizeof(semanas[i].ventas) / sizeof(struct Venta);

        for (int j = 0; j < tamanoVentas; j++)
        {
            double valorVenta = semanas[i].ventas[j].cantidad * semanas[i].ventas[j].producto.valor;
            double valorMayorVenta = mayorVenta.cantidad * mayorVenta.producto.valor;
            if (valorVenta > valorMayorVenta)
            {
                semana = i;
                mayorVenta = semanas[i].ventas[j];
            }
        }
    }

    printf("Semana: %d\n", semana + 1);
    printf("Vendedor: %s\n", mayorVenta.vendedor.nombre);
    printf("Producto: %s\n", mayorVenta.producto.tipo);
    printf("Cantidad: %d\n", mayorVenta.cantidad);
    printf("Valor unitario: %.2f\n", mayorVenta.producto.valor);
    printf("Valor total venta: %.2f\n", (mayorVenta.cantidad * mayorVenta.producto.valor));
}

// Funciones para obtener cifras
double venta_total_vendido_producto(struct Venta *ventas, int tamano, struct Producto producto)
{
    double total_venta = 0;

    for (int i = 0; i < tamano; i++)
    {
        if (ventas[i].producto.id == producto.id)
        {
            double valor_venta = ventas[i].producto.valor * ventas[i].cantidad;
            total_venta = total_venta + valor_venta;
        }
    }

    return total_venta;
}

double comision_vendido_vendedor_producto(struct Venta *ventas, int tamano, struct Vendedor vendedor, struct Producto producto)
{
    double total_comision = 0;

    for (int i = 0; i < tamano; i++)
    {
        if (ventas[i].vendedor.id == vendedor.id && ventas[i].producto.id == producto.id)
        {
            double valor_venta = ventas[i].producto.valor * ventas[i].cantidad;
            double valor_comision = valor_venta * ventas[i].producto.comision;
            total_comision = total_comision + valor_comision;
        }
    }

    return total_comision;
}

double comision_vendido_vendedor(struct Venta *ventas, int tamano, struct Vendedor vendedor)
{
    double total_comision = 0;

    for (int i = 0; i < tamano; i++)
    {
        if (ventas[i].vendedor.id == vendedor.id)
        {
            double valor_venta = ventas[i].producto.valor * ventas[i].cantidad;
            double valor_comision = valor_venta * ventas[i].producto.comision;
            total_comision = total_comision + valor_comision;
        }
    }

    return total_comision;
}

struct Venta venta_mas_alta(struct Venta *ventas, int tamano)
{
    struct Venta venta;

    for (int i = 0; i < tamano; i++)
    {
        double total_venta = ventas[i].cantidad * ventas[i].producto.valor;
        if (total_venta > venta.cantidad * venta.producto.valor)
        {
            venta.cantidad = ventas[i].cantidad;
            venta.producto = ventas[i].producto;
            venta.vendedor = ventas[i].vendedor;
        }
    }

    return venta;
}

// Definir funcion imprimir venta por vendedor
void imprimir_venta_por_vendedor(struct Venta *ventas, int tamano, struct Producto producto)
{
    printf("Producto %s:", producto.tipo);
    for (int i = 0; i < tamano; i++)
    {
        if (ventas[i].producto.id == producto.id)
        {
            printf(" %s:", ventas[i].vendedor.nombre);
            printf(" %d;", ventas[i].cantidad);
        }
    }
    printf("\n");
}

// Definir funcion imprimir venta por producto
void imprimir_venta_por_producto(struct Venta *ventas, int tamano, struct Producto producto)
{
    int sum = 0;
    printf("Producto %s:", producto.tipo);
    for (int i = 0; i < tamano; i++)
    {
        if (ventas[i].producto.id == producto.id)
        {
            sum = sum + ventas[i].cantidad;
        }
    }
    printf(" %d\n", sum);
}

// Definir funcion filtrar por vendedor
struct Venta *filtrar_por_producto(struct Producto producto, struct Venta *ventas, int tamano, int *tamano_filtrado)
{
    struct Venta *filtrado = malloc(tamano * sizeof(struct Venta));
    for (int i = 0; i < tamano; ++i)
    {
        if (ventas[i].producto.id == producto.id)
        {
            filtrado[(*tamano_filtrado)++] = ventas[i];
        }
    }
    return filtrado;
}

// Definir funcion filtrar por vendedor
struct Venta *filtrar_por_vendedor(struct Vendedor vendedor, struct Venta *ventas, int tamano, int *tamano_filtrado)
{
    struct Venta *filtrado = malloc(tamano * sizeof(struct Venta));
    for (int i = 0; i < tamano; ++i)
    {
        if (ventas[i].vendedor.id == vendedor.id)
        {
            filtrado[(*tamano_filtrado)++] = ventas[i];
        }
    }
    return filtrado;
}