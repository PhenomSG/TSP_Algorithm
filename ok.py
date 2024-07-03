import matplotlib.pyplot as plt
import numpy as np

# Example data (execution times for each algorithm for 4 different inputs)
algorithms = [
    "backtracking.cpp",
    "bitmask_dp.cpp",
    "branch_n_bound.cpp",
    "dp.cpp",
    "hungarian.cpp",
    "mst.cpp",
    "reduced_matrix.cpp"
]

# Execution times for each algorithm for 4 inputs (just illustrative)
execution_times = [
    [0.714656, 0.737326, 1.08067, 0.714453, 0.826416, 1.02653, 0.907802],
    [0.742735, 1.1, 1.3, 1.2, 1.4, 1.5, 1.6],
    [0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4],
    [0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2]
]

# Number of inputs (categories or groups)
inputs = ['Input 1', 'Input 2', 'Input 3', 'Input 4']

# Setting up positions for bars
bar_width = 0.15
index = np.arange(len(algorithms))

# Plotting
plt.figure(figsize=(12, 8))

for i in range(len(inputs)):
    plt.bar(index + i * bar_width, execution_times[i], bar_width, label=inputs[i])

plt.xlabel('Algorithms')
plt.ylabel('Execution Time (seconds)')
plt.title('Execution Time vs Algorithms vs Number of Inputs')
plt.xticks(index + bar_width * (len(inputs) - 1) / 2, algorithms)
plt.legend()
plt.grid(axis='y', linestyle='--', alpha=0.7)
plt.tight_layout()

# Save the plot
plt.savefig('execution_time_vs_algorithm_vs_inputs.png')

# Display the plot
plt.show()
