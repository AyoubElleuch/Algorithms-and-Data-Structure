#include<iostream>
#include<vector>

#define INF 1e9

using namespace std;

// Implementation of a minimum heap taken from my personal Homework 2 code

// AVL tree node structure <generics>
template<class T> struct Node {
public:
    T val;
    long long height;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    // Constructor
    Node(T v){
        val = v;
        height = 1;
    }
};

// AVL Tree structure <generics>
template<class T> struct AVL{
public:
    // Root of the tree
    Node<T>* root = nullptr;
    int size = 0;

    // Function that returns the height of a node. Worst case: O(1)
    long long height(Node<T>* node){
        if(node==nullptr) return 0;
        return node->height;
    }

    // Function that return the balance factor of a node. Worst case: O(1)
    long long BF(Node<T>* node){
        if(node==nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    // Function that updates the height of a node. Worst case: O(1)
    void newHeight(Node<T>* node){
        node->height = 1 + max(height(node->left), height(node->right));
    }

    // Function that performs a left-rotation. Worst case: O(1)
    Node<T>* leftRotate(Node<T>* x){
        Node<T>* y = x->right;
        Node<T>* beta = y->left;
        y->left = x;
        x->right = beta;
        newHeight(x);
        newHeight(y);
        return y;
    }

    // Function that performs a right-rotation. Worst case: O(1)
    Node<T>* rightRotate(Node<T>* y){
        Node<T>* x = y->left;
        Node<T>* beta = x->right;
        x->right = y;
        y->left = beta;
        newHeight(y);
        newHeight(x);
        return x;
    }

    // Function that performs a left-right-rotation. Worst case: O(1)
    Node<T>* leftRightRotate(Node<T>* y){
        y->left = leftRotate(y->left);
        return rightRotate(y);
    }

    // Function that performs a right-left-rotation. Worst case: O(1)
    Node<T>* rightLeftRotate(Node<T>* y){
        y->right = rightRotate(y->right);
        return leftRotate(y);
    }

    // The steps of "add" function are inspired from: https://www.programiz.com/dsa/avl-tree

    // Function that add a new node to the AVL Tree. Worst case: O(log(n))
    Node<T>* add(Node<T>* node, T v){
        // Find the correct position to insert the tree
        if(node==nullptr){
            return new Node<T>(v);
        }
        if(v < node->val){
            node->left = add(node->left, v);
        }else if(v > node->val){
            node->right = add(node->right, v);
        }else{
            return node;
        }

        // After inserting the new node, we update the height of the parent node
        newHeight(node);

        // Check the balance factor after the insertion
        long long balanceFactor = BF(node);

        // Perform the adequate rotation if the tree is not balanced
        if(balanceFactor>1){
            if(v < node->left->val){
                return rightRotate(node);
            }
            else if(v > node->left->val){
                return leftRightRotate(node);
            }
        }
        if(balanceFactor<-1) {
            if (v > node->right->val) {
                return leftRotate(node);
            } else if (v < node->right->val) {
                return rightLeftRotate(node);
            }
        }
        return node;
    }

    // A function that insert a new value to the tree which uses add() function above: O(log(n))
    void insert(T v){
        if(find(root, v)!=nullptr) return;
        size++;
        root = add(root, v);
    }

    // A function that find the node with the minimum value in a subtree. Worst case: O(log(n))
    Node<T>* findMin(Node<T>* node){
        if(node->left==nullptr){
            return node;
        }
        return findMin(node->left);
    }

    // The steps of "erase" function are inspired by: https://www.programiz.com/dsa/avl-tree

    // A function that removes a node from the tree. Worst case: O(log(n))
    Node<T>* erase(Node<T>* node, T v){

        // Find the node to be deleted
        if(node==nullptr) return nullptr;
        else if(v < node->val) node->left = erase(node->left, v);
        else if(v > node->val) node->right = erase(node->right, v);
        else{
            if(node->left==nullptr && node->right==nullptr){
                return nullptr;
            }
            else if(node->left!=nullptr && node->right==nullptr){
                *node = *node->left;
            }
            else if(node->right!=nullptr && node->left==nullptr){
                *node = *node->right;
            }
            else{
                Node<T>* minNode = findMin(node->right);
                node->val = minNode->val;
                node->right = erase(node->right, minNode->val);
            }
        }

        // Update the height of the parent node
        newHeight(node);
        // Check the balance factor after the deletion
        long long balanceFactor = BF(node);

        // Perform the adequate rotation if the tree is not balanced
        if(balanceFactor>1){
            if(BF(node->left)>=0){
                return rightRotate(node);
            }else{
                return leftRightRotate(node);
            }
        }
        if(balanceFactor<-1){
            if(BF(node->right)<=0){
                return leftRotate(node);
            }else{
                return rightLeftRotate(node);
            }
        }
        return node;
    }

    // A function that deletes a value from the tree which uses erase() function above. Worst case: O(log(n));
    void del(T v){
        if(find(root, v)==nullptr) return;
        size--;
        root = erase(root, v);
    }

    // A function that find a specific value in the tree. Worst case: O(log(n));
    Node<T>* find(Node<T>* node, T v){
        if(node==nullptr){
            return nullptr;
        }
        if(node->val == v){
            return node;
        }
        if(v>node->val){
            return find(node->right, v);
        }else{
            return find(node->left, v);
        }
    }

    bool isEmpty(){
        if(size==0) return true;
        return false;
    }
};

// Generic Edge class
template<class T>
class Edge{
public:
    T weight;
    T bandwidth;

    Edge(T w, T b){
        weight = w;
        bandwidth = b;
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

    // A vector to store the vertices and an adjacency matrix to store the edges
    vector<V> vertices;
    vector<vector<E>> adj;

    // Constructor
    Graph(int N, E dummyEdge){
        // Initialize the adjacency matrix
        adj = vector<vector<E>>(N, vector<E>(N, dummyEdge));
    }

    // A method that adds a new vertex to the graph. Worst case time complexity: O(1)
    void addVertex(V vertex){
        vertices.push_back(vertex);
    }

    // A method that searches for a vertex and returns its index in the vector of vertices.
    // Worst case time complexity: O(N)
    int findVertex(V vertex){
        for(int i = 0; i<int(vertices.size()); i++){
            if(vertices[i].value == vertex.value) return i;
        }
        return -1;
    }

    // A method that adds a new edge to the graph. Worst case time complexity: O(N)
    void addEdge(E edge, V vertex1, V vertex2){
        int i = findVertex(vertex1);
        int j = findVertex(vertex2);
        adj[i][j] = edge;
    }

    // A method that finds the shortest path from vertex A to vertex B with a minimum required bandwidth
    // using Dijkstra's Algorithm
    void findShortestPath(V currentVertex, V destinationVertex, int minBandwidth, int N, E dummyEdge){

        // Declare priority_queue
        AVL<pair<int, int>> priority_queue;

        // Initialize the distance vector
        vector<int> dis(N, INF);

        // Initialize a vector to keep track of the parent of a chosen vertex

        vector<int> parent(N, -1);

        // Initialize the visited vector
        vector<bool> visited(N, false);

        // Initialize a vector to keep track of the path
        vector<int> trackedVertices(N, -1);

        // Keep track of the slowest bandwidth within the path
        vector<int> band(N, INF);

        // Getting the index of the starting vertex A
        int currentIndex = findVertex(currentVertex);

        // Initialize the distance of the first vertex A to 0
        dis[currentIndex] = 0;

        // Add the first vertex A to the tracked vertices
        trackedVertices[currentIndex] = currentIndex;

        // While we haven't reached the vertex B we apply the steps of the algorithm
        while(currentVertex.value!=destinationVertex.value){

            // Set the current vertex as visited
            visited[currentIndex] = true;

            // Add the vertex from which we came to the current vertex to the trackedVertices (only of it is not the vertex A)
            if(trackedVertices[currentIndex]!=currentIndex){
                trackedVertices[currentIndex] = parent[currentIndex];
            }

            // Go over all the edges of the current vertex and update the distances of the adjacent vertices
            for(int i=0; i<N; i++){
                // Get the edge
                E currentEdge = adj[currentIndex][i];

                // Check if the edge is not a dummy edge (i.e. the edge actually exists between the two vertices)
                if(currentEdge.bandwidth!=dummyEdge.bandwidth && currentEdge.weight!=dummyEdge.weight){
                    // Check if the adjacent vertex is not yet visited
                    if(!visited[i]){
                        // Check the bandwidth requirement and update the distance if needed
                        if((dis[currentIndex]+currentEdge.weight)<dis[i] && currentEdge.bandwidth >= minBandwidth){
                            // Update the distance
                            dis[i] = dis[currentIndex]+currentEdge.weight;
                            // Keep track of the current vertex in case we choose this adjacent vertex later
                            parent[i] = currentIndex;
                            // Update the bandwidth
                            band[i] = min(currentEdge.bandwidth, band[currentIndex]);
                            // Insert the vertex into the priority_queue
                            pair<int, int> p = make_pair(dis[i], i);
                            priority_queue.insert(p);
                        }
                    }
                }
            }

            currentIndex = -1;
            // Get the vertex with the minimum distance that is not yet visited
            while(!priority_queue.isEmpty()) {
                Node<pair<int, int>> *p = priority_queue.findMin(priority_queue.root);
                if (!visited[(*p).val.second]) {
                    currentIndex = (*p).val.second;
                    currentVertex = vertices[currentIndex];
                    priority_queue.del((*p).val);
                    break;
                }
                priority_queue.del((*p).val);
            }

            // If there is no vertex that can be visited then it is impossible to reach the destination vertex
            if(currentIndex==-1){
                cout << "IMPOSSIBLE" << endl;
                return;
            }
        }

        // Add the parent of the vertex B to the trackedVertices
        trackedVertices[currentIndex] = parent[currentIndex];

        // Get the total distance of the path
        int totalDistance = dis[findVertex(destinationVertex)];

        // Get the bandwidth
        int bandwidth = band[findVertex(destinationVertex)];

        // Initialize a vector in which the final path will be in it
        vector<int> track;

        // Iterate from the vertex B all the way up to the vertex A
        // and each time push the current vertex's value to the track vector
        while(trackedVertices[currentIndex]!=currentIndex){
            track.push_back(currentIndex);
            currentIndex = trackedVertices[currentIndex];
        }
        // Push the first index (vertex A)
        track.push_back(currentIndex);

        // Print the output
        cout << track.size() << " " << totalDistance << " " << bandwidth << endl;
        for(int i=int(track.size())-1; i>=0; i--) cout << vertices[track[i]].value << " ";
        cout << endl;
    }
};


int main(){
    // Declare needed variables
    int start, finish, minBandwidth;
    int N, M;

    cin >> N >> M;

    // Initialize a dummy edge
    Edge<int> dummyEdge(INF, INF);
    // Initialize the graph
    Graph<Vertex<int>, Edge<int>> myGraph(N, dummyEdge);

    // Get the input
    for(int i=0; i < M; i++){
        int n1;
        int n2;
        int weight;
        int bandwidth;
        cin >> n1 >> n2 >> weight >> bandwidth;
        Vertex<int> vertex1(n1);
        Vertex<int> vertex2(n2);
        Edge<int> edge(weight, bandwidth);

        // Check if the vertices already exist in the graph or not
        // if they don't exist then add them to the graph.
        if(myGraph.findVertex(vertex1)==-1){
            myGraph.addVertex(vertex1);
        }
        if(myGraph.findVertex(vertex2)==-1){
            myGraph.addVertex(vertex2);
        }

        // Add the edge to the graph
        myGraph.addEdge(edge, vertex1, vertex2);
    }

    cin >> start >> finish >> minBandwidth;

    // Initialize the starting vertex and the destination vertex
    Vertex<int> startVertex(start);
    Vertex<int> finishVertex(finish);

    // Call the function to find the shortest path
    myGraph.findShortestPath(startVertex, finishVertex, minBandwidth, N, dummyEdge);

    return 0;
}
