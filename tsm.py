import networkx as nx
import matplotlib.pyplot as mp

G = nx.Graph()
G.add_nodes_from([1, 2, 3, 4])
G.add_weighted_edges_from([(1, 2, 10),(1, 3, 2),(1, 4, 4), (2, 3, 5), (2, 4, 8), (3, 4, 10)])

pos=nx.spring_layout(G) # pos = nx.nx_agraph.graphviz_layout(G)
nx.draw_networkx(G,pos)
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)

mp.show()

#nx.draw(G, pos = None, ax = None, with_labels = True,font_size = 20, node_size = 2000, node_color = 'lightgreen'0
#G.add_edge('A', 'B')
#G.add_edges_from([('A', 'B'), ('A', 'G'), ('A', 'D'), ('B', 'G'),  ('B', 'C'), ('B', 'E'), ('C', 'E'), ('C', 'F'), ('D', 'F'), ('E', 'F'), ('F', 'G')])

#Adjacency list = {'A': ['B', 'G', 'D'],'B': ['A', 'G', 'C', 'E'],'C': ['B', 'E', 'F'],'D': ['A', 'F'],'E': ['B', 'C', 'F'],'F': ['G', 'D', 'C', 'E'],'G': ['A', 'B', 'F']}
#G = nx.Graph(Adjacency list)

#G.edges()
#Output
#EdgeView([('A', 'B'), ('A', 'D'), ('A', 'G'), ('B', 'G'), ('B', 'C'), ('B', 'E'), ('C', 'F'), ('C', 'E'), ('D', 'F'), ('E', 'F'), ('F', 'G')])

#G.add_weighted_edges_from( [(1,2,0), (1,3,1) , (1,4,-1) , (2,4,1) , (2,3,-1), (3,4,10) ] )