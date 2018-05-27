#include <iostream>
#include <vector>

using namespace std;

class Edge {
public:
  int v1;
  int v2;
  int weight;
};

class Edge2 {
public:
  Edge2() = default;
  Edge2(int v2, int weight) : v2(v2), weight(weight){}
  int v2;
  int weight;
};

// Adjacency list.
vector<vector<Edge2>> G;

// Adjacency matrix.
vector<vector<int>> G_matrix;

// List of edges.
vector<Edge> G_edges;

vector<bool> marked;
void dfs(int v) {
  marked[v] = true;
  cout << v << ' ';
  for (int i = 0; i < G[v].size(); ++i)
  {
    if (!marked[G[v][i].v2])
      dfs(G[v][i].v2);
  }
}

void read_graph() {
  int n, m;
  cin >> n >> m;

  G_matrix.resize(n);
  G.resize(n);
  for (int i = 0; i < n; i++)
    G_matrix[i].resize(n);

  
  for (int i = 0; i < m; i++)
  {
    Edge current;
    cin >> current.v1 >> current.v2 >> current.weight;

    G[current.v1].push_back(Edge2(current.v2, current.weight));
    G[current.v2].push_back(Edge2(current.v1, current.weight));
  }
}

void connected_comps() {
  for (int i = 0; i < marked.size(); i++) {
    if (!marked[i]) {
      cout << "Start " << i << ": ";
      dfs(i);
      cout << endl;
    }
  }
}

int main() {
  read_graph();
  marked.resize(G.size());

  for (int i = 0; i < G.size(); ++i)
    marked[i] = false;

  connected_comps();
  return 0;
}

/*
|V| |E|
repeated |V| times
v1 v2 w

7 8
0 4 3
1 3 8
0 2 6
4 5 1
4 6 5
5 6 2
0 6 22
2 4 14
*/