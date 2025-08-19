#include <iostream>
#include <vector>
#include <string>


// Prints the elements in the half-open range [b, e) to std::cout,
  // separated by spaces, followed by a trailing newline.
  //
  // Requirements:
  //   - It meets InputIterator requirements (copyable, !=, *, ++).
  //   - *b is stream-insertable into std::ostream (operator<< defined).
  //   - [b, e) is a valid range.
  //
  // Notes:
  //   - Elements are copied into currValue; for heavy types consider:
  //       const auto& currValue = *b;
  //     to avoid copying.
  //   - Complexity: O(n) insertions where n == distance(b, e).
  //   - Side effects: writes to std::cout; output may interleave across threads.

template<typename It>
void dwim(It b, It e) {
    while (b != e) {
        auto currValue = *b; // copy the current element
        std::cout << currValue << " ";
        ++b; // move to the next element
    }
    std::cout << "\n";
}

int main() {
    std::vector<int> numbers = {1, 2, 3, 4};
    dwim(numbers.begin(), numbers.end()); // works with vector

    std::string s = "Hello";
    dwim(s.begin(), s.end());             // works with string

    int arr[] = {10, 20, 30};
    dwim(arr, arr + 3);                   // works with raw array
}
