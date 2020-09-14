#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Graph {
  // Number of vertices
  int vertices;
  // Adjancency list
  list<int>* adjlist;
public:
  // Constructor
  Graph(int count) {
    this->vertices = count;
    this->adjlist = new list<int>[count];
  }

  // Display graph
  void display_graph() {
    // Iterate over all vertices
    for(int index = 0; index < this->vertices; index++) {
      cout << "\n" << index << " : ";
      for(auto itr : this->adjlist[index]) {
        cout << " --> " << itr;
      }
    }
  }

  // Insert edge
  void add_edge(int source, int destination) {
    this->adjlist[source].push_back(destination);
  }

  // Perform breadth first search
  void BFS(int source);

};

void Graph::BFS(int source) {
  // Inititialize visit array
  bool* visited = new bool[vertices];
  for(int index = 0; index < vertices; index++) {
    visited[index] = false;
  }
  cout << "\nBFS Traversal from " << source << " : ";
  queue<int> QUEUE;
  visited[source] = true;
  QUEUE.push(source);
  while(!QUEUE.empty()) {
    int vertex = QUEUE.front();
    QUEUE.pop();
    cout << " " << vertex;
    // Traverse adjacency list
    for(auto itr = adjlist[vertex].begin(); itr != adjlist[vertex].end(); itr++) {
        int adjacenct = *itr;
        if(visited[adjacenct] == false) {
          visited[adjacenct] = true;
          QUEUE.push(adjacenct);
        }
    }
  }
}

int main() {
  Graph graph(4);
  graph.add_edge(0, 1);
  graph.add_edge(0, 2);
  graph.add_edge(1, 2);
  graph.add_edge(2, 0);
  graph.add_edge(2, 3);
  graph.add_edge(3, 3);
  graph.display_graph();
  graph.BFS(2);
  return 0;
}
