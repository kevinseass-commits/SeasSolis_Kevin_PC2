## Actividad 2 - CC232

### Integrante
- Kevin Seas Solis


#### Bloque 1 - Núcleo conceptual de la semana

**1. Expliquen con sus palabras qué significa que un arreglo use memoria contigua.**

Significa que los elementos se almacenan uno tras otro en posiciones consecutivas de memoria. Si el primer elemento está en la dirección `A`, el segundo en `A + tamaño`, el tercero en `A + 2*tamaño`, etc. Esto permite calcular la dirección de cualquier elemento directamente, sin necesidad de recorrer la estructura.

**2. Expliquen por qué acceder a A[i] es una operación de costo O(1).**

Porque el cálculo de la dirección es una fórmula aritmética: `dirección_base + i * tamaño_elemento`. El tiempo de esta operación no depende del tamaño del arreglo ni del valor de `i`. Es constante.

**3. Expliquen la diferencia entre size y capacity.**

- **size:** Número real de elementos almacenados en la estructura (tamaño lógico).
- **capacity:** Número total de celdas reservadas en memoria (tamaño físico).
- La condición siempre es `size ≤ capacity`. El espacio extra entre `size` y `capacity` permite futuras inserciones sin redimensionar.

**4. Expliquen por qué un arreglo dinámico no puede crecer "en el mismo sitio" y necesita reservar un bloque nuevo al hacer resize().**

Un arreglo requiere un bloque contiguo de memoria. No se puede garantizar que haya espacio libre inmediatamente después del bloque actual, porque esa memoria puede estar siendo usada por otras variables. Por lo tanto, la única opción es pedir al sistema un bloque nuevo más grande, copiar todos los elementos y liberar el bloque viejo.

**5. Expliquen por qué duplicar capacidad permite defender costo amortizado O(1) para inserciones al final.**

Si duplicamos la capacidad cada vez que se llena, el número de redimensionamientos es O(log n). Cada redimensionamiento copia O(n) elementos. La suma total de copias es una serie geométrica dominada por el último término (aproximadamente 2n veces). Dividiendo entre las n inserciones, el costo amortizado por inserción es O(1). (En DengVector se usa `_capacity <<= 1`).

Si se aumentara en una cantidad fija (ej: +10), el número de redimensionamientos sería O(n) y el costo total sería O(n²).

**6. Comparen ArrayStack y DengVector: ¿qué comparten y qué cambia en interfaz o intención didáctica?**

**Comparten:**
- Ambos usan memoria contigua (`array<T> a` en ArrayStack, `T* _elem` en DengVector).
- Ambos manejan `size` (n) y `capacity` (a.length / _capacity).
- Ambos tienen `add/insert`, `remove`, `get`, `set`, `resize/expand/shrink`.

**Diferencias:**

| Aspecto | ArrayStack (Morin) | DengVector (Deng) |
|---------|-------------------|-------------------|
| Intención | Implementación minimalista de List | Vector más completo, similar a std::vector |
| Operaciones | `add(i, x)`, `remove(i)`, `get(i)`, `set(i, x)` | Mismas plus `find`, `traverse`, `operator[]` |
| Crecimiento | Duplica capacidad (`2*n`) | Duplica capacidad (`_capacity <<= 1`) |
| Reducción | Si `a.length ≥ 3*n` reduce | Si `_size * 4 > _capacity` reduce |
| Constructor copia | Usa asignación de `array<T>` | `copyFrom` explícito |
| `traverse` | No tiene | Sí, para procesamiento uniforme |

**7. Expliquen qué mejora FastArrayStack respecto a ArrayStack.**

FastArrayStack reemplaza los bucles explícitos de copia y desplazamiento por rutinas optimizadas de la biblioteca estándar:
- `std::copy` en `resize()` y `remove()`
- `std::copy_backward` en `add(i, x)`

**Mejora:** El rendimiento práctico (constante oculta) es mejor, pero la complejidad asintótica sigue siendo la misma (O(n) para inserciones/eliminaciones en posición arbitraria, O(1) amortizado para `push_back`).

**8. Expliquen cuál es la idea espacial central de RootishArrayStack.**

