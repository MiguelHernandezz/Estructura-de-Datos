

#include "ccontrol.h"

void mostrarMenu() {
    std::cout << "\n========= GESTION DE PEDIDOS EDITORIAL =========\n";
    std::cout << "1- Insertar una libreria de forma manual.\n";
    std::cout << "2- Borrar una libreria del arbol.\n";
    std::cout << "3- Mostrar pedidos de una libreria dada.\n";
    std::cout << "4- Buscar un pedido concreto por su ID.\n";
    std::cout << "5- Extraer un pedido concreto.\n";
    std::cout << "6- Llevar un pedido concreto de una libreria a otra.\n";
    std::cout << "7- Mostrar una estadistica de las librerias.\n";
    std::cout << "8- Continuar con la distribucion de pedidos.\n";
    std::cout << "9- VER ABB EN INORDEN (Solo ID y Localidad).\n";
    std::cout << "0- Salir del programa.\n";
    std::cout << "================================================\n";
    std::cout << "Opcion: ";
}

int main() {
    srand(time(NULL)); // Semilla aleatoria

    Editorial sistema;

    // Inicialización automática al arrancar
    sistema.inicializarSistema();

    int opcion;

    do {
        mostrarMenu();
        std::cin >> opcion;

        // --- BLOQUE DE SEGURIDAD PARA EL MENÚ ---
        // Si el usuario mete una letra, cin falla y pone opcion = 0.
        // Esto evita que el programa se cierre por error.
        if (std::cin.eof()) {
            opcion = 0;                   // Fin de la entrada: salimos
        } else if (std::cin.fail()) {
            std::cin.clear();             // 1. Reseteamos el estado de error de cin
            std::cin.ignore(10000, '\n'); // 2. Limpiamos la letra del buffer
            opcion = -1;                  // 3. Forzamos un valor inválido (no 0) para que vaya al 'default'
        }
        // ----------------------------------------

        switch(opcion) {
            case 1: sistema.opcion1_InsertarLibreria(); break;
            case 2: sistema.opcion2_BorrarLibreria(); break;
            case 3: sistema.opcion3_MostrarPedidosLibreria(); break;
            case 4: sistema.opcion4_BuscarPedidoID(); break;
            case 5: sistema.opcion5_ExtraerPedido(); break;
            case 6: sistema.opcion6_MoverPedido(); break;
            case 7: sistema.opcion7_Estadistica(); break;
            case 8: sistema.opcion8_ContinuarDistribucion(); break;
            case 9: sistema.opcion9_VerInordenSimple(); break;

            case 0: std::cout << "Saliendo...\n"; break;

            default: std::cout << "Opcion incorrecta. Introduce un numero del 0 al 8.\n";
        }
    } while (opcion != 0);

    return 0;
}
