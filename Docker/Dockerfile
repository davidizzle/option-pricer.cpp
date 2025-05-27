FROM ubuntu:latest

# Install essential build tools: g++, make, libc++ etc.
RUN apt-get update && apt-get install -y build-essential

# Install CMake, git, and Boost Math
RUN apt-get install -y cmake git libboost-math-dev

# Clean up apt cache to keep image size down
# RUN apt-get autoremove -y \
#     && apt-get clean -y \
#     && rm -rf /var/lib/apt/lists/*

WORKDIR /workspaces/option-pricer.cpp
# COPY ./src/ ./src/
# COPY ./CMakeLists.txt ./CMakeLists.txt

# Compile executable
# RUN cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug
# RUN cmake --build ./build --target option-pricer.cpp

# Clean up
# RUN rm -rf ./option-pricer.cpp CMakeLists.txt ./build