La idea es dividir la lista en bloques de tamaños crecientes: bloque 0 con capacidad 1, bloque 1 con capacidad 2, bloque 2 con capacidad 3, etc. La capacidad total con `r` bloques es la suma de 1+2+...+r = r(r+1)/2. Cada bloque se almacena en un arreglo independiente (memoria contigua dentro del bloque), pero los bloques no son contiguos entre sí.

**9. Expliquen por qué RootishArrayStack usa bloques de tamaños 1, 2, 3, ....**

Esta progresión minimiza el desperdicio espacial. El número de bloques `r` es aproximadamente √(2n), y el último bloque puede estar parcialmente lleno. El desperdicio total es O(√n), mucho menor que el desperdicio O(n) de un arreglo que duplica capacidad (puede tener hasta ~50% de desperdicio). Con bloques 1,2,3,..., el desperdicio relativo tiende a 0 cuando n crece.

**10. Expliquen qué relación hay entre representación, costo temporal y desperdicio espacial en estas estructuras.**

| Estructura | Representación | Costo `get(i)` | Costo `add(i)/remove(i)` | Desperdicio espacial |
|------------|----------------|----------------|--------------------------|---------------------|
| ArrayStack | Un solo arreglo contiguo | O(1) | O(n - i) | O(n) (hasta 100% en peor caso) |
| FastArrayStack | Un solo arreglo contiguo | O(1) | O(n - i) | O(n) (mismo que ArrayStack) |
| RootishArrayStack | Bloques independientes 1,2,3,... | O(1) (con i2b) | O(n - i) pero con mejor localidad | O(√n) |
| DengVector | Un solo arreglo contiguo | O(1) | O(n - i) con expand/shrink | O(n) (mismo que ArrayStack) |

**Trade-off:** RootishArrayStack sacrifica un poco de simplicidad en el acceso (necesita `i2b`) para reducir drásticamente el desperdicio de espacio. Las estructuras de un solo arreglo son más simples pero pueden desperdiciar hasta el 100% de memoria en el peor caso (justo después de un `resize`).


#### Bloque 2 - Demostración y trazado guiado

**Tabla de demos**

| Archivo | Salida u observable importante | Idea estructural | Argumento de costo o espacio |
|---------|-------------------------------|------------------|----------------------------|
| demo_array_basico.cpp | `array.length`, contenido, asignación `b = a` transfiere ownership | Arreglo contiguo básico con transferencia de memoria | Asignación O(1) porque solo mueve punteros, no copia elementos |
| demo_arraystack.cpp | `size`, elementos, `remove(1)` devuelve el valor | ArrayStack: un solo arreglo, elementos en `a[0..n-1]` | `add(i)` y `remove(i)` cuestan O(n-i) por desplazamientos |
| demo_arraystack_explicado.cpp | `debug_print` muestra arreglo interno, capacidad, tamaño | Mismo que ArrayStack pero con impresión pedagógica | Los desplazamientos en `add(1,15)` y `remove(0)` muestran el costo lineal |
| demo_fastarraystack.cpp | `size`, elementos, `add(3,99)` inserta en medio | Usa `std::copy_backward` y `std::copy` en lugar de bucles manuales | Misma complejidad asintótica, mejor constante oculta |
| demo_rootisharraystack.cpp | `size`, elementos, `remove(3)` | Bloques independientes de tamaños 1,2,3,... | `get(i)` es O(1) con `i2b`, desperdicio espacial O(√n) |
| demo_rootisharraystack_explicado.cpp | `debug_print` muestra bloques, `locate(i)` muestra (bloque, offset) | Mapeo índice lógico → (bloque, offset) mediante `i2b` | El mapeo permite O(1) sin necesidad de un solo arreglo grande |
| demo_deng_vector.cpp | `capacity` crece duplicándose, `traverse` con funciones | Vector completo con `expand()`, `shrink()`, `copyFrom` | Duplicación de capacidad da costo amortizado O(1) por inserción |
| demo_stl_vector_contraste.cpp | `capacity` también se duplica (o multiplica por 1.5) | `std::vector` usa misma estrategia de crecimiento dinámico | Mismo análisis amortizado que DengVector |

**Respuestas**

**1. En demo_array_basico.cpp, ¿qué deja claro sobre arreglo, longitud y asignación?**

