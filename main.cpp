#include "option-pricer.hpp"
#include "helper-functions.hpp"

int main(int argc, char** argv)
{
    std::cout << "-----Welcome to my first ever option pricer, as a CLI tool!-----" << std::endl;

    std::string model_choice = get_model_type("Choose a pricing model (black-scholes, binomial, garman-kohlhagen, monte-carlo): ");
    // Get common inputs
    double S = get_float_input("Current Stock Price (S): ");
    double K = get_float_input("Option Strike Price (K): ");
    double T = get_float_input("Time to Expiration in Years (T, e.g., 0.5 for 6 months): ");
    double r = get_float_input("Risk-Free Interest Rate (r, e.g., 0.05 for 5%): ");
    double sigma = get_float_input("Volatility (sigma, e.g., 0.20 for 20%): ");
    std::string option_type = get_option_type("Option Type ('call' or 'put'): ");

    double price = 0.0;

    try {
        if (model_choice == "black-scholes") {
            price = black_scholes_price(S, K, T, r, sigma, option_type);
            std::cout << "\n--- Black-Scholes Model Results ---" << std::endl;
        } else if (model_choice == "binomial") {
            int N_steps = get_int_input("Number of steps for Binomial Model (e.g., 100, 500): ");
            price = binomial_option_price(S, K, T, r, sigma, N_steps, option_type);
            std::cout << "\n--- Binomial Model Results ---" << std::endl;
        } else if (model_choice == "garman-kohlhagen") {
            double r_foreign = get_float_input("Foreign Risk-Free Interest Rate (r_foreign, e.g., 0.02 for 2%): ");
            price = garman_kohlhagen_price(S, K, T, r, r_foreign, sigma, option_type);
            std::cout << "\n--- Garman-Kohlhagen Model Results ---" << std::endl;
        } else if (model_choice == "monte-carlo") {
            int num_simulations = get_int_input("Number of Monte Carlo Simulations (e.g., 100000): ");
            // Note: For simplicity, this MC implementation is for European options and doesn't use multiple steps.
            // For American options or path-dependent options, a more advanced MC would be needed.
            price = monte_carlo_price(S, K, T, r, sigma, num_simulations, option_type);
            std::cout << "\n--- Monte Carlo Simulation Results ---" << std::endl;
        }

        // Format output to two decimal places
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "The theoretical " << option_type << " option price is: $" << price << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "\nError during calculation: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\nAn unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}