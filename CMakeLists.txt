# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(OptionPricer CXX)

# Specify the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Prefer standard conformance

set(BOOST_ROOT "C:/Users/david/development/vcpkg/installed/x64-windows")
set(Boost_NO_SYSTEM_PATHS ON)
set(Boost_INCLUDE_DIR "${BOOST_ROOT}/include")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/lib")

# Find the Boost libraries
# REQUIRED means CMake will error if Boost is not found.
# COMPONENTS math specifies that we need the Boost.Math library.
find_package(Boost 1.70 COMPONENTS math REQUIRED)

# If Boost is found, add its include directories and link its libraries
if (Boost_FOUND)
    message(STATUS "Boost found. Headers: ${Boost_INCLUDE_DIRS}")

    # Define all source files for the executable
    set(PROJECT_SOURCES
        main.cpp
        helper-functions.cpp
        option-pricer.cpp
    )

    # Add the executable target
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
    # Add Boost include directories so your compiler can find Boost headers
    target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})


    # Ensure the compiler can find your own project headers (.hpp files)
    # This assumes your .hpp files are in the same directory as your .cpp files.
    # If they were in a separate 'include' folder, you'd add that path here.
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

    # Link the Boost libraries
    target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})
    message(STATUS "Boost libraries linked: ${Boost_LIBRARIES}")
else()
    message(FATAL_ERROR "Boost not found. Please set BOOST_ROOT or BOOST_LIBRARYDIR.")
endif()