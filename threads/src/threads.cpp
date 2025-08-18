#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

std::mutex m;                  // shared mutex
std::vector<int> sharedData;   // shared resource

// Function run by multiple threads
void AddToSharedData(int value) {
    // Lock the mutex for the duration of this scope
    std::lock_guard<std::mutex> g(m);  

    // Critical section: safe access to sharedData
    sharedData.push_back(value);
    std::cout << "Thread " << std::this_thread::get_id()
              << " added " << value << "\n";

    // g goes out of scope -> mutex is automatically unlocked
}

int main() {

    const int theAnswer = 42;
    auto x = theAnswer;
    auto y = &theAnswer;


    std::thread t1(AddToSharedData, 10);
    std::thread t2(AddToSharedData, 20);
    std::thread t3(AddToSharedData, 30);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Final sharedData: ";
    for (int v : sharedData) {
        std::cout << v << " ";
    }
    std::cout << "\n";
}
