## Actividad 3 - CC232

### Estudiante
- Kevin Seas Solis

---

#### Bloque 1 - Núcleo conceptual de la semana

**1. Explica con tus palabras qué cambia cuando una estructura pasa de almacenamiento contiguo a almacenamiento dinámico (enlazado).**

En almacenamiento contiguo (arreglos), los elementos están uno tras otro en memoria. Esto permite acceder por índice en O(1), pero insertar o eliminar en medio requiere desplazar muchos elementos. En almacenamiento dinámico enlazado (listas), los elementos (nodos) están dispersos en memoria y se conectan mediante punteros. El acceso por índice se vuelve O(n) porque hay que recorrer nodos, pero insertar o eliminar en una posición conocida (si ya tenemos el nodo) es O(1).

**2. Explica la diferencia entre acceso por rango y acceso por posición o enlace.**

- **Acceso por rango (indexado):** Se usa un número (índice) para localizar el elemento. En estructuras contiguas es O(1) por aritmética de punteros. Ej: `arreglo[i]`.
- **Acceso por posición o enlace:** Se usa una referencia directa al nodo (puntero). No se necesita un índice numérico. Ej: en `SLList`, si ya tienes un nodo `u`, puedes acceder a `u->next` en O(1).

**3. Explica por qué una lista enlazada mejora inserciones y eliminaciones locales, pero empeora el acceso por índice.**

- **Mejora:** Insertar o eliminar un nodo una vez localizado solo requiere ajustar punteros (O(1)). No hay que desplazar elementos como en arreglos.
- **Empeora:** Para acceder al elemento i-ésimo hay que recorrer desde la cabeza (o cola) nodo por nodo (O(n)), mientras que en un arreglo es O(1).

**4. Explica por qué SLList implementa bien operaciones de Stack y Queue.**

- **Stack (LIFO):** `push()` y `pop()` operan sobre la cabeza. En `SLList`, `push()` crea un nodo y lo pone al inicio (O(1)). `pop()` elimina el primer nodo (O(1)).
- **Queue (FIFO):** `add()` (enqueue) opera al final usando `tail` (O(1)). `remove()` (dequeue) opera al inicio usando `head` (O(1)). La implementación de `SLList` mantiene `head` y `tail`, lo que hace eficientes ambas operaciones.

**5. Explica por qué SLList no implementa naturalmente todas las operaciones de un Deque con el mismo costo.**

Un `Deque` requiere inserciones y eliminaciones eficientes en ambos extremos (inicio y final). `SLList` puede insertar/eliminar al inicio (O(1)) gracias a `head`. Insertar al final también es O(1) gracias a `tail`. **Pero eliminar al final** es O(n) porque para encontrar el penúltimo nodo hay que recorrer desde `head` (no hay puntero hacia atrás). La función `secondLast()` muestra esta limitación: recorre toda la lista hasta encontrar el nodo anterior a `tail`.

**6. Explica qué aporta el nodo centinela dummy en DLList.**

El nodo centinela `dummy` (un nodo que no almacena datos útiles) simplifica el manejo de casos borde:
- La lista vacía tiene `dummy.next = dummy` y `dummy.prev = dummy`.
- No hay necesidad de tratar `nullptr` como caso especial.
- Insertar antes o después de cualquier nodo (incluyendo primero y último) usa la misma lógica.
- Las operaciones `addBefore()` y `removeNode()` funcionan uniformemente.

**7. Explica por qué DLList permite justificar get(i), set(i,x), add(i,x) y remove(i) con costo O(1 + min(i, n-i)).**

`DLList::getNode(i)` decide desde dónde recorrer según la posición:
- Si `i < n/2`, empieza desde `dummy.next` (cabeza) y avanza i pasos.
- Si `i >= n/2`, empieza desde `dummy.prev` (cola) y retrocede n-i pasos.
Así, el número de pasos es el mínimo entre ir desde el inicio y desde el final, resultando en O(1 + min(i, n-i)). Las operaciones `get`, `set`, `add` y `remove` usan `getNode` para localizar el nodo.

**8. Explica cuál es la idea espacial central de SEList.**

`SEList` combina listas enlazadas con arreglos. En lugar de un elemento por nodo, cada nodo contiene un `BDeque` (basado en `ArrayDeque`) con capacidad para múltiples elementos (hasta b+1). Esto reduce la sobrecarga de memoria por punteros (menos nodos) y mejora la localidad de caché. El equilibrio se mantiene: cada bloque tiene entre b-1 y b+1 elementos, excepto posiblemente el último.

**9. Explica por qué SEList reutiliza una BDeque basada en ArrayDeque.**

- `BDeque` hereda de `ArrayDeque` pero sobrescribe `resize()` para que no redimensione (el tamaño es fijo, b+1). Esto evita realocaciones dentro del bloque.
- Usar un `ArrayDeque` permite operaciones O(1) por bloque (inserción/eliminación por índice dentro del bloque, acceso por índice).
- La estructura externa (`SEList`) maneja la distribución entre bloques mediante `spread()` y `gather()`.

**10. Explica qué papel cumple DengList dentro de esta semana y por qué no reemplaza a las estructuras de Morin.**

`DengList` es una lista doblemente enlazada más completa (similar a `CleanList`), con operaciones como `sort()`, `dedup()`, `reverse()`, `traverse()`, `find()`, `search()`. Sirve como **puente algorítmico**:
- `MorinDengBridge.h` permite convertir entre `DLList`/`SEList` y `DengList`.
- Funciones como `stable_sort_with_deng`, `dedup_with_deng`, `reverse_with_deng` reutilizan los algoritmos de `DengList` sin reimplementarlos en las estructuras de Morin.

