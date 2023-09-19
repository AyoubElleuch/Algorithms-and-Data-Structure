#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;


// A sturct to store points
struct point{
    public:
        int index;
        long long x;
        long long y;
        long long pos;
        point(long long a, long long b, long long p, long long i){
            x = a;
            y = b;
            pos = p;
            index = i;
        }
        point(){

        }
        bool operator >(point a){
            if(x==a.x){
                return y>a.y;
            }
            return x>a.x;
        }
        bool operator <(point a){
            if(x==a.x){
                return y<a.y;
            }
            return x<a.x;
        }
        bool operator >=(point a){
            if(x>a.x || x==a.x){
                return true;
            }
            return false;
        }
        bool operator <=(point a){
            if(x<a.x || x==a.x){
                return true;
            }
            return false;
        }
        bool operator ==(point a){
            if(x==a.x && y==a.y) return true;
            return false;
        }
};

ostream& operator << (ostream& output, point& a){
    output << a.x << " " << a.y;
    return output;
}

// A struct to store segments
struct segment{
    public:
        point start;
        point end;

        // Constructor
        segment(point s, point e){
            start = s;
            end = e;
        }

        // A function to print the coordinates of endpoints of the segment
        void show(){
            cout << start.x << " " << start.y << " " << end.x << " " << end.y << endl;
        }
};


// A function that checks if two segments intersects. Worst case: O(1)
bool doIntersect(segment s1, segment s2){
    long long xa = s1.start.x;
    long long xb = s1.end.x;
    long long xc = s2.start.x;
    long long xd = s2.end.x;
    long long ya = s1.start.y;
    long long yb = s1.end.y;
    long long yc = s2.start.y;
    long long yd = s2.end.y;
    // First we check if they are parallel or coincident
    long long denom = (xa-xb)*(yc-yd)-(ya-yb)*(xc-xd);
    if(denom==0) return false;

    // Calculate the coordinates of the point of intersection of the lines (not the segments)
    double xp = (double(xa*yb-ya*xb)*double(xc-xd)-double(xa-xb)*double(xc*yd-yc*xd));
    xp/=double(xa-xb)*(yc-yd)-double(ya-yb)*(xc-xd);
    double yp = (double(xa*yb-ya*xb)*double(yc-yd)-double(ya-yb)*double(xc*yd-yc*xd));
    yp/=double(xa-xb)*(yc-yd)-double(ya-yb)*(xc-xd);

    // Check if the point of intersection lies on the first segment
    double cross = (yp-ya)*(xb-xa)-(xp-xa)*(yb-ya);
    if(fabs(cross)>1e-8) return false;
    // check dot product 
    double dot = (xp-xa)*(xb-xa)+(yp-ya)*(yb-ya);
    if(dot<0) return false;
    double temp = double(xb-xa)*double(xb-xa)+double(yb-ya)*double(yb-ya);
    if(dot>temp) return false;

    // Check if the point of intersection lies on the second segment
    cross = (yp-yc)*(xd-xc)-(xp-xc)*(yd-yc);
    if(fabs(cross)>1e-8) return false;
    // check the dot product
    dot = (xp-xc)*(xd-xc)+(yp-yc)*(yd-yc);
    if(dot<0) return false;
    temp = double(xd-xc)*double(xd-xc)+double(yd-yc)*double(yd-yc);
    if(dot>temp) return false;

    return true;
}

// AVL tree node structure <generics>
template<class T> struct Node {
    T val;
    long long height;
    Node<T>* left = NULL;
    Node<T>* right = NULL;
    // Constructor
    Node(T v){
        val = v;
        height = 1;
    }
};

// Max function
long long max(long long a, long long b){
    if(a>b) return a;
    return b;
}

