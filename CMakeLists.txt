# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name
project(option-pricer CXX)

# Specify the C++ standard to use (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF) # Prefer standard conformance

# Set the path to Boost's include directory
set(BOOST_INCLUDE_DIR /usr/include)

# Set the path to Boost's library directory
set(BOOST_LIBRARY_DIR /usr/lib/x86_64-linux-gnu)

# Define the specific Boost.Math libraries we need based on your 'ls' output.
# We'll prioritize the non-c99/tr1 versions if they exist, otherwise use c99/tr1.
# Usually, a project just needs 'boost_math'. However, Ubuntu's package names
# are often explicitly `_c99` or `_tr1`. We'll include both and let CMake decide.
# The list order implies preference (CMake tries them in order).
set(BOOST_MATH_LIBRARIES
    boost_math # Generic name (might not exist as a separate lib)
    boost_math_c99 # For C99 mathematical functions
    boost_math_tr1 # For TR1 mathematical functions
    boost_math_c99f # float version of c99
    boost_math_c99l # long double version of c99
    boost_math_tr1f # float version of tr1
    boost_math_tr1l # long double version of tr1
)

# Find the specific Boost.Math library file
# find_library will search for 'lib' + NAME + '.so' or '.a'
find_library(FOUND_BOOST_MATH_LIB
             NAMES ${BOOST_MATH_LIBRARIES}
             PATHS ${BOOST_LIBRARY_DIR}
             NO_DEFAULT_PATH)

# Check if we successfully found *any* of the Boost.Math libraries
if (FOUND_BOOST_MATH_LIB)
    message(STATUS "Successfully found Boost.Math library: ${FOUND_BOOST_MATH_LIB}")
    # Set the variable to be used in target_link_libraries
    set(PROJECT_LINK_LIBS ${FOUND_BOOST_MATH_LIB})
else()
    message(FATAL_ERROR "Could not find any of the specified Boost.Math libraries in ${BOOST_LIBRARY_DIR}. "
                       "Please ensure 'libboost-math-dev' is correctly installed via apt-get.")
endif()

message(STATUS "Boost found. Headers: ${Boost_INCLUDE_DIR}")

# Define all source files for the executable
set(PROJECT_SOURCES
    src/main.cpp
    src/helper-functions.cpp
    src/option-pricer.cpp
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
target_link_libraries(${PROJECT_NAME} PUBLIC ${PROJECT_LINK_LIBS})
message(STATUS "Boost libraries linked: ${Boost_LIBRARIES}")


# Enable all warnings on GCC/Clang and MSVC
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message("Setting compiler options for GCC/Clang...")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Setting compiler options for MSVC...")
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
endif()

# Define installation rules
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin) # Installs the executable to ${CMAKE_INSTALL_PREFIX}/bin