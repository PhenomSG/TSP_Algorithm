#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <sys/resource.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>

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
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}

// Function to benchmark a TSP algorithm
void benchmark(const std::string& file, const std::string& inputFile, const std::string& outputFile, const std::string& qualityFile) {
    auto start = std::chrono::high_resolution_clock::now();

    // Run the algorithm
    std::string command = "g++ -o algorithm " + file + " && ./algorithm < " + inputFile + " > " + outputFile;
    std::system(command.c_str());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    size_t memoryUsage = getCurrentMemoryUsage();

    // Assuming the output file contains the solution quality as the last line
    std::ifstream qualityStream(outputFile);
    std::string line;
    std::string solutionQuality;
    while (std::getline(qualityStream, line)) {
        solutionQuality = line;
    }

    // Log results
    std::ofstream logFile("benchmark_results.txt", std::ios_base::app);
    logFile << "Algorithm: " << file << "\n";
    logFile << "Execution Time: " << duration.count() << " seconds\n";
    logFile << "Memory Usage: " << memoryUsage << " KB\n";
    logFile << "Solution Quality: " << solutionQuality << "\n";
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

    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";
    std::string qualityFile = "quality.txt";

    // Clear previous results
    std::ofstream logFile("benchmark_results.txt");
    logFile << "Benchmark Results\n";
    logFile << "=================\n";
    logFile.close();

    for (const auto& file : files) {
        benchmark(file, inputFile, outputFile, qualityFile);
    }

    std::cout << "Benchmarking completed. Results are in benchmark_results.txt" << std::endl;
    return 0;
}
