#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/*
    * Datos del fichero "semillas.txt":

    El fichero "semillas.txt" contiene los datos de las semillas, organizados de la siguiente manera:
    Cada línea del fichero representa los datos de una semilla con la siguiente información:

    1. Identificador (No hay un vector para esto):
        - Cada semilla tiene un identificador único entre 1 y 7000.

    2. Año de incorporación al banco de semillas:
        - Desde el año 2020 hasta el año actual, 2024.

    3. Año de caducidad:
        - Año en que la semilla caduca.

    4. Número de semillas de la muestra:
        - Cantidad de semillas de ese tipo que se conservan en el banco.

    5. Sección del banco de semillas:
        - La sección del banco donde se encuentra la semilla, con un valor entre 1 y 100. 

    6. Nivel de peligro de extinción de la especie:
        1. Riesgo extremo.
        2. Riesgo alto.
        3. Riesgo medio.
        4. Riesgo bajo.
        5. Sin riesgo.

    7. Tipo de planta según crecimiento:
        1. Árbol.
        2. Arbusto.
        3. Hierba.
        4. Planta trepadora.

    8. Tipo de planta según reproducción:
        1. Planta con flores (angiospermas): produce flores y frutos.
        2. Planta sin flores (gimnospermas): genera semillas sin producir flores o frutos.

    9. Tipo de planta según la adaptación al ambiente:
        1. Xerófitas: pueden sobrevivir en condiciones secas o desérticas.
        2. Hidrófitas: son capaces de vivir en el agua o en ambientes acuáticos.
        3. Halófitas: se adaptan a ambientes salinos.
        4. Otras.

    10. Tipo de planta según el ciclo de vida:
        1. Anual: crece en un solo ciclo.
        2. Bienal: completa su ciclo de vida en dos temporadas.
        3. Perenne: vive varios años.

    Ejemplo de una línea en el fichero "semillas.txt":
        - La semilla con identificador 4667 entró en el banco en el año 2023, caduca en 2095.
          Hay 1982 semillas de ese tipo (muestra). Se encuentra en la sección 92,
          tiene riesgo bajo de extinción (4), es una hierba (3), es una planta con flores (1),
          xerófita (1) y anual (1).
*/


//! --------------------- CONSTANTS --------------------- 

//* Number of types of seeds in the bank
#define N_SEMILLAS 7000 // Número de tipos de semillas del banco
// Related array: All arrays are of size N_SEMILLAS (e.g., vAnyo, vCaducidad, etc.).

//* Number of sections in the bank
#define N_SECCIONES 100 // Número de secciones del banco
// Related array: vSeccion (stores the section number of each seed).

//* Risk levels for species extinction
#define RIESGO_EXTREMO 1 // Constantes que definen el nivel de peligro de extinción de la especie - Extremo
#define RIESGO_ALTO 2    // Nivel alto de peligro de extinción
#define RIESGO_MEDIO 3   // Nivel medio de peligro de extinción
#define RIESGO_BAJO 4    // Nivel bajo de peligro de extinción
#define SIN_RIESGO 5     // Sin riesgo de extinción
// Related array: vRiesgo (stores the extinction risk level of each seed).

//* Plant types by growth
#define ARBOL 1              // Constantes que definen el tipo de planta según su crecimiento - Árbol
#define ARBUSTO 2            // Arbusto
#define HIERBA 3             // Hierba
#define PLANTA_TREPADORA 4   // Planta trepadora
// Related array: vTipoCrecimiento (stores the growth type of each seed).

//! My Constants:
#define NUM_OF_TYPES_OF_SEEDS 4
// Related concept: Used as a grouping variable, not directly stored in an array.

//* Plant types by reproduction
#define CON_FLORES 1  // Constantes que definen el tipo de planta según reproducción - Con flores
#define SIN_FLORES 2  // Sin flores
// Related array: vTipoReproduccion (stores the reproduction type of each seed).

//* Plant types by environmental adaptation
#define DESERTICAS 1  // Constantes que definen los tipos de plantas según la adaptación al ambiente - Desérticas
#define VIVEN_AGUA 2  // Viven en agua
#define SALINAS 3     // Salinas
#define OTROS 4       // Otros
// Related array: vTipoAdaptacion (stores the environmental adaptation type of each seed).

//* Plant types by life cycle
#define ANUALES 1     // Constantes que definen los tipos de plantas según ciclo de la vida - Anuales
#define BIENALES 2    // Bienales
#define PERENNES 3    // Perennes
// Related array: vTipoCiclo (stores the life cycle type of each seed).

