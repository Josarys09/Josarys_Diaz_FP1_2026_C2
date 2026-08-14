#include <stdio.h>
#include <stdlib.h>
#include <math.h>   // Para la función ceil()

// ============================================================
// 1. PARÁMETROS FIJOS DE COSTO POR KILÓMETRO (constantes)
//    Costo fijo de desgaste (sin incluir combustible)
// ============================================================

#define COSTO_MANTENIMIENTO_KM    2.00      // RD$10,000 / 5,000 km
#define COSTO_NEUMATICOS_KM       0.1538    // RD$10,000 / 65,000 km
#define COSTO_INSPECCION_KM       0.0125    // RD$500 / 40,000 km
#define COSTO_SEGURO_KM           1.00      // RD$40,000 / 40,000 km
#define COSTO_PLACA_KM            0.025     // RD$1,000 / 40,000 km

// Costo Fijo de Desgaste por Kilómetro (suma de todos los rubros, sin combustible)
// Aproximadamente RD$3.1913 / km
#define COSTO_DESGASTE_TOTAL_KM   (COSTO_MANTENIMIENTO_KM + COSTO_NEUMATICOS_KM + \
                                   COSTO_INSPECCION_KM + COSTO_SEGURO_KM + \
                                   COSTO_PLACA_KM)

// ============================================================
// 2. PARÁMETROS PARA EL CÁLCULO DE GASOLINA
// ============================================================

#define PRECIO_GALON             312.00    // RD$312.00 por galón
#define RENDIMIENTO_KM_GALON     33.0      // 33 km por galón

// ============================================================
// PROTOTIPOS DE FUNCIONES
// ============================================================

void limpiar_buffer(void);
void mostrar_recibo(double distancia_total, double costo_desgaste,
                    int galones_necesarios, double costo_combustible,
                    double total_peajes, double cargo_adicional,
                    double tarifa_base, double total_final);

// ============================================================
// FUNCIÓN PRINCIPAL
// ============================================================

int main(void) {
    double distancia_km;          // Distancia en km (solo ida)
    double distancia_total;       // Distancia ida y vuelta (distancia_km * 2)
    int cantidad_peajes;          // Número de peajes en el trayecto
    double total_peajes = 0.0;    // Suma de todos los peajes
    double cargo_adicional;       // Tarifa de manejo o cargo extra
    double tarifa_base;           // Costo fijo del servicio
    double costo_desgaste;        // Costo de desgaste del vehículo
    int galones_necesarios;       // Galones de gasolina necesarios
    double costo_combustible;     // Costo total de combustible
    double sub_total_transporte;  // Costo desgaste + combustible + peajes + cargo
    double total_general;         // Subtotal + tarifa base

    // ============================================================
    // 3. ENTRADA DE DATOS INTERACTIVA
    // ============================================================

    printf("========================================\n");
    printf("  CALCULO DE COSTO DE TRANSPORTE\n");
    printf("========================================\n\n");

    // 1. Distancia al destino (solo ida)
    printf("1. Distancia al destino (km): ");
    if (scanf("%lf", &distancia_km) != 1) {
        printf("Error: Entrada invalida.\n");
        return 1;
    }
    limpiar_buffer();

    // Multiplicar por 2 para ida y vuelta
    distancia_total = distancia_km * 2.0;

    // 2. Cantidad de peajes
    printf("2. Cantidad de peajes en el trayecto: ");
    if (scanf("%d", &cantidad_peajes) != 1) {
        printf("Error: Entrada invalida.\n");
        return 1;
    }
    limpiar_buffer();

    // Bucle para ingresar el costo de cada peaje
    if (cantidad_peajes > 0) {
        printf("\n   Ingrese el costo de cada peaje (ida y vuelta):\n");
        for (int i = 1; i <= cantidad_peajes; i++) {
            double peaje;
            printf("   Peaje %d: RD$ ", i);
            if (scanf("%lf", &peaje) != 1) {
                printf("Error: Entrada invalida.\n");
                return 1;
            }
            limpiar_buffer();
            total_peajes += peaje;
        }
    } else {
        printf("   (No hay peajes en el trayecto)\n");
    }

    // 3. Cargo adicional / tarifa de manejo
    printf("\n3. Cargo adicional (si no aplica ingrese 0): RD$ ");
    if (scanf("%lf", &cargo_adicional) != 1) {
        printf("Error: Entrada invalida.\n");
        return 1;
    }
    limpiar_buffer();

    // 4. Tarifa base del servicio
    printf("4. Tarifa base del servicio (costo fijo): RD$ ");
    if (scanf("%lf", &tarifa_base) != 1) {
        printf("Error: Entrada invalida.\n");
        return 1;
    }
    limpiar_buffer();

    // ============================================================
    // 4. CÁLCULOS REQUERIDOS
    // ============================================================

    // Costo de desgaste del vehículo (sin combustible)
    costo_desgaste = distancia_total * COSTO_DESGASTE_TOTAL_KM;

    // Cálculo de galones necesarios (redondeo hacia arriba con ceil)
    galones_necesarios = (int)ceil(distancia_total / RENDIMIENTO_KM_GALON);

    // Costo total de combustible
    costo_combustible = galones_necesarios * PRECIO_GALON;

    // Total cobro transporte = desgaste + combustible + peajes + cargo adicional
    sub_total_transporte = costo_desgaste + costo_combustible + total_peajes + cargo_adicional;

    // Gran total final al cliente
    total_general = tarifa_base + sub_total_transporte;

    // ============================================================
    // 5. SALIDA / RECIBO
    // ============================================================

    mostrar_recibo(distancia_total, costo_desgaste, galones_necesarios,
                   costo_combustible, total_peajes, cargo_adicional,
                   tarifa_base, total_general);

    printf("\nPresione Enter para salir...");
    getchar();
    return 0;
}