No reemplaza a las estructuras de Morin porque `DengList` es un tipo específico (doble enlace con nodos centinela), mientras que Morin ofrece variedad (`SLList`, `DLList`, `SEList`) para estudiar diferentes compromisos estructurales. La integración es opcional (requiere `CC232_ENABLE_DENG_BRIDGE`).


#### Bloque 2 - Demostración y trazado guiado

**Tabla de demos**

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo, espacio o diseño |
|---------|-------------------------------|------------------|--------------------------------------|
| demo_sllist.cpp | `size=3`, `peek=5`, `pop=5`, `remove=10` | SLList con `head` y `tail` | `push`/`pop` O(1); `add` al final O(1); `remove`/`pop` O(1); acceso por índice O(n) |
| demo_dllist.cpp | `DLList: 10 20 30` | DLList con nodo centinela `dummy` | `get(i)` O(1+min(i,n-i)); `add(i,x)` O(1+min(i,n-i)) |
| demo_selist.cpp | `SEList: 0 10 20 30 40 50 60 70 80 90` | Bloques de tamaño `b` con `BDeque` | `get(i)` O(b + min(i,n-i)/b); espacio: n + O(b + n/b) |
| demo_deng_list.cpp | `size=4`, `front=5`, `back=20`, `ordenada: 5 10 20 30` | `DengList` (lista doble con nodos centinela) + algoritmos (`sort`) | `push_back`/`push_front` O(1); `sort` O(n log n) con vector auxiliar |
| demo_morin_deng_bridge.cpp | `DLList reforzada con Deng: 1 2 3 4`; `Removido = 1` | Puente entre Morin (`DLList`) y Deng (`DengList`) | Conversión O(n); algoritmos reutilizados sin reescribir |
| demo_capitulo3_panorama.cpp | Muestra SLList, DLList, SEList, LinkedStack, LinkedQueue, LinkedDeque, ArrayDeque | Panorama completo de la semana | Demuestra coexistencia de múltiples estructuras |
| demo_min_structures.cpp | `MinStack min=3 top=7`; `MinQueue min=2 front=4`; `MinDeque min=1 front=3 back=1` | Almacenan información adicional (mínimo acumulado) | `min()` O(1) manteniendo pares (valor, min) |
| demo_xor_list.cpp | `XorList: 5 10 20`; `front=5 back=20` | XorList usa XOR para almacenar dos punteros en uno | Ahorra memoria (un puntero por nodo) pero más compleja |
| demo_linked_adapters.cpp | Muestra `LinkedStack`, `LinkedQueue`, `LinkedDeque` | Adaptadores sobre SLList/DLList | Reutilización: Stack y Queue sobre SLList; Deque sobre DLList |
| demo_contiguous_vs_linked.cpp | Compara `ArrayDeque` (contiguo) vs `LinkedDeque`/`DLList` (enlazado) | Contraste entre representaciones | Contiguo: mejor localidad; Enlazado: inserciones locales O(1) |

**Respuestas**

**1. En demo_sllist.cpp, ¿qué secuencia deja más clara la coexistencia de comportamiento tipo pila y tipo cola dentro de SLList?**

La secuencia: `q.add(10)` (cola: agrega al final), `q.add(20)` (cola), `q.push(5)` (pila: agrega al inicio), luego `q.peek()` (muestra el inicio, comportamiento de pila), `q.pop()` (elimina del inicio, pila), `q.remove()` (también elimina del inicio, cola). Esto muestra que `SLList` puede comportarse como pila (`push`/`pop`) y como cola (`add` al final, `remove` del inicio) simultáneamente.

**2. En demo_dllist.cpp, ¿qué operación muestra mejor la inserción en una posición intermedia?**

`d.add(1, 20)` inserta en la posición 1 (entre 10 y 30). La salida `10 20 30` demuestra que la inserción funcionó correctamente. Esto muestra que `DLList` puede insertar en cualquier posición, no solo en los extremos.

**3. En demo_selist.cpp, ¿qué observable permite defender que la lista mantiene orden lógico aunque internamente trabaje por bloques?**

La salida `0 10 20 30 40 50 60 70 80 90` muestra que los elementos aparecen en el orden correcto (secuencia aritmética), aunque internamente estén distribuidos en bloques de tamaño `b=3`. El orden lógico se preserva gracias al mapeo de índices a través de los bloques.

**4. En demo_deng_list.cpp, ¿qué evidencia muestra que la lista reforzada por Deng ofrece operaciones más cercanas a un ADT de lista completo?**

La demo usa `push_back`, `push_front`, `size`, `front`, `back`, `sort()`, `to_vector()`. Esto muestra que `DengList` ofrece un ADT más completo que las estructuras de Morin, incluyendo ordenamiento y conversión a vector.

**5. En demo_morin_deng_bridge.cpp, ¿qué parte de la salida permite justificar que se reutilizan algoritmos sin reescribir la estructura base?**

La salida muestra `DLList reforzada con Deng: 1 2 3 4` y `Removido = 1`. La lista original (4,1,3,1,2) fue ordenada (`stable_sort_with_deng`) y deduplicada (`dedup_with_deng`) usando algoritmos de `DengList`, sin modificar la clase `DLList`. Esto demuestra reutilización algorítmica.

**6. En demo_min_structures.cpp, ¿qué diferencia conceptual observas entre almacenar valores y almacenar información adicional para responder min()?**

