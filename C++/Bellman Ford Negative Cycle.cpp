#include<iostream>
#include<vector>
#include<math.h>
#include <bits/stdc++.h>

#define INF 10000000

using namespace std;

// Generic Edge class
template<class T>
class Edge{
public:
    // An edge has the indices of both ends and its weight
    T u;
    T v;
    T weight;

    // Constructor
    Edge(T f, T s, T w){
        weight = w;
        u = f;
        v = s;
    }
};

// Generic Vertex class
template<class T>
class Vertex{
public:
    T value;

    Vertex(T v){
        value = v;
    }
};

// Generic Graph class
template<class V, class E>
class Graph{
public:

    // A vector to store the vertices and a vector to store the edges
    vector<V> vertices;
    vector<E> edges;

    // A method to add an edge to the graph
    void addEdge(E edge){
        edges.push_back(edge);
    }

    // A method that finds a negative cycle within the graph using Bellman Ford's Algorithm.
    // Worst case time complexity: O(V^3)
    void negativeCycle(int N,  vector<int>& dis, vector<int>& pre){

        // Relax all edges N-1 times
        for(int i=0; i<N-1; i++){
            for(E edge : edges){
                int v = edge.v;
                int u = edge.u;
                int w = edge.weight;

                // If the new distance is less than the current one update it and set the predecessor of
                // the destination vertex to be the current vertex
                if(dis[v]>dis[u]+w){
                    dis[v] = dis[u]+w;
                    // Handle the overflow
                    if(dis[v]<-100000) dis[v] = -5000;
                    pre[v] = u;
                }
            }
        }

        // Iterate over the edge one last time
        for(E edge : edges){
            int v = edge.v;
            int u = edge.u;
            int w = edge.weight;

            // If the new distance is less than the current one means that a negative cycle is found
            if(dis[v]>dis[u]+w){
                // Update the distance
                dis[v] = dis[u]+w;
                // Handle the overflow
                if(dis[v]<-10000) dis[v] = -5000;
                pre[v] = u;

                // Get the index of the last vertex which its distance changed
                int end = v;

                // Iterate over the indices of the negative cycle N times to guarantee that you start from a
                // vertex that is a part of the negative cycle
                for(int i=0; i<N; i++){
                    end = pre[end];
                }

                // Iterate over the indices of the negative cycle and add them into ind vector
                int start = pre[end];
                vector<int> ind;
                ind.push_back(end);
                while(start!=end){
                    ind.push_back(start);
                    start = pre[start];
                }

                // Print the answer
                if(ind.size()>0){
                    cout << "YES\n" << ind.size() << endl;
                    for(int i=ind.size()-1; i>=0; i--){
                        cout << ind[i]+1 << " ";
                    }
                    cout << endl;
                    return;
                }
            }
        }

        cout << "NO" << endl;
    }
};


int main(){
    // Declare the graph
    Graph<int, Edge<int>> myGraph;

    int N;
    bool edgeExist = false;
    cin >> N;

    // Get the adjacency Matrix
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){

            int weight;
            cin >> weight;

            // Check if there is a cycle of size 1
            if (i == j && weight < 0) {
                cout << "YES\n1\n" << i + 1 << endl;
                return 0;
            }

            // Check if the edge exist and add it to the edges of the graph
            if(weight!=100000 && fabs(weight)<10000) {
                edgeExist = true;
                Edge<int> edge(i, j, weight);
                myGraph.addEdge(edge);
            }
        }
    }

    // Check if there are no edges
    if(!edgeExist){
        cout << "NO" << endl;
        return 0;
    }

    // Initialize the distance and predecessor vectors
    vector<int> dis(N, INF);
    vector<int> pre(N, 0);
    dis[0] = 0;

    // Solve
    myGraph.negativeCycle(N, dis, pre);

    return 0;
}
