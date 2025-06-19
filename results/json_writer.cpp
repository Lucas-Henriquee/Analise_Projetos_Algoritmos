#include "../include/defines.hpp"

void save_results_to_json(const vector<json> &fibonacci_results, const vector<json> &polynomial_results)
{
    string filename = "results/output.json";

    json output;
    output["fibonacci"] = fibonacci_results;
    output["polynomial"] = polynomial_results;

    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error creating results file: " << filename << endl;
        return;
    }

    file << setw(4) << output << endl;
    file.close();
    cout << "Results saved in: " << filename << endl;
}