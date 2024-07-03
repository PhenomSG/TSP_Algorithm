import matplotlib.pyplot as plt

# Data for execution times (seconds) for each algorithm and each input
algorithms = [
    "backtracking.cpp",
    "bitmask_dp.cpp",
    "branch_n_bound.cpp",
    "dp.cpp",
    "hungarian.cpp",
    "mst.cpp",
    "reduced_matrix.cpp"
]

execution_times = {
    "backtracking.cpp": [0.742735, 0.644649, 0.624782, 0.966647],
    "bitmask_dp.cpp": [0.89569, 1.4215, 0.817725, 0.779244],
    "branch_n_bound.cpp": [1.04291, 1.89139, 1.0128, 1.29519],
    "dp.cpp": [0.7228, 1.45728, 0.661948, 0.948979],
    "hungarian.cpp": [0.833986, 1.28733, 0.782738, 1.2187],
    "mst.cpp": [0.706372, 1.62029, 0.889292, 0.857328],
    "reduced_matrix.cpp": [0.801222, 1.53412, 0.827809, 1.08901]
}

# Inputs
inputs = ['Input 2', 'Input 3', 'Input 4', 'Input 5']

# Create figure and axes
fig, ax = plt.subplots(figsize=(12, 8))

# Plot each algorithm's execution times
for alg in algorithms:
    ax.plot(inputs, execution_times[alg], marker='o', label=alg)

# Set labels and title
ax.set_xlabel('Inputs')
ax.set_ylabel('Execution Time (seconds)')
ax.set_title('Execution Time vs Inputs for Different Algorithms')
ax.grid(True)
ax.legend()

# Save the plot
plt.savefig('execution_time_vs_inputs.png')

# Display the plot
plt.show()
