import matplotlib.pyplot as plt
nodes, edges = [], []

with open("data/out.txt", "r+") as fh:
    nodes = dict([(int(line.split(' ')[0]), list(map(float, line.split(' ')[1:]))) for line in fh.read().split('\n')[:-1]])
    print(nodes)

with open("data/in.txt", "r+") as fh:
    edges = [list(map(int, line.split(' ')[1:3])) for line in fh.read().split('\n')[:-1]]

for edge in edges:
    u_id, v_id = edge

    x_coords = [nodes[u_id][0], nodes[v_id][0]]
    y_coords = [nodes[u_id][1], nodes[v_id][1]]
    
    plt.plot(x_coords, y_coords, 'k-', alpha=0.3, zorder=1)

x_vals = [n[0] for n in nodes.values()]
y_vals = [n[1] for n in nodes.values()]
plt.scatter(x_vals, y_vals, color='red', zorder=2)
plt.axis('equal')
plt.show()
