## PC2 - CC232 - Seas Solis Kevin

### Estudiante
- Nombre: Kevin Seas Solis
- Código: 20202164I
- Problema asignado: LeetCode 907 - Sum of Subarray Minimums
- Enlace: https://leetcode.com/problems/sum-of-subarray-minimums/

### Referencia oficial
- Archivo de asignación:
  https://github.com/kapumota/CC-232/blob/main/Practicas/Practica2_CC232/Problemas-Evaluacion2.csv

### Tema principal
- Semana: 3 y 4
- Estructura o técnica principal: Monotonic Stack

### Resumen de la solución
Para cada elemento arr[i], encontramos:
- left[i] = índice del anterior menor (estricto)
- right[i] = índice del siguiente menor o igual
- Contribución = (i - left[i]) * (right[i] - i) * arr[i]
- Sumamos todo mód 1e9+7

### Complejidad
- Tiempo: O(n)
- Espacio: O(n)

### Invariante o idea clave
El stack mantiene índices con valores crecientes (monótono creciente).

### Archivos relevantes
- include/SubarrayMinimums.h
- src/SubarrayMinimums.cpp
- src/main.cpp
- tests/test_subarray_minimums.cpp

### Compilación con CMake
```bash
cmake -S . -B build
cmake --build build
### Compilación directa con g++
bash
g++ -std=c++17 -Iinclude -o main.exe src/main.cpp src/SubarrayMinimums.cpp
g++ -std=c++17 -Iinclude -o tests.exe tests/test_subarray_minimums.cpp src/SubarrayMinimums.cpp
### Ejecución
bash
./build/main.exe
# o
./main.exe
### Tests
bash
./build/tests.exe
# o
./tests.exe
### Casos de prueba
1.	[3,1,2,4] → 17
2.	[11,81,94,43,3] → 444
3.	[1] → 1
4.	[2,1] → 4
5.	[5,5,5] → 30
### Actividades completadas
•	Actividad 1: Semana1/actividad1-CC232/actividad1_semana1.md
•	Actividad 2: Semana2/actividad2-CC232/actividad2_semana2.md
•	Actividad 3: Semana3/Actividad3-CC232/actividad3_cc232.md
### Historial de commits
Ver en GitHub: https://github.com/kevinseass-commits/SeasSolis_Kevin_PC2/commits/main
### Declaración de autoría
Declaro que entiendo el código entregado, que puedo explicarlo, compilarlo, ejecutarlo y modificarlo sin ayuda externa durante la grabación.
