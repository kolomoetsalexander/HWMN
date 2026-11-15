import csv
import matplotlib.pyplot as plt

results = {
    "gaussian": {"contiguous": [], "jagged": []},
    "bareiss": {"contiguous": [], "jagged": []},
}

with open("../build/results.csv", newline="") as file:
    reader = csv.DictReader(file)

    for row in reader:
        algorithm = row["algorithm"]
        layout = row["layout"]

        results[algorithm][layout].append((int(row["size"]), float(row["time_ms"])))

for algorithm in results:
    plt.figure(figsize=(8, 5))

    for layout in results[algorithm]:
        points = sorted(results[algorithm][layout])

        sizes = [point[0] for point in points]
        times = [point[1] for point in points]

        plt.plot(sizes, times, marker="o", label=layout)

    plt.title(f"{algorithm.capitalize()} benchmark")
    plt.xlabel("Matrix size (n)")
    plt.ylabel("Time (ms)")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    plt.savefig(f"{algorithm}.png", dpi=200)

#сomparison with theoretical cubic complexity
plt.figure(figsize=(8, 5))

points = sorted(results["bareiss"]["contiguous"])
sizes = [point[0] for point in points]
times = [point[1] for point in points]

scale = times[0] / sizes[0]**3
theoretical = [scale * n**3 for n in sizes]

plt.plot(sizes, times, "o-", label="Bareiss measured")
plt.plot(sizes, theoretical, "--", label="O(n^3) reference")

plt.xlabel("Matrix size (n)")
plt.ylabel("Time (ms)")
plt.title("Bareiss complexity")
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig("complexity.png", dpi=200)

plt.show()
