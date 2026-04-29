# Actividad 1 - CC232

Integrante
- Kevin Seas Solis



## Bloque 1 - Núcleo conceptual

**1. Diferencia entre problema, algoritmo, ADT e implementación:**
- **Problema:** Qué necesita resolverse (ej: ordenar un arreglo)
- **Algoritmo:** Secuencia de pasos (ej: bubble sort)
- **ADT:** Especificación de operaciones sin detallar cómo se hacen (ej: `IntSequence` con `get`, `set`, `add`, `remove`)
- **Implementación:** Código concreto (ej: `FixedArraySequence` usa arreglo fijo, `VectorSequence` usa `std::vector`)

**2. En `bubble_sort.cpp`, el observable que conecta correctitud y costo:**
Las `BubbleStats` con `comparisons` y `swaps`. La correctitud se observa con `isSortedNonDecreasing()`, el costo se mide con la cantidad de comparaciones e intercambios.

**3. En `power.cpp`, por qué `power` mejora la versión ingenua:**
`powerBF` (fuerza bruta) tiene costo O(n) porque multiplica n veces. `power` (exponenciación binaria) tiene costo O(log n) porque divide el exponente por 2 en cada paso.

**4. En `fibonacci.cpp`, por qué una función correcta puede ser mala elección práctica:**
`fib(int n)` recursivo es correcto pero tiene costo O(2^n) porque recalcula los mismos valores muchas veces. `fibI(int n)` iterativo es O(n) y mucho más práctico para n grandes.

**5. En `count_ones.cpp`, por qué el tamaño de entrada no siempre coincide con el valor numérico:**
El tamaño de entrada es el número de bits (ej: 32 bits para `unsigned int`), no el valor numérico. Para n=1024, el valor es grande pero tiene solo 11 bits en 1.

**6. En `demo_adt_secuencia.cpp`, por qué la misma interfaz convive con distintas representaciones:**
`IntSequence` define las operaciones (`size`, `get`, `set`, `add`, `remove`). `FixedArraySequence` usa arreglo fijo, `VectorSequence` usa `std::vector`. El mismo ADT, implementaciones diferentes.



## Bloque 2 - Demos y trazado guiado

**Tabla de demos:**

