#include "editorial.h"

void mostrarMenu() {
    std::cout << "\n========= MENU SIMULADOR EDITORIAL =========\n";
    std::cout << "1) Generar " << N_PEDIDOS_PASO << " pedidos aleatorios\n";
    std::cout << "2) Procesar paso de simulacion\n";
    std::cout << "3) Mostrar estado completo del sistema\n";
    std::cout << "4) Ver contenido de una caja de una libreria\n";
    std::cout << "0) Salir del programa\n";
    std::cout << "==========================================\n";
    std::cout << "Elige una opcion: ";
}

int main() {
    srand(time(NULL)); //para números aleatorios distintos iniciar

    Editorial miEditorial;//LLamada a contructor editorial y d ahí a stock
    int opcion;
    int id_caja;

    do {
        mostrarMenu();
        std::cin >> opcion;

        // Si se acaba la entrada (EOF) salimos; si se mete una letra, la descartamos
        if (std::cin.eof()) {
            opcion = 0;
        } else if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            opcion = -1;
        }

        switch (opcion) {
            case 1:
                miEditorial.generarNuevosPedidos();
                break;
            case 2:
                miEditorial.procesarPasoDeSimulacion();
                break;
            case 3:
                miEditorial.mostrarEstadoDelSistema();
                break;
            case 4:
                std::cout << "Introduce el ID de la libreria (0-" << LIBRERIAS - 1 << "): ";
                std::cin >> id_caja;
                miEditorial.verContenidoDeCaja(id_caja);
                break;
            case 0:
                std::cout << "Saliendo del simulador...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intentalo de nuevo.\n";
                break;
        }
    } while (opcion != 0);

    return 0;
}
