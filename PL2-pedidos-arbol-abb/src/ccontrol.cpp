#include "ccontrol.h"

// =================================================================
// || IMPLEMENTACIÓN LISTA                                        ||
// =================================================================

NodoL::NodoL(Pedido p, NodoL* s) { info = p; sig = s; }

Lista::Lista() { primero = NULL; ultimo = NULL; }

Lista::~Lista() {
    NodoL *aux;
    while(primero) {
        aux = primero;
        primero = primero->sig;
        delete aux;
    }
}

bool Lista::estaVacia() { return (primero == NULL); }

void Lista::InsertarFin(Pedido p) {
    NodoL *nuevo = new NodoL(p, NULL);
    if (estaVacia()) primero = nuevo;
    else ultimo->sig = nuevo;
    ultimo = nuevo;
}

Pedido Lista::Eliminar(std::string id_pedido) {
    if (estaVacia()) return Pedido();
    NodoL *actual = primero;
    NodoL *anterior = NULL;
    while (actual != NULL && actual->info.id_pedido != id_pedido) {
        anterior = actual;
        actual = actual->sig;
    }
    if (actual == NULL) return Pedido();
    Pedido p = actual->info;
    if (anterior == NULL) {
        primero = actual->sig;
    if (primero == NULL) ultimo = NULL;
    } else {
        anterior->sig = actual->sig;
        if (actual == ultimo) ultimo = anterior;
    }
    delete actual;
    return p;
}

Pedido Lista::Buscar(std::string id_pedido) {
    NodoL *actual = primero;
    while(actual) {
        if (actual->info.id_pedido == id_pedido) return actual->info;
        actual = actual->sig;
    }
    return Pedido();
}


void Lista::Mostrar() {
    if (estaVacia()) {
        std::cout << "    (Sin pedidos)" << std::endl;
        return;
    }
    NodoL *actual = primero;
    std::cout << "    ID      | Libro  | Materia      | Uds | Fecha     " << std::endl;
    std::cout << "    --------------------------------------------------" << std::endl;
    while(actual) {
        std::cout << "    " << std::left << std::setw(8) << actual->info.id_pedido
                  << "| " << std::setw(7) << actual->info.cod_libro
                  << "| " << std::setw(13) << actual->info.materia
                  << "| " << std::setw(4) << actual->info.unidades
                  << "| " << actual->info.fecha_envio << std::endl;
        actual = actual->sig;
    }
}

int Lista::Contar() {
    int c = 0;
    NodoL *actual = primero;
    while(actual) { c++; actual = actual->sig; }
    return c;
}


// =================================================================
// || IMPLEMENTACIÓN ÁRBOL                                        ||
// =================================================================

NodoA::NodoA(Libreria l, NodoA *i, NodoA *d) { info = l; izq = i; der = d; }

Arbol::Arbol() { raiz = NULL; }
Arbol::~Arbol() { destruir(raiz); }

void Arbol::destruir(NodoA *c) {
    if (c) {
        destruir(c->izq);
        destruir(c->der);
        delete c;
    }
}



void Arbol::Insertar(Libreria l) {
    Insertar(raiz, l);

}

void Arbol::Insertar(NodoA *&c, Libreria l) {
    if (c == NULL) {
        c = new NodoA(l);
    } else {
        if (l.id_libreria < c->info.id_libreria) Insertar(c->izq, l);
        else if (l.id_libreria > c->info.id_libreria) Insertar(c->der, l);
        // Si es igual, no insertamos (evitar duplicados)
    }
}

NodoA* Arbol::Buscar(int id_libreria) { return Buscar(raiz, id_libreria); }
NodoA* Arbol::Buscar(NodoA *c, int id_libreria) {
    if (c == NULL) return NULL;
    if (id_libreria == c->info.id_libreria) return c;
    else if (id_libreria < c->info.id_libreria) return Buscar(c->izq, id_libreria);
    else return Buscar(c->der, id_libreria);
}

