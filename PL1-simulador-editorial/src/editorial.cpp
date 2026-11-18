#include "editorial.h"

Nodo::Nodo(Pedido p, Nodo* sig) {
    this->pedido = p;
    this->siguiente = sig;
}

// Const y Dest
Cola::Cola() {
    frente = NULL;
    fin = NULL;
}

Cola::~Cola() {
    while (!estaVacia()) {
        desencolar();
    }
}

//Métodos de Cola
void Cola::encolar(Pedido p) {
    Nodo* nuevo = new Nodo(p, NULL);
    if (estaVacia()) {
        frente = nuevo;
    } else {
        fin->siguiente = nuevo;
    }
    fin = nuevo;
}

Pedido Cola::desencolar() {
    if (estaVacia()) return Pedido();
    Pedido p = frente->pedido;
    Nodo* aux = frente;
    frente = frente->siguiente;
    if (frente == NULL) {
        fin = NULL;
    }
    delete aux;
    return p;
}

Pedido Cola::verFrente() {
    if (estaVacia()) return Pedido();
    return frente->pedido;
}

bool Cola::estaVacia() {
    return (frente == NULL);
}

void Cola::mostrar() {
    if (estaVacia()) {
        std::cout << "(vacia)" << std::endl;
        return;
    }
    Nodo* actual = frente;
    std::cout << std::left;
    std::cout << std::setw(5) << "Lib|" << std::setw(8) << "Id" << "|" << std::setw(9) << "Codigo" << "|"
              << std::setw(13) << "Materia" << "|" << std::setw(4) << "U" << "|" << std::setw(10) << "Estado" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    while (actual != NULL) {
        std::cout << std::setw(5) << actual->pedido.id_editorial << "|"
                  << std::setw(8) << actual->pedido.id_pedido << "|"
                  << std::setw(9) << actual->pedido.cod_libro << "|"
                  << std::setw(13) << actual->pedido.materia << "|"
                  << std::setw(4) << actual->pedido.unidades << "|"
                  << std::setw(10) << actual->pedido.estado << std::endl;
        actual = actual->siguiente;
    }
}




// Const y Destru (Pila)
Pila::Pila() {
    cima = NULL;
    contador = 0;
}

Pila::~Pila() {
    while (!estaVacia()) {
        desapilar();
    }
}

//Métodos de Pils
void Pila::apilar(Pedido p) {
    if (estaLlena()) return;
    Nodo* nuevo = new Nodo(p, cima);
    cima = nuevo;
    contador++;
}

Pedido Pila::desapilar() {
    if (estaVacia()) return Pedido();
    Pedido p = cima->pedido;
    Nodo* aux = cima;
    cima = cima->siguiente;
    delete aux;
    contador--;
    return p;
}

Pedido Pila::verCima() {
    if (estaVacia()) return Pedido();
    return cima->pedido;
}

bool Pila::estaVacia() {
    return (cima == NULL);
}

bool Pila::estaLlena() {
    return (contador >= CAP_CAJA);
}

void Pila::mostrar() {
    if (estaVacia()) {
        std::cout << " (vacia)" << std::endl;
        return;
    }
    Nodo* actual = cima;
    std::cout << std::left;
    std::cout << std::setw(5) << "Lib|" << std::setw(8) << "Id" << "|" << std::setw(9) << "Codigo" << "|"
              << std::setw(13) << "Materia" << "|" << std::setw(4) << "U" << "|" << std::setw(10) << "Estado" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    while (actual != NULL) {
        std::cout << std::setw(5) << actual->pedido.id_editorial << "|"
                  << std::setw(8) << actual->pedido.id_pedido << "|"
                  << std::setw(9) << actual->pedido.cod_libro << "|"
                  << std::setw(13) << actual->pedido.materia << "|"
                  << std::setw(4) << actual->pedido.unidades << "|"
                  << std::setw(10) << actual->pedido.estado << std::endl;
        actual = actual->siguiente;
    }
}





// Constructor
Editorial::Editorial() {
    inicializarStock();
}

//Métodos Públicos
void Editorial::generarNuevosPedidos() {
    std::cout << "\nGenerando " << N_PEDIDOS_PASO << " pedidos en Iniciado..." << std::endl;
    for (int i = 0; i < N_PEDIDOS_PASO; i++) {
        Iniciado.encolar(generarPedidoAleatorio());
    }
}

