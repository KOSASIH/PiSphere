#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

#include <string>
#include <chrono>

std::string generateRandomData(size_t size) {
    std::string data;
    for (size_t i = 0; i < size; i++) {
        data += static_cast<char>(rand() % 256);
    }
    return data;
}

template <typename F>
double measureExecutionTime(F func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

#endif // BENCHMARK_UTILS_H
