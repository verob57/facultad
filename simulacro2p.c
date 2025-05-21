#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    char codigo_vuelo[25];
    char linea_aerea[25];
    int num_pasajeros;
    char origen_de_vuelo[25];
    char destino_de_vuelo[25];
    int pista_aterrizaje;
    char hora_vuelo[75];
    char hora_aterrizaje[75];
    int pista_at2;
    int pista_at22;
    char tipo_de_vuelo[18];
} vuelos;

void obtenerFechaHora(char *buffer, size_t tamano) {
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    char *formato = "%Y-%m-%d %H:%M:%S";

    if (strftime(buffer, tamano, formato, &tiempoLocal) == 0) {
        snprintf(buffer, tamano, "Error al obtener la fecha y hora");
    }
}

int main() {
    vuelos aviones[25];
    char fechaHora[70];
    int opc;
    int n, i;

    //int cont_arribos = 0, cont_salidas = 0;
    int num_vuelos = 0;
    int suma_pasajeros = 0;
    int total2=0, total22 = 0;
    do {
        printf("BIENVENIDO AL MENU DE VUELO :)\n");
        printf("Por favor ingrese la opcion que desea.\n ");
        printf("Ingrese 1 para cargar vuelos.\n");
        printf("Ingrese 2 para ver las estadisticas.\n");
        printf("Ingrese 0 para finalizar el programa.\n");
        scanf("%d", &opc);
        getchar(); // Limpia el salto de línea tras scanf

        switch (opc) {
        case 1:
            printf("Ingrese la cantidad de vuelos que desea cargar [1 hasta 25]: ");
            scanf("%d", &n);
            getchar();

            if (n >= 1 && n <= 25 && (num_vuelos + n) <= 25) {
                for (i = 0; i < n; i++) {
                    printf("Ingrese el codigo de vuelo: ");
                    fgets(aviones[num_vuelos].codigo_vuelo, sizeof(aviones[num_vuelos].codigo_vuelo), stdin);
                    aviones[num_vuelos].codigo_vuelo[strcspn(aviones[num_vuelos].codigo_vuelo, "\n")] = '\0';

                    printf("Ingrese la linea aerea que corresponde: ");
                    fgets(aviones[num_vuelos].linea_aerea, sizeof(aviones[num_vuelos].linea_aerea), stdin);
                    aviones[num_vuelos].linea_aerea[strcspn(aviones[num_vuelos].linea_aerea, "\n")] = '\0';

                    printf("Ingrese el numero de pasajeros de su vuelo: ");
                    scanf("%d", &aviones[num_vuelos].num_pasajeros);
                    getchar();
                    suma_pasajeros += aviones[num_vuelos].num_pasajeros;

                    printf("Ingrese el origen del vuelo: ");
                    fgets(aviones[num_vuelos].origen_de_vuelo, sizeof(aviones[num_vuelos].origen_de_vuelo), stdin);
                    aviones[num_vuelos].origen_de_vuelo[strcspn(aviones[num_vuelos].origen_de_vuelo, "\n")] = '\0';

                    printf("Ingrese la hora del vuelo: ");
                    obtenerFechaHora(aviones[num_vuelos].hora_vuelo, sizeof(aviones[num_vuelos].hora_vuelo));
                    printf("%s\n", aviones[num_vuelos].hora_vuelo); // muestra la hora generada

                    printf("Ingrese el destino: ");
                    fgets(aviones[num_vuelos].destino_de_vuelo, sizeof(aviones[num_vuelos].destino_de_vuelo), stdin);
                    aviones[num_vuelos].destino_de_vuelo[strcspn(aviones[num_vuelos].destino_de_vuelo, "\n")] = '\0';

                    printf("Ingrese la pista de aterrizaje o despegue [2 o 22]: ");
                    scanf("%d", &aviones[num_vuelos].pista_aterrizaje);
                    getchar();
                    if (aviones[num_vuelos].pista_aterrizaje == 2) {
                        aviones[num_vuelos].pista_at2 = 1;
                        total2++;
                    } else if (aviones[num_vuelos].pista_aterrizaje == 22) {
                        aviones[num_vuelos].pista_at22 = 1;
                        total22++;
                    } else {
                        printf("Pista invalida, no existe esta pista dentro del hangar.\n");
                    }

                    num_vuelos++;
                }
            } else {
                printf("Cantidad invalida o supera el limite de vuelos.\n");
            }
            break;
        case 2:
            //estadisticas
            printf("**\n");
            printf("Cantidad de vuelos cargados: %d\n", num_vuelos);
          //cuantos fueron de arribos   printf("Cant de arribos %d\n", cont_arribos);               
          //cuantos fueron de salidas   printf("Cant de salidas %d\n", cont_salidas);             
            printf("Cant de vuelos en pista 2: %d\n", total2); //cuantos visitaron pista 2
            printf("Cant de vuelos en pista 22: %d\n", total22); //cuantos visitaron pista 22
            printf("Total pasajeros: %d\n", suma_pasajeros);
            printf("Promedio pasajeros: %.2f\n", (float)suma_pasajeros/num_vuelos);
            printf("**\n");

            printf("Primer vuelo cargado: %s\n", aviones[0].codigo_vuelo);
            printf("Ultimo vuelo cargado: %s\n", aviones[num_vuelos - 1].codigo_vuelo);
            //el que tuvo mayor cantidad de pasajeros
            int indice_mayor = 0;  // Guarda la posición del vuelo con más pasajeros
            int mayor_pasajeros = aviones[0].num_pasajeros;

            for(i = 1; i < num_vuelos; i++) {  // Puedes empezar desde i=1
                if(aviones[i].num_pasajeros > mayor_pasajeros) {
                    mayor_pasajeros = aviones[i].num_pasajeros;
                    indice_mayor = i;  // Actualiza la posición
                }
            }

            // Luego puedes mostrar toda la información del vuelo:
            printf("\nVuelo con MAS pasajeros:\n");
            printf("Codigo: %s\n", aviones[indice_mayor].codigo_vuelo);
            printf("Pasajeros: %d\n", mayor_pasajeros);
            printf("Origen: %s\n", aviones[indice_mayor].origen_de_vuelo);
            printf("Destino: %s\n", aviones[indice_mayor].destino_de_vuelo);
            
          
            if(num_vuelos == 0) {
                printf("No hay vuelos registrados\n");
                break;
            }
            break;

        case 0:
            printf("Programa finalizado.\n");
            break;

        default:
            printf("Opción inválida.\n");
            break;
        }
    } while (opc != 0);

    return 0;
}
