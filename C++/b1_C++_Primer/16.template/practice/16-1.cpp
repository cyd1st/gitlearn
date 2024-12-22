#include <iostream>
#include <vector>
#include <list>

using namespace std;

template<typename Iterator, typename T>
Iterator MyFind(Iterator begin, Iterator end, T value)
{
    for (auto it = begin; it != end; ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end;
}

int main()
{
    // Example with vector<int>
    std::vector<int> vec = {1, 2, 3, 4, 5};
    int target_value = 3;
    auto found_it = MyFind(vec.begin(), vec.end(), target_value);
    
    if (found_it != vec.end()) {
        std::cout << "Found value " << *found_it << " at position " << std::distance(vec.begin(), found_it) << std::endl;
    } else {
        std::cout << "Value not found." << std::endl;
    }

    // Example with list<string>
    std::list<std::string> lst = {"apple", "banana", "cherry"};
    std::string target_string = "banana";
    auto found_it_str = MyFind(lst.begin(), lst.end(), target_string);

    if (found_it_str != lst.end()) {
        std::cout << "Found string " << *found_it_str << std::endl;
    } else {
        std::cout << "String not found." << std::endl;
    }

    return 0;
}