Deja claro que:
- Un arreglo tiene una longitud fija (`a.length`) que se define al crear.
- La asignación `b = a` **no copia** los elementos, sino que **transfiere la propiedad** del bloque de memoria (`array<T>` usa transferencia de ownership). Esto es muy diferente a `std::vector` o DengVector, que hacen copia profunda.
- Después de la asignación, `b.length` cambia y `b` tiene los elementos que antes tenía `a`.

**2. En demo_arraystack_explicado.cpp, ¿qué operación muestra mejor el costo por desplazamientos?**

La operación **`add(1, 15)`** muestra mejor el costo por desplazamientos. El demo lo explica claramente: "Se desplazan a la derecha los elementos desde i hasta n-1". También la operación **`remove(0)`** muestra desplazamiento a la izquierda. Ambas tienen costo O(n-i) porque mueven todos los elementos después de la posición afectada.

**3. En demo_fastarraystack.cpp, ¿qué cambia en la implementación aunque no cambie la complejidad asintótica?**

Cambia el uso de **rutinas optimizadas de la biblioteca estándar**:
- `resize()` usa `std::copy` en lugar de un bucle `for`.
- `add(i, x)` usa `std::copy_backward` en lugar de un bucle `for` descendente.
- `remove(i)` usa `std::copy` en lugar de un bucle `for` ascendente.

**Complejidad:** Sigue siendo O(n) para inserciones/eliminaciones en posición arbitraria y O(n) para `resize()`. La mejora es en la **constante oculta** (rendimiento práctico), no en la cota asintótica.

**4. En demo_rootisharraystack_explicado.cpp, ¿qué ejemplo explica mejor el mapeo de índice lógico a bloque y offset?**

El ejemplo con `print_location` es el mejor. Muestra para índices específicos (0, 2, 5) la salida:
indice logico 0 -> bloque 0, offset 0, valor=10
indice logico 2 -> bloque 1, offset 1, valor=30
indice logico 5 -> bloque 2, offset 2, valor=60
Esto demuestra cómo funciona la función `i2b(i)` y cómo se distribuyen los elementos en bloques de tamaño 1, 2, 3...

**5. En demo_deng_vector.cpp, ¿qué observable permite defender el crecimiento de capacity?**

La salida que muestra `capacity` después de cada `insert`. Por ejemplo:

insert(0) -> size=1, capacity=3
insert(10) -> size=2, capacity=3
insert(20) -> size=3, capacity=3
insert(30) -> size=4, capacity=6 ← aquí se duplica (expande)
insert(40) -> size=5, capacity=6
insert(50) -> size=6, capacity=6
insert(60) -> size=7, capacity=12 ← aquí se duplica otra vez
Esta evidencia muestra que la capacidad se duplica cuando `size == capacity`, lo que permite defender el costo amortizado O(1).

**6. En demo_stl_vector_contraste.cpp, ¿qué similitud conceptual observan con DengVector?**

Ambos usan la misma estrategia de crecimiento dinámico:
- **DengVector:** Duplica capacidad (`_capacity <<= 1`) cuando `_size == _capacity`.
- **std::vector:** También duplica (o multiplica por 1.5 en algunas implementaciones) cuando `size() == capacity()`.
- Ambos muestran cómo `capacity` crece gradualmente, no de uno en uno.

La diferencia principal es que `std::vector` es una implementación de producción, mientras que DengVector es didáctica.

**7. ¿Qué demo sirve mejor para defender amortización y cuál sirve mejor para defender uso de espacio?**

| Propósito | Mejor demo | Razón |
|-----------|-----------|-------|
| **Amortización** | demo_deng_vector.cpp o demo_stl_vector_contraste.cpp | Muestran cómo `capacity` se duplica, lo que permite que el costo de `resize()` se distribuya entre muchas inserciones. |
| **Uso de espacio** | demo_rootisharraystack_explicado.cpp | Muestra la estructura por bloques de tamaños 1,2,3... y cómo el desperdicio espacial es O(√n), mucho menor que el desperdicio O(n) de ArrayStack. |


#### Bloque 3 - Pruebas públicas, stress y correctitud

**1. ¿Qué operaciones mínimas valida la prueba pública para ArrayStack?**

