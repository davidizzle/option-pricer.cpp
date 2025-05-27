#include "helper-functions.hpp"

double get_float_input(const std::string& prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) 
        {
            std::cout << "Invalid input — please, enter a number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Make an exception only for Rf to allow it to be negative
        if(prompt.find("Risk-Free Interest Rate") == std::string::npos && value < 0)
        {
            std::cout << "Input cannot be negative — please enter a positive number." << std::endl;
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

int get_int_input(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail())
        {
            std::cout << "Invalid input — please, enter an integer." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        else if (value <= 0)
        {
            std::cout << "Invalid input — please, enter a positive integer.";
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }
}

std::string get_option_type(const std::string& prompt)
{
    std::string option_type;

    while (true)
    {
        std::cout << prompt;
        std::cin >> option_type;

        for (char &c : option_type)
        {
            c = static_cast<char>(std::tolower(c));
        }

        if (option_type != "call" && option_type != "put")
        {
            std::cout << "Invalid option type — has to be 'call' or 'put'." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return option_type;
    }
}

std::string get_model_type(const std::string& prompt)
{
    std::string model_type;

    while (true)
    {
        std::cout << prompt;
        std::cin >> model_type;

        for (char &c : model_type)
        {
            c = static_cast<char>(std::tolower(c));
        }

        if (model_type != "black-scholes"      && 
            model_type != "binomial"           &&
            model_type != "garman-kohlhagen"   &&
            model_type != "monte-carlo"        )
        {
            std::cout << "Invalid model type — choose from:  black-scholes, binomial, garman-kohlhagen, monte-carlo." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return model_type;
    }
}