// ============================================================
// FUNCIONES AUXILIARES
// ============================================================

/**
 * Limpia el búfer de entrada (stdin) después de usar scanf.
 * Descarta cualquier carácter pendiente hasta el siguiente '\n'.
 */
void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // No hacer nada, solo descartar caracteres
    }
}

/**
 * Muestra un recibo/factura formateado con todos los detalles del cálculo.
 */
void mostrar_recibo(double distancia_total, double costo_desgaste,
                    int galones_necesarios, double costo_combustible,
                    double total_peajes, double cargo_adicional,
                    double tarifa_base, double total_final) {

    // Limpieza de pantalla (funciona en Windows y Unix/Linux/Mac)
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("\n");
    printf("============================================================\n");
    printf("              RECIBO / FACTURA DE SERVICIO\n");
    printf("============================================================\n\n");

    // Distancia recorrida (ida y vuelta)
    printf("  DISTANCIA RECORRIDA (Ida y Vuelta):\n");
    printf("    Distancia total: %.2f km\n\n", distancia_total);

    // Desglose detallado del costo de desgaste vehicular por kilómetro
    printf("  DESGLOSE DE COSTO DE DESGASTE VEHICULAR POR KILOMETRO:\n");
    printf("    Mantenimiento    : RD$ %8.4f / km\n", COSTO_MANTENIMIENTO_KM);
    printf("    Neumaticos (Gomas): RD$ %8.4f / km\n", COSTO_NEUMATICOS_KM);
    printf("    Seguro Full      : RD$ %8.4f / km\n", COSTO_SEGURO_KM);
    printf("    Placa (Marbete)  : RD$ %8.4f / km\n", COSTO_PLACA_KM);
    printf("    Inspeccion/Revista: RD$ %8.4f / km\n", COSTO_INSPECCION_KM);
    printf("    ----------------------------------------------\n");
    printf("    TOTAL DESGASTE x KM: RD$ %8.4f / km\n\n", COSTO_DESGASTE_TOTAL_KM);

    // Costo de desgaste total por distancia recorrida
    printf("  COSTO DE DESGASTE VEHICULAR POR DISTANCIA:\n");
    printf("    %.2f km * RD$ %.4f / km = RD$ %8.2f\n\n",
           distancia_total, COSTO_DESGASTE_TOTAL_KM, costo_desgaste);

    // Costo de combustible (galones enteros)
    printf("  COSTO DE COMBUSTIBLE (Gasolina):\n");
    printf("    Distancia total: %.2f km\n", distancia_total);
    printf("    Rendimiento: %.1f km / galon\n", RENDIMIENTO_KM_GALON);
    printf("    Galones necesarios: %d galones (redondeo hacia arriba)\n", galones_necesarios);
    printf("    Costo por galon: RD$ %.2f\n", PRECIO_GALON);
    printf("    Costo combustible: %d * RD$ %.2f = RD$ %8.2f\n\n",
           galones_necesarios, PRECIO_GALON, costo_combustible);

    // Peajes
    printf("  TOTAL DE PEAJES:\n");
    printf("    RD$ %8.2f\n\n", total_peajes);

    // Cargos adicionales
    printf("  CARGOS ADICIONALES:\n");
    printf("    RD$ %8.2f\n\n", cargo_adicional);

    // SUB-TOTAL TRANSPORTE Y DESPLAZAMIENTO
    double sub_total = costo_desgaste + costo_combustible + total_peajes + cargo_adicional;
    printf("  ----------------------------------------------\n");
    printf("  SUB-TOTAL TRANSPORTE Y DESPLAZAMIENTO:\n");
    printf("    RD$ %8.2f\n\n", sub_total);

    // TARIFA BASE DEL SERVICIO
    printf("  TARIFA BASE DEL SERVICIO (Costo fijo):\n");
    printf("    RD$ %8.2f\n\n", tarifa_base);

    // TOTAL GENERAL
    printf("  =============================================\n");
    printf("  ** TOTAL GENERAL A COBRAR AL CLIENTE **\n");
    printf("  **      RD$ %8.2f              **\n", total_final);
    printf("  =============================================\n");
    printf("============================================================\n");
}
