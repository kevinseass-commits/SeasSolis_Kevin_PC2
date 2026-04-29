## Actividad 1 - CC232

### Integrantes
- Kevin Seas Solis (Código: [TU_CÓDIGO])

---

#### Bloque 1 - Núcleo conceptual

**1. Diferencia entre problema, algoritmo, ADT e implementación:**
- **Problema:** Qué se necesita resolver (entrada → salida)
- **Algoritmo:** Secuencia de pasos para resolver el problema
- **ADT (Tipo Abstracto de Datos):** Especificación de operaciones sin detallar cómo se implementan
- **Implementación:** Código concreto que realiza las operaciones del ADT

**2. En bubble_sort.cpp, el observable que conecta correctitud y costo:**
El número de comparaciones e intercambios. La correctitud se observa cuando el arreglo queda ordenado; el costo se mide por la cantidad de operaciones realizadas.

**3. En power.cpp, por qué power mejora la versión ingenua:**
La versión ingenua multiplica n veces (O(n)), mientras que power usa exponenciación binaria (O(log n)), reduciendo drásticamente las operaciones.

**4. En fibonacci.cpp, por qué una función correcta puede ser mala elección práctica:**
Fibonacci recursivo sin memoización es correcto pero tiene costo exponencial O(2^n), volviéndose impracticable para n grandes.

**5. En count_ones.cpp, por qué el tamaño de entrada no siempre coincide con el valor numérico:**
El tamaño de entrada es el número de bits (log₂(n)), no el valor numérico. Para n=1024, el valor es grande pero solo tiene 11 bits.

**6. En demo_adt_secuencia.cpp, por qué la misma interfaz convive con distintas representaciones:**
El ADT define las operaciones (add, get, size), pero la implementación puede ser con arreglo dinámico o lista enlazada.

---

#### Bloque 2 - Demos y trazado guiado

**Tabla de demos:**

| archivo | salida u observable importante | idea algorítmica | argumento de costo |
|---------|-------------------------------|------------------|-------------------|
| demo_bubblesort.cpp | número de intercambios | ordenamiento burbuja | O(n²) en peor caso |
| demo_power.cpp | comparación recursivo vs iterativo | exponenciación binaria | O(log n) |
| demo_fibonacci.cpp | tiempo de ejecución para n=40 | recursivo vs iterativo | O(2^n) vs O(n) |
| demo_countones.cpp | bits en 1 vs valor numérico | contar bits | O(log n) |

**Respuestas:**

1. **demo_bubblesort.cpp:** La salida que muestra el número de intercambios y comparaciones sirve para defender el costo O(n²).

2. **demo_power.cpp:** La comparación concreta del número de multiplicaciones muestra la mejora algorítmica.

3. **demo_fibonacci.cpp:** El crecimiento defendible es O(n) con iterativo vs O(2^n) con recursivo.

4. **demo_countones.cpp:** El ejemplo de n=1024 ayuda a distinguir valor numérico (1024) de tamaño en bits (11 bits).

---

#### Bloque 3 - Pruebas públicas

**1. ¿Qué funciones o ideas verifican las pruebas públicas?**
Verifican que las funciones producen la salida correcta para entradas específicas.

**2. ¿Qué sí demuestra una prueba pública?**
Que la función es correcta para los casos probados.

**3. ¿Qué no demuestra una prueba pública?**
No demuestra eficiencia, ni correctitud para todos los casos posibles, ni comportamiento en casos borde no incluidos.

**4. Pregunta seleccionada de preguntas_semana1.md:**
*¿Qué diferencia hay entre correctitud y eficiencia?*
La correctitud asegura que la función produce el resultado esperado. La eficiencia mide cuántos recursos (tiempo/espacio) consume. Una función puede ser correcta pero ineficiente.

**5. Autoevaluación con rúbrica:**
- Comprensión conceptual: 4/5
- Sustentación de correctitud: 4/5
- Análisis de eficiencia: 4/5

---

#### Bloque 4 - Puente con Proyecto0

**1. demo_const_refs.cpp:** Muestra que pasar por referencia evita copias, pasar por valor copia el objeto, y pasar por const referencia permite leer sin copiar ni modificar.

**2. bench_vector_growth.cpp:** `reserve()` evita redimensionamientos múltiples, reduciendo el costo amortizado.

**3. bench_vector_ops.cpp:** `push_back` es O(1) amortizado, `insert(begin())` es O(n) porque desplaza elementos, `insert(middle)` también es O(n).

**4. bench_cache_effects.cpp:** Muestra que acceder memoria contigua (recorrido secuencial) es más rápido que accesos aleatorios por la localidad espacial de la caché.

---

#### Bloque 5 - Extensión con Ejercicios0

**1. Orden correcto antes de optimizar:** Medir primero, identificar cuellos de botella, luego optimizar.

**2. stl_optimizacion_demostracion.cpp muestra:** `reserve` mejora rendimiento, `nth_element` es parcialmente ordenado, `partial_sort` ordena solo parte, `lower_bound` búsqueda binaria.

**3. resolver_ejercicios0_v4.2.sh produce:** Evidencia experimental de tiempos de ejecución.

**4. Limitaciones de entorno mencionadas:** Dependencia del hardware, compilador, flags de optimización.

**5. Por qué no reemplaza discusión de correctitud:** La optimización no garantiza correctitud; primero debe funcionar bien, luego rápido.

---

#### Bloque 6 - Cierre comparativo

**¿Qué cambia cuando pasamos de defender correctitud básica a comparar implementaciones con evidencia experimental?**

- **Afirmación de especificación:** La función debe cumplir la interfaz definida (entrada → salida esperada).

- **Afirmación de correctitud:** Para toda entrada válida, la función produce la salida correcta.

- **Afirmación de costo:** No basta con que funcione; debemos medir tiempo y espacio (complejidad temporal y espacial).

- **Afirmación de representación o memoria:** La elección de estructura (vector vs lista, contigua vs enlazada) afecta el rendimiento.

- **Advertencia metodológica:** Las pruebas de rendimiento dependen del entorno (hardware, compilador, optimizaciones); los resultados deben interpretarse con cuidado y preferiblemente promediarse.

