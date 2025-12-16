import matplotlib.pyplot as plt
import os


BASE_DIR = os.path.dirname(os.path.abspath(__file__))
GRAPH_FILE = os.path.join(BASE_DIR, "graph.txt")

# ============================
# READ GRAPH DATA
# ============================
with open(GRAPH_FILE, "r") as file:
    n = int(file.readline())

    city_coords = {}
    for _ in range(n):
        name, x, y = file.readline().split()
        city_coords[name] = (float(x), float(y))

    m = int(file.readline())

    edges = []
    for _ in range(m):
        c1, c2, dist = file.readline().split()
        edges.append((c1, c2, int(dist)))

# ============================
# DRAW GRAPH
# ============================
plt.figure(figsize=(8, 6))

# Draw edges and distance labels
for c1, c2, dist in edges:
    x1, y1 = city_coords[c1]
    x2, y2 = city_coords[c2]

    # Draw line
    plt.plot([x1, x2], [y1, y2])

    # Distance label (middle of line)
    mid_x = (x1 + x2) / 2
    mid_y = (y1 + y2) / 2
    plt.text(mid_x, mid_y, str(dist),
             fontsize=10,
             bbox=dict(facecolor='white', edgecolor='black'))

# Draw city nodes
for city, (x, y) in city_coords.items():
    plt.scatter(x, y, s=1200, edgecolors="black")
    plt.text(x, y, city,
             ha="center", va="center",
             color="white", fontsize=12, fontweight="bold")

# Styling
plt.title("Smart City Navigation Graph")
plt.axis("equal")
plt.grid(True)
plt.show()