- **MinStack:** Cada elemento almacena `(valor, min_hasta_ahora)`. Al apilar, se compara con el mínimo actual.
- **MinQueue:** Usa dos pilas (entrada/salida) para mantener semántica FIFO y consultar mínimo.
- **MinDeque:** Usa dos estructuras (`front_` y `back_`) con rebalanceo.

La diferencia clave es que para `min()` en O(1) no basta con almacenar solo valores; se necesita información adicional (mínimo acumulado, estructuras auxiliares).

**7. En demo_linked_adapters.cpp, ¿qué adaptador representa mejor la idea de reutilizar una estructura existente para ofrecer una interfaz nueva?**

`LinkedStack` y `LinkedQueue` son adaptadores sobre `SLList`, reutilizando `push` (apilar) o `add` (encolar) y `pop`/`remove`. `LinkedDeque` adapta `DLList`. El mejor ejemplo es `LinkedQueue`, porque `add` usa `SLList::add` (al final) y `remove` usa `SLList::remove` (del inicio), mostrando cómo una misma estructura base puede servir para interfaces muy diferentes (cola vs pila).

**8. En demo_contiguous_vs_linked.cpp, ¿qué contraste se observa entre acceso por índice, inserción local y localidad de memoria?**

- **Acceso por índice:** `ArrayDeque` tiene O(1), `DLList` tiene O(min(i,n-i)). La demo no muestra tiempos, pero la observación final lo indica.
- **Inserción local:** Las estructuras enlazadas (`LinkedDeque`) insertan/eliminan en O(1) en los extremos, mientras que `ArrayDeque` puede requerir desplazamientos (aunque sigue siendo eficiente por ser circular).
- **Localidad de memoria:** El demo concluye que "la representación contigua ofrece mejor localidad de memoria" (elementos cercanos en memoria → mejor uso de caché). La representación enlazada tiene nodos dispersos, perdiendo localidad.


#### Bloque 3 - Pruebas públicas, stress y correctitud

**1. ¿Qué operaciones mínimas valida la prueba pública para SLList?**

Basado en test_public_week3.cpp, valida: add(x), push(x), size(), peek(), pop(), remove(). El caso concreto: s.add(10); s.add(20); s.push(5); assert(s.size() == 3); assert(s.peek() == 5); assert(s.pop() == 5); assert(s.remove() == 10); assert(s.size() == 1).

**2. ¿Qué operaciones mínimas valida la prueba pública para DLList?**

Valida: add(i, x), size(), get(i), remove(i). El caso concreto: d.add(0,10); d.add(1,30); d.add(1,20); assert(d.size()==3); assert(d.get(0)==10); assert(d.get(1)==20); assert(d.get(2)==30); assert(d.remove(1)==20); assert(d.size()==2).

**3. ¿Qué operaciones mínimas valida la prueba pública para SEList?**

Valida: add(i,x), size(), get(i), set(i,x), remove(i). El caso concreto: ods::SEList<int> s(3); for (int i=0;i<10;++i) s.add(i,i); assert(s.size()==10); assert(s.get(5)==5); assert(s.set(5,50)==5); assert(s.get(5)==50); assert(s.remove(5)==50); assert(s.size()==9).

**4. ¿Qué operaciones nuevas quedan cubiertas por test_public_extras.cpp?**

Cubre operaciones adicionales: en SLList: secondLast(), reverse(), checkSize(). En DLList: rotate(r), checkSize(), isPalindrome(), truncate(i). En MinStack/MinQueue/MinDeque: min(). En XorList: push_back, push_front, reverse(), get(), pop_front, pop_back.

**5. ¿Qué valida específicamente test_public_linked_adapters.cpp sobre LinkedStack, LinkedQueue y LinkedDeque?**

Valida que los adaptadores reutilicen correctamente las estructuras base: LinkedStack sobre SLList valida empty, push, top, pop, size. LinkedQueue sobre SLList valida empty, add, front, remove, size. LinkedDeque sobre DLList valida empty, addFirst, addLast, front, back, removeFirst, removeLast, size.

**6. ¿Qué demuestra test_public_deng_bridge.cpp sobre integración y reutilización?**

Demuestra que DengList ofrece ADT completo (push_back, push_front, add, get, contains, find_index). stable_sort_with_deng ordena DLList/SEList. dedup_with_deng elimina duplicados. reverse_with_deng invierte. to_vector y assign_from_deng convierten entre representaciones. La reutilización funciona sin modificar Morin.

**7. En stress_selist_week3.cpp, ¿qué comportamiento intenta estresar sobre crecimiento, borrado y mantenimiento del tamaño lógico?**

Intenta estresar: add(i,i) para 500 elementos (crecimiento, spread). remove(0) 250 veces (eliminación desde inicio, gather). add(i,-i) 100 veces (reinserción). Objetivo: verificar que SEList mantiene tamaño lógico, consistencia de bloques y equilibrio (bloques entre b-1 y b+1) tras muchas operaciones.

**8. ¿Qué sí demuestra una prueba pública sobre una estructura enlazada?**

Demuestra que las operaciones básicas (inserción, eliminación, acceso) funcionan para los casos probados. Que la estructura mantiene invariantes básicos (size se actualiza correctamente). Que los adaptadores cumplen la interfaz prometida. Que el puente con Deng produce resultados correctos.

**9. ¿Qué no demuestra una prueba pública por sí sola?**

No demuestra: correctitud universal (solo casos probados), ausencia de pérdidas de memoria, eficiencia (no mide tiempos), comportamiento con casos extremos, invariantes estructurales (consistencia de punteros prev/next), costo amortizado de SEList (spread/gather ocurren con baja frecuencia).

**10. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes, punteros y complejidad?**

