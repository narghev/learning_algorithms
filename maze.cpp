#include <iostream>
#include <vector>
#include <queue>

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

// Maze
vector<vector<char>> maze;

void make_maze() {
  int vNumber = 0;
  for (int i = 0; i < maze.size(); i++) {
    for (int j = 0; j < maze[0].size(); j++) {
      if (maze[i][j] == '.') {
        if (i + 1 < maze.size() && maze[i + 1][j] == '.') {
          Edge current;
          current.v1 = vNumber;
          current.v2 = vNumber + maze[0].size();
          G[vNumber].push_back(Edge2(current.v2, 1));

          int index = vNumber + maze[0].size();
          G[index].push_back(Edge2(current.v1, 1));
        }
        if (j + 1 < maze[0].size() && maze[i][j + 1] == '.') {
          Edge current;
          current.v1 = vNumber;
          current.v2 = vNumber + 1;
          G[vNumber].push_back(Edge2(current.v2, 1));
          G[vNumber + 1].push_back(Edge2(current.v1, 1));
        }
      }
      vNumber++;
    }
  }
}

void read_maze() {
  int h, w;
  cin >> h >> w;
  maze.resize(h);

  for (int i = 0; i < h; i++)
    maze[i].resize(w);

  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++)
      cin >> maze[i][j];

  G.resize(h * w);
  make_maze();
}

vector<int> marked;
bool found = false;

void draw() {
    int i = G.size() - 1, h = maze.size(), w = maze[0].size();
    maze[h - 1][w - 1] = 'x';

    while(marked[i] != -1) {
      int x = marked[i] / w;
      int y = marked[i] % w;
      maze[x][y] = 'x';
      i = marked[i];
    }
}

void print() {
  cout<<endl<<"Output"<<endl;

  for(int i = 0; i < maze.size(); i++) {
    for(int j = 0; j < maze[0].size(); j++) {
        cout << maze[i][j];
    }
    cout << endl;
  }
}

void bfs(int v) {
  queue <int> q;
  marked[v] = -1;
  q.push(v);

  while (!q.empty()) {
    int currentVertex = q.front();

    for (int i = 0; i < G[currentVertex].size(); i++) {
      if (marked[G[currentVertex][i].v2] == -2) {
        marked[G[currentVertex][i].v2] = currentVertex;
        q.push(G[currentVertex][i].v2);
      }
    }
    q.pop();
  }
}

void setup()
{
  read_maze();
  marked.resize(G.size());
  for (int i = 0; i < G.size(); ++i)
    marked[i] = -2;
  bfs(0);
  draw();
}

int main() {
  setup();
  print();
  return 0;
}

/*
6 9
..#....##
#...##.##
##.#....#
#..######
#.......#
######...
*/