#include <stdio.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define CANT_PALABRAS 5
#define MAX_LARGO 50
#define CANT_COLORES 7

/* Codigo ANSI que vuelve la consola a su color normal */
#define RESET "\033[0m"

/* Dos arreglos "paralelos": nombres[i] usa el codigo codigos[i] */
const char *nombres[CANT_COLORES] = {
    "ROJO", "VERDE", "AMARILLO", "AZUL", "MAGENTA", "CIAN", "BLANCO"
};
const char *codigos[CANT_COLORES] = {
    "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m"
};

/* Pasa un texto a mayusculas para que "rojo", "Rojo" y "ROJO" sirvan igual */
void aMayusculas(char texto[])
{
    int i;
    for (i = 0; texto[i] != '\0'; i++) {
        texto[i] = toupper((unsigned char)texto[i]);
    }
}

/* Devuelve la posicion del color en el arreglo, o -1 si no existe */
int buscarColor(const char color[])
{
    int i;
    for (i = 0; i < CANT_COLORES; i++) {
        if (strcmp(color, nombres[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int main(void)
{
    char palabras[CANT_PALABRAS][MAX_LARGO];
    int colorDePalabra[CANT_PALABRAS];   /* guarda el indice del color de cada palabra */
    char color[MAX_LARGO];
    int i, j;

#ifdef _WIN32
    /* En Windows hay que activar los colores ANSI en la consola */
    HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD modo = 0;
    GetConsoleMode(consola, &modo);
    SetConsoleMode(consola, modo | 0x0004); /* ENABLE_VIRTUAL_TERMINAL_PROCESSING */
#endif

    printf("Colores disponibles:");
    for (j = 0; j < CANT_COLORES; j++) {
        printf(" %s%s%s", codigos[j], nombres[j], RESET);
    }
    printf("\n\n");

    for (i = 0; i < CANT_PALABRAS; i++) {
        /* Pedimos el color hasta que ingrese uno valido */
        do {
            printf("Ingrese Color: ");
            scanf("%49s", color);
            aMayusculas(color);
            colorDePalabra[i] = buscarColor(color);

            if (colorDePalabra[i] == -1) {
                printf("  El color \"%s\" no existe, intente de nuevo.\n", color);
            }
        } while (colorDePalabra[i] == -1);

        printf("        Palabra: ");
        scanf("%49s", palabras[i]);
    }

    /* Salida: cada palabra con su color, separadas por un espacio */
    printf("\nSalida en la consola\n\n");
    for (i = 0; i < CANT_PALABRAS; i++) {
        printf("%s%s%s ", codigos[colorDePalabra[i]], palabras[i], RESET);
    }
    printf("\n");

    return 0;
}