Porque las pruebas solo verifican casos particulares, no la verdad universal. Una prueba puede pasar aunque los punteros prev/next estén inconsistentes en casos no probados. No demuestra que getNode(i) elige entre inicio o final según min(i,n-i). No verifica que rotate(r) mantiene la lista circular. No demuestra que reverse() invierte todos los enlaces. Solo el análisis de invariantes garantiza la correctitud universal.


#### Bloque 4 - SLList, DLList y SEList: lectura cercana del código

**1. En SLList, ¿qué papel cumplen head, tail y n?**

- **head:** Puntero al primer nodo de la lista. Si la lista está vacía, head es nullptr.
- **tail:** Puntero al último nodo de la lista. Permite inserciones al final en O(1). Si la lista está vacía, tail es nullptr.
- **n:** Entero que almacena el número de elementos en la lista (tamaño lógico). Se actualiza en cada inserción y eliminación.

**2. En SLList::push, pop, add y remove, ¿qué punteros cambian exactamente?**

- **push(x):** Se crea nuevo nodo u. u->next = head. head = u. Si n == 0, tail = u. n++.
- **pop():** Se guarda head en u. head = head->next. Si n == 1, tail = nullptr. delete u. n--.
- **add(x):** Se crea u. Si n == 0: head = tail = u. Si no: tail->next = u, tail = u. n++.
- **remove():** Igual que pop(): guarda head, avanza head, si queda vacío tail = nullptr, delete, n--.

**3. Explica cómo funciona secondLast() y por qué no puede resolverse directamente con solo mirar tail.**

secondLast() recorre desde head hasta encontrar el nodo cuyo next sea tail, devolviendo su valor. No puede resolverse directamente porque SLList solo tiene puntero next (no prev). Desde tail no se puede retroceder al penúltimo nodo. La única forma es recorrer desde el inicio.

**4. Explica paso a paso cómo funciona reverse() y por qué no necesita estructura auxiliar.**

Paso 1: prev = nullptr, curr = head, tail = head (el último nodo será el que era primero). Paso 2: Mientras curr no sea nulo: guardar next = curr->next, invertir puntero curr->next = prev, avanzar prev = curr, curr = next. Paso 3: Al final, head = prev. No necesita estructura auxiliar porque los punteros se reutilizan in-place.

**5. Explica qué verifica checkSize() y por qué esta función ayuda a defender correctitud.**

Verifica que el número de nodos recorridos (count) coincida con n, que si n == 0 head y tail sean nullptr, y que si n > 0 head no sea nulo y tail apunte al último nodo. Ayuda a defender correctitud porque permite detectar inconsistencias (n mal actualizado, tail desincronizado).

**6. En DLList, explica por qué getNode(i) puede empezar desde el inicio o desde el final.**

Porque compara i con n/2. Si i < n/2, empieza desde dummy.next (cabeza) y avanza i pasos. Si i >= n/2, empieza desde dummy.prev (cola) y retrocede n-i pasos. Esto garantiza O(1 + min(i, n-i)) en lugar de O(n) fijo.

**7. En DLList::addBefore, ¿qué enlaces se actualizan y por qué el nodo centinela elimina casos borde?**

Se actualizan cuatro enlaces: u->prev = w->prev, u->next = w, u->prev->next = u, u->next->prev = u. El nodo centinela dummy tiene prev y next apuntando a sí mismo cuando la lista está vacía, por lo que insertar antes de dummy (equivalente a insertar al final) o después de dummy (insertar al inicio) usa la misma lógica sin condiciones especiales.

**8. Explica cómo funciona rotate(r) sin mover los datos elemento por elemento.**

rotate(r) ajusta los punteros de la lista circularmente. Calcula r % n. Encuentra el nuevo primer nodo (getNode(n-r)). Luego reconecta: oldLast->next = oldFirst, oldFirst->prev = oldLast, newLast->next = &dummy, dummy.prev = newLast, dummy.next = newFirst, newFirst->prev = &dummy. No recorre elemento por elemento; solo cambia punteros en los extremos.

**9. Explica cómo isPalindrome() aprovecha la naturaleza doblemente enlazada de la estructura.**

isPalindrome() usa dos punteros: left (desde dummy.next) y right (desde dummy.prev). Avanza left hacia adelante y right hacia atrás simultáneamente, comparando left->x con right->x. Si en algún punto son diferentes, no es palíndromo. Solo funciona porque DLList tiene enlaces prev y next que permiten recorrer en ambas direcciones.

**10. En SEList, explica qué representa Location.**

Location es una estructura auxiliar (definida dentro de SEList) que contiene dos campos: u (puntero al Node que contiene el bloque BDeque) y j (índice dentro de ese bloque donde se encuentra el elemento). Permite localizar un elemento lógico i en términos de bloque físico y offset.

**11. Explica qué hacen spread() y gather() y en qué situaciones aparecen.**

- **spread():** Cuando un bloque se llena (tamaño b+1) y se necesita insertar, spread() redistribuye elementos entre bloques vecinos para crear espacio. Aparece en add() cuando no hay espacio local.
- **gather():** Cuando un bloque se vacía demasiado (tamaño b-1) y se necesita eliminar, gather() fusiona bloques contiguos para mantener el equilibrio. Aparece en remove() cuando un bloque queda por debajo del mínimo.

**12. Explica cómo el tamaño de bloque b afecta el trade-off entre acceso, actualización y uso de espacio.**

