#ifndef EDITORIAL_H
#define EDITORIAL_H

#include <iostream>
#include <string>
#include <iomanip> // Para formatear la salida en tablas
#include <cstdlib> // Para rand() y srand()


//Constantes para el proyecto
#define MAX_TITULOS 10
#define N_PEDIDOS_PASO 12
#define TAM_LOTE 10
#define LIBRERIAS 6
#define CAP_CAJA 5

//Estructura pedidos
struct Pedido {
    int id_editorial;
    std::string id_pedido;
    std::string cod_libro;
    std::string materia;
    int unidades;
    std::string estado;
};

//Clase Nodo (privada para ser usada por Pila y Cola)
class Nodo {
private:
    Pedido pedido;
    Nodo* siguiente;


    Nodo(Pedido p, Nodo* sig = NULL);

    friend class Pila;
    friend class Cola;
};

//La Clase Cola
class Cola {
private:
    Nodo* frente;
    Nodo* fin;

public:
    // Const y Dest
    Cola();
    ~Cola();

    // Métodos varios (cola)
    void encolar(Pedido p);
    Pedido desencolar();
    Pedido verFrente();
    bool estaVacia();
    void mostrar();
};

//Clase Pila
class Pila {
private:
    Nodo* cima;
    int contador;

public:
    // Const y Dest
    Pila();
    ~Pila();

    // Métodos varios (Pila)
    void apilar(Pedido p);
    Pedido desapilar();
    Pedido verCima();
    bool estaVacia();
    bool estaLlena();
    void mostrar();
};

// Estructura Stock
struct StockLibro {
    std::string cod_libro;
    std::string materia;
    int unidades;
};

//Clase Principal: Editorial
class Editorial {
private:
    //Atributos
    Cola Iniciado, Almacen, Imprenta, Listo;//Colas
    Pila cajas[LIBRERIAS];//Array Pilas (6)
    StockLibro stock[MAX_TITULOS];//Array Stock 10)

    // Funciones auxiliares privadas
    void inicializarStock();
    Pedido generarPedidoAleatorio();
    int buscarLibroEnStock(std::string cod_libro);

public:
    // Constructor
    Editorial();

    // Métodos públicos
    void generarNuevosPedidos();
    void procesarPasoDeSimulacion();
    void mostrarEstadoDelSistema();
    void verContenidoDeCaja(int id_libreria);
};

#endif // EDITORIAL_H
