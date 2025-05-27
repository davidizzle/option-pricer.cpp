#pragma once
#include <iostream>
#include <string>
#include <algorithm>

// Helper function to parse float input
double get_float_input(const std::string& prompt);

int get_int_input(const std::string& prompt);

std::string get_option_type(const std::string& prompt);

std::string get_model_type(const std::string& prompt);
