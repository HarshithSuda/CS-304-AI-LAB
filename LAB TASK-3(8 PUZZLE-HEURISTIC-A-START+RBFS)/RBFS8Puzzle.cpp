#include<bits/stdc++.h>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;

vector<vector<int>>goal={{0,1,2},{3,4,5},{6,7,8}};
unordered_map<int,pair<int,int>>m{{0,{0,0}},{1,{0,1}},{2,{0,2}},{3,{1,0}},{4,{1,1}},{5,{1,2}},{6,{2,0}},{7,{2,1}},{8,{2,2}}};
struct Node{
    Node* parent;
    int x,y;
    vector<vector<int>>state;
    int cost;
    int g;
};

int manhattenDistance(vector<vector<int>>&state){
    int cost=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(state[i][j] == 0) continue;
            cost+=abs(i-m[state[i][j]].first)+abs(j-m[state[i][j]].second);
        }
    }
    return cost;
}
Node *createRoot(vector<vector<int>>state,int x,int y){
    Node* node=new Node();
    node->parent=NULL;
    node->x=x;node->y=y;
    node->state=state;
    node->cost=manhattenDistance(state);
    node->g=0;
    return node;
}
void printVectorOfVector(vector<vector<int>>&v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[0].size();j++){
            // cout<<"value of i:"<<i<<"value of j:"<<j<<" ";
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    return;
}

bool isSolvable(vector<vector<int>>&puzzle){
    vector<int>v;
    for(int i=0;i<puzzle.size();i++){
        for(int j=0;j<puzzle[0].size();j++){
            v.push_back(puzzle[i][j]);
        }
    }
    int invcnt=0;
    for(int i=0;i<8;i++){
        for(int j=i+1;j<9;j++){
            if(v[i] && v[j] && v[i]>v[j]){
                invcnt++;
            }
        }
    }
    return (invcnt%2)==0;
}


Node *createNode(Node* parent,int x,int y){
    Node* node=new Node();
    vector<vector<int>>temp=parent->state;
    node->x=x;node->y=y;
    swap(temp[x][y],temp[parent->x][parent->y]);
    node->state=temp;
    node->parent=parent;
    node->g=parent->g+1;
    node->cost=manhattenDistance(temp)+node->g;
    return node;
}


bool valid(int x,int y,int n){
    if(x>=0 && y>=0 && x<n && y<n){
        return true;
    }
    return false;
}
bool sameState(vector<vector<int>>&a,vector<vector<int>>&b){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(a[i][j]!=b[i][j]){
                return false;
            }
        }
    }
    return true;
}

void backtrackSolution(Node* node){
    vector<vector<vector<int>>>v;
    while(node){
        v.push_back(node->state);
        node=node->parent;
    }
    reverse(v.begin(),v.end());
    for(int i=0;i<v.size();i++){
        printVectorOfVector(v[i]);
        if(i!=v.size()-1){
            cout<<"Next->"<<endl;
        }
    }
    return;
}
vector<Node*> neighbours(Node* node){
    vector<int>X={1,-1,0,0};
    vector<int>Y={0,0,1,-1};
    vector<Node*>res;
    for(int i=0;i<4;i++){
        int newX=node->x+X[i];
        int newY=node->y+Y[i];
        if(valid(newX,newY,3)){
            Node* temp=createNode(node,newX,newY);
            if(node->parent && sameState(temp->state,node->parent->state)){
                delete temp; continue;
            }
            res.push_back(temp);
            
        }
    }
    return res;
}


struct comp{
    bool operator()(const Node* a,const Node* b)const{
        return a->cost>b->cost;
    }
};


pair<Node*,int> RBFSPuzzle(Node* node,int flimit){
    if(goal==node->state){
        backtrackSolution(node);
        cout<<"Found solution"<<endl;
        return {node,flimit};
    }
    priority_queue<Node*,vector<Node*>,comp>successors;
    for(auto &x : neighbours(node)){
        x->cost=max(x->cost,node->cost);
        successors.push(x);
    }
    if(successors.empty()){
        return {NULL,INT_MAX};
    }
    
    while(true){
        if(successors.empty()){
            return {NULL,INT_MAX};
        }
        
        Node* best=successors.top();
        int bestf=best->cost;
        successors.pop();
        // cout<<"current state"<<endl;
        // printVectorOfVector(best->state);
        if(bestf>flimit){
            return {NULL,bestf};
        }
        int alternativeCost = successors.empty() ? INT_MAX : successors.top()->cost;
        auto result=RBFSPuzzle(best,alternativeCost);
        if(result.first!=NULL){
            return result;
        }
        best->cost=result.second;
        successors.push(best);
    }
    return {NULL,flimit};
}


int main(){


    
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    auto t1=high_resolution_clock::now();
    vector<vector<int>>p={{1, 4, 2},{3, 7, 5},{6,8,0}};
    if(isSolvable(p)){
        Node* node=createRoot(p,2,2);
        RBFSPuzzle(node,INT_MAX);
    }
    else{
        printVectorOfVector(p);
        cout<<"IMPOSSIBLE TO SOLVE";
    }

    auto t2=high_resolution_clock::now();
    duration<double,std::milli>mil_double=t2-t1;
    double timeTaken=mil_double.count();
    cout<<"Time Taken for RBFS* : "<<timeTaken<<" milliseconds"<<endl;

   

    return 0;
}