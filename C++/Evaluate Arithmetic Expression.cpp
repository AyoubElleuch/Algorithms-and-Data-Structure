#include <iostream>
#include <string>
using namespace std;

bool isDigit(string s);

int operation(string x, int a, int b);

int pr(string s){
    if(s=="-" || s=="+") return 1;
    else if(s=="*" || s=="/") return 2;
    return 0;
}


template <class T> struct node{
    public:
        T data;
        node<T> *next;
        node<T> *prev;
};

template <class T> class stack{
    public:
        node<T>* head;
        node<T>* tail;
        stack<T>(){
            head = NULL;
            tail = NULL;
        }
        int p = 0;
        T top(){
            if(tail!=NULL){
                return tail->data;
            }
        }
        void pop(){
            p--;
            if(tail!=NULL){
                if(head==tail){
                    head = NULL;
                    tail = NULL;
                }else{
                    tail = tail->prev;
                }
            }
        }
        int size(){
            return p;
        }
        void push(T value){
            p++;
            node<T>* temp = new node<T>;
            temp->data = value;
            if(head==NULL){
                head = temp;
                tail = temp;
            }else{
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }
        }
        bool empty(){
            if(p>0){
                return false;
            }
            return true;
        }
};

template <class T> class queue{
    public:
        node<T>* head;
        node<T>* tail;
        queue<T>(){
            head = NULL;
            tail = NULL;
        }
        int p = 0;
        T front(){
            if(head!=NULL){
                return head->data;
            }
        }
        void pop(){
            p--;
            if(head!=NULL){
                if(head==tail){
                    head = NULL;
                    tail = NULL;
                }else{
                    head = head->next;
                }
            }
        }
        int size(){
            return p;
        }
        void push(T value){
            p++;
            node<T>* temp = new node<T>;
            temp->data = value;
            if(head==NULL){
                head = temp;
                tail = temp;
            }else{
                tail->next = temp;
                tail = temp;
            }
        }
        bool empty(){
            if(p>0){
                return false;
            }
            return true;
        }
};

int main(){
    stack<string> myStack;
    queue<string> output, line;
    string s;
    getline(cin, s);
    string el = "";
    for(int i=0; i<int(s.size()); i++){
        if(int(s[i])==32){
            if(el.size()>0){
                if(el == ","){
                    line.push(")");
                    line.push(el);
                    line.push("(");
                }else if( el == ")" || el == "("){
                    line.push(el);
                    line.push(el);
                }else{
                    line.push(el);
                }
                el = "";
            }
        }else{
            el=el+s[i];
        }
    }

    line.push(el);
    if(el==")"){
        line.push(")");
    }

    while(!line.empty()){
        string token = line.front();
        line.pop();
        if(isDigit(token)){
            output.push(token);
        }else if(token == "(" || token == "min" || token == "max"){
            myStack.push(token);
        }else if(token == ")"){
            while(!myStack.empty()){
                if(myStack.top()!="("){
                    output.push(myStack.top());
                    myStack.pop();
                }else{
                    myStack.pop();
                    break;
                }
            }
            if(!myStack.empty() && (myStack.top()=="min" || myStack.top()=="max")){
                output.push(myStack.top());
                myStack.pop();
            }
        }
        else if(token == "*" || token == "-" || token == "+" || token == "/"){
            while(!myStack.empty() && pr(myStack.top())>=pr(token)){
                output.push(myStack.top());
                myStack.pop();
            }
            myStack.push(token);
        }
    }   

    while(!myStack.empty()){
        output.push(myStack.top());
        myStack.pop();
    }

    stack<int> st;

    while(!output.empty()){
        string x = output.front();
        output.pop();
        if(isDigit(x)){
            st.push(int(x[0]-'0'));
        }else{
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            st.push(operation(x, a, b));
        }
    }
    
    cout << st.top();
    return 0;
}

bool isDigit(string s){
    string digits[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    for(string el : digits){
        if(s==el) return true;
    }
    return false;
}

int operation(string x, int a, int b){
    int res;
    if(x=="+") res=a+b;
    else if(x=="-") res=b-a;
    else if(x=="*") res=a*b;
    else if(x=="/") res=b/a;
    else if(x=="min"){
        if(a<b) res = a;
        else res = b;
    }
    else{
        if(a>b) res = a;
        else res = b;
    }
    return res;
}
