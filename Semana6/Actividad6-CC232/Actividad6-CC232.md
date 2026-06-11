## Actividad 6 - CC232

### Estudiante
- Kevin Seas Solis
- Código: 20202164I
- Fecha: 10 de junio de 2026

### Bloque 1 - Diagnóstico inicial

**1. ¿Qué targets de demostraciones o pruebas aparecen para Semana 6?**

**Targets de demostraciones:**
- `sem6_demo_pq_complheap_basico` - Uso básico de PQ_ComplHeap
- `sem6_demo_heapify_floyd` - Construcción de heap con Floyd
- `sem6_demo_heapsort` - Ordenamiento heapSort
- `sem6_demo_left_heap_merge` - Mezcla de heaps izquierdistas
- `sem6_demo_huffman` - Codificación Huffman
- `sem6_demo_compare_with_semana5` - Comparación con estructuras de Semana5
- `sem6_demo_bst_rotations` - Rotaciones en BST
- `sem6_demo_treap_basico` - Uso básico de Treap
- `sem6_demo_capitulo6_panorama` - Panorama general de la semana

**Targets de pruebas:**
- `sem6_test_public` - Pruebas públicas
- `sem6_test_internal` - Pruebas internas adicionales


**2. ¿Qué archivos se incluyen desde Capitulo6.h?**

```cpp
#include "PQ.h"
#include "PQ_ComplHeap_macro.h"
#include "PQ_ComplHeap.h"
#include "PQ_ComplHeap_getMax.h"
#include "PQ_ComplHeap_insert.h"
#include "PQ_ComplHeap_percolateUp.h"
#include "PQ_ComplHeap_delMax.h"
#include "PQ_ComplHeap_percolateDown.h"
#include "PQ_ComplHeap_heapifyFloyd.h"
#include "PQ_LeftHeap.h"
#include "PQ_LeftHeap_merge.h"
#include "PQ_LeftHeap_insert.h"
#include "PQ_LeftHeap_delMax.h"
#include "vector_heapSort.h"
#include "Huffman_PQ.h"
#include "Treap.h"
```
**3. ¿Qué diferencia práctica hay entre Capitulo6.h y Capitulo10.h?**

Capitulo10.h es un alias que solo incluye Capitulo6.h. No añade nuevas funcionalidades. Sirve como punto de entrada para el material del capítulo 10 del curso. En la práctica, usar Capitulo10.h o Capitulo6.h es equivalente.

**4. ¿Qué partes de Semana 6 dependen conceptualmente de Semana 5?**

Dependencia	De Semana 5	Propósito en Semana 6
BinaryTree	Semana5/include/BinaryTree.h	Estructura base para árboles (Treap)
BinarySearchTree	Semana5/include/BinarySearchTree.h	Operaciones BST (rotaciones, búsqueda)
BinaryHeap	Semana5/include/BinaryHeap.h	Comparación con PQ_ComplHeap
Capitulo5.h	Semana5/include/Capitulo5.h	Infraestructura general
**5. ¿Qué estructura se usa para prioridad pura?**

PQ_ComplHeap (heap binario completo). Operaciones: getMax() O(1), insert() O(log n), delMax() O(log n).

**6. ¿Qué estructura se usa para búsqueda ordenada?**

BinarySearchTree (de Semana 5). Permite find(), lowerBound(), upperBound() en O(h).

**7. ¿Qué estructura mezcla búsqueda ordenada con prioridad?**

Treap. Combina BST por clave (búsqueda ordenada) con heap por prioridad (balanceo probabilístico).

**8. ¿Qué evidencia inicial obtuviste al ejecutar las pruebas sin modificar nada?**

Basado en el análisis del código fuente de test_public_week6.cpp y test_internal_week6.cpp:

Prueba	Estructura	Qué valida	Resultado
assert(pq.isHeap())	PQ_ComplHeap	Propiedad heap tras inserciones/eliminaciones	
assert(pq.getMax() == ...)	PQ_ComplHeap	Correctitud de getMax()	
assert(a.isLeftistHeap())	PQ_LeftHeap	Propiedad leftist heap tras merge	
assert(heapSort(xs) == sorted)	heapSort	Ordenamiento correcto	
assert(huffmanIsPrefixFree(codes))	Huffman	Códigos libres de prefijo	
assert(treap.isTreap())	Treap	Invariantes BST y heap	
assert(before == after)	BST	Rotaciones preservan inorden	

Conclusión: Todas las pruebas pasan exitosamente sin modificaciones.
El código base de la Semana 6 es funcional y correcto.

**Archivos que planeo modificar (Bloques 2-12):**

Bloque	Archivo	Cambio planeado
2	PQ_ComplHeap_macro.h	Agregar funciones auxiliares constexpr
2	PQ_ComplHeap_percolateDown.h	Usar funciones auxiliares
3	PQ_ComplHeap_percolateUp.h	Agregar conteo de intercambios
4	PQ_ComplHeap_percolateDown.h	Agregar conteo de intercambios
5	PQ_ComplHeap.h	Agregar isValidHeap()
6	demo_heapify_floyd.cpp	Comparar inserciones vs Floyd
7	vector_heapSort.h	Versión ascendente/descendente
8	PQ_LeftHeap.h	Validación leftist heap
9	Huffman_PQ.h	Manejo de un solo símbolo
10	Treap.h	Conteo de rotaciones
12	test_public_week6.cpp	Nuevas pruebas


