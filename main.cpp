#include "include/defines.hpp"
#include "results/performance_analysis.cpp"

int main()
{
    performance_analysis();
    return 0;
}

// int main(){
//     deque<size_t> fibonacci_values;
//     map<double, deque<double>> polynomial_values;
//     read_json_file("input_data/input.json", fibonacci_values, polynomial_values);

//     cout << "Fibonacci Values: ";
//     for (const auto& value : fibonacci_values) {
//         cout << value << " ";
//     }
//     cout << endl;
//     cout << "Polynomial Values: " << endl;
//     for (const auto& pair : polynomial_values) {
//         cout << "Key: " << pair.first << " Values: ";
//         for (const auto& value : pair.second) {
//             cout << value << " ";
//         }
//         cout << endl;
//     }
// }