void Editorial::procesarPasoDeSimulacion() {
    // El orden de las fases al contrario para que no se haga un pedido entero de una sola vez
    // Se procesa "de atrás hacia adelante".

    // Fase 1: Mover de 'Listo' a 'Caja'
    int encoladosCaja = 0;
    // Bucle: mientras 'Listo' tenga pedidos y no hayamos movido el límite (12)...
    while (!Listo.estaVacia() && encoladosCaja < N_PEDIDOS_PASO) {
        // 1. Mira (sin sacar) el primer pedido de 'Listo'.
        Pedido p = Listo.verFrente();

        // 2. Comprueba si la caja de esa librería NO está llena.
        if (!cajas[p.id_editorial].estaLlena()) {
            // 3. Si hay sitio, AHORA SÍ lo saca de 'Listo'.
            p = Listo.desencolar();
            p.estado = "Caja"; // Actualiza su estado.
            // 4. Y lo apila en la caja correcta.
            cajas[p.id_editorial].apilar(p);
        }
        // 5. Incrementa el contador (incluso si no pudo moverlo, para no quedarse pillado).
        encoladosCaja++;
    }

    // Fase 2: Mover de 'Imprenta' a 'Listo'
    // Esta fase solo procesa UN pedido por paso.
    if (!Imprenta.estaVacia()) {
        // 1. Saca UN pedido de la cola de imprenta.
        Pedido p = Imprenta.desencolar();
        // 2. Busca el libro en stock.
        int idx = buscarLibroEnStock(p.cod_libro);
        // 3. Añade un lote de (10) libros al stock.
        if (idx != -1) stock[idx].unidades += TAM_LOTE;
        // 4. Mueve el pedido a 'Listo', ya que el stock se ha repuesto.
        p.estado = "Listo";
        Listo.encolar(p);
    }

    // Fase 3: Mover de 'Almacén' a 'Imprenta' O 'Listo'
    int procesadosAlmacen = 0;
    // Bucle: mientras 'Almacen' tenga pedidos Y no hayamos movido el límite (12)...
    while (!Almacen.estaVacia() && procesadosAlmacen < N_PEDIDOS_PASO) {
        // 1. Saca un pedido de 'Almacen'.
        Pedido p = Almacen.desencolar();
        // 2. Busca su libro en el stock.
        int idx = buscarLibroEnStock(p.cod_libro);

        // 3.¿Hay stock suficiente?
        if (idx != -1 && stock[idx].unidades >= p.unidades) {
            // Sí:
            stock[idx].unidades -= p.unidades; // Resta las unidades.
            p.estado = "Listo";
            Listo.encolar(p); // Lo manda a 'Listo' (camino de 4 pasos).
        } else {
            // No:
            p.estado = "Imprenta";
            Imprenta.encolar(p); // Lo manda a 'Imprenta' (camino de 5 pasos).
        }
        procesadosAlmacen++;
    }

    // Fase 4: Mover de 'Iniciado' a 'Almacén'
    int procesadosIniciado = 0;
    // Bucle: mientras 'Iniciado' tenga pedidos Y no hayamos movido el límite (12)...
    while(!Iniciado.estaVacia() && procesadosIniciado < N_PEDIDOS_PASO){
        // 1. Saca un pedido de 'Iniciado'.
        Pedido p = Iniciado.desencolar();
        // 2. Actualiza su estado.
        p.estado = "Almacen";
        // 3. Lo encola en 'Almacen'.
        Almacen.encolar(p);
        procesadosIniciado++;
    }
    std::cout << "\nPaso de simulacion ejecutado.\n";
}






void Editorial::mostrarEstadoDelSistema() {
    std::cout << "\n--- ESTADO ACTUAL DEL SISTEMA ---\n";
    std::cout << "\n== COLA INICIADO ==" << std::endl;
    Iniciado.mostrar();
    std::cout << "\n== COLA ALMACEN ==" << std::endl;
    Almacen.mostrar();
    std::cout << "\n== COLA IMPRENTA ==" << std::endl;
    Imprenta.mostrar();
    std::cout << "\n== COLA LISTO ==" << std::endl;
    Listo.mostrar();

    std::cout << "\n== STOCK ==" << std::endl;
    std::cout << std::left << std::setw(10) << "Codigo" << "|" << std::setw(13) << "Materia" << "|" << "Unidades" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (int i = 0; i < MAX_TITULOS; ++i) {
        std::cout << std::setw(10) << stock[i].cod_libro << "|" << std::setw(13) << stock[i].materia << "|" << stock[i].unidades << std::endl;
    }

    std::cout << "\n== CAJAS (PILAS por Libreria) ==" << std::endl;
    for (int i = 0; i < LIBRERIAS; ++i) {
        std::cout << "\n-- Caja Libreria " << i << " (top -> bottom) --" << std::endl;
        cajas[i].mostrar();
    }
    std::cout << "\n-----------------------------------\n";
}

void Editorial::verContenidoDeCaja(int id_libreria) {
    if (id_libreria < 0 || id_libreria >= LIBRERIAS) {
        std::cout << "ID de libreria no valido." << std::endl;
        return;
    }
    std::cout << "\n== Caja Libreria " << id_libreria << " (top -> bottom) ==" << std::endl;
    cajas[id_libreria].mostrar();
}

//Métodos Privados
void Editorial::inicializarStock() {
    std::string materias[] = {"Matematicas", "Fisica", "Tecnologia", "Musica", "Historia", "Lengua"};
    for (int i = 0; i < MAX_TITULOS; ++i) {
        stock[i].cod_libro = std::to_string(rand() % 900 + 100) +   char('A' + rand() % 26) + char('A' + rand() % 26);
        stock[i].materia = materias[rand() % 6];
        stock[i].unidades = rand() % 50 + 10;
    }
}

Pedido Editorial::generarPedidoAleatorio() {
    Pedido p;
    p.id_editorial = rand() % LIBRERIAS;
    p.id_pedido = "P" + std::to_string(rand() % 90000 + 10000);
    int libro_idx = rand() % MAX_TITULOS;
    p.cod_libro = stock[libro_idx].cod_libro;
    p.materia = stock[libro_idx].materia;
    p.unidades = rand() % 20 + 1;
    p.estado = "Iniciado";
    return p;
}

int Editorial::buscarLibroEnStock(std::string cod_libro) {
    for (int i = 0; i < MAX_TITULOS; ++i) {
        if (stock[i].cod_libro == cod_libro) {
            return i;
        }
    }
    return -1;
}
