#pragma once
#include "option-pricer.hpp"

double black_scholes_price (double S, double K, double T, double r, double sigma, const std::string& option_type)
{
    assert(T > 0 && "Time to maturity of option cannot be negative.");
    assert(sigma > 0 && "Volatility of underlying cannot be negative.");
    
    boost::math::normal_distribution<> N;
    double d1 = (std::log(S / K) + ( r + 0.5 * sigma * sigma ) * T ) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    
    if (option_type == "call")
    {
        return S * boost::math::cdf(N, d1) - K * std::exp(-r * T) * boost::math::cdf(N, d2);
    }
    
    // If not, it's a put
    return K * std::exp(-r * T) * boost::math::cdf(N, -d2) - S * boost::math::cdf(N, -d1);
}

double binomial_option_price (double S, double K, double T, double r, double sigma, size_t N_steps, const std::string& option_type)
{
    assert(T > 0 && "Time to maturity of option cannot be negative.");
    assert(sigma > 0 && "Volatility of underlying cannot be negative.");
    assert(N_steps > 0 && "Number of steps for binomial pricing cannot be negative.");
    
    double dt = T / static_cast<double>(N_steps);
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1.0 / u;
    double p = (std::exp(r * dt) - d) / (u - d);
    double discount_factor = std::exp(-r * dt);
    
    std::vector<double> option_values(N_steps + 1);
    
    for(size_t ii = 0; ii <= static_cast<size_t>(N_steps); ++ii)
    {
        double curr_stock_price = S * std::pow(u, ii) * std::pow(d, N_steps - ii);
        
        if (option_type == "call")
        {
            option_values[ii] = std::max(0.0, curr_stock_price - K);
            continue;
        }
        
        // Else it's a put
        option_values[ii] = std::max(0.0, K - curr_stock_price);
    }
    
    for (int jj = N_steps - 1; jj >= 0; --jj)
    {
        for (size_t ii = 0; ii <= static_cast<size_t>(jj); ++ii)
        {
            option_values[ii] = (p * option_values[ii + 1] + (1 - p) * option_values[ii]) * discount_factor;
        }
    }
    
    return option_values[0];
}

double garman_kohlhagen_price (double S, double K, double T, double r_domestic, double r_foreign, double sigma, const std::string& option_type)
{
    assert(T > 0 && "Time to maturity of option cannot be negative.");
    assert(sigma > 0 && "Volatility of underlying cannot be negative.");
    
    boost::math::normal_distribution<> N;
    double d1 = (std::log(S/K) + (r_domestic - r_foreign + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    
    if (option_type == "call")
    {
        return S * std::exp(-r_foreign * T) * boost::math::cdf(N, d1) - K * std::exp(-r_domestic * T) * boost::math::cdf(N, d2);
    }
    
    // If not, it's a put
    return K * std::exp(-r_domestic * T) * boost::math::cdf(N, -d2) - S * std::exp(-r_foreign * T) * boost::math::cdf(N, -d1);
}

double monte_carlo_price (double S, double K, double T, double r, double sigma, size_t N_simulations, const std::string& option_type)
{
    assert(T > 0 && "Time to maturity of option cannot be negative.");
    assert(sigma > 0 && "Volatility of underlying cannot be negative.");
    assert(N_simulations > 0 && "Number of simulations for Monte-Carlo pricing cannot be negative.");

    // Random number generation
    std::random_device rd;
    std::mt19937 generator(rd()); // Mersenne Twister!
    std::normal_distribution<> distribution(0.0, 1.0);

    double sum_payoffs = 0.0;
    double dt = T;

    for (int ii = 0; ii < N_simulations; ++ii)
    {
        // Simulate a random stock price at expiration using Geometric Brownian Motion
        // Random draw from distribution
        double z = distribution(generator);
        double St = S * std::exp((r - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * z);

        double payoff = 0.0;
        if (option_type == "call")  payoff = std::max(0.0, St - K);
        else                        payoff = std::max(0.0, K - St);

        sum_payoffs += payoff;
    }

    double average_payoff = sum_payoffs / (double) N_simulations;
    double discounted_price = average_payoff * std::exp(-r * T);

    return discounted_price;
}