void Arbol::Eliminar(int id_libreria) { Eliminar(raiz, id_libreria); }
void Arbol::Eliminar(NodoA *&c, int id_libreria) {
    if (c == NULL) return;

    if (id_libreria < c->info.id_libreria) Eliminar(c->izq, id_libreria);
    else if (id_libreria > c->info.id_libreria) Eliminar(c->der, id_libreria);
    else {
        if (c->izq == NULL) {
            NodoA *aux = c; c = c->der; delete aux;
        } else if (c->der == NULL) {
            NodoA *aux = c; c = c->izq; delete aux;
        } else {
            NodoA *min = minimo(c->der);
            c->info = min->info;
            Eliminar(c->der, min->info.id_libreria);
        }
    }
}

NodoA* Arbol::minimo(NodoA *c) {
    if (c == NULL) return NULL;
    if (c->izq == NULL) return c;
    return minimo(c->izq);
}

void Arbol::Inorden() { Inorden(raiz); }
void Arbol::Inorden(NodoA *c) {
    if (c) {
        Inorden(c->izq);
        std::cout << "LIB ID: " << c->info.id_libreria << " (" << c->info.localidad << ")\n";
        c->info.listaPedidos.Mostrar();
        Inorden(c->der);
    }
}

void Arbol::InordenEstadistica() {
    std::cout << std::left << std::setw(10) << "ID" << std::setw(15) << "Localidad" << "Num. Pedidos" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    InordenEstadistica(raiz);
}
void Arbol::InordenEstadistica(NodoA *c) {
    if (c) {
        InordenEstadistica(c->izq);
        std::cout << std::setw(10) << c->info.id_libreria
                  << std::setw(15) << c->info.localidad
                  << c->info.listaPedidos.Contar() << std::endl;
        InordenEstadistica(c->der);
    }
}

Pedido Arbol::BuscarPedidoGlobal(std::string id_pedido, int &id_lib_encontrada) {
    bool encontrado = false;
    return BuscarPedidoRecursivo(raiz, id_pedido, encontrado, id_lib_encontrada);
}

Pedido Arbol::BuscarPedidoRecursivo(NodoA *c, std::string id_pedido, bool &encontrado, int &id_lib_encontrada) {
    if (c == NULL || encontrado) return Pedido();
    Pedido p = c->info.listaPedidos.Buscar(id_pedido);
    if (!p.id_pedido.empty()) {
        encontrado = true;
        id_lib_encontrada = c->info.id_libreria;
        return p;
    }
    Pedido pIzq = BuscarPedidoRecursivo(c->izq, id_pedido, encontrado, id_lib_encontrada);
    if (encontrado) return pIzq;
    return BuscarPedidoRecursivo(c->der, id_pedido, encontrado, id_lib_encontrada);
}


// =================================================================
// || IMPLEMENTACIÓN GESTOR (Editorial)                           ||
// =================================================================

Editorial::Editorial() {
    // Constructor vacío. La inicialización se llama desde el main.
}

// --- Generadores Aleatorios Auxiliares ---
std::string Editorial::generarIdPedido() {
    return "P" + std::to_string(rand() % 90000 + 10000); // P + 5 cifras
}
std::string Editorial::generarCodLibro() {
    // Formato 963K76 (3 cifras, 1 letra, 2 cifras)
    return std::to_string(rand() % 900 + 100) +
           (char)('A' + rand() % 26) +
           std::to_string(rand() % 90 + 10);
}
std::string Editorial::generarMateria() {
    std::string mats[] = {"Matematicas", "Fisica", "Tecnologia", "Musica", "Historia", "Lengua"};
    return mats[rand() % 6];
}
std::string Editorial::generarFecha() {
    int dia = rand() % 28 + 1;
    int mes = rand() % 12 + 1;
    return (dia < 10 ? "0" : "") + std::to_string(dia) + "-" +
           (mes < 10 ? "0" : "") + std::to_string(mes) + "-2025";
}
std::string Editorial::generarLocalidad() {
    std::string locs[] = {"Mostoles", "Alcala", "Leganes", "Fuenlabrada", "Getafe",
                          "Alcorcon", "Torrejon", "Parla", "Alcobendas", "Coslada"};
    return locs[rand() % 10];
}

