import matplotlib.pyplot as plt

# Heap sizes
sizes = [100, 200, 300, 400, 500]

# Comparison data
binary_heap = {
    "Create": [442, 850, 1335, 1758, 2203],
    "Insert": [1, 2, 2, 3, 2],
    "Delete": [12, 12, 14, 16, 16],
    "Merge": [273, 519, 821, 1059, 1335]
}

leftist_heap = {
    "Create": [657, 1587, 2062, 3407, 4468],
    "Insert": [5, 5, 2, 4, 6],
    "Delete": [7, 9, 7, 7, 10],
    "Merge": [8, 8, 8, 8, 11]
}

binomial_heap = {
    "Create": [1304, 2834, 4424, 6096, 7888],
    "Insert": [4, 4, 5, 4, 7],
    "Delete": [33, 33, 43, 23, 49],
    "Merge": [16, 16, 22, 16, 37]
}

# Plotting
operations = ["Create", "Insert", "Delete", "Merge"]
fig, axs = plt.subplots(2, 2, figsize=(15, 10))
axs = axs.ravel()

for i, op in enumerate(operations):
    axs[i].plot(sizes, binary_heap[op], marker='o', label='Binary Heap')
    axs[i].plot(sizes, leftist_heap[op], marker='s', label='Leftist Heap')
    axs[i].plot(sizes, binomial_heap[op], marker='^', label='Binomial Heap')
    axs[i].set_title(f'{op} Comparison Counts')
    axs[i].set_xlabel('Heap Size (n)')
    axs[i].set_ylabel('Comparisons')
    axs[i].legend()
    axs[i].grid(True)

plt.tight_layout()
plt.show()