Basado en test_public_week2.cpp, valida:
- add(i, x): inserta en posicion (ej: s.add(1, 99))
- add(x): inserta al final (s.add(1))
- size(): para verificar cantidad de elementos
- get(i): para leer elementos
- remove(i): para eliminar por posicion

**Caso concreto:**
s.add(1); s.add(2); s.add(1, 99);
assert(s.get(0) == 1); assert(s.get(1) == 99); assert(s.get(2) == 2);
assert(s.remove(1) == 99); assert(s.size() == 2);

**2. ¿Qué operaciones mínimas valida la prueba pública para FastArrayStack?**

Valida las mismas operaciones basicas que ArrayStack porque FastArrayStack hereda de ArrayStack:
- add(size(), x): inserciones al final
- add(i, x): insercion en posicion intermedia (s.add(1, 7))
- size()
- get(i)
- remove(i)

**Caso concreto:**
s.add(s.size(), 5); s.add(s.size(), 6); s.add(1, 7);
assert(s.get(1) == 7); assert(s.remove(0) == 5); assert(s.get(0) == 7);

**3. ¿Qué operaciones mínimas valida la prueba pública para RootishArrayStack?**

Valida:
- add(i, x): inserciones en posicion
- size()
- get(i)
- set(i, x): actualizacion de elementos
- remove(i)

**Caso concreto:**
for (int i = 0; i < 6; ++i) s.add(i, i);
assert(s.get(4) == 4);
assert(s.set(4, 40) == 4);
assert(s.get(4) == 40);
assert(s.remove(2) == 2);
assert(s.size() == 5);

**4. ¿Qué sí demuestra una prueba pública sobre una estructura?**

Una prueba publica demuestra que:
- Las operaciones basicas funcionan para los casos especificos probados.
- La estructura mantiene invariantes basicos (ej: despues de add, size aumenta; despues de remove, size disminuye).
- El acceso por indice (get, set) devuelve los valores esperados.
- Diferentes implementaciones (ArrayStack, FastArrayStack, RootishArrayStack) cumplen la misma interfaz.

**5. ¿Qué no demuestra una prueba pública?**

Una prueba publica NO demuestra:
- Correctitud universal: Que funciona para TODAS las entradas posibles, solo para las probadas.
- Eficiencia: No mide cuanto tiempo tardan las operaciones ni cuantas copias/desplazamientos ocurren.
- Comportamiento con casos extremos: Por ejemplo, insertar en posicion 0 en un arreglo de 1,000,000 elementos.
- Costo amortizado: No muestra que resize() es O(n) pero ocurre pocas veces.
- Desperdicio espacial: No mide cuanta memoria se desperdicia en capacity - size.
- Reduccion (shrink): No prueba que la estructura libere memoria cuando queda muy vacia.

**6. En resize_stress_week2.cpp, ¿qué comportamiento intenta estresar sobre crecimiento, reducción o estabilidad?**

resize_stress_week2.cpp intenta estresar:

- ArrayStack: Inserta 200 elementos, luego elimina los ultimos 100. Prueba estabilidad.
- FastArrayStack: Inserta 200 elementos, luego elimina los primeros 50. Fuerza desplazamientos masivos.
- RootishArrayStack: Inserta 120 elementos, luego elimina los ultimos 60. Prueba shrink().
- DengVector: Inserta 1000 elementos, elimina los primeros 700, luego inserta 300 mas. Prueba expand(), shrink() y consistencia.

Objetivo: Verificar que despues de muchas operaciones, la estructura no pierde elementos, no corrompe indices y gestiona correctamente memoria.

**7. ¿Por qué pasar pruebas no reemplaza una explicación de invariantes y complejidad?**

Porque las pruebas solo verifican casos particulares, no la verdad universal de la estructura.

Razones:
- Una prueba puede pasar incluso si la estructura tiene bugs que no se activaron con los valores probados.
- Las pruebas no demuestran por que la estructura es correcta (no explican invariantes como que en ArrayStack n <= a.length).
- No demuestran complejidad: una estructura podria pasar las pruebas pero ser O(n²) donde deberia ser O(1) amortizado.
- No demuestran que resize() duplica capacidad correctamente en todos los casos borde.
- No verifican invariantes mas sutiles: en RootishArrayStack, que i2b(i) realmente da el bloque correcto para cualquier i.

