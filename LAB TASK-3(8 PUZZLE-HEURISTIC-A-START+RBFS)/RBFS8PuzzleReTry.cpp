#include<bits/stdc++.h>
using namespace std;

#define INF 1e9

vector<int>goal={0,1,2,3,4,5,6,7,8};
void printVectorOfVector(vector<vector<int>>&v){
    for(int i=0;i<v.size();i++){
        for(int j=0;j<v[0].size();j++){
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
struct Node{
    Node* parent;
    vector<int>state;
    int pathCost;
    int TotalCost; //pathcost+heuristic

    Node(vector<int>state,Node* parent,int pathcost){
        this->state=state;
        this->parent=parent;
        this->pathCost=pathcost;
        this->TotalCost=pathcost;
    }
    int heuristic(){
        int cost=0;
        for(int i=0;i<state.size();i++){
            if(state[i]==0){
                continue;
            }
            cost+=abs(i/3-state[i]/3)+abs(i%3-state[i]%3);
        }
        return cost;
    }
    vector<Node*>Neighbours(){
        int zeroPos=find(state.begin(),state.end(),0)-state.begin();
        vector<Node*>neigh;
        int x=zeroPos/3;
        int y=zeroPos%3;
        vector<int>X={-1,1,0,0};
        vector<int>Y={0,0,1,-1};
        int nx,ny;
        for(int i=0;i<4;i++){
            nx=x+X[i];
            ny=y+Y[i];
            if(nx>=0 && ny>=0 && nx<=2 && ny<=2){
                vector<int>temp=state;
                swap(temp[3*x+y],temp[3*nx+ny]);
                Node *node=new Node(temp,this,pathCost+1);
                neigh.push_back(node);
            }
        }
        return neigh;
    }
};

struct comp{
    bool operator()(const Node*a,const Node*b){
        return a->TotalCost>b->TotalCost;
    }
};

void IntegerVectorToMatrix(vector<int>&v){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cout<<v[3*i+j]<<" ";
        }
        cout<<endl;
    }
    return;
}
void RecursivePrintPath(Node* curr){
    vector<vector<int>>path;
    while(curr){
        path.push_back(curr->state);
        curr=curr->parent;
    }
    
    for(int i=path.size()-1;i>0;i--){
        IntegerVectorToMatrix(path[i]);
        cout<<"->";
    }
    IntegerVectorToMatrix(path[0]);
    // cout<<endl;
    return;
}
pair<Node*,int>RBFS(Node* node,int fLimit){
    if(node->state==goal){
        RecursivePrintPath(node);
        return{node,0};
    }
    vector<Node*>neigh=node->Neighbours();
    vector<Node*>Successors;
    for(auto &s : neigh){
        s->TotalCost=max(s->TotalCost,node->TotalCost);
        Successors.push_back(s);
    }
    sort(Successors.begin(),Successors.end(),comp());
    while(true){
        cout<<"here"<<endl;
        Node* best=Successors[0];
        if(best->TotalCost>fLimit){
            return {NULL,best->TotalCost};
        }
        int alt = (Successors.size() > 1)?Successors[1]->TotalCost:INF;
        // Node* alt=Successors[1];
        auto result=RBFS(best,min(alt,fLimit));
        if(result.first!=NULL){
            return result;
        }
        Successors[0]->TotalCost=result.second;
    }
    
}


int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);


    // SOLVABLE CASE
    vector<vector<int>>p={{1, 2, 3},{4, 0, 6},{7, 5, 8}};
    if(isSolvable(p)){
        vector<int>q={1, 2, 3,4, 0, 6,7, 5, 8};
        Node* node=new Node(q,NULL,0);
        pair<Node*,int>j=RBFS(node,INF);
    }
    else{
        printVectorOfVector(p);
        cout<<"IMPOSSIBLE TO SOLVE";
    }
    return 0;
}