| archivo | salida u observable importante | idea algorítmica | argumento de costo |
|---------|-------------------------------|------------------|-------------------|
| demo_bubblesort.cpp | comparaciones, intercambios, lastSwapIndex | bubble sort con optimización: termina cuando no hay intercambios | O(n²) peor caso, pero mejora en datos ordenados o casi ordenados |
| demo_power.cpp | powerBF vs power (ambos dan el mismo resultado) | exponenciación binaria: divide exponente por 2 en cada paso | O(log n) vs O(n) |
| demo_fibonacci.cpp | fib (recursivo) vs fibI (iterativo) | recursivo sin memoización vs iterativo con acumuladores | O(2ⁿ) vs O(n) |
| demo_countones.cpp | countOnes1 vs countOnes2 (mismo resultado) | Kernighan: elimina el bit 1 más bajo; conteo por bloques | O(#bits en 1) vs O(log bits) |

**Respuestas:**

**1. En demo_bubblesort.cpp, ¿qué salida sirve para defender costo y no solo resultado?**

La salida que muestra `comparaciones`, `intercambios` y `lastSwapIndex`. El resultado (`printArray`) solo indica que el arreglo quedó ordenado, pero no dice cuánto trabajo costó. Las métricas de comparaciones e intercambios permiten medir el costo real del algoritmo. Además, `lastSwapIndex` muestra una optimización: los elementos después de ese índice ya están ordenados, por lo que el algoritmo puede terminar antes sin revisarlos nuevamente.

**2. En demo_power.cpp, ¿qué comparación concreta muestra una mejora algorítmica?**

La comparación entre `powerBF(base, exp)` y `power(base, exp)`. Ambos producen el mismo resultado numérico, por ejemplo para base=3, exp=5 ambos dan 243. La mejora está en la cantidad de multiplicaciones: `powerBF` hace 5 multiplicaciones (una por cada unidad del exponente), mientras que `power` hace solo 3 multiplicaciones (una por cada bit en 1 del exponente, más los cuadrados). Para exponentes grandes, la diferencia es enorme.

**3. En demo_fibonacci.cpp, ¿qué crecimiento se vuelve defendible?**

El crecimiento O(n) del `fibI` iterativo es defendible. Se puede defender porque el número de iteraciones es directamente proporcional a n: para calcular fib(40) se hacen 40 iteraciones. En cambio, el crecimiento O(2ⁿ) del `fib` recursivo es indefendible porque para n=40 ya hace más de 100 millones de llamadas, y para n=100 es computacionalmente imposible.

**4. En demo_countones.cpp, ¿qué ejemplo ayuda más a distinguir valor numérico de tamaño en bits?**

El ejemplo `x = 0b101101001` (361 en decimal) ayuda porque muestra que un número puede tener un valor numérico moderado (361) pero relativamente pocos bits en 1 (6 bits). También ayuda el contraste entre `countOnes1(1024)` y `countOnes1(1023)`: 1024 tiene valor grande pero solo 1 bit en 1 (rápido), mientras que 1023 tiene valor menor pero 10 bits en 1 (más lento). Esto demuestra que el tamaño de entrada relevante son los bits, no el valor numérico.


## Bloque 3 - Pruebas públicas

**1. ¿Qué funciones o ideas están verificando las pruebas públicas?**

Basado en `test_public_week1.cpp` y `test_public_week1_extra.cpp`, las pruebas verifican:

- **Suma:** `sumI`, `sum`, `sum` (versión con rango)
- **Potencia:** `powerBF`, `power`, `power2BF_I`, `power2_I`, `power2BF`, `power2`
- **Fibonacci:** `fibI` (iterativo), `fib` (recursivo), `fib` (con prev)
- **Clase Fib:** `Fib::get()`
- **Bubble sort:** `bubbleSortOptimized`, `isSortedNonDecreasing`
- **Conteo de bits:** `countOnes1`, `countOnes2`
- **Máximo:** `maxI`, `maxRLinear`, `maxRDivide`
- **Reversa:** `reverseRecursive`
- **Desplazamiento:** `shiftLeftByK`
- **MCD:** `gcdCN`
- **Torres de Hanoi:** `solveHanoi`, `hanoiMoveCount`

Las ideas principales que verifican son:
- Corrección de algoritmos recursivos e iterativos
- Comparación entre versiones diferentes del mismo algoritmo
- Casos base y casos borde (ej: arreglo vacío)

**2. ¿Qué sí demuestra una prueba pública?**

Una prueba pública demuestra que las funciones producen la salida esperada **para los casos específicos que se probaron**. Por ejemplo, que `sumI({1,2,3,4}, 4)` devuelve 10, o que `power(2,10)` devuelve 1024. También demuestra que diferentes implementaciones del mismo problema (`powerBF` y `power`) llegan al mismo resultado correcto.

**3. ¿Qué no demuestra una prueba pública?**

Una prueba pública **no demuestra**:
- **Correctitud universal:** Que la función funciona para TODAS las entradas posibles, solo para las probadas.
- **Eficiencia:** No mide cuántas operaciones hizo ni cuánto tiempo tomó.
- **Comportamiento con entradas extremas:** No prueba con números negativos en funciones que no lo soportan, ni con tamaños muy grandes.
- **Costo amortizado:** No muestra si `push_back` es O(1) amortizado.
- **Casos borde no contemplados:** Por ejemplo, arreglos muy grandes o valores límite.

**4. Pregunta elegida de preguntas_semana1.md (Pregunta 2: Entrada)**

*Explicación del concepto de entrada:*

La entrada es toda la información que recibe un algoritmo para poder ejecutarse y producir una salida. Define el problema que el algoritmo debe resolver.

**Ejemplos concretos:**

| Función | Entrada | Qué representa |
|---------|---------|----------------|
| `sumI(A, n)` | arreglo A y su tamaño n | Los números a sumar y cuántos son |
| `powerBF(a, n)` | base a y exponente n | a elevado a la n |
| `fibI(n)` | entero n | posición en la secuencia de Fibonacci |
| `gcdCN(a, b)` | dos enteros a y b | números para calcular su máximo común divisor |
| `solveHanoi(n, 'A', 'B', 'C')` | número de discos y nombres de torres | configuración inicial del problema |

**Características importantes de la entrada:**
- Determina el tamaño del problema (n, tamaño del arreglo, número de discos)
- Puede tener restricciones (n ≥ 0, arreglo no vacío en algunas funciones)
- En algoritmos recursivos, la entrada se reduce en cada llamada (ej: `fib(n-1)`)

**5. Autoevaluación con rúbrica:**

| Criterio | Puntaje (1-5) | Justificación |
|----------|---------------|---------------|
| **Comprensión conceptual** | 4/5 | Entiendo la diferencia entre entrada, algoritmo y salida. Puedo identificar las entradas en cada función. |
| **Sustentación de correctitud** | 4/5 | Sé que las pruebas públicas verifican casos específicos, no la correctitud universal. Puedo explicar qué casos probarían correctitud total (propiedades invariantes, casos borde). |
| **Análisis de eficiencia** | 3/5 | Las pruebas públicas no miden eficiencia, pero sé que deberían complementarse con benchmarks y análisis de complejidad teórica O(n), O(log n), etc. |

**Para mejorar:** Agregar pruebas con temporizadores y casos grandes para medir eficiencia.



## Bloque 4 - Puente corto con Proyecto0

**1. ¿Qué diferencia observable deja demo_const_refs.cpp entre lectura, modificación y copia?**

Basado en `demo_const_refs.cpp`:

- **Lectura (`sum_readonly(original)`):** Recibe `const std::vector<int>&`, solo lee los valores. El vector original no cambia. Observable: `original` sigue siendo `{1,2,3}` después de la suma.

- **Modificación (`append_in_place(original, 4)`):** Recibe `std::vector<int>&` (referencia no constante). Modifica directamente el vector original. Observable: `original` cambia a `{1,2,3,4}`.

- **Copia (`appended_copy(original, 99)`):** Recibe `const std::vector<int>&` pero devuelve una copia modificada. El original no cambia. Observable: `original` sigue siendo `{1,2,3,4}`, mientras que `copied` es `{1,2,3,4,99}`.

**Conclusión:** Pasar por `const &` evita copias innecesarias y protege contra modificaciones. Pasar por `&` permite modificar. Devolver por valor crea una copia nueva.



**2. En bench_vector_growth.cpp, ¿qué cambia con `reserve`?**

En `bench_vector_growth.cpp` se comparan dos versiones:

- **Sin reserve:** `vector` crece automáticamente. Cada vez que supera su capacidad, se redimensiona (copia todos los elementos a memoria nueva). Esto es costoso.

- **Con reserve:** `values.reserve(n)` reserva espacio para `n` elementos al inicio. Durante las inserciones, nunca necesita redimensionarse.

**Qué cambia:** El tiempo de ejecución mejora drásticamente. Sin `reserve`, el vector redimensiona varias veces (cada vez que duplica capacidad), causando copias O(n) en cada redimensionamiento. Con `reserve`, hay cero redimensionamientos y las inserciones son O(1) amortizado sin sobrecarga extra.

El benchmark muestra que `push_back sin reserve` es más lento que `push_back con reserve` porque evita múltiples asignaciones de memoria y copias.



**3. En bench_vector_ops.cpp, ¿por qué `push_back`, `insert(begin())` e `insert(middle)` no cuestan lo mismo?**

| Operación | Complejidad | Razón |
|-----------|-------------|-------|
| `push_back` | O(1) amortizado | Agrega al final. Si hay capacidad, es inmediato; si no, redimensiona (costoso pero poco frecuente). |
| `insert(begin())` | O(n) | Inserta al inicio. Todos los elementos existentes deben desplazarse una posición a la derecha. |
| `insert(middle)` | O(n) | Inserta en el medio. La mitad de los elementos se desplazan a la derecha. |

En `bench_vector_ops.cpp`, `n = 20000`:
- `push_back` hace ~20,000 operaciones rápidas
- `insert(comienzo)` hace ~200 millones de desplazamientos
- `insert(medio)` hace ~100 millones de desplazamientos

El benchmark muestra que `insert(begin())` es el más lento, luego `insert(middle)`, y `push_back` es el más rápido.



**4. En bench_cache_effects.cpp, ¿qué intuición deja sobre localidad de memoria?**

El benchmark compara tres recorridos sobre `n = 2,000,000` elementos:

| Recorrido | Tiempo esperado | Razón |
|-----------|-----------------|-------|
| **Vector secuencial** | Más rápido | Accede a memoria contigua. La CPU carga bloques (caché) y los siguientes elementos ya están en caché. **Localidad espacial.** |
| **Vector acceso aleatorio** | Más lento | Salta a posiciones arbitrarias. La CPU no puede predecir el siguiente acceso, causando fallos de caché constantemente. |
| **std::list** | Lento | Los nodos están dispersos en memoria (no contiguos). Cada iteración sigue un puntero, y los nodos vecinos no comparten línea de caché. |

**Intuición clave:** La **localidad espacial** (acceder a posiciones cercanas en memoria) es fundamental para el rendimiento. Los vectores (memoria contigua) aprovechan la caché mucho mejor que las listas (memoria enlazada, dispersa).

El benchmark demuestra que para el mismo número de elementos, el recorrido secuencial de vector es mucho más rápido que el acceso aleatorio y que recorrer una lista.


## Bloque 5 - Extensión breve con Ejercicios0

**1. Según Ejercicios0.md, ¿cuál es el orden correcto antes de optimizar?**

El orden correcto es:

1. **Primero elegir bien el algoritmo** (la estructura de datos adecuada para el problema)
2. **Luego verificar que el programa sea correcto** (que funcione bien para todos los casos)
3. **Después medir el rendimiento** (con benchmarks y profiling)
4. **Finalmente explorar optimizaciones avanzadas** del compilador (-O2, -O3, etc.)

La idea clave es que **-O3 no reemplaza a nth_element, a lower_bound, a un buen reserve(), ni a una prueba bien hecha**. La optimización del compilador no puede corregir una mala elección algorítmica.


**2. ¿Qué quiere mostrar stl_optimizacion_demostracion.cpp con reserve, nth_element, partial_sort y lower_bound?**

El programa demuestra que **elegir el algoritmo correcto es más importante que micro-optimizar**:

| Función | Qué demuestra | Comparación |
|---------|---------------|-------------|
| `reserve()` | Reservar capacidad evita realocaciones costosas | `push_back` sin reserve vs con reserve |
| `nth_element()` | Para encontrar la mediana o k-ésimo elemento | O(n) promedio vs O(n log n) de `sort` completo |
| `partial_sort()` | Para obtener Top-K elementos | Ordenar solo K elementos vs ordenar todo el arreglo |
| `lower_bound()` | Búsqueda binaria en vector ordenado | O(log n) vs O(n) de búsqueda lineal |

**Conclusión principal:** La mejora algorítmica (cambiar la complejidad) gana frente al microajuste (optimizaciones del compilador). Un `nth_element` O(n) siempre será mejor que un `sort` O(n log n) para encontrar la mediana, sin importar qué nivel de optimización se use.


**3. ¿Qué tipo de evidencia puede producir resolver_ejercicios0_v4.2.sh?**

El script produce **evidencia experimental cuantitativa**:

| Tipo de evidencia | Cómo se genera |
|-------------------|----------------|
| **Tiempos de ejecución** | Mide con `time` o `/usr/bin/time` para cada experimento |
| **Tamaño de ejecutables** | Usa `stat -c '%s'` o `wc -c` para medir bytes |
| **Estado de compilación** | Registra si cada build falló o tuvo warnings |
| **Warnings por nivel** | Cuenta la cantidad de warnings en cada compilación |
| **Cobertura de código** | Usa `gcov` para ver líneas y ramas ejecutadas |
| **Perfil de funciones** | Usa `gprof` para identificar funciones calientes |
| **Errores detectados** | Sanitizers (ASan, UBSan, TSan) reportan UB y carreras de datos |

**Ejemplo concreto:** Para el experimento STL (ejercicio 2), el script produce una tabla como:

Caso	Tiempo (us)
push_back sin reserve	823.45
push_back con reserve	312.78
sort completo y tomar mediana	12345.67
nth_element para mediana	3456.78

**4. ¿Qué limitaciones de entorno menciona INSTRUCCIONES_Ejercicios0_v4.2.md?**

Las limitaciones principales son:

| Limitación | Explicación |
|------------|-------------|
| **Sanitizers en Windows** | ASan, UBSan o TSan pueden no enlazar correctamente en MSYS2/Git Bash |
| **gcov** | Puede requerir ajustes extra en Windows |
| **gprof** | Puede fallar o no generar perfiles útiles en Windows |
| **LTO** | `-flto` puede no funcionar en todos los entornos |
| **PGO** | Requiere soporte del compilador y puede fallar en Windows |

**Recomendación del script:** Para sanitizers, cobertura y profiling, es mejor usar **WSL Ubuntu o Linux nativo**. Para compilación normal, **UCRT64 en MSYS2** es la mejor opción en Windows.

**Advertencia importante:** El script dice explícitamente que si un ejercicio falla, no significa que el código esté mal, sino que el entorno tiene limitaciones.


**5. ¿Por qué esta parte no reemplaza la discusión de correctitud de Semana1?**

Porque **correctitud y eficiencia son temas diferentes**:

| Correctitud (Semana1) | Eficiencia (Ejercicios0) |
|----------------------|--------------------------|
| ¿El programa produce la salida correcta para toda entrada? | ¿Cuánto tiempo tarda? ¿Cuánta memoria usa? |
| Se verifica con pruebas, invariantes, pre/postcondiciones | Se verifica con benchmarks, profiling, análisis de complejidad |
| Una función puede ser correcta pero ineficiente (fib recursivo) | Una función puede ser eficiente pero incorrecta |
| Las pruebas públicas demuestran correctitud para casos específicos | Los benchmarks demuestran rendimiento en entornos específicos |

**El script `resolver_ejercicios0_v4.2.sh` no verifica correctitud.** Solo mide rendimiento, cobertura y errores de memoria/UB. Una función puede pasar todos los experimentos de optimización (ser rápida, tener buena cobertura, no tener UB) pero seguir siendo **lógicamente incorrecta** si no cumple con su especificación.

Por eso el orden propuesto en Ejercicios0.md es: **primero asegurar correctitud, luego medir rendimiento**. La optimización no puede corregir un algoritmo que ya es incorrecto desde el punto de vista lógico.



## Bloque 6 - Cierre comparativo

**¿Qué cambia cuando pasamos de defender correctitud básica en Semana1 a comparar implementaciones con evidencia experimental?**

**Afirmación de especificación:**
En Semana1, la especificación era simple: "la función debe ordenar el arreglo" o "debe devolver la suma correcta". Con evidencia experimental, la especificación se vuelve más precisa: debemos definir no solo qué hace la función, sino también bajo qué condiciones medimos (tamaño de entrada, distribución de datos, patrones de acceso). Por ejemplo, `bubbleSortOptimized` no solo debe ordenar, sino que debe hacerlo eficientemente cuando el arreglo está casi ordenado (gracias a `lastSwapIndex`).

**Afirmación de correctitud:**
La correctitud básica (pasar pruebas públicas) sigue siendo necesaria pero ya no es suficiente. Una implementación puede ser correcta (pasar todos los `assert`) pero ser inútil en la práctica si es demasiado lenta, como `fib(n)` recursivo. Con evidencia experimental, la correctitud se extiende a verificar que los resultados sean consistentes entre diferentes implementaciones del mismo problema (`powerBF` vs `power`). Además, los sanitizers (ASan, UBSan) permiten verificar que no haya errores de memoria o comportamiento indefinido.

**Afirmación de costo:**
En Semana1, el costo se discutía de forma teórica: "bubble sort es O(n²)". Con evidencia experimental, podemos medir el costo real: comparaciones, intercambios, tiempo de ejecución, bytes de memoria. El benchmark de `stl_optimizacion_demostracion.cpp` muestra que `nth_element` (O(n) promedio) es mucho más rápido que `sort` (O(n log n)) para encontrar la mediana, y que `reserve()` mejora la constante oculta aunque no cambie el Big-O. También podemos ver que `partial_sort` para Top-K es mejor que ordenar todo el arreglo.

**Afirmación de representación o memoria:**
La elección de representación impacta directamente el rendimiento. `FixedArraySequence` (arreglo fijo) tiene capacidad limitada a 16 elementos pero operaciones rápidas; `VectorSequence` (vector dinámico) crece automáticamente pero paga el costo de realocaciones. `bench_cache_effects.cpp` demuestra que un `vector` (memoria contigua) es mucho más rápido de recorrer que una `list` (memoria enlazada, dispersa) debido a la localidad espacial de caché. Esta evidencia cuantitativa permite justificar por qué elegir una representación sobre otra.

**Advertencia metodológica:**
Los benchmarks experimentales dependen críticamente del entorno: CPU, memoria caché, compilador, flags de optimización, e incluso el input usado. Como advierte `INSTRUCCIONES_Ejercicios0_v4.2.md`, ASan, UBSan, LTO, PGO y gprof pueden fallar en Windows (MSYS2) pero funcionar en Linux/WSL. Por lo tanto, los resultados deben interpretarse con cuidado: una implementación puede ser más rápida en un entorno pero más lenta en otro. Además, las pruebas públicas pasan no significa que los tests sean buenos (`experiment_6_coverage` muestra que faltaban casos), y medir mal puede engañar más que no medir.



## Autoevaluación 

**Qué podemos defender con seguridad:**
- La diferencia entre correctitud (que el programa funcione) y eficiencia (qué tan rápido funciona).
- Que `nth_element` es más eficiente que `sort` para encontrar la mediana (O(n) vs O(n log n)).
- Que `reserve()` mejora el rendimiento de `push_back` al evitar realocaciones.
- Que los sanitizers ayudan a detectar errores de memoria y comportamiento indefinido.
- Que la localidad de memoria (vector contiguo) es más rápida que lista enlazada.

**Qué todavía confundimos:**
- Cómo interpretar correctamente los resultados de profiling (`gprof` puede ser engañoso en entornos Windows).
- Por qué algunas optimizaciones de compilador (`-O3`, `-flto`, `-fprofile-use`) a veces empeoran el rendimiento en lugar de mejorarlo.
- Cómo diseñar benchmarks realmente representativos que no estén sesgados por el caché o el input específico.
- La diferencia entre cobertura de líneas, ramas y condiciones (cuando usar `--coverage` vs `-fcondition-coverage`).

**Qué evidencia usaríamos en una sustentación:**
- Tablas de tiempos del script `resolver_ejercicios0_v4.2.sh` para comparar `push_back` con/sin `reserve`.
- Capturas de `gcov` mostrando líneas no ejecutadas en `modulo.cpp`.
- Salida de ASan/UBSan detectando acceso fuera de rango en `demo_ub.cpp`.
- Comparación de tiempos entre `sort` y `nth_element` en `stl_optimizacion_demostracion.cpp`.
- Gráfico de crecimiento de tiempo vs tamaño de entrada para demostrar complejidad O(n) vs O(n²).
- Ejemplo concreto de `fib(40)` recursivo (imposible de calcular) vs `fibI(40)` (instantáneo).