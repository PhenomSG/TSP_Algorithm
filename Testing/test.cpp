#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <array>
#include <cstdlib>
#include <cstring>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <psapi.h>
#else
#include <sys/resource.h>
#include <unistd.h>
#endif

// Function to execute a command and capture its output
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

// Function to get the current memory usage of the process
size_t getCurrentMemoryUsage() {
#if defined(_WIN32) || defined(_WIN64)
    PROCESS_MEMORY_COUNTERS memCounter;
    GetProcessMemoryInfo(GetCurrentProcess(), &memCounter, sizeof(memCounter));
    return memCounter.PeakWorkingSetSize / 1024; // Convert to KB
#else
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // Memory usage in KB
#endif
}

// Function to benchmark a TSP algorithm
void benchmark(const std::string& file) {
    auto start = std::chrono::high_resolution_clock::now();

    // Determine the correct command to compile and run the algorithm based on the OS
    std::string command;
#if defined(_WIN32) || defined(_WIN64)
    command = "g++ -o algorithm " + file + " && algorithm";
#else
    command = "g++ -o algorithm " + file + " && ./algorithm";
#endif

    std::string output = exec(command.c_str());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    size_t memoryUsage = getCurrentMemoryUsage();

    // Extract solution quality from output
    std::string solutionQuality;
    std::istringstream outputStream(output);
    std::string line;
    while (std::getline(outputStream, line)) {
        if (line.find("Minimum cost:") != std::string::npos) {
            solutionQuality = line;
        }
    }

    // Log results
    std::ofstream logFile("benchmark_results.txt", std::ios_base::app);
    logFile << "Algorithm: " << file << "\n";
    logFile << "Execution Time: " << duration.count() << " seconds\n";
    logFile << "Memory Usage: " << memoryUsage << " KB\n";
    logFile << solutionQuality << "\n";
    logFile << "-------------------------------------\n";
    logFile.close();
}

int main() {
    std::vector<std::string> files = {
        "backtracking.cpp",
        "bitmask_dp.cpp",
        "branch_n_bound.cpp",
        "dp.cpp",
        "hungarian.cpp",
        "mst.cpp",
        "reduced_matrix.cpp"
    };

    // Clear previous results
    std::ofstream logFile("benchmark_results.txt");
    logFile << "Benchmark Results\n";
    logFile << "=================\n";
    logFile.close();

    for (const auto& file : files) {
        benchmark(file);
    }

    std::cout << "Benchmarking completed. Results are in benchmark_results.txt" << std::endl;
    return 0;
}
