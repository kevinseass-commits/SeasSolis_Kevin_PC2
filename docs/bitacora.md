# Bitácora de desarrollo - PC3

## 8 de junio de 2026
- Creé la estructura base del repositorio `PC3_SeasSolis`.
- Configuré las carpetas obligatorias: `include/`, `src/`, `tests/`, `demos/`, `docs/`, `resultados/`, `benchmark/`, `video/`.
- Configuré las carpetas de actividades previas: `Semana4/Actividad4-CC232/`, `Semana5/Actividad5-CC232/`, `Semana6/Actividad6-CC232/`.
- Configuré la carpeta `Practicas/practica-calificada3/`.
- Creé el archivo `.gitignore` para excluir builds, ejecutables y archivos temporales.
- Creé el `CMakeLists.txt` funcional.
- Completé la **Actividad 4** (Semana 4) con todos sus bloques.
- Completé la **Actividad 5** (Semana 5) con todos sus bloques.

## 9 de junio de 2026
- Creé y corregí el `README.md` según las observaciones de la PC2 - Creé `docs/bitacora.md` (este archivo).
- Subí los cambios a GitHub.


## 10 de junio de 2026
- Creé la estructura base de la **Actividad 6** (Semana 6).
- Completé el **Bloque 1** (Diagnóstico inicial):
  - Identifiqué los targets de demostraciones y pruebas.
  - Revisé los archivos incluidos en `Capitulo6.h`.
  - Comparé `Capitulo6.h` con `Capitulo10.h`.
  - Determiné las dependencias con Semana 5.
  - Identifiqué las estructuras: `PQ_ComplHeap` (prioridad pura), `BinarySearchTree` (búsqueda ordenada), `Treap` (búsqueda + prioridad).
- Completé el **Bloque 2** (Modificación de utilidades de heap completo):
  - Agregué funciones auxiliares `constexpr` en `PQ_ComplHeap_macro.h`:
    - `pqHasLeftChild`, `pqHasRightChild`, `pqIsLeaf`, `pqIsInternal`
  - Modifiqué `PQ_ComplHeap_percolateDown.h` para usar las nuevas funciones.
  - Respondí las preguntas teóricas sobre ventajas de `constexpr`, casos borde y condiciones de hoja.
  - Verifiqué que la complejidad se mantiene en O(log n).
- Subí los cambios a GitHub.

