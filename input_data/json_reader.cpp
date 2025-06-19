#include "include/defines.hpp"

void read_json_file(const string &filename, deque<size_t> &fibonacci_values, map<double, deque<double>> &polynomial_values)
{
    // Open the JSON file
    ifstream file(filename);
    // Check if the file is open
    if (!file.is_open())
    {
        cerr << "Error opening file: " << endl;
        return;
    }
    // Parse the JSON file
    json data = json::parse(file);

    // Close the fileq
    file.close();

    // Extract the Fibonacci and polynomial data
    if (data["fibonacci"].empty())
        cerr << "No Fibonacci data found in the JSON file." << endl;

    else
    {
        for (const auto &item : data["fibonacci"])
            fibonacci_values.push_back(item.get<size_t>());
    }

    if (data["polynomial"].empty())
        cerr << "No Polynomial data found in the JSON file." << endl;

    else
    {
        for (const auto &item : data["polynomial"])
        {
            double x = item["x"].get<double>();
            deque<double> values;

            for (const auto &term : item["terms"])
                values.push_back(term.get<double>());

            polynomial_values[x] = values;
        }
    }
}