| b pequeño (ej: 2) | b grande (ej: 32) |
|-------------------|-------------------|
| Más bloques, más sobrecarga de punteros | Menos bloques, menos sobrecarga |
| get(i) recorre más bloques (O(n/b)) | get(i) más rápido (menos bloques) |
| spread()/gather() más frecuentes | spread()/gather() menos frecuentes pero más costosos |
| Mejor para inserciones/eliminaciones frecuentes | Mejor para acceso frecuente |
| Espacio: n + O(b + n/b) está optimizado cuando b ≈ √n |


#### Bloque 5 - Adaptadores y estructuras derivadas

**1. ¿Cómo reutiliza LinkedStack a SLList?**

LinkedStack contiene un miembro privado `SLList<T> list`. Las operaciones se delegan directamente:
- `push(x)` → `list.push(x)`
- `pop()` → `list.pop()`
- `top()` → `list.peek()`
- `size()` → `list.size()`
- `empty()` → `list.empty()`
- `clear()` → `list.clear()`

**2. ¿Cómo reutiliza LinkedQueue a SLList?**

LinkedQueue también contiene un miembro privado `SLList<T> list`. Las operaciones se delegan:
- `add(x)` → `list.add(x)` (agrega al final usando tail)
- `remove()` → `list.remove()` (elimina del inicio usando head)
- `front()` → `list.peek()`
- `size()` → `list.size()`
- `empty()` → `list.empty()`
- `clear()` → `list.clear()`

**3. ¿Por qué LinkedDeque se construye naturalmente sobre DLList y no sobre SLList?**

Porque un deque (double-ended queue) requiere inserciones y eliminaciones eficientes en **ambos extremos**. SLList no puede eliminar del final en O(1) porque no tiene puntero `prev` para encontrar el penúltimo nodo. DLList, con su estructura doblemente enlazada y nodo centinela, permite `addFirst()` y `addLast()` en O(1) usando `add(0, x)` y `add(n, x)`, y `removeFirst()` y `removeLast()` en O(1) usando `remove(0)` y `remove(n-1)`.

**4. En MinStack, ¿por qué cada entrada guarda el valor y el mínimo acumulado?**

Cada entrada es un `Entry` con `value` (el dato) y `current_min` (el mínimo hasta ese punto). Al apilar, se compara el nuevo valor con el `current_min` del tope actual. Esto permite responder `min()` en O(1) sin recorrer toda la pila. Si solo se guardara el valor, para obtener el mínimo habría que recorrer toda la pila (O(n)).

**5. En MinQueue, ¿por qué usar dos pilas permite mantener semántica FIFO y consulta de mínimo?**

MinQueue usa dos `MinStack`: `in_` (para entradas) y `out_` (para salidas). La técnica es:
- `add(x)` → `in_.push(x)`
- `remove()` → si `out_` está vacía, mover todos los elementos de `in_` a `out_` (invirtiendo el orden), luego `out_.pop()`
- `front()` → si `out_` está vacía, mover elementos, luego `out_.top()`
- `min()` → mínimo entre `in_.min()` y `out_.min()`

Esto logra FIFO con dos LIFO y mantiene `min()` en O(1) amortizado porque cada elemento se mueve de `in_` a `out_` solo una vez.

**6. En MinDeque, ¿qué problema resuelve el rebalanceo entre front_ y back_?**

MinDeque usa dos `MinStack`: `front_` (para el lado izquierdo) y `back_` (para el lado derecho). El problema es que las operaciones `front()` y `back()` pueden fallar si una de las dos pilas está vacía. `rebalance()` resuelve esto:
- Toma una foto del orden actual con `snapshotOrder()`.
- Reconstruye la división: la mitad izquierda va a `front_` (en orden inverso para mantener LIFO correcto) y la mitad derecha a `back_`.
Así garantiza que ambas pilas tengan elementos para responder `front()` y `back()`.

**7. Compara "implementar una estructura" y "adaptar una estructura existente" usando ejemplos de este bloque.**

| Aspecto | Implementar una estructura | Adaptar una estructura existente |
|---------|---------------------------|--------------------------------|
| Definición | Escribir todo el código desde cero | Reutilizar una estructura base para ofrecer una interfaz diferente |
| Ejemplo en bloque | `MinStack` (implementa lógica de mínimos sobre `SLList`) | `LinkedStack` (solo delega en `SLList`) |
| Cantidad de código | Más código (gestión de nodos, punteros) | Mínimo código (solo delegación) |
| Riesgo de errores | Mayor (hay que manejar punteros, casos borde) | Menor (se reutiliza código ya probado) |
| Flexibilidad | Total (puedes optimizar lo que quieras) | Limitada (dependes de la estructura base) |
| `LinkedQueue` | No implementa nodos; usa `SLList::add` y `SLList::remove` | Adaptador sobre `SLList` |

**8. ¿Qué operaciones puedes defender como constantes y cuáles debes defender como amortizadas?**

| Estructura | Operaciones constantes O(1) | Operaciones amortizadas O(1) |
|------------|---------------------------|------------------------------|
| `LinkedStack` | `push`, `pop`, `top`, `size`, `empty` | Ninguna (todas constantes) |
| `LinkedQueue` | `add`, `remove`, `front`, `size`, `empty` | Ninguna (todas constantes) |
| `LinkedDeque` | `addFirst`, `addLast`, `removeFirst`, `removeLast`, `front`, `back` | Ninguna (todas constantes) |
| `MinStack` | `push`, `pop`, `top`, `min`, `size`, `empty` | Ninguna (todas constantes) |
| `MinQueue` | `add`, `front`, `remove` (por el movimiento entre pilas) → amortizado | `min()` (constante, pero depende de `in_` y `out_`) |
| `MinDeque` | `addFirst`, `addLast`, `removeFirst`, `removeLast` | `front()`, `back()`, `min()` (rebalanceo) |


