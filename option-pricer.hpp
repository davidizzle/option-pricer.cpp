#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

// Include boost
#include <boost/math/distributions/normal.hpp>

double black_scholes_price      (double S, double K, double T, double r, double sigma, const std::string& option_type);
double binomial_option_price    (double S, double K, double T, double r, double sigma, int N_steps, const std::string& option_type);
double garman_kohlhagen_price   (double S, double K, double T, double r_domestic, double r_foreign, double sigma, const std::string& option_type);
double monte_carlo_price        (double S, double K, double T, double r, double sigma, int N_simulations, const std::string& option_type);