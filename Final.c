#include <stdio.h>

#define NUM_TRAB 5
#define MAX_LONGITUD 50

void ingresarCantidad(const char productos[][MAX_LONGITUD], const float precios[], int cantidades[]);
void imprimirFactura(const char* nombre, const char* equipo, const char* fecha, const char* hora, const char* descripcion, const char productos[][MAX_LONGITUD], const float precios[], const int cantidades[]);
float obtenerTotal(const float precios[], const int cantidades[]);
void guardarUsuario(const char* nombre, const char* equipo, const char* fecha, const char* hora, const char* descripcion, const char productos[][MAX_LONGITUD], const float precios[], const int cantidades[]);

int main() {
    char nombre[50];
    char equipo[50];
    char fecha[50];
    char hora[50];
    char descripcion[100];
    int opcion;

    printf("Ingrese su nombre: ");
    fgets(nombre, 50, stdin);
    printf("Ingrese la marca de su Equipo: ");
    fgets(equipo, 50, stdin);
    printf("Ingrese la fecha: ");
    fgets(fecha, 50, stdin);
    printf("Ingrese la hora: ");
    fgets(hora, 50, stdin);
    printf("Ingrese una descripción corta del problema: ");
    fgets(descripcion, 50, stdin);

    const char productos[NUM_TRAB][MAX_LONGITUD] = {
            "Mantenimiento preventivo",
            "Instalación de programas",
            "Revisión general",
            "Formateo disco duro",
            "Repotenciación de memoria"
    };

    const float precios[NUM_TRAB] = { 50.0, 60.0, 30.0, 25.0, 100.0 };
    int cantidades[NUM_TRAB] = { 0 };

    do {
        printf("\n\t\tMENU\n");
        printf("1. Ingresar un trabajo\n");
        printf("2. Imprimir factura  \n");
        printf("3. Obtener total de la factura\n");
        printf("4. Guardar y salir del programa\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
        getchar(); // Capturar el salto de línea

        switch (opcion) {
            case 1:
                ingresarCantidad(productos, precios, cantidades);
                break;
            case 2:
                imprimirFactura(nombre, equipo, fecha, hora, descripcion, productos, precios, cantidades);
                break;
            case 3:
                printf("\nTOTAL DE LA FACTURA: $%.2f\n", obtenerTotal(precios, cantidades));
                break;
            case 4:
                guardarUsuario(nombre, equipo, fecha, hora, descripcion, productos, precios, cantidades);
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}

void ingresarCantidad(const char productos[][MAX_LONGITUD], const float precios[], int cantidades[]) {
    int opcion;
    int cantidad;

    printf("\n\tTRABAJOS Y PRECIOS:\n");

    for (int i = 0; i < NUM_TRAB; i++) {
        printf("%d. %s: $%.2f\n", i + 1, productos[i], precios[i]);
    }

    printf("\nIngrese el número del trabajo: ");
    scanf("%d", &opcion);
    printf("Ingrese la cantidad: ");
    scanf("%d", &cantidad);
    getchar(); /// Capturar el salto de línea

    opcion--; /// Ajustar el índice del producto

    printf("Cantidad ingresada correctamente.\n");

    /// Actualizar la cantidad del producto
    if (opcion >= 0 && opcion < NUM_TRAB) {
        cantidades[opcion] += cantidad;
    }
}

void imprimirFactura(const char* nombre, const char* equipo, const char* fecha, const char* hora, const char* descripcion, const char productos[][MAX_LONGITUD], const float precios[], const int cantidades[]) {
    printf("\n\t\tFACTURA\n");
    printf("Nombre: %s", nombre);
    printf("Equipo: %s", equipo);
    printf("Fecha: %s", fecha);
    printf("Hora: %s", hora);
    printf("Descripción: %s", descripcion);

    for (int i = 0; i < NUM_TRAB; i++) {
        if (cantidades[i] > 0) {
            printf("%s: $%.2f x %d\n", productos[i], precios[i], cantidades[i]);
        }
    }
}

float obtenerTotal(const float precios[], const int cantidades[]) {
    float total = 0.0;

    for (int i = 0; i < NUM_TRAB; i++) {
        total += precios[i] * cantidades[i];
    }

    return total;
}

void guardarUsuario(const char* nombre, const char* equipo, const char* fecha, const char* hora, const char* descripcion, const char productos[][MAX_LONGITUD], const float precios[], const int cantidades[]) {
    FILE* archivo = fopen("usuarios.txt", "w");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    float total = 0.0;
    int orden = 1;  // Variable para el número de orden

    fprintf(archivo, "FACTURA %d\n", orden);
    fprintf(archivo, "Fecha: %s", fecha);
    fprintf(archivo, "Hora: %s", hora);
    fprintf(archivo, "Nombre: %s", nombre);
    fprintf(archivo, "Equipo: %s", equipo);
    fprintf(archivo, "Descripción: %s", descripcion);

    for (int i = 0; i < NUM_TRAB; i++) {
        if (cantidades[i] > 0) {
            fprintf(archivo, "Orden %d: %s: $%.2f x %d\n", orden, productos[i], precios[i], cantidades[i]);
            total += precios[i] * cantidades[i];
            orden++;  // Incrementar el número de orden
        }
    }

    fprintf(archivo, "Total de la factura: $%.2f\n", total);

    fclose(archivo);
}