#### Bloque 6 - Deng como refuerzo algorítmico y puente de integración

**1. ¿Qué operaciones del ADT de lista aparecen reforzadas en DengList?**

DengList refuerza las operaciones del ADT de lista con funcionalidades adicionales:
- **Básicas:** `size()`, `empty()`, `clear()`, `push_front()`, `push_back()`, `add()`, `add(index, value)`, `front()`, `back()`, `get()`, `set()`, `remove()`
- **Búsqueda:** `contains()`, `find_index()`
- **Algoritmos de alto nivel:** `sort()` (ordenación estable), `dedup()` (eliminación de duplicados), `uniquify()` (eliminación de duplicados consecutivos), `reverse()` (inversión)
- **Conversión:** `to_vector()` (exportar a vector)

**2. ¿Qué ventaja tiene encapsular una lista más rica sin cambiar el resto de estructuras de Semana 3?**

La ventaja es **reutilización sin modificación**. Las estructuras de Morin (`DLList`, `SEList`) no necesitan implementar `sort()`, `dedup()` ni `reverse()`. Gracias al puente (`MorinDengBridge`), se puede:
- Convertir una estructura Morin a `DengList` con `to_deng()`
- Aplicar el algoritmo sobre `DengList` (ej: `sort()`)
- Convertir de vuelta con `assign_from_deng()`

Esto mantiene el código de Morin limpio y centrado en su propósito original (listas enlazadas), mientras que Deng aporta algoritmos sin invasión.

**3. Explica qué hacen to_deng y assign_from_deng.**

- **`to_deng(src)`:** Convierte una estructura de Morin (`DLList` o `SEList`) en un `DengList`. Recorre la estructura original elemento por elemento y los agrega al `DengList` con `push_back()`.
- **`assign_from_deng(dst, src)`:** Asigna el contenido de un `DengList` a una estructura de Morin. Limpia el destino (`dst.clear()`) y luego agrega cada elemento del `DengList` usando `dst.add(value)` (o `dst.add(index++)` para SEList).

**4. Explica por qué stable_sort_with_deng no obliga a reimplementar ordenamiento dentro de DLList o SEList.**

Porque `stable_sort_with_deng` sigue estos pasos:
1. Convierte la lista de Morin a `DengList` con `to_deng()`
2. Llama a `tmp.sort()` (el ordenamiento ya está implementado en `DengList`/`CleanList`)
3. Convierte de vuelta con `assign_from_deng()`

Así, no se necesita reimplementar ordenamiento en `DLList` ni `SEList`. La reutilización es total.

**5. Explica qué hace dedup_with_deng y qué relación guarda con deduplicate() o uniquify() de la teoría.**

- **`dedup_with_deng`** elimina todos los elementos duplicados en toda la lista (no solo consecutivos). Usa dos bucles anidados para comparar cada elemento con todos los siguientes.
- **Relación con la teoría:**
  - `deduplicate()` en vectores no ordenados elimina duplicados en O(n²) recorriendo el prefijo.
  - `uniquify()` en vectores ordenados elimina duplicados consecutivos en O(n).
  - `dedup_with_deng` implementa la versión no ordenada (O(n²)), similar a `deduplicate()`.

**6. Explica por qué reverse_with_deng es un ejemplo de reutilización de algoritmos sobre una interfaz común.**

`reverse_with_deng` funciona con `DLList` y con `SEList` usando el mismo código:
1. Convierte cualquier lista a `DengList`
2. Llama a `tmp.reverse()` (implementado en `DengList`/`CleanList`)
3. Convierte de vuelta

La interfaz común es la capacidad de convertirse a `DengList` y desde `DengList`. Una vez que una estructura soporta `to_deng()` y `assign_from_deng()`, puede reutilizar **todos** los algoritmos de Deng.

**7. ¿Qué costo adicional introduce la conversión entre estructuras y cuándo vale la pena aceptarlo?**

**Costo adicional:**
- **Tiempo:** O(n) para recorrer la estructura original (tanto en `to_deng` como en `assign_from_deng`)
- **Espacio:** O(n) para almacenar temporalmente el `DengList` (que internamente es una `CleanList` con nodos doblemente enlazados)

**Vale la pena aceptarlo cuando:**
- Los algoritmos reutilizados (`sort`, `dedup`, `reverse`) tienen costo O(n log n) o O(n²). La conversión O(n) es aceptable comparada con el costo del algoritmo.
- Se aplica sobre listas de tamaño moderado.
- Se prioriza la **productividad del desarrollo** (no reescribir algoritmos) sobre la máxima eficiencia.
- Se usa en contexto didáctico para mostrar integración entre bibliotecas.

**Ejemplo:** Ordenar una lista de 1,000 elementos con `stable_sort_with_deng`. `sort()` cuesta O(n log n) ≈ 10,000 operaciones. La conversión O(1000) es solo un 10% adicional, un costo razonable por no implementar ordenamiento en `DLList`.


#### Bloque 7 - Comparación enlazado vs contiguo, variantes y evidencia experimental

**1. Compara ArrayDeque y LinkedDeque: ¿qué cambia en representación y qué cambia en costo observable?**

