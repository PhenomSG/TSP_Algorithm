import matplotlib.pyplot as plt

algorithms = [
    "backtracking.cpp",
    "bitmask_dp.cpp",
    "branch_n_bound.cpp",
    "dp.cpp",
    "hungarian.cpp",
    "mst.cpp",
    "reduced_matrix.cpp"
]

memory_usage = {
    "backtracking.cpp": [4896, 4836, 4844, 4848],
    "bitmask_dp.cpp": [5008, 4948, 4956, 4960],
    "branch_n_bound.cpp": [5016, 4948, 4956, 4960],
    "dp.cpp": [5016, 4948, 4956, 4960],
    "hungarian.cpp": [5016, 4948, 4956, 4960],
    "mst.cpp": [4964, 4948, 4956, 4960],
    "reduced_matrix.cpp": [5016, 4948, 4956, 4960]
}

inputs = ['Input 2', 'Input 3', 'Input 4', 'Input 5']
plt.figure(figsize=(12, 8))

for alg in algorithms:
    plt.plot(inputs, memory_usage[alg], marker='o', label=alg)

plt.xlabel('Inputs')
plt.ylabel('Memory Usage (KB)')
plt.title('Memory Usage of Algorithms vs Inputs')
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig('memory_usage_vs_inputs.png')
plt.show()
