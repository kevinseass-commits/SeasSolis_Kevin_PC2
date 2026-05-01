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
    
    // Caso 4: Dos elementos [1,2]
    assert(sol.sumSubarrayMins({1,2}) == 4);
    
    // Caso 5: Dos elementos [2,1]
    assert(sol.sumSubarrayMins({2,1}) == 4);
    
    // Caso 6: Tres elementos iguales [5,5,5] -> 6 subarreglos * 5 = 30
    assert(sol.sumSubarrayMins({5,5,5}) == 30);
    
    std::cout << "Todos los tests pasaron correctamente" << std::endl;
    return 0;
}