| Aspecto | ArrayDeque (contiguo) | LinkedDeque (enlazado) |
|---------|----------------------|----------------------|
| **Representación** | Un solo arreglo contiguo con índices `j` y `n`; usa aritmética modular `(j+i)%length` | DLList con nodos doblemente enlazados y nodo centinela `dummy` |
| **Memoria** | Bloque contiguo, mejor localidad de caché | Nodos dispersos, cada nodo tiene dos punteros (prev/next) |
| **get(i)** | O(1) directo (acceso por índice) | O(1 + min(i, n-i)) (recorre desde extremo más cercano) |
| **add(i,x)/remove(i)** | O(1 + min(i, n-i)) con desplazamientos locales | Mismo costo asintótico, pero con ajuste de punteros en lugar de desplazar elementos |
| **addFirst/addLast** | O(1) amortizado (puede requerir resize) | O(1) constante (solo ajusta punteros) |
| **Localidad** | Excelente (elementos cercanos en memoria) | Pobre (nodos dispersos, sigue punteros) |

**2. ¿Qué significa que una representación contigua tenga mejor localidad de memoria?**

Significa que los elementos están almacenados en posiciones de memoria consecutivas. Cuando la CPU accede a un elemento, carga en caché un bloque de memoria (línea de caché) que contiene también los elementos vecinos. Esto hace que accesos secuenciales o cercanos sean muy rápidos porque los datos ya están en caché. En estructuras enlazadas, los nodos están dispersos, por lo que cada acceso puede requerir cargar una línea de caché diferente (fallo de caché).

**3. ¿Qué tipo de operaciones favorecen más a la representación enlazada?**

Las operaciones que favorecen a la representación enlazada son:
- **Inserciones y eliminaciones en posición conocida** (ej: después de un nodo ya localizado) – O(1)
- **Operaciones en los extremos** (addFirst, addLast, removeFirst, removeLast) – O(1)
- **Cuando se trabaja con referencias a nodos en lugar de índices**
- **Cuando el tamaño de los elementos es grande** (la sobrecarga de punteros se amortiza)
- **Cuando se necesita dividir o concatenar listas** (O(1) con punteros)

**4. En el benchmark, ¿qué comparación sirve mejor para discutir acceso aleatorio y cuál sirve mejor para discutir operaciones en extremos?**

Basado en `benchmark_semana3.cpp`:

| Propósito | Comparación | Explicación |
|-----------|-------------|-------------|
| **Acceso aleatorio** | `random_get_arraydeque` vs `random_get_dllist` | ArrayDeque accede directamente O(1); DLList recorre desde el extremo más cercano (medio recorrido). El benchmark muestra que ArrayDeque es mucho más rápido. |
| **Operaciones en extremos** | `deque_contiguo_arraydeque` vs `deque_enlazado_linkeddeque` | Ambos son O(1) amortizado, pero el benchmark puede mostrar diferencias en constantes ocultas (resize en ArrayDeque vs ajuste de punteros en LinkedDeque). |

**5. ¿Por qué el benchmark no debe leerse como prueba absoluta de superioridad de una estructura sobre otra?**

Por las siguientes razones:

- **Dependencia del hardware:** Los resultados varían según CPU, memoria caché, velocidad de RAM.
- **Dependencia del compilador:** Las optimizaciones (-O2, -O3) afectan los tiempos.
- **Dependencia del patrón de acceso:** Un benchmark que favorece acceso secuencial (ArrayDeque) no refleja un uso mixto.
- **Tamaño de entrada:** Para n pequeño, la sobrecarga de punteros puede dominar; para n grande, la localidad gana.
- **Representatividad:** Un benchmark no cubre todos los posibles patrones de uso del mundo real.
- **Costo amortizado:** Los benchmarks cortos no capturan el costo de redimensionamientos (resize) que ocurren esporádicamente.

**6. ¿Qué idea intenta mostrar XorList respecto al ahorro de punteros?**

XorList (lista XOR) intenta mostrar que se puede **ahorrar un puntero por nodo** en una lista doblemente enlazada. En lugar de almacenar `prev` y `next` por separado, guarda un solo campo `link = prev XOR next`. Dado cualquier nodo, se puede recuperar el vecino si se conoce el otro. Esto reduce la memoria de 2 punteros a 1 puntero por nodo, aproximadamente un 50% de ahorro en la estructura de enlaces.

**7. ¿Qué desventaja práctica introduce una estructura como XorList aunque sea interesante desde el punto de vista del espacio?**

Las principales desventajas prácticas son:

