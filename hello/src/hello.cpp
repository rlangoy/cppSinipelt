#include <iostream>
#include <vector>
#include <string>




//make a class that prints the numbers 1, 2, 3, 4   




int main() {
    

    std::cout << "\n--- Numbers  ---\n";
    
    std::vector<int> numbers = {1, 2, 3, 4};
    
    for (auto& i : numbers) {
        std::cout << i << " ";
    }
}
