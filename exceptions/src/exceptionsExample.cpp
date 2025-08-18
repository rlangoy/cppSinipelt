#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

class Widget {
    int value;
public:
    Widget(int v) : value(v) {}
    int GetValue() const { return value; }
};

std::unique_ptr<Widget> CreateWidget(int v) {
    if (v < 0) {
        throw std::invalid_argument("Value must be non-negative");
    }
    return std::make_unique<Widget>(v); // RAII-safe
}

int main() {
    std::vector<std::unique_ptr<Widget>> widgets;

    try {
        widgets.push_back(CreateWidget(10));
        widgets.push_back(CreateWidget(-5));  // will throw
        widgets.push_back(CreateWidget(20));
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Unknown exception occurred\n";
    }

    std::cout << "Widgets created: " << widgets.size() << "\n";
    for (const auto& w : widgets) {
        std::cout << w->GetValue() << " ";
    }
    std::cout << "\n";
}
