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
    this->adjlist  = new list<int>[count];
  }

  // Destructor
  ~Graph() {
    delete[] adjlist;
  }

  // Display graph
  void show_graph() {
    // Iterate over all vertices
    for(int index = 0; index < this->vertices; index++) {
      cout << "\n" << index << " --> ";
      for(auto itr : this->adjlist[index]) {
        cout << "\t" << itr;
      }
    }
  }

  // Insert edge
  void add_edge(int source, int destination) {
    this->adjlist[source].push_back(destination);
  }

  // Perform BFS from source
  void bfs_traversal(int source);

  // Perform topological sort
  void topological_sort();

};

// BFS Traversal - keep visited vertices in queue
void Graph::bfs_traversal(int source) {
  // Inititialize visit array
  bool visited[vertices];
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

// Topological sort
void Graph::topological_sort() {
  // Create indegree array for vertices
  int indegree[vertices];
  for(int index = 0; index < vertices; index++) {
    indegree[index] = 0;
  }
  // Iterate over all vertices
  for(int index = 0; index < vertices; index++) {
    // Iterate over all edges of specific vertex
    for(auto neighbor : adjlist[index]) {
      // Increment indegree
      indegree[neighbor] ++;
    }
  }
  // Inititialize queue with all vertices with in-degree 0
  queue<int>  QUEUE;
  vector<int> RESULT;
  for(int vertex = 0; vertex < vertices; vertex++) {
    if(indegree[vertex] == 0) {
      QUEUE.push(vertex);
    }
  }
  // Until queue is not empty
  while(!QUEUE.empty()) {
    // Mark vertex as visited
    int vertex = QUEUE.front();
    QUEUE.pop();
    RESULT.push_back(vertex);
    // Iterate over adjacent neighbors of visited vertex
    for(auto neighbor : adjlist[vertex]) {
      // Decrement indegree
      indegree[neighbor] --;
      // If indegree reaches 0, add it to queue
      if(indegree[neighbor] == 0) {
        QUEUE.push(neighbor);
      }
    }
  }
  // Check if visited is equal to number of vertices
  if(RESULT.size() == vertices) {
    cout << "\nTopological sort: ";
    for(auto vertex: RESULT)
      cout << "\t" << vertex;
  } else {
    cout << "\nTopological sort not possible";
  }
}

int main() {
  Graph graph(6);
  graph.add_edge(5, 2);
  graph.add_edge(5, 0);
  graph.add_edge(4, 0);
  graph.add_edge(4, 1);
  graph.add_edge(2, 3);
  graph.add_edge(3, 1);
  // // Break topological sort
  // graph.add_edge(1, 0);
  // graph.add_edge(0, 1);
  graph.show_graph();
  graph.topological_sort();
  //graph.bfs_traversal(5);
  return 0;
}