// AVL Tree structure <generics>
template<class T> struct AVL{
    public:
        // Root of the tree
        Node<T>* root = NULL;

        // Function that returns the height of a node. Worst case: O(1)
        long long height(Node<T>* node){
            if(node==NULL) return 0;
            return node->height;
        }

        // Function that return the balance factor of a node. Worst case: O(1)
        long long BF(Node<T>* node){
            if(node==NULL) return 0;
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
        
        // Function that performs a left-right-roration. Worst case: O(1)
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
            if(node==NULL){
                return new Node<T>(v);
            }
            if(v < node->val){
                node->left = add(node->left, v);
            }else if(v > node->val){
                node->right = add(node->right, v);
            }else{
                return node;
            }

            // After insertigng the new node, we update the height of the parent node
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
            if(balanceFactor<-1){
                if(v>node->right->val){
                    return leftRotate(node);
                }
                else if(v<node->right->val){
                    return rightLeftRotate(node);
                }
            }
            return node;
        }

        // A function that insert a new value to the tree which uses add() function above: O(log(n))
        void insert(T v){
            root = add(root, v);
            return;
        }

        // A function that find the node with the minimum value in a subtree. Worst case: O(log(n))
        Node<T>* findMin(Node<T>* node){
            if(node->left==NULL){
                return node;
            }
            return findMin(node->left);
        }

        // The steps of "erase" function are inspired by: https://www.programiz.com/dsa/avl-tree

        // A function that removes a node from the tree. Worst case: O(log(n))
        Node<T>* erase(Node<T>* node, T v){

            // Find the node to be deleted
            if(node==NULL) return NULL;
            else if(v < node->val) node->left = erase(node->left, v);
            else if(v > node->val) node->right = erase(node->right, v);
            else{
                if(node->left==NULL && node->right==NULL){
                    return NULL;
                }
                else if(node->left!=NULL && node->right==NULL){
                    *node = *node->left;
                }
                else if(node->right!=NULL && node->left==NULL){
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
            root = erase(root, v);
        }

        // A function that find a specific value in the tree. Worst case: O(log(n));
        Node<T>* find(Node<T>* node, T v){
            if(node==NULL){
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


        // A function that finds the largest value that is strictly less than v. Worst case: O(log(n));
        Node<T>* prev(Node<T>* node, T v){
            T temp = v;
            Node<T>* p = node;
            while(node!=NULL){
                if(node->val<v){
                    temp = node->val;
                    p = node;
                    node = node->right;
                }else if(node->val>=v){
                    node = node->left;
                }
            }
            if(temp==v){
                return NULL;
            }else{
                return p;
            }
        }

        // A function that finds the smallest value that is strictly larger than v. Worst case: O(log(n));
        Node<T>* next(Node<T>* node, T v){
            T temp = v;
            Node<T>* n = node;
            while(node!=NULL){
                if(node->val<=v){
                    node = node->right;
                }else if(node->val>v){
                    temp = node->val;
                    n = node;
                    node = node->left;
                }
            }
            if(temp==v){
                return NULL;
            }else{
                return n;
            }
        }
};


// MergeSort function <generics>. Worst case: O(nlog(n))
template<class T>
void mergeSort(vector<T>* v, bool(*compare)(T ta, T tb)){
    if((*v).size()==1) return;
    int mid = (*v).size()/2;

    // Divide the vector in half
    vector<T> firstHalf;
    vector<T> secondHalf;
    for(int i=0; i<mid; i++){
        firstHalf.push_back((*v)[i]);
    }
    for(int i=mid; i<int((*v).size()); i++){
        secondHalf.push_back((*v)[i]);
    }

    // Sort both subvectors
    mergeSort<T>(&firstHalf, compare);
    mergeSort<T>(&secondHalf, compare);

    // Merge both sorted vectors and put the result in the intial vector
    (*v) = {};
    int i = 0; 
    int j = 0;
    int f = int(firstHalf.size());
    int s = int(secondHalf.size());

    while(i<f || j<s){
        if(f>i){
            if(s>j){
                if(compare(firstHalf[i],secondHalf[j])){
                    (*v).push_back(firstHalf[i]);
                    i++;
                }else{
                    (*v).push_back(secondHalf[j]);
                    j++;
                }
            }else{
                (*v).push_back(firstHalf[i]);
                i++;
            }
        }else{
            if(s>j){
                (*v).push_back(secondHalf[j]);
                j++;
            }
        }
    }
    return;
}

int main() {
    // Optimize the large input
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    // Creating the variables needed
    AVL<point> tree; // The AVL tree
    vector<point> vpoints; // A vector to store all the endpoitns
    vector<segment> vsegments; // A vector to store all the modified segments
    // A vector to store all segments (original segments used to output the coordinates exactly similar to the input)
    vector<segment> osegments;

    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        // Get the two coordinates
        long long a, b, c, d;
        cin >> a >> b >> c >> d;

        // Create both endpoints
        point start(a, b, 0, vsegments.size());
        point end(c, d, 1, vsegments.size());

        // Create the segment of the endpoints and push it into the original segments vector
        segment s(start, end);
        osegments.push_back(s);

        // Check which endpoint will be scanned by the sweepline first
        if(d<b){
            // If the end-point will be scanned before the start-point then we swap the points within the segment
            start.pos=1;
            end.pos=0;
            s.start=end;
            s.end=start;
        }
        // Here we push the segment into vsegments
        vsegments.push_back(s);

        // Push the endpoints to the vpoints vector
        vpoints.push_back(start);
        vpoints.push_back(end);
    }
    
    // Sort the points in an ascendent order
    mergeSort<point>(&vpoints, [](point p1, point p2){
        return p1.y<=p2.y;
    });
    
    // Move the sweepline and check for intersections
    for(int i=0; i<int(vpoints.size()); i++){
        // Get the point scanned by the sweepline
        point currentPoint = vpoints[i];

        // Check if it is a start-point or an end-point of a segment
        // 0->start-point, 1->end-point
        if(currentPoint.pos==0){
            // Insert the start-point into the AVL Tree
            tree.insert(currentPoint);

            // Get the smallest point that is strictly larger than the current point if it exists
            Node<point>* nextPt = tree.next(tree.root, currentPoint);

            // Check if it exists
            if(nextPt!=nullptr){
                point nextPoint = nextPt->val;

                // Get the segments of the two points
                segment s1 = vsegments[currentPoint.index];
                segment s2 = vsegments[nextPoint.index];

                //  Check if the two segments intersect
                if(doIntersect(s1, s2)){
                    cout << "INTERSECTION" << endl;
                    osegments[currentPoint.index].show();
                    osegments[nextPoint.index].show();
                    return 0;
                }
            }

            // Get the largest point that is strictly smaller than the current point if it exists
            Node<point>* prevPt = tree.prev(tree.root, currentPoint);

            // Check if it exists
            if(prevPt!=nullptr){
                point prevPoint = prevPt->val;

                // Get the segments of the two points
                segment s1 = vsegments[currentPoint.index];
                segment s2 = vsegments[prevPoint.index];

                //  Check if the two segments intersect
                if(doIntersect(s1, s2)){
                    cout << "INTERSECTION" << endl;
                    osegments[currentPoint.index].show();
                    osegments[prevPoint.index].show();
                    return 0;
                }
            }
        }
        else{
            // In this case the point is an end-point of a segment

            // Get the start-point of the segment
            point start = vsegments[currentPoint.index].start;

            // Get the smallest point that is strictly larger than the current point if it exists
            // And getthe largest point that is strictly smaller than the current point if it exists
            Node<point>* nextPt = tree.next(tree.root, start);
            Node<point>* prevPt = tree.prev(tree.root, start);

            // Check if both points exist
            if(nextPt!=nullptr && prevPt!=nullptr){
                point nextPoint = nextPt->val;
                point prevPoint = prevPt->val;

                // Get both segments
                segment s1 = vsegments[nextPoint.index];
                segment s2 = vsegments[prevPoint.index];

                // Check if both segments intersect
                if(doIntersect(s1, s2)){
                    cout << "INTERSECTION" << endl;
                    osegments[nextPoint.index].show();
                    osegments[prevPoint.index].show();
                    return 0;
                }
            }
            tree.del(start);
        }
    }
    
    // In case there is no intersection
    cout << "NO INTERSECTIONS" << endl;
    return 0;
}
