#include <iostream>
#include <vector>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Generate a random polynomial of a given degree
std::vector<int> generate_polynomial(int degree)
{
    std::vector<int> poly(degree + 1);

    for(int i = 0; i < degree; ++i)
    {
        poly[i] = rand() % 2; // Randomly 0 or 1
    }

    poly[degree] = 1; // Ensure the highest degree coefficient is 1
    return poly;
}

// Calculate Hamming weight of a polynomial
int hamming_weight(const std::vector<int> &poly)
{
    int weight = 0;

    for(int coef : poly)
    {
        weight += coef;
    }

    return weight;
}

// Generate a list of random polynomials of a given degree
std::vector<std::vector<int>> generate_polynomials(int degree, int count)
{
    std::vector<std::vector<int>> polynomials;

    for(int i = 0; i < count; ++i)
    {
        polynomials.push_back(generate_polynomial(degree));
    }

    return polynomials;
}

// Calculate code rate and other parameters
double calculate_parameters(int data_length, int error_bits, int constraint_length, const std::vector<std::vector<int>> &polynomials)
{
    int num_polynomials = polynomials.size();

    if(num_polynomials == 0)
    {
        return 0.0;
    }

    double code_rate = 1.0 / num_polynomials;
    return code_rate;
}

int main()
{
    // Seed random number generator
    std::srand(std::time(nullptr));
    int data_length = 1024;
    int error_bits = 100;
    int constraint_length = 15;
    int num_polynomials = 4;
    // Generate polynomials
    std::vector<std::vector<int>> polynomials = generate_polynomials(constraint_length, num_polynomials);
    double code_rate = calculate_parameters(data_length, error_bits, constraint_length, polynomials);
    // Print generated polynomials
    std::cout << "Generated Polynomials:\n";

    for(const auto &poly : polynomials)
    {
        for(int coef : poly)
        {
            std::cout << coef;
        }

        std::cout << "\n";
    }

    // Print code rate
    std::cout << "Code Rate: " << code_rate << "\n";
    return 0;
}