Ejemplo: Un ArrayStack podria pasar todas las pruebas pero implementar resize() copiando elemento por elemento en orden incorrecto. Pasaria las pruebas con numeros pequeños pero fallaria con datos grandes. Solo el analisis de invariantes y complejidad garantiza la correctitud universal.


#### Bloque 4 - Vector como puente entre teoría y código

**1. ¿Qué papel cumplen _size, _capacity y _elem?**

- **_size:** Número actual de elementos válidos en el vector (tamaño lógico).
- **_capacity:** Número total de celdas reservadas en memoria (tamaño físico). Siempre _size ≤ _capacity.
- **_elem:** Puntero al arreglo dinámico que almacena los elementos en memoria contigua y permite acceso directo por índice.

**2. ¿Cuándo debe ejecutarse expand()?**

expand() debe ejecutarse antes de insertar un nuevo elemento cuando el vector esta lleno, es decir, cuando _size == _capacity. Si no se ejecutara expand(), se produciria un desbordamiento (overflow) al intentar escribir en una posicion fuera del arreglo reservado.

**3. ¿Por qué insert(r, e) necesita desplazar elementos?**

Porque el vector debe mantener memoria contigua y orden secuencial. Al insertar en posicion r, todos los elementos desde r hasta el final deben moverse una posicion a la derecha para abrir espacio. Esto preserva el invariante de que los elementos ocupen posiciones consecutivas [0, _size). El costo del desplazamiento es O(_size - r).

**4. ¿Qué diferencia conceptual hay entre remove(r) y remove(lo, hi)?**

- remove(r): Elimina un solo elemento en la posicion r. Es un caso particular de remove(lo, hi).
- remove(lo, hi): Elimina un intervalo [lo, hi) de elementos. Es mas eficiente que eliminar uno por uno porque desplaza el sufijo una sola vez, no una por cada elemento eliminado.

**5. ¿Qué evidencia de copia profunda aparece en la demo?**

En demo_deng_vector.cpp, se crean copia y asignado a partir de v. Luego se modifica copia con increaseByOne() y asignado con MultiplyByTwo(). Los resultados son independientes entre si y del original. Esto demuestra que el constructor de copia y el operador de asignacion realizan copia profunda (crean un nuevo arreglo independiente).

**6. ¿Por qué traverse() es una buena interfaz didáctica?**

Porque traverse() demuestra:

- Abstraccion: El usuario no necesita conocer la representacion interna para procesar todos los elementos.
- Polimorfismo: Acepta tanto funciones como objetos funcion (functor).
- Encapsulamiento: La estructura controla el recorrido sin exponer sus detalles internos.
- Procesamiento uniforme: Aplica la misma operacion a toda la coleccion.

**7. ¿Qué ventaja tiene implementar un vector propio antes de depender de std::vector?**

Ventajas:

- Comprension profunda de gestion de memoria dinamica (new[], delete[]).
- Entendimiento del costo amortizado por duplicacion de capacidad.
- Internalizacion de invariantes (size ≤ capacity, elementos en [0, size)).
- Aprendizaje de la necesidad de constructor de copia y operador de asignacion.
- Capacidad de instrumentar el codigo para depurar (prints, asserts).
- Independencia de la implementacion particular de std::vector.
- Transicion natural a std::vector una vez comprendidos los conceptos.

#### Bloque 5 - RootishArrayStack: espacio y mapeo

**1. ¿Cómo se distribuyen los elementos entre bloques?**

Los elementos se distribuyen en bloques de tamaños crecientes:
- Bloque 0: capacidad 1 (almacena el elemento en posición lógica 0)
- Bloque 1: capacidad 2 (almacena posiciones lógicas 1 y 2)
- Bloque 2: capacidad 3 (almacena posiciones lógicas 3, 4 y 5)
- Bloque b: capacidad b+1

Dentro de cada bloque, los elementos se almacenan de forma contigua. El mapeo se calcula con:
- b = i2b(i) (bloque que contiene el índice i)
- j = i - b*(b+1)/2 (offset dentro del bloque)

**2. ¿Por qué con r bloques la capacidad total es r(r+1)/2?**

Porque la suma de los primeros r números naturales es la fórmula de Gauss: 1 + 2 + 3 + ... + r = r(r+1)/2.

