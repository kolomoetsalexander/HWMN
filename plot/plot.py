import json
import matplotlib.pyplot as plt

with open("../build-release/results.json") as file:
    data = json.load(file)

benchmarks = {
    "BM_Gaussian<Matrix<double>>": "Gaussian (contiguous)",
    "BM_Gaussian<JaggedMatrix<double>>": "Gaussian (jagged)",
    "BM_Bareiss<Matrix<long long>>": "Bareiss (contiguous)",
    "BM_Bareiss<JaggedMatrix<long long>>": "Bareiss (jagged)"
}

plt.figure(figsize=(10, 6))

for name, label in benchmarks.items():
    sizes = []
    times = []

    for result in data["benchmarks"]:
        if result.get("aggregate_name") != "median":
            continue

        if not result["name"].startswith(name + "/"):
            continue

        size = int(result["name"].split("/")[1].split("_")[0])

        sizes.append(size)
        times.append(result["cpu_time"])

    plt.plot(sizes, times, marker="o", label=label)

plt.xlabel("Matrix size")
plt.ylabel("CPU time (ms)")
plt.title("Determinant computation performance")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("complexity.png", dpi=300)
plt.show()