//! --------------------- CONSTANTS END --------------------- 


//! --------------------- FUNCTIONS DECLARATIONS --------------------- 

//* Prints all the constants defined in the program
void print_constants_info(void);

//* Reads seed data from the file and fills the arrays
int lee_datos(int vAnyo[], int vCaducidad[], int vNumSemillas[], int vSeccion[], int vRiesgo[], int vTipoCrecimiento[], int vTipoReproduccion[], int vTipoAdaptacion[], int vTipoCiclo[]);

void menu(int *memory_of_menu_option);

void peligro_extincion(int vRiesgo[], int vTipoCrecimiento[]);

int caducidad_semillas(int vAnyo[], int vCaducidad[], int vNumSemillas[]);

int especies_bioma(int vSeccion[], int vAnyo[], int vCaducidad[]);

int donacion(int vAnyo[], int vCaducidad[], int vNumSemillas[], int vRiesgo[],
int vTipoReproduccion[], int vTipoAdaptacion[], int vTipoCiclo[], int* contadorDonadas, int* contadorNoDonadas);


//! --------------------- FUNCTIONS DECLARATIONS END --------------------- 

int main() {

    //! --------------------- GLOBAL VARS ---------------------

    //* Arrays to store information about each seed (from semillas.txt)
    int vAnyo[N_SEMILLAS] = {0};           // Year of incorporation into the bank
    int vCaducidad[N_SEMILLAS] = {0};      // Expiration year of each seed
    int vNumSemillas[N_SEMILLAS] = {0};    // Number of seeds in the sample
    int vSeccion[N_SEMILLAS] = {0};        // Section number where each seed is stored
    int vRiesgo[N_SEMILLAS] = {0};         // Extinction risk level of each seed
    int vTipoCrecimiento[N_SEMILLAS] = {0}; // Growth type of each seed
    int vTipoReproduccion[N_SEMILLAS] = {0}; // Reproduction type of each seed
    int vTipoAdaptacion[N_SEMILLAS] = {0};  // Environmental adaptation type of each seed
    int vTipoCiclo[N_SEMILLAS] = {0};       // Life cycle type of each seed

    //* Counters for donated and non-donated seeds
    int contadorDonadas, contadorNoDonadas = 0;

    //! --------------------- GLOBAL VARS END ---------------------

    // Call the function to read data from the file
    // Returns an error if file cannot be opened
    if(lee_datos(vAnyo, vCaducidad, vNumSemillas, vSeccion, vRiesgo,
                  vTipoCrecimiento, vTipoReproduccion, vTipoAdaptacion,
                  vTipoCiclo) == -1) {
        fprintf(stderr, "Error: No se pudo abrir el archivo semillas.txt\n");
        return 0;
    }

    int menu_option;

    do {

        menu(&menu_option); // Display menu and get user's choice


        switch (menu_option) {

            case 1:
                // Function to process seeds in danger of extinction
                peligro_extincion(vRiesgo, vTipoCrecimiento);
                break;

            case 2:
                // Function to calculate seed expiration
                if(caducidad_semillas(vAnyo, vCaducidad, vNumSemillas) == -1) {
                    fprintf(stderr, "Error: No se pudo crear el archivo caducadas.txt");
                    return 1;
                };
                break;

            case 3:
                // Function to find the biome with the highest percentage of species
                if(especies_bioma(vSeccion, vAnyo, vCaducidad) == -1){
                    fprintf(stderr, "Error: No se pudo crear el archivo bioma.txt");
                    return 1;
                };
                break;

            case 4:
                // Function to process seed donation
                if(donacion(vAnyo, vCaducidad, vNumSemillas, vRiesgo,
                        vTipoReproduccion, vTipoAdaptacion, vTipoCiclo, &contadorDonadas, &contadorNoDonadas) == -1) {
                            fprintf(stderr, "Error: No se pudo crear los archivos");
                            return 1;
                        } else {
                            int total = contadorDonadas + contadorNoDonadas;
                            printf("Semillas que cumplen las condiciones %d (%.1f%%):\n", total, total / (float) N_SEMILLAS * 100);
                            printf("    Donadas %d (%.1f%%)\n", contadorDonadas, contadorDonadas / (float) N_SEMILLAS * 100);
                            printf("    No donadas %d (%.1f%%)\n", contadorNoDonadas, contadorNoDonadas / (float) N_SEMILLAS * 100);
                        }
                break;

            case 0:
                printf("Finalizando el programa...\n");
                return 1;
                break;

            default:
                printf("Opción inválida. Por favor, elija una opción entre 0 y 4.\n");
                break;

        }

    } while(menu_option != 0);

    // print_constants_info(); //print constant values

    return 0;
}