// --- Inicialización del Sistema ---
void Editorial::inicializarSistema() {
    std::cout << "--- INICIALIZANDO SISTEMA ---\n";

    // 1. Generar N_LIBRERIAS (10)
    for (int i = 0; i < N_LIBRERIAS; i++) {
        Libreria l;
        l.id_libreria = rand() % 900 + 100; // 3 cifras aleatorias (100-999)
        l.localidad = generarLocalidad();
        arbolLibrerias.Insertar(l);
    }
    std::cout << "-> " << N_LIBRERIAS << " librerias creadas en el arbol.\n";

    // 2. Generar y repartir N_PEDIDOS (30)
    std::cout << "-> Generando y repartiendo " << N_PEDIDOS << " pedidos...\n";

    for (int i = 0; i < N_PEDIDOS; i++) {
        Pedido p;
        p.id_libreria = rand() % 900 + 100; // ID aleatorio para buscar destino
        p.id_pedido = generarIdPedido();
        p.cod_libro = generarCodLibro();
        p.materia = generarMateria();
        p.unidades = rand() % 20 + 1;
        p.fecha_envio = generarFecha();

        NodoA* nodo = arbolLibrerias.Buscar(p.id_libreria);
        if (nodo != NULL) {
            nodo->info.listaPedidos.InsertarFin(p);
            // Mostrar por pantalla el pedido generado
            std::cout << "   Pedido " << p.id_pedido << " asignado a Libreria " << p.id_libreria << "\n";
        } else {
            // Si la librería aleatoria no existe, lo ignoramos
            // o reducimos 'i' para intentar otro.
            i--;
        }
    }
    std::cout << "-> Inicializacion completada. Pulse ENTER para continuar...";
    std::cin.get();
}


// --- OPCIÓN 1: Insertar Librería (CON VALIDACIÓN) ---
void Editorial::opcion1_InsertarLibreria() {
    Libreria l;
    bool entradaValida = false;

    do {
        std::cout << "ID Libreria (3 cifras, ej: 101): ";
        std::cin >> l.id_libreria;

        if (std::cin.fail()) {
            std::cout << "Error: Solo numeros.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        else if (l.id_libreria < 100 || l.id_libreria > 999) {
            std::cout << "Error: El ID debe tener exactamente 3 cifras (100-999).\n";
        }
        else {
            entradaValida = true;
        }
    } while (!entradaValida);

    std::cout << "Localidad: ";
    std::cin.ignore();
    std::getline(std::cin, l.localidad);

    arbolLibrerias.Insertar(l);
    std::cout << "Libreria insertada (Lista de pedidos vacia).\n";
}

// --- OPCIÓN 2: Borrar Librería ---
void Editorial::opcion2_BorrarLibreria() {
    int id;
    std::cout << "ID Libreria a borrar: ";
    std::cin >> id;
    arbolLibrerias.Eliminar(id);
    std::cout << "Operacion finalizada.\n";

}

// --- OPCIÓN 3: Mostrar Pedidos ---
void Editorial::opcion3_MostrarPedidosLibreria() {
    int id;
    std::cout << "ID Libreria: "; std::cin >> id;
    NodoA* nodo = arbolLibrerias.Buscar(id);
    if (nodo != NULL) {
        std::cout << "Pedidos de " << nodo->info.localidad << " (ID " << id << "):\n";
        nodo->info.listaPedidos.Mostrar();
    } else {
        std::cout << "Libreria no encontrada.\n";
    }
}

// --- OPCIÓN 4: Buscar Pedido Global ---
void Editorial::opcion4_BuscarPedidoID() {
    std::string id_ped;
    int id_lib = -1;
    std::cout << "ID Pedido a buscar: "; std::cin >> id_ped;
    Pedido p = arbolLibrerias.BuscarPedidoGlobal(id_ped, id_lib);
    if (!p.id_pedido.empty()) {
        std::cout << "Pedido encontrado en Libreria ID " << id_lib << ":\n";
        std::cout << "Libro: " << p.cod_libro << " (" << p.materia << ") | Uds: " << p.unidades << "\n";
    } else {
        std::cout << "Pedido no encontrado.\n";
    }
}

