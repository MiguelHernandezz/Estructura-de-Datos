
#ifndef CCONTROL_H
#define CCONTROL_H

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>


#define N_LIBRERIAS 10
#define N_PEDIDOS 30

// =================================================================
// ||  NIVEL 1: PEDIDO Y LISTA                                    ||
// =================================================================

// Struct Pedido
struct Pedido {
    int id_libreria;         // Para saber a quién pertenece al generarlo
    std::string id_pedido;   // Formato P#####
    std::string cod_libro;   // Formato 963K76
    std::string materia;     // Matemáticas, Física...
    int unidades;            // Número de ejemplares
    std::string fecha_envio; // DD-MM-2025
};

class NodoL {
private:
    Pedido info;
    NodoL *sig;
public:
    NodoL(Pedido p, NodoL* s = NULL);
    friend class Lista;
};

class Lista {
private:
    NodoL *primero;
    NodoL *ultimo;
public:
    Lista();
    ~Lista();
    void InsertarFin(Pedido p);
    Pedido Eliminar(std::string id_pedido);
    Pedido Buscar(std::string id_pedido);
    void Mostrar();
    bool estaVacia();
    int Contar();
};

// =================================================================
// ||  NIVEL 2: LIBRERÍA Y ÁRBOL                                  ||
// =================================================================

// Struct Libreria
struct Libreria {
    int id_libreria;// 3 cifras
    std::string localidad; // Móstoles, Alcalá...
    Lista listaPedidos;

    Libreria() : id_libreria(0) {} //Me aseguro ID a 0
};

class NodoA {
private:
    Libreria info;
    NodoA *izq;
    NodoA *der;
public:
    NodoA(Libreria l, NodoA *i = NULL, NodoA *d = NULL);
    friend class Arbol;
    friend class Editorial;
};

class Arbol {
private:
    NodoA *raiz;
    void Insertar(NodoA *&c, Libreria l);
    NodoA* Buscar(NodoA *c, int id_libreria);
    void Inorden(NodoA *c);
    void InordenEstadistica(NodoA *c);
    void VerInordenSimple(NodoA *c);//Para verlo en Inorden
    void Eliminar(NodoA *&c, int id_libreria);
    NodoA* minimo(NodoA *c);
    void destruir(NodoA *c);
    void verArbol(NodoA *p, int n);
    Pedido BuscarPedidoRecursivo(NodoA *c, std::string id_pedido, bool &encontrado, int &id_lib_encontrada);

public:
    Arbol();
    ~Arbol();
    void Insertar(Libreria l);
    NodoA* Buscar(int id_libreria);
    void Inorden();
    void InordenEstadistica();
    void VerInordenSimple();//Más inorden
    void Eliminar(int id_libreria);
    void verArbol();
    Pedido BuscarPedidoGlobal(std::string id_pedido, int &id_lib_encontrada);
};

// =================================================================
// ||  NIVEL 3: GESTOR (EDITORIAL)                                ||
// =================================================================

class Editorial {
private:
    Arbol arbolLibrerias;

    // Métodos auxiliares privados
    std::string generarIdPedido();
    std::string generarCodLibro();
    std::string generarMateria();
    std::string generarFecha();
    std::string generarLocalidad();

public:
    Editorial(); // Aquí se ejecutará la inicialización automática

    // Inicialización automática (Llamada desde el main)
    void inicializarSistema();

    // Opciones del menú
    void opcion1_InsertarLibreria();
    void opcion2_BorrarLibreria();
    void opcion3_MostrarPedidosLibreria();
    void opcion4_BuscarPedidoID();
    void opcion5_ExtraerPedido();
    void opcion6_MoverPedido();
    void opcion7_Estadistica();
    void opcion8_ContinuarDistribucion();
    void opcion9_VerInordenSimple();
};

#endif // CCONTROL_H