//! --------------------- FUNCTIONS --------------------- 

//* Function to process seeds in danger of extinction
void peligro_extincion(int vRiesgo[], int vTipoCrecimiento[]) {

    int count_total_riesgo_extremo = 0;

    int count_by_type[NUM_OF_TYPES_OF_SEEDS] = {0}; // Index 0: ARBOL - 1, 1: ARBUSTO - 1, 2: HIERBA - 1, 3: PLANTA_TREPADORA - 1
    float percentages[NUM_OF_TYPES_OF_SEEDS] = {0}; // Index 0: ARBOL - 1, 1: ARBUSTO - 1, 2: HIERBA - 1, 3: PLANTA_TREPADORA - 1

    const char *type_names[] = {"arboles", "arbustos", "hierbas", "plantas trepadoras"};

    for (int i = 0; i < N_SEMILLAS; i++) {

        if (vRiesgo[i] == RIESGO_EXTREMO) { 
            count_total_riesgo_extremo++;

            count_by_type[vTipoCrecimiento[i] - 1]++;
        }

    }

    //prevents division by 0
    if(count_total_riesgo_extremo == 0) {
        printf("Hay 0 especies en peligro de extincion");
        return;
    } 


    for (int i = 0; i < NUM_OF_TYPES_OF_SEEDS; i++) {
        percentages[i] = (count_by_type[i] / (float) count_total_riesgo_extremo * 100);
    }

    //Find type with highest risk:
    int index_of_highest_risk = 0;

    for (int i = 0; i < NUM_OF_TYPES_OF_SEEDS; i++) {
        if(percentages[i] > percentages[index_of_highest_risk]) index_of_highest_risk = i;
    }


    // Print the total number of endangered species
    printf("Hay %d especies en peligro de extincion:\n", count_total_riesgo_extremo);

    // Print the breakdown of endangered species by plant type
    for (int i = 0; i < NUM_OF_TYPES_OF_SEEDS; i ++) {
            printf("    %d %s (%.1f%% del total de %s)\n", count_by_type[i], type_names[i], percentages[i], type_names[i]);
    }

    // Print the plant type with the highest percentage of endangered species
    printf("\nEl mayor porcentaje de especies en peligro de extincion corresponde a %s %.1f%%\n", type_names[index_of_highest_risk], percentages[index_of_highest_risk]);

}

//* Function to calculate seed expiration
int caducidad_semillas(int vAnyo[], int vCaducidad[], int vNumSemillas[]) {

    FILE *file = fopen("caducadas.txt", "w");

    if (file == NULL) {
        return -1; // Return error code if the file couldn't be created
    }

    int start_year, end_year;

    int count_total_expired_seeds = 0; // Counter for expired seeds

    int count_total_seed_samples = 0; // Counter for total seed samples
    int count_total_expired_seed_samples = 0; // Counter for expired seed samples

    // Get the start year (with input validation)
    do {
        printf("Introduce el anyo de inicio: ");
        if (scanf("%d", &start_year) != 1 || start_year < 2020) {
            printf("Entrada invalida. El anyo de inicio debe ser un numero entero mayor o igual a 2020.\n");
            while (getchar() != '\n'); // Clear invalid input from the buffer
            start_year = -1; 
        }
    } while (start_year < 2020);

    // Get the end year (with input validation)
    do {
        printf("Introduce el anyo de finalizacion: ");
        if (scanf("%d", &end_year) != 1 || end_year < start_year) {
            printf("Entrada invalida. El anyo de finalizacion debe ser un numero entero mayor o igual al anyo de inicio.\n");
            while (getchar() != '\n'); // Clear invalid input from the buffer
            end_year = -1;
        }
    } while (end_year < start_year);

    // Checks all seeds and filter based on expiration date
    for (int i = 0; i < N_SEMILLAS; i++) {
        // Check if the seed's expiration date falls within the range
        if (vCaducidad[i] >= start_year && vCaducidad[i] <= end_year) {
            // Write seed details to the file
            fprintf(file, "Semilla %d: anyo de entrada %d anyo de caducidad %d (muestra %d)\n",
                    i + 1, vAnyo[i], vCaducidad[i], vNumSemillas[i]);

            // Increment expired seeds and their sample count
            count_total_expired_seeds++;
            count_total_expired_seed_samples += vNumSemillas[i];
        }

        // Count total samples across all seeds
        count_total_seed_samples += vNumSemillas[i];
    }

    // Prevent division by zero (just in case)
    if (count_total_seed_samples == 0) {
        printf("Error: No hay muestras de semillas en el banco.\n");
        fclose(file);
        return -1;
    }

    // Calculate percentages
    float percentage_of_total_expired_seeds = count_total_expired_seeds / (float) N_SEMILLAS * 100;
    float percentage_of_total_expired_seed_samples = count_total_expired_seed_samples / (float) count_total_seed_samples * 100;

    // Display results to the user
    printf("Cantidad de muestras de semillas caducadas: %d (%.1f%% del total)\n",
           count_total_expired_seed_samples, percentage_of_total_expired_seed_samples);
    printf("Numero de semillas caducadas: %d (%.1f%% del total)\n",
           count_total_expired_seeds, percentage_of_total_expired_seeds);

    fclose(file);
    return 0;
}

