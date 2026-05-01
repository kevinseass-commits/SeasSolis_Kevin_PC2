#include <iostream>
#include <vector>
#include "SubarrayMinimums.h"

int main() {
    SubarrayMinimums sol;
    std::vector<int> arr = {2,1};
    std::cout << "Resultado para [2,1]: " << sol.sumSubarrayMins(arr) << std::endl;
    return 0;
}
