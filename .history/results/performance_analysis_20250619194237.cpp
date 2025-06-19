#include "../include/defines.hpp"

#include "../src/fibonacci_recursive.cpp"
#include "../src/fibonacci_iterative.cpp"
#include "../src/polynomial_recursive.cpp"
#include "../src/polynomial_iterative.cpp"

#include "../llm_generated/fibonacci_llm_generated.cpp"
#include "llm_generated/polynomial_llm_generated.cpp"

#include "input_data/json_reader.cpp"
#include "results/json_writer.cpp"

void performance_analysis()
{
    deque<size_t> fibonacci_values;
    map<double, deque<double>> polynomial_values;

    vector<json> fibonacci_results;
    vector<json> polynomial_results;

    read_json_file("input_data/input.json", fibonacci_values, polynomial_values);

    // Fibonacci performance analysis
    for (size_t fibonacci_value : fibonacci_values)
    {
        json fibo_entry;
        fibo_entry["n"] = fibonacci_value;

        // Call the iterative Fibonacci function
        auto start = chrono::high_resolution_clock::now();
        size_t result = fibonacci_iterative(fibonacci_value);
        auto end = chrono::high_resolution_clock::now();
        double time = chrono::duration<double>(end - start).count();
        cout << "[Iterative] Fibonacci(" << fibonacci_value << ") = " << result << " in " << time << "s" << endl;
        fibo_entry["iterative"] = { {"result", result}, {"time", time} };

        // Call the recursive Fibonacci function
        start = chrono::high_resolution_clock::now();
        result = fibonacci_recursive(fibonacci_value);
        end = chrono::high_resolution_clock::now();
        time = chrono::duration<double>(end - start).count();
        cout << "[Recursive] Fibonacci(" << fibonacci_value << ") = " << result << " in " << time << "s" << endl;
        fibo_entry["recursive"] = { {"result", result}, {"time", time} };

        start = chrono::high_resolution_clock::now();
        // result = fibonacci_llm_generated(fibonacci_value);
        cout << "Fibonacci LLM generated result for " << fibonacci_value << ": " << result << endl;
        end = chrono::high_resolution_clock::now();
        time = chrono::duration<double>(end - start).count();
        cout << "[LLM] Fibonacci(" << fibonacci_value << ") = " << result << " in " << time << "s" << endl;
        fibo_entry["llm"] = { {"result", result}, {"time", time} };

        // Save the results for Fibonacci
        fibonacci_results.push_back(fibo_entry);
    }

    // Polynomial performance analysis
    for (const auto &polynomial_entry : polynomial_values)
    {
        double x = polynomial_entry.first;
        deque<double> coefficients = polynomial_entry.second;
        size_t max_degree = coefficients.size() - 1;

        json poly_entry;
        poly_entry["x"] = x;
        poly_entry["coefficients"] = coefficients;

        // Call the iterative Polynomial function
        auto start = chrono::high_resolution_clock::now();
        double result = polynomial_iterative(x, coefficients, max_degree);
        auto end = chrono::high_resolution_clock::now();
        double time = chrono::duration<double>(end - start).count();
        cout << "[Iterative] Polynomial(x = " << x << ") = " << result << " in " << time << "s" << endl;
        poly_entry["iterative"] = { {"result", result}, {"time", time} };

        // Call the recursive Polynomial function
        start = chrono::high_resolution_clock::now();
        result = polynomial_recursive(coefficients, x);
        end = chrono::high_resolution_clock::now();
        time = chrono::duration<double>(end - start).count();
        cout << "[Recursive] Polynomial(x = " << x << ") = " << result << " in " << time << "s" << endl;
        poly_entry["recursive"] = { {"result", result}, {"time", time} };

        // Call the LLM generated Polynomial function
        start = chrono::high_resolution_clock::now();
        // result = polynomial_llm_generated(coefficients, x);
        end = chrono::high_resolution_clock::now();
        time = chrono::duration<double>(end - start).count();
        cout << "[LLM] Polynomial(x = " << x << ") = " << result << " in " << time << "s" << endl;
        poly_entry["llm"] = { {"result", result}, {"time", time} };

        // Save the results for Polynomial
        polynomial_results.push_back(poly_entry);
    }

    save_results_to_json(fibonacci_results, polynomial_results);
}