// --- OPCIÓN 5: Extraer Pedido ---
void Editorial::opcion5_ExtraerPedido() {
    int id_lib;
    std::string id_ped;
    std::cout << "ID Libreria: "; std::cin >> id_lib;
    NodoA* nodo = arbolLibrerias.Buscar(id_lib);
    if (nodo) {
        std::cout << "ID Pedido a extraer: "; std::cin >> id_ped;
        Pedido p = nodo->info.listaPedidos.Eliminar(id_ped);
        if (!p.id_pedido.empty()) std::cout << "Pedido " << p.id_pedido << " extraido.\n";
        else std::cout << "Pedido no encontrado.\n";
    } else {
        std::cout << "Libreria no encontrada.\n";
    }
}

// --- OPCIÓN 6: Mover Pedido ---
void Editorial::opcion6_MoverPedido() {
    int id_or, id_dest;
    std::string id_ped;

    std::cout << "Origen (ID): "; std::cin >> id_or;
    NodoA* nOr = arbolLibrerias.Buscar(id_or);
    if (!nOr) { std::cout << "No existe.\n"; return; }

    std::cout << "Destino (ID): "; std::cin >> id_dest;
    NodoA* nDest = arbolLibrerias.Buscar(id_dest);
    if (!nDest) { std::cout << "No existe.\n"; return; }

    std::cout << "ID Pedido: "; std::cin >> id_ped;
    Pedido p = nOr->info.listaPedidos.Eliminar(id_ped);

    if (!p.id_pedido.empty()) {
        nDest->info.listaPedidos.InsertarFin(p);
        std::cout << "Pedido movido con exito.\n";
    } else {
        std::cout << "Pedido no encontrado en origen.\n";
    }
}

// --- OPCIÓN 7: Estadística ---
void Editorial::opcion7_Estadistica() {
    std::cout << "\n--- Estadistica de Librerias ---\n";
    arbolLibrerias.InordenEstadistica();
}

// --- OPCIÓN 8: Continuar Distribución ---
void Editorial::opcion8_ContinuarDistribucion() {
    std::cout << "Generando otros " << N_PEDIDOS << " pedidos...\n";
    // Reutilizamos la lógica de inicialización pero sin borrar lo anterior
    for (int i = 0; i < N_PEDIDOS; i++) {
        Pedido p;
        p.id_libreria = rand() % 900 + 100;
        p.id_pedido = generarIdPedido();
        p.cod_libro = generarCodLibro();
        p.materia = generarMateria();
        p.unidades = rand() % 20 + 1;
        p.fecha_envio = generarFecha();

        NodoA* nodo = arbolLibrerias.Buscar(p.id_libreria);
        if (nodo != NULL) {
            nodo->info.listaPedidos.InsertarFin(p);
            std::cout << " + Pedido " << p.id_pedido << " -> Lib " << p.id_libreria << "\n";
        } else {
            i--; // Reintentar si la librería no existe
        }
    }
}



// --- NUEVO OPCIÓN 9: Ver Inorden Simple

void Editorial::opcion9_VerInordenSimple() {
    arbolLibrerias.VerInordenSimple();
}
//Privado
void Arbol::VerInordenSimple(NodoA *c) {

    if (c == NULL) return;

    VerInordenSimple(c->izq);

    std::cout << "ID: " << std::setw(3) << c->info.id_libreria
              << " | Localidad: " << c->info.localidad << std::endl;

    VerInordenSimple(c->der);
}
//Publico
void Arbol::VerInordenSimple() {
    std::cout << "\n--- LISTADO INORDEN (ID y Localidad) ---\n";
    if (raiz == NULL) {
        std::cout << "(Arbol vacio)\n";
    } else {
        VerInordenSimple(raiz);
    }
    std::cout << "----------------------------------------\n";
}