Cada bloque b tiene capacidad b+1. Si tenemos bloques 0,1,2,...,r-1 (r bloques en total), la capacidad total es:
1 + 2 + 3 + ... + r = r(r+1)/2

**3. ¿Qué problema resuelve i2b(i)?**

i2b(i) resuelve el problema de encontrar a qué bloque pertenece un índice lógico i sin recorrer todos los bloques.

Dada la ecuación de capacidad acumulada: b(b+1)/2 ≤ i < (b+1)(b+2)/2
Despejando: b = ⌈(-3 + sqrt(9 + 8i)) / 2⌉

Esto permite O(1) por acceso, en lugar de O(√n) si hubiera que buscar linealmente.

**4. ¿Qué información produce locate(i) en la versión explicada?**

locate(i) devuelve un par (bloque, offset):
- bloque (b): índice del bloque que contiene el elemento i
- offset (j): posición del elemento dentro de ese bloque (0 ≤ j ≤ b)

Implementación:
cpp
std::pair<int, int> locate(int i) const {
    const int b = i2b(i);
    const int j = i - b * (b + 1) / 2;
    return {b, j};
}
En el demo: índice 0 → bloque 0, offset 0; índice 2 → bloque 1, offset 1; índice 5 → bloque 2, offset 2.

**5. ¿Qué se gana en espacio frente a ArrayStack?**

| Estructura | Desperdicio espacial | Explicación |
|------------|---------------------|-------------|
| ArrayStack | O(n) - hasta 100% | capacity = 2n, size = n, desperdicio = n celdas vacías |
| RootishArrayStack | O(√n) - aproximadamente √(2n) | Solo el último bloque está parcialmente lleno |

Para n = 10,000:
- ArrayStack desperdicia hasta 10,000 celdas
- RootishArrayStack desperdicia ≈ 141 celdas

**6. ¿Qué se conserva igual respecto a la interfaz?**

La interfaz pública es idéntica a ArrayStack y FastArrayStack:
- size(): cantidad de elementos
- get(i), set(i, x): acceso por índice
- add(i, x), remove(i): inserción y eliminación
- clear(): limpiar

El usuario no necesita saber que la implementación usa múltiples bloques.

**7. ¿Qué parte les parece más difícil de defender oralmente: el mapeo, el análisis espacial o el costo amortizado de grow/shrink?**

La más difícil es el análisis espacial:

- Mapeo (bajo): Matemático pero directo; se ejemplifica fácil con índices pequeños.
- Costo amortizado (medio): Similar a ArrayStack; cada grow copia todo, pero ocurre pocas veces.
- Análisis espacial (alto): Hay que demostrar por qué el desperdicio es O(√n). Se debe explicar que solo el último bloque aporta desperdicio, y su tamaño crece como √(2n). La intuición es que la suma 1+2+...+r ≈ r²/2 ≈ n, por lo que r ≈ √(2n).

#### Bloque 6 - Refuerzo de lectura

**1. ¿Qué aporta operator[] a la idea de vector?**

operator[] aporta la sintaxis natural de acceso por índice, similar a los arreglos nativos. Permite escribir `v[i]` en lugar de `v.get(i)`, haciendo el código más legible y familiar. Esto acerca la abstracción del vector a la intuición del programador sin romper el encapsulamiento.

**2. ¿Qué supone find(e) sobre igualdad entre elementos?**

find(e) supone que el tipo T sobrecarga el operador `==` o tiene una forma de comparar igualdad. Esto implica que los elementos almacenados deben soportar comparación de igualdad. Para tipos básicos (int, float, etc.) funciona directamente; para tipos personalizados, el usuario debe definir `operator==`.

**3. ¿Qué muestra traverse() sobre procesamiento uniforme de toda la estructura?**

traverse() muestra que se puede aplicar una misma operación a todos los elementos sin exponer la representación interna. Acepta tanto funciones como functores, demostrando polimorfismo y flexibilidad. Es útil para operaciones como imprimir, modificar o transformar todos los elementos.

**4. ¿Por qué esta lectura sirve como refuerzo natural de DengVector aunque no sea el centro exclusivo de la semana?**

