#include<iostream>
#include<vector>

using namespace std;

// Generic struct of a node
template<class T>
struct node{
    public:
        T value;
};

// Generic struct of an edge
template<class T, class B>
struct edge{
    public:
        // The weight of the edge
        B weight;
        // end-nodes of the edge
        node<T> S;
        node<T> E;
};

// Generic struct of a graph
template<class T>
struct Graph{
    public:
        int n;

        // Adjacency List
        vector<pair<node<T>, vector<node<T>>>> nodes;

        // Adjacency Matrix
        vector<vector<int>> adj;

        // Constructor
        Graph(int m){
            n = m;
            adj = vector<vector<int>>(m, vector<int>(m, 0));
        }

        // Check the connectivity. Worst case time complexity: O(n);
        string isConnected(){
            // Keep track of the number of visited nodes
            int count = 0;

            // Keep track of the visited nodes
            vector<int> visited(n, 0);

            // A stack for DFS
            vector<int> myStack;

            // We start with the first node in the adj and we mark it as visited
            myStack.push_back(0);
            visited[0] = 1;

            // DFS
            while(myStack.size()>0){
                int current = myStack[myStack.size()-1];
                myStack.pop_back();
                count++;

                // Loop over all other nodes and check which one connects to the current one
                for(int i=0; i<n; i++){
                    if(adj[current][i]==1){
                        if(visited[i]==0){
                            // If the node that connects to the current one is not yet visited
                            // we add it to the stack and mark it as visited
                            myStack.push_back(i);
                            visited[i]=1;
                        }
                    }
                }
            }
            // Check if the number of visited nodes equals to the total number of nodes
            if(count==n) return "YES\n";
            return "NO\n";
        }

};


int main(){
    int n;
    cin >> n;
    Graph<int> myGraph(n);

    // Get the adjacency matrix
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> myGraph.adj[i][j];
        }
    }

    // Check the connectivity
    cout << myGraph.isConnected();
    return 0;
}
