#include <algorithm>
#include <random>
#include <vector>
#include <iostream>

#include <algorithm>
#include <random>
#include <vector>
#include <iostream>
#include <memory>   // for smart pointers

void printVector(const std::vector<std::shared_ptr<int>>& vec) {
    for (const auto& elem : vec) {
        std::cout << *elem << " ";  // dereference smart pointer
    }
    std::cout << std::endl;
}

struct CompareByValueAsc {
    template <typename Ptr>
    bool operator()(const Ptr& a, const Ptr& b) const {
        return *a < *b;
    }
};

struct CompareByValueDesc {
    template <typename Ptr>
    bool operator()(const Ptr& a, const Ptr& b) const {
        return *a > *b;
    }
};


int main() {
    // Create vector of shared_ptr<int>
    std::vector<std::shared_ptr<int>> numbers;
    for (int i = 1; i <= 10; ++i) {
        numbers.push_back(std::make_shared<int>(i));
    }

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the vector
    std::shuffle(numbers.begin(), numbers.end(), g);

    // Print the shuffled vector
    std::cout << "Shuffled numbers: " << std::endl;
    printVector(numbers);
    std::cout << std::endl;

    // Sort & Print the vector in ascending order
	std::sort(numbers.begin(), numbers.end(), CompareByValueAsc()); 
    std::cout << "Sorted numbers in ascending order:" << std::endl;
    printVector(numbers);

    // Sort the vector in descending order and print it
	std::sort(numbers.begin(), numbers.end(), CompareByValueDesc());    
    std::cout << "\nSorted numbers in descending order:" << std::endl;
    printVector(numbers);

    return 0;
}

