<div align="center">

# 🌳 Estructura de Datos · UAH

**Data Structures (Estructuras de Datos, 780009) · B.S. Computer Engineering · Universidad de Alcalá**

[![build](https://github.com/MiguelHernandezz/Estructura-de-Datos/actions/workflows/build.yml/badge.svg)](https://github.com/MiguelHernandezz/Estructura-de-Datos/actions/workflows/build.yml)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Pointers](https://img.shields.io/badge/dynamic_memory-161B22?style=flat-square)
![Team](https://img.shields.io/badge/team-2_people-00C853?style=flat-square)

</div>

Two simulations of a book publisher's order pipeline, each built on **hand-written dynamic data structures** in C++ (no STL containers): nodes, pointers, `new`/`delete` and destructors that free every node.

> Done in a **team of 2**; my teammate's name and both IDs have been removed from the reports for privacy.

Every push is compiled with **AddressSanitizer + UBSan** and run on Ubuntu by [GitHub Actions](.github/workflows/build.yml), so invalid memory accesses fail the build.

---

## 📁 Contents

| Folder | Practice | Data structures | Report |
|---|---|---|---|
| [`PL1-simulador-editorial`](PL1-simulador-editorial) | Order-processing simulator | Linked **queues** (FIFO) and **stacks** (LIFO) | [Memoria_PL1.pdf](PL1-simulador-editorial/Memoria_PL1.pdf) |
| [`PL2-pedidos-arbol-abb`](PL2-pedidos-arbol-abb) | Order management across bookshops | **Binary search tree** of bookshops, each holding a **linked list** of orders | [Memoria_PL2.pdf](PL2-pedidos-arbol-abb/Memoria_PL2.pdf) |

---

## PL1 · Publisher simulator (queues & stacks)

Random orders move through four **queues**: *Started → Warehouse → Printing → Ready*. Each simulation step moves a batch forward, checking book stock and sending orders to the printer when stock runs out. Finished orders are packed into one **stack** (box) per bookshop, with a fixed box capacity.

- `Cola`: linked queue with front/rear pointers (`encolar`, `desencolar`, `verFrente`).
- `Pila`: linked stack with a counter to detect a full box (`apilar`, `desapilar`, `estaLlena`).
- `Editorial`: simulation logic and stock table.

## PL2 · Orders by bookshop (BST + lists)

Bookshops are stored in a **binary search tree** keyed by ID. Each node owns a **linked list** of its orders. The system starts with 10 bookshops and 30 random orders.

- BST operations: recursive insert, search, **delete (including the two-children case via in-order minimum)**, in-order traversal, tree printing and full destruction.
- Global order search across the whole tree, extract an order, and **move an order between bookshops**.
- Per-bookshop statistics computed during an in-order traversal.

---

## ▶️ Build and run

Any C++17 compiler works (g++, clang++, MinGW on Windows).

```bash
cd PL1-simulador-editorial
g++ -std=c++17 -Wall -Iinclude main.cpp src/*.cpp -o editorial
./editorial

cd ../PL2-pedidos-arbol-abb
g++ -std=c++17 -Wall -Iinclude main.cpp src/*.cpp -o pedidos
./pedidos
```

Both programs are menu-driven. On Windows you can also open the `.cbp` file in **Code::Blocks** and press *Build and run*.

---

<!-- syllabus:start -->
## 📘 Syllabus · official UAH teaching guide

> **Estructuras de Datos (780009)** · 6 ECTS · 2nd year · 1st semester · contents from the 2025-26 teaching guide · [official subject page](https://www.uah.es/es/estudios/estudios-oficiales/grados/asignatura/Estructuras-de-Datos-780009/)

| Unit | Hours | Topics |
|---|---|---|
| Foundations | 8 h | Abstract data types and their specification |
| Linear data structures | 20 h | Arrays and sorting methods · Stacks, queues and lists · Implementations and applications |
| Non-linear data structures | 28 h | Binary trees, AVL trees, heaps, general trees · Graphs · Implementations and applications |
<!-- syllabus:end -->

---

<div align="center">

Miguel Hernández López · [GitHub](https://github.com/MiguelHernandezz) · [LinkedIn](https://www.linkedin.com/in/miguel-hernandez-lopez/)

</div>
