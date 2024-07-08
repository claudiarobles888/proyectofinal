//Claudia Robles y Francisco Romero
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//Funcion para determinar tiempo de ejecucion del programa
double medirTiempoEjecucion(clock_t start_time, clock_t end_time)
{
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
}


// Función para verificar si cumple con la edad mínima
int cumpleEdadMinima(int nacimiento)
{
    return (2024 - nacimiento) >= 16;
}


// Función para validar el formato del número de cédula
int validarCedula(char *input)
{
    size_t length = strlen(input);
    if (length != 10)
    {
        printf("El número de cédula debe contener exactamente 10 dígitos.\n");
        return 0;
    }
    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("El número de cédula debe contener solo dígitos numéricos.\n");
            return 0;
        }
    }
    return 1;
}


void solicitarDatosVotante()
{
    int nacimiento;
    char input[100];


    do
    {
        printf("Ingrese su año de nacimiento: ");
        scanf("%d", &nacimiento);
        while (getchar() != '\n')
            ; // Limpiar buffer de entrada
    } while (nacimiento < 1914 || nacimiento > 2008);


    if (!cumpleEdadMinima(nacimiento))
    {
        printf("Lo siento, no cumple con la edad mínima para votar.\n\n");
        exit(0);
    }


    do
    {
        printf("Ingrese su número de cédula (10 dígitos): ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Eliminar el salto de línea


    } while (!validarCedula(input));
}


int main()
{
    int can1 = 0, can2 = 0, can3 = 0, can4 = 0, can5 = 0, nul = 0, total_votos = 0;
    int voto, requisitos, nacimiento, anadir, ganador;
    char input[100];
    clock_t start_time, end_time;
    double time_elapsed;

    //INICIA A MEDIR EL TIEMPO DE EJECUCION
    start_time = clock();

    {
        printf("--------ELECCIONES PRESIDENCIALES--------\n");


        printf("Reglas para poder ser votante:\n");
        printf("1. Ser un habitante con una edad mínima de 16 años:\n");
        printf("2. Contar con una cédula de identidad válida (10 dígitos numéricos):\n\n");


        printf("Si cumple con ambas opciones oprima:\n 1. Para continuar\n 2. Para terminar\n\n");
        scanf("%d", &requisitos);


        while (getchar() != '\n')
            ; // Limpiar buffer de entrada


        switch (requisitos)
        {
        case 1:
            solicitarDatosVotante();


            // Ahora pedir el voto
            printf("\n-----Candidatos presidenciales-----\n");
            printf("Ingrese 1 si su voto es para el candidato 1\n"
                   "Ingrese 2 si su voto es para el candidato 2\n"
                   "Ingrese 3 si su voto es para el candidato 3\n"
                   "Ingrese 4 si su voto es para el candidato 4\n"
                   "Ingrese 5 si su voto es para el candidato 5\n"
                   "Presione Enter para un voto en blanco\n"
                   "Ingrese cualquier otra cosa para un voto nulo\n");


            fgets(input, sizeof(input), stdin);


            if (strlen(input) == 1 && input[0] == '\n')
            {
                nul++;
            }
            else if (isdigit(input[0]) && strlen(input) == 2 && input[1] == '\n')
            {
                voto = atoi(input);


                switch (voto)
                {
                case 1:
                    can1++;
                    break;
                case 2:
                    can2++;
                    break;
                case 3:
                    can3++;
                    break;
                case 4:
                    can4++;
                    break;
                case 5:
                    can5++;
                    break;
                default:
                    nul++;
                    break;
                }


                total_votos++;
            }
            else
            {
                nul++;
            }


            printf("Gracias por sufragar.\n\n");
            break;


        case 2:
            printf("No cumple con al menos un requisito.\n");
            anadir = 2; // Para salir del bucle
            break;


        default:
            printf("Opción no válida.\n");
            break;
        }


        // Preguntar si desea añadir otro votante
        if (requisitos == 1)
        {
            do
            {
                printf("¿Desea añadir un nuevo votante?\n"
                       "Si desea añadir un nuevo sufragante presione 1\n"
                       "Si las elecciones han terminado presione 2: ");
                scanf("%d", &anadir);
                while (getchar() != '\n')
                    ; // Limpiar buffer de entrada


            } while (anadir != 1 && anadir != 2);
        }


    } while (anadir != 2);


    // Calcular porcentajes
    double porcentaje1 = (double)can1 / total_votos * 100;
    double porcentaje2 = (double)can2 / total_votos * 100;
    double porcentaje3 = (double)can3 / total_votos * 100;
    double porcentaje4 = (double)can4 / total_votos * 100;
    double porcentaje5 = (double)can5 / total_votos * 100;
    double porcentaje_nulos = (double)nul / total_votos * 100;


    // Mostrar resultados
    printf("\n-----RESULTADOS ELECTORALES-----\n");
    printf("Votos para el candidato 1: %d (%.2f%%)\n", can1, porcentaje1);
    printf("Votos para el candidato 2: %d (%.2f%%)\n", can2, porcentaje2);
    printf("Votos para el candidato 3: %d (%.2f%%)\n", can3, porcentaje3);
    printf("Votos para el candidato 4: %d (%.2f%%)\n", can4, porcentaje4);
    printf("Votos para el candidato 5: %d (%.2f%%)\n", can5, porcentaje5);
    printf("Votos nulos: %d (%.2f%%)\n", nul, porcentaje_nulos);
    printf("Total de votos contabilizados: %d\n", total_votos);


    // Determinar ganador
    int max_votos = can1;
    ganador = 1;


    if (can2 > max_votos)
    {
        max_votos = can2;
        ganador = 2;
    }
    if (can3 > max_votos)
    {
        max_votos = can3;
        ganador = 3;
    }
    if (can4 > max_votos)
    {
        max_votos = can4;
        ganador = 4;
    }
    if (can5 > max_votos)
    {
        max_votos = can5;
        ganador = 5;
    }


    // Verificar si hay empate
    int empate = 0;


    if (can1 == max_votos)
        empate++;
    if (can2 == max_votos)
        empate++;
    if (can3 == max_votos)
        empate++;
    if (can4 == max_votos)
        empate++;
    if (can5 == max_votos)
        empate++;


    if (empate > 1)
    {
        printf("\nHay un empate con %d votos.\n", max_votos);
        printf("-----EXISTE UN EMPATE POR LO CUAL SE REALIZARA UNA SEGUNDA VUELTA CON LOS CANDIDATOS-----\n");


        // Mostrar solo los candidatos que empataron en la primera vuelta
        printf("Candidatos en segunda vuelta:\n");
        if (can1 == max_votos)
            printf("1. Candidato 1\n");
        if (can2 == max_votos)
            printf("2. Candidato 2\n");
        if (can3 == max_votos)
            printf("3. Candidato 3\n");
        if (can4 == max_votos)
            printf("4. Candidato 4\n");
        if (can5 == max_votos)
            printf("5. Candidato 5\n");


        // Implementación de la segunda vuelta
        int candidatos_empate[5] = {can1 == max_votos, can2 == max_votos, can3 == max_votos, can4 == max_votos, can5 == max_votos};
        total_votos = 0;
        can1 = can2 = can3 = can4 = can5 = nul = 0;


        do
        {
            printf("--------SEGUNDA VUELTA PRESIDENCIALES--------\n");
            solicitarDatosVotante();


            printf("Ingrese el número del candidato o 0 para finalizar y mostrar resultados: ");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';


            if (strlen(input) == 0)
            {
                nul++;
            }
            else if (isdigit(input[0]) && strlen(input) == 1)
            {
                voto = atoi(input);


                // Verificar si el voto es válido para la segunda vuelta
                if (voto >= 1 && voto <= 5 && candidatos_empate[voto - 1])
                {
                    switch (voto)
                    {
                    case 1:
                        can1++;
                        break;
                    case 2:
                        can2++;
                        break;
                    case 3:
                        can3++;
                        break;
                    case 4:
                        can4++;
                        break;
                    case 5:
                        can5++;
                        break;
                    }
                    total_votos++;
                }
                else if (voto != 0)
                {
                    printf("Por favor digite el código del candidato que se encuentra en la segunda vuelta.\n");
                }
            }
            else
            {
                nul++;
            }


        } while (voto != 0);


        // Recalcular porcentajes
        porcentaje1 = (double)can1 / total_votos * 100;
        porcentaje2 = (double)can2 / total_votos * 100;
        porcentaje3 = (double)can3 / total_votos * 100;
        porcentaje4 = (double)can4 / total_votos * 100;
        porcentaje5 = (double)can5 / total_votos * 100;
        porcentaje_nulos = (double)nul / total_votos * 100;


        // Mostrar resultados de la segunda vuelta
        printf("\n-----RESULTADOS ELECTORALES (Segunda vuelta)-----\n");
        printf("Votos para el candidato 1: %d (%.2f%%)\n", can1, porcentaje1);
        printf("Votos para el candidato 2: %d (%.2f%%)\n", can2, porcentaje2);
        printf("Votos para el candidato 3: %d (%.2f%%)\n", can3, porcentaje3);
        printf("Votos para el candidato 4: %d (%.2f%%)\n", can4, porcentaje4);
        printf("Votos para el candidato 5: %d (%.2f%%)\n", can5, porcentaje5);
        printf("Votos nulos: %d (%.2f%%)\n", nul, porcentaje_nulos);
        printf("Total de votos contabilizados: %d\n", total_votos);


        // Determinar ganador de la segunda vuelta
        max_votos = can1;
        ganador = 1;


        if (can2 > max_votos)
        {
            max_votos = can2;
            ganador = 2;
        }
        if (can3 > max_votos)
        {
            max_votos = can3;
            ganador = 3;
        }
        if (can4 > max_votos)
        {
            max_votos = can4;
            ganador = 4;
        }
        if (can5 > max_votos)
        {
            max_votos = can5;
            ganador = 5;
        }


        printf("\nEl ganador del sufragio electoral (Segunda vuelta) es el candidato %d con %d votos.\n", ganador, max_votos);
    }
    else
    {
        // Mostrar ganador
        printf("\nEl ganador del sufragio electoral es el candidato %d con %d votos.\n", ganador, max_votos);
    }

    //SE DETIENE TIEMPO DE EJECUCION
    end_time = clock();
    time_elapsed = medirTiempoEjecucion(start_time, end_time);


    // SE MUESTRA TIEMPO DE EJECUCION
    printf("\nTiempo de ejecucion: %.2f segundos\n", time_elapsed);

    return 0;
}