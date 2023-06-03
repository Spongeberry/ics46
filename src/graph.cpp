#include "graph.h"

void error(string msg) {
    cout << "Error: " << msg << endl;
}

DisjointSet::DisjointSet(int numVertices) {
    subsets.resize(numVertices);
    for (int v = 0; v < numVertices; ++v)
        makeSet(v);
}

void DisjointSet::makeSet(Vertex x) {
    subsets[x].parent = x;
}

Vertex DisjointSet::findSet(Vertex x) {
    if (x != subsets[x].parent)
        subsets[x].parent = findSet(subsets[x].parent);
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
    Vertex xroot = findSet(x);
    Vertex yroot = findSet(y);
    if (xroot != yroot)
        subsets[xroot].parent = yroot;
}

Graph Graph::sort_edges() const {
    Graph sorted_graph = *this;
    sort(sorted_graph.begin(), sorted_graph.end(),
        [](Edge const& a, Edge const& b) { return a.weight < b.weight; });
    return sorted_graph;
}

VertexList Graph::edges_from(Vertex vertex) const {
    VertexList edges;
    for(const auto &edge : *this) {
        if(edge.u == vertex) {
            edges.push_back(edge.v);
        }
    }
    return edges;
}

EdgeList Kruskals(const Graph& G) {
    DisjointSet ds(G.numVertices);
    EdgeList MST;
    Graph sorted_graph = G.sort_edges();
    for (auto && edge : sorted_graph) {
        if (ds.findSet(edge.u) != ds.findSet(edge.v)) {
            MST.push_back(edge);
            ds.unionSets(edge.u, edge.v);
        }
    }
    return MST;
}

int sum_weights(EdgeList const& L) {
    return accumulate(L.begin(), L.end(), 0, [](int acc, Edge const& e) { return acc + e.weight; });
}

void file_to_graph(string filename, Graph & G) {
    ifstream file(filename);
    file >> G;
}

VertexList dfs(const Graph& graph, Vertex startVertex){
    VertexList result;
    vector<bool> visited(graph.size(), false);
    stack<Vertex> stk;
    visited[startVertex] = true;
    stk.push(startVertex);
    while (!stk.empty()) {
        Vertex vertex = stk.top();
        stk.pop();
        result.push_back(vertex);
            for (Vertex v : graph.edges_from(vertex))
                if (!visited[v]) {
                    visited[v] = true;
                    stk.push(v);
                }
    }
    return result;
}


VertexList bfs(const Graph& graph, Vertex startVertex) {
    VertexList  result;
    vector<bool> visited(graph.size(), false);
    queue<Vertex> queue;
    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        Vertex vertex = queue.front();
        queue.pop();
        result.push_back(vertex);
        for (Vertex v : graph.edges_from(vertex))
            if (!visited[v]) {
                visited[v] = true;
                queue.push(v);
            }
    }
    return result;
}


string get_arg(int argc, char *argv[], string def) {
    return argc > 1 ? argv[1] : def;
}