//* Function to find the biome with the highest percentage of species
int especies_bioma(int vSeccion[], int vAnyo[], int vCaducidad[]) {

    FILE *file = fopen("bioma.txt", "w");

    if(file == NULL) return -1;

    int biomas[10] = {0};
    float percentage_biomas[10] = {0};

    const char *bioma_names[] = {
        "Tundra",                                  // Biome 1
        "Bosque caducifolio y bosque mediterráneo", // Biome 2
        "Pradera",                                 // Biome 3
        "Chaparral",                               // Biome 4
        "Desierto",                                // Biome 5
        "Taiga",                                   // Biome 6
        "Estepa",                                  // Biome 7
        "Selva tropical",                          // Biome 8
        "Sabana",                                  // Biome 9
        "Biomas acuáticos y arrecifes de coral"    // Biome 10
    };

    for (int i = 0; i < N_SEMILLAS; i ++) {
        int biome_index = vSeccion[i] % 10;
        biomas[biome_index]++;
    }

    int index_of_highest_biome = 0;

    for (int i = 0; i < (10); i++) {
        percentage_biomas[i] = (biomas[i] / (float) N_SEMILLAS) * 100;

        // printf("\nBioma %d: %.2f\n", i + 1, percentage_biomas[i]);

        if (biomas[i] > biomas[index_of_highest_biome]) {
            index_of_highest_biome = i;
        }
    }


    fprintf(file, "Semillas del bioma %s \n\n", bioma_names[index_of_highest_biome]);
    for (int i = 0; i < N_SEMILLAS; i ++) {

        int biome_index = vSeccion[i] % 10;

        if(biome_index == index_of_highest_biome) {
            fprintf(file, "Semilla %d: entrada %d caducidad %d\n", i + 1, vAnyo[i], vCaducidad[i]);
        }
    }
    
    printf("El bioma con mayor porcentaje de semillas en el banco es: %s (semillas %d, %.1f%% del total)\n", bioma_names[index_of_highest_biome], biomas[index_of_highest_biome], percentage_biomas[index_of_highest_biome]);

    return 0;
}

