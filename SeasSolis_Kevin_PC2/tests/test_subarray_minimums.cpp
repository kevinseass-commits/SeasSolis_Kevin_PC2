#include <iostream>
#include <cassert>
#include "SubarrayMinimums.h"

int main() {
    SubarrayMinimums sol;
    
    // Caso 1: Ejemplo del problema
    assert(sol.sumSubarrayMins({3,1,2,4}) == 17);
    
    // Caso 2: Segundo ejemplo
    assert(sol.sumSubarrayMins({11,81,94,43,3}) == 444);
    
    // Caso 3: Un solo elemento
    assert(sol.sumSubarrayMins({1}) == 1);
    
    // Caso 4: Dos elementos crecientes [1,2]
    assert(sol.sumSubarrayMins({1,2}) == 4);  // [1]=1, [2]=2, [1,2]=1 → 4
    
    // Caso 5: Dos elementos decrecientes [2,1]
    assert(sol.sumSubarrayMins({2,1}) == 4);  // [2]=2, [1]=1, [2,1]=1 → 4
    
    std::cout << "✅ Todos los tests pasaron correctamente." << std::endl;
    return 0;
}