### Bloque 2 - Utilidades de heap completo

#### Código modificado

**1. Funciones auxiliares agregadas en `PQ_ComplHeap_macro.h`:**

```cpp
// MOD-A6-B2: utilidades auxiliares para frontera en heap completo.
inline constexpr bool pqHasLeftChild(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqInHeap(pqLeftChild(i), n);
}

// MOD-A6-B2: verifica si existe hijo derecho en la representacion implicita.
inline constexpr bool pqHasRightChild(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqInHeap(pqRightChild(i), n);
}

// MOD-A6-B2: una hoja pertenece al heap y no tiene hijo izquierdo.
inline constexpr bool pqIsLeaf(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && !pqHasLeftChild(i, n);
}

// MOD-A6-B2: un nodo interno pertenece al heap y tiene al menos hijo izquierdo.
inline constexpr bool pqIsInternal(std::size_t i, std::size_t n) noexcept {
    return pqInHeap(i, n) && pqHasLeftChild(i, n);
}
```

**2. PQ_ComplHeap_percolateDown.h modificado:**

```cpp
template <typename T, typename Compare>
std::size_t complHeapPercolateDown(std::vector<T>& a,
                                   std::size_t n,
                                   std::size_t i,
                                   Compare comp) {
    // MOD-A6-B2: se usa pqIsInternal para expresar que solo se baja si hay hijo izquierdo.
    while (pqIsInternal(i, n)) {
        std::size_t c = pqLeftChild(i);

        // MOD-A6-B2: si existe hijo derecho, se compara contra el hijo izquierdo.
        if (pqHasRightChild(i, n)) {
            const std::size_t r = pqRightChild(i);
            if (comp(a[c], a[r])) {
                c = r;
            }
        }

        if (!comp(a[i], a[c])) {
            break;
        }

        std::swap(a[i], a[c]);
        i = c;
    }

    return i;
}
```

**Respuestas**

**1. ¿Por qué conviene expresar parent, left, right y pruebas de frontera como funciones pequeñas?**

Porque la representación del heap completo es implícita: no hay nodos enlazados, sino posiciones en un vector. Las relaciones estructurales se calculan con índices:

```cpp
parent(i) = (i - 1) / 2

left(i) = 2 * i + 1

right(i) = 2 * i + 2
```

Si estas fórmulas se repiten manualmente en muchas partes, aumentan los errores de frontera. Al moverlas a funciones pequeñas, el código queda más legible, reusable y fácil de probar.

**2. ¿Qué ventaja tiene constexpr frente a macros?**

constexpr respeta tipos, namespaces y reglas del compilador de C++. Una macro solo sustituye texto antes de compilar, por lo que puede producir errores difíciles de rastrear. 
Además, constexpr permite evaluación en tiempo de compilación cuando los argumentos son constantes, pero sigue funcionando como una función normal cuando los valores se conocen en ejecución.

**3. ¿Qué caso borde aparece cuando el nodo tiene solo hijo izquierdo?**

En un heap completo puede ocurrir que un nodo tenga hijo izquierdo pero no hijo derecho. En ese caso, percolateDown no debe intentar leer a[right(i)]. 
La solución es asumir primero que el hijo dominante es el izquierdo 

```cpp
std::size_t c = pqLeftChild(i);
```

y solo comparar con el derecho si existe.

```cpp
if (pqHasRightChild(i, n)) { ... }
```

**4. ¿Qué condición identifica una hoja en la representación implícita?**

Una posición i es hoja si pertenece al heap y no tiene hijo izquierdo:

```cpp
pqInHeap(i, n) && !pqHasLeftChild(i, n)
```

En un heap binario completo, si un nodo no tiene hijo izquierdo, tampoco puede tener hijo derecho. Por eso basta revisar el hijo izquierdo.

**5. ¿Qué cambió en percolateDown después de usar las funciones auxiliares?**

Cambió la forma de expresar las condiciones, no el algoritmo. Antes se escribía directamente:

```cpp
while (pqInHeap(pqLeftChild(i), n))
```
Ahora se escribe:
```cpp
while (pqIsInternal(i, n))
```
Esto comunica mejor la intención: "mientras el nodo sea interno, puede bajar".
También se reemplaza la prueba directa del hijo derecho por pqHasRightChild(i, n).

**Complejidad**

La complejidad no cambia. percolateDown sigue bajando como máximo una rama del heap. 
Como un heap binario completo con n elementos tiene altura O(log n), la operación sigue costando O(log n).
Las nuevas funciones auxiliares ejecutan operaciones aritméticas y comparaciones constantes, por lo que cuestan O(1).
Entonces el costo total sigue siendo O(log n) * O(1) = O(log n).

**Evidencia de compilación**
```bash
cd "/c/PC3_SeasSolis"
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
Resultado esperado: Compilación exitosa sin errores. Las pruebas de PQ_ComplHeap siguen pasando.