//* Function to process seed donation
int donacion(int vAnyo[], int vCaducidad[], int vNumSemillas[], int vRiesgo[],
             int vTipoReproduccion[], int vTipoAdaptacion[], int vTipoCiclo[], int* contadorDonadas, int* contadorNoDonadas) {

    FILE *_donadas = fopen("donadas.txt", "w");
    FILE *_nodonadas = fopen("nodonadas.txt", "w");

    if(_donadas == NULL || _nodonadas == NULL) return -1;

    *contadorDonadas = 0;
    *contadorNoDonadas = 0;

    for (int i = 0; i < N_SEMILLAS; i++) {

        int seed_id = i + 1;

        bool can_donate = true; //change it to false if does not meet at least one of UPV restrictions

        //check if seed meets donation creterias from minister
        if(vTipoCiclo[i] == 2 && vTipoReproduccion[i] == 2 && vTipoAdaptacion[i] == 4) {
            
            //restriction 1:
            if(vRiesgo[i] == 1 || vRiesgo[i] == 2) {
                fprintf(_nodonadas, "Semilla %d no se puede donar por ser de alto riego de extinction\n", seed_id);
                can_donate = false;
            }

            //restriction 2:
            if(vNumSemillas[i] < 1000) {
                fprintf(_nodonadas, "Semilla %d no se puede donar por tener menos de 1000 semillas en el banco\n", seed_id);
                can_donate = false;
            }

            //restriction 3:
            if(vCaducidad[i] < 2030) {
                fprintf(_nodonadas,"Semilla %d no se puede donar por caducar antes del año 2030\n", seed_id);
                can_donate = false;
            }

            //restriction 4:
            if((vNumSemillas[i] - (vNumSemillas[i] * 0.17)) < 500) {
                fprintf(_nodonadas, "Semilla %d no se puede donar porque nos quedarian menos de 500 semillas\n", seed_id);
                can_donate = false;
            }

            //if seed does not fall under UPV restrictions for donations, then donate them and write it to file:
            if(can_donate) {
                (*contadorDonadas)++;
                fprintf(_donadas, "Semilla %d donada, quedan %.0f semillas en la muestra\n", seed_id, ceil(vNumSemillas[i] - (vNumSemillas[i] * 0.17)));
            } else (*contadorNoDonadas)++;


        }

    }


    fclose(_donadas);
    fclose(_nodonadas);
    return 0;
}

//* Function to read data from the file "semillas.txt"
int lee_datos(int vAnyo[], int vCaducidad[], int vNumSemillas[], int vSeccion[], int vRiesgo[], int vTipoCrecimiento[], int vTipoReproduccion[], int vTipoAdaptacion[], int vTipoCiclo[]){
    FILE *file = fopen("semillas.txt", "r");

    // Check if the file was successfully opened
    if(file == NULL) {
        return -1;
    }

    int identificador;
    int anyo, caducidad, numSemillas, seccion, riesgo, tipoCrecimiento, tipoReproduccion, tipoAdaptacion, tipoCiclo;

    // Read data line by line
    while(fscanf(file, "%d %d %d %d %d %d %d %d %d %d", &identificador, &anyo, &caducidad, &numSemillas, &seccion,
                  &riesgo, &tipoCrecimiento, &tipoReproduccion, &tipoAdaptacion, &tipoCiclo) == 10) {

        //the index of each type of seed is its identifier - 1            
        int index = identificador - 1;

        vAnyo[index] = anyo;
        vCaducidad[index] = caducidad;
        vNumSemillas[index] = numSemillas;
        vSeccion[index] = seccion;
        vRiesgo[index] = riesgo;
        vTipoCrecimiento[index] = tipoCrecimiento;
        vTipoReproduccion[index] = tipoReproduccion;
        vTipoAdaptacion[index] = tipoAdaptacion;
        vTipoCiclo[index] = tipoCiclo;
    }

    fclose(file); // Close the file
    return 0;     // Return success
}


//* Menu function with input validation
void menu(int *memory_of_menu_option) {

        printf("\n\n");
        printf("--------------- Menu de opciones -----------------------\n");
        printf("1. Semillas de especies en peligro de extincion.\n");
        printf("2. Caducidad de semillas.\n");
        printf("3. Bioma con mayor porcentaje de especies en el banco.\n");
        printf("4. Donacion de semillas.\n");
        printf("0. Finalizar.\n");
        printf("---------------------------------------------------------\n");
        printf("Elige una opcion (0-4): ");

        // Check if input is valid
        if (scanf("%d", memory_of_menu_option) != 1) {
            *memory_of_menu_option = -1; // Assign an invalid value if input is not a number
            while (getchar() != '\n');   // Clear the input buffer
        }

        printf("\n\n");
}


//* Function to print the constants defined in the program
void print_constants_info(void) {
    printf("\n\n");
    printf("Número de semillas: %d\n", N_SEMILLAS);
    printf("Nivel de riesgo extremo: %d\n", RIESGO_EXTREMO);
    printf("Tipo de planta: Árbol (%d), Arbusto (%d)\n", ARBOL, ARBUSTO);
    printf("Planta con flores: %d, Sin flores: %d\n", CON_FLORES, SIN_FLORES);
    printf("Planta desértica: %d, Salinas: %d\n", DESERTICAS, SALINAS);
    printf("Ciclo de vida: Anuales (%d), Perennes (%d)\n", ANUALES, PERENNES);
    printf("\n\n");
}