Porque DengVector implementa exactamente los conceptos de la lectura de Deng (vector dinámico, memoria contigua, redimensionamiento, copia profunda). Aunque el foco de la semana son las estructuras de Morin (ArrayStack, RootishArrayStack, etc.), DengVector conecta la teoría con una implementación concreta y completa, sirviendo como puente didáctico entre la especificación abstracta y el código real.

#### Bloque 7 - Cierre comparativo

**¿Qué cambia cuando pasamos de "usar un arreglo" a "diseñar una estructura dinámica basada en arreglo"?**

**Afirmación sobre representación:**
Un arreglo nativo es un bloque fijo de memoria contigua con tamaño determinado en tiempo de compilación o en el heap pero inmutable. Una estructura dinámica basada en arreglo añade campos auxiliares como `_size`, `_capacity` y `_elem`, separando el tamaño lógico (elementos válidos) del tamaño físico (memoria reservada).

**Afirmación sobre correctitud:**
En un arreglo nativo, la correctitud es responsabilidad del programador (no acceder fuera de límites). En una estructura dinámica, la correctitud se garantiza mediante invariantes como `0 ≤ _size ≤ _capacity`, `_elem` siempre apunta a memoria válida, y las operaciones mantienen estos invariantes con `assert()` o verificaciones.

**Afirmación sobre costo amortizado:**
Un arreglo nativo tiene costo O(1) por acceso, pero no crece dinámicamente. Una estructura dinámica introduce el costo de `resize()` (O(n) copias), pero con duplicación de capacidad se demuestra que el costo amortizado por inserción es O(1), distribuyendo el costo de las copias entre muchas operaciones.

**Afirmación sobre uso de espacio:**
Un arreglo nativo no desperdicia espacio (capacity = size) pero se desborda si se excede. Una estructura dinámica desperdicia espacio (capacity - size) para permitir crecimiento eficiente. Se puede desperdiciar hasta 100% en ArrayStack (justo después de resize), mientras que RootishArrayStack reduce el desperdicio a O(√n).

**Comparación entre ArrayStack, FastArrayStack y RootishArrayStack:**

| Aspecto | ArrayStack | FastArrayStack | RootishArrayStack |
|---------|-----------|----------------|-------------------|
| Representación | Un solo arreglo contiguo | Un solo arreglo contiguo | Múltiples bloques 1,2,3,... |
| get(i), set(i) | O(1) directo | O(1) directo | O(1) con i2b(i) |
| add(i), remove(i) | O(n - i) desplazamientos | O(n - i) con std::copy | O(n - i) pero mejor localidad |
| Desperdicio espacial | O(n) hasta 100% | O(n) hasta 100% | O(√n) ≈ √(2n) |
| Constante oculta | Baja | Muy baja (optimizada) | Media (por i2b) |
| Uso recomendado | General, simple | Producción, velocidad | Memoria limitada, grandes volúmenes |

#### Autoevaluación breve

**Qué podemos defender con seguridad:**
- La diferencia entre size (elementos válidos) y capacity (memoria reservada).
- Que duplicar capacidad da costo amortizado O(1) por inserción.
- Que el acceso por índice es O(1) por memoria contigua.
- Que ArrayStack vs FastArrayStack cambia la constante oculta, no la complejidad.
- Que RootishArrayStack mejora el desperdicio espacial a O(√n).
- La implementación de `i2b(i)` y `locate(i)` en RootishArrayStack.

**Qué todavía confundimos:**
- La diferencia exacta entre `shrink()` en DengVector vs `resize()` en ArrayStack.
- Por qué RootishArrayStack no se usa más ampliamente en la práctica (std::vector es suficiente).
- Cuándo conviene usar `reserve()` para evitar múltiples redimensionamientos.
- El análisis amortizado en secuencias con inserciones y eliminaciones mezcladas.

**Qué evidencia usaríamos en una sustentación:**
- Tabla de `capacity` en demo_deng_vector.cpp para mostrar duplicación.
- Salida de `debug_print()` en demo_rootisharraystack_explicado.cpp para mostrar bloques y mapeo.
- Captura de `test_public_week2.cpp` y `resize_stress_week2.cpp` pasando exitosamente.
- Comparación visual de desperdicio espacial con ejemplos concretos (n=10,000).
- Código de `i2b()` explicado con ejemplos (i=0,1,2,3,4,5).
- Trazas de `std::copy_backward` en FastArrayStack para mostrar optimización.