| Desventaja | Explicación |
|------------|-------------|
| **No se puede depurar fácilmente** | Los depuradores no pueden mostrar los enlaces directamente (son valores XOR) |
| **Mayor complejidad de código** | Las operaciones requieren mantener el nodo anterior y siguiente manualmente |
| **No funciona con recolección de basura** | Algunos lenguajes (Java, C#) no permiten manipular punteros como enteros |
| **No es compatible con punteros inteligentes** | En C++, `std::unique_ptr` o `std::shared_ptr` no soportan XOR |
| **Riesgo de errores sutiles** | Un error en el cálculo XOR puede corromper toda la lista y es difícil de rastrear |
| **Limitado a punteros de mismo tipo** | No funciona con polimorfismo o herencia compleja |
| **Iteración más lenta** | Cada paso requiere calcular el siguiente nodo con XOR, no es tan rápido como seguir un puntero directo |

**Conclusión:** XorList es un ejemplo interesante desde el punto de vista teórico y de ahorro de memoria, pero rara vez se usa en la práctica debido a su complejidad y a las limitaciones que introduce.


#### Bloque 8 - Cierre comparativo y preparación de sustentación

**¿Qué cambia cuando pasamos de "usar arreglos dinámicos" a "diseñar estructuras enlazadas y adaptadores sobre nodos"?**

**Afirmación sobre representación:**
En arreglos dinámicos (contiguos), los elementos se almacenan en un bloque único de memoria, y el orden lógico coincide con el orden físico. En estructuras enlazadas, los elementos se almacenan en nodos dispersos conectados por punteros, y el orden lógico se mantiene únicamente a través de los enlaces entre nodos. Esto introduce una sobrecarga de memoria por punteros (1 en SLList, 2 en DLList) pero elimina la necesidad de desplazar elementos.

**Afirmación sobre acceso por rango frente a acceso por posición:**
En arreglos dinámicos, el acceso por rango (índice) es O(1) porque se calcula la dirección directamente. En listas enlazadas, el acceso por índice es O(n) en SLList y O(1 + min(i, n-i)) en DLList (porque puede empezar desde el extremo más cercano). El acceso por posición (referencia directa al nodo) es O(1) en ambas, pero obtener esa referencia requiere recorrido si se parte de un índice.

**Afirmación sobre inserciones y eliminaciones locales:**
En arreglos dinámicos, insertar o eliminar en una posición intermedia requiere desplazar O(n - i) elementos, lo que es costoso. En listas enlazadas, una vez localizado el nodo, insertar o eliminar requiere solo ajustar punteros (O(1)). Esto hace que las listas sean muy eficientes cuando las modificaciones son frecuentes y se trabaja con referencias directas a nodos (ej: en adaptadores como LinkedStack, LinkedQueue).

**Afirmación sobre complejidad de SLList, DLList y SEList:**

| Estructura | get(i) / set(i) | add(i) / remove(i) | addFirst / addLast | Espacio adicional |
|------------|-----------------|-------------------|-------------------|------------------|
| SLList | O(n) | O(n) para posición arbitraria; O(1) en extremos | O(1) | 1 puntero por nodo |
| DLList | O(1 + min(i, n-i)) | O(1 + min(i, n-i)) | O(1) | 2 punteros por nodo |
| SEList | O(b + min(i, n-i)/b) | O(b + min(i, n-i)/b) + amortizado | O(1) (por bloques) | O(b + n/b) |

**Afirmación sobre reutilización mediante adaptadores o puentes:**
Los adaptadores (`LinkedStack`, `LinkedQueue`, `LinkedDeque`) reutilizan estructuras existentes (`SLList`, `DLList`) sin reescribir la lógica de nodos. El puente con Deng (`MorinDengBridge`) permite reutilizar algoritmos (`stable_sort_with_deng`, `dedup_with_deng`, `reverse_with_deng`) sobre `DLList` y `SEList` sin modificar su código, demostrando que convertir entre representaciones (O(n)) puede ser aceptable para obtener funcionalidad avanzada.

**Comparación entre representación contigua y enlazada:**

| Criterio | Representación contigua (ArrayDeque) | Representación enlazada (DLList) |
|----------|-------------------------------------|----------------------------------|
| Acceso por índice | O(1) directo | O(1 + min(i, n-i)) |
| Inserción/eliminación en extremos | O(1) amortizado (resize) | O(1) constante |
| Inserción/eliminación en medio | O(n - i) desplazamientos | O(1 + min(i, n-i)) localización + O(1) ajuste |
| Localidad de memoria | Excelente (caché) | Pobre (nodos dispersos) |
| Memoria por elemento | Solo el dato | Dato + 1 o 2 punteros |
| Redimensionamiento | Necesita resize() (copia O(n)) | Crece/shrink instantáneo (nuevo nodo) |
| Uso recomendado | Acceso frecuente por índice, pocas modificaciones en medio | Modificaciones frecuentes, poco acceso por índice |

---

#### Autoevaluación breve

**Qué puedo defender con seguridad:**
- La diferencia fundamental entre memoria contigua y memoria enlazada.
- Que `SLList` implementa eficientemente `Stack` y `Queue` porque sus operaciones se concentran en los extremos (head y tail).
- Que `DLList` con nodo centinela elimina casos borde y permite `get(i)` con O(1 + min(i, n-i)) gracias a recorrido bidireccional.
- Que `SEList` reduce desperdicio espacial usando bloques de tamaño b, con un trade-off entre acceso, actualización y espacio.
- Que los adaptadores (`LinkedStack`, `LinkedQueue`, `LinkedDeque`) son ejemplos de reutilización de código.
- Que `XorList` ahorra memoria (un puntero por nodo) pero es compleja de depurar.

**Qué todavía confundo:**
- El análisis amortizado exacto de `spread()` y `gather()` en `SEList` (cómo se demuestra que el costo total es O(bm) para m operaciones).
- Por qué `MinQueue` con dos pilas da `min()` O(1) amortizado pero `remove()` también es amortizado (movimiento entre pilas).
- La diferencia práctica entre `dedup()` y `uniquify()` en `DengList` (uno elimina todos los duplicados, otro solo consecutivos).
- Cuándo conviene usar `SEList` sobre `DLList` en un problema real (depende de b, tamaño de elementos, frecuencia de acceso).

**Qué evidencia usaría en una sustentación:**
- Capturas de `demo_sllist.cpp`, `demo_dllist.cpp`, `demo_selist.cpp` mostrando salidas.
- Tabla de `benchmark_semana3.cpp` comparando `random_get_arraydeque` vs `random_get_dllist`.
- Código de `MinStack` mostrando cómo cada `Entry` guarda `value` y `current_min` para `min()` O(1).
- Captura de `demo_morin_deng_bridge.cpp` mostrando ordenamiento y deduplicación de `DLList` usando algoritmos de Deng.
- Diagrama de `SEList::getLocation(i)` explicando cómo se distribuyen los elementos en bloques de tamaño b.
- Comparación de tiempos entre `ArrayDeque` y `LinkedDeque` para acceso secuencial vs acceso aleatorio.

