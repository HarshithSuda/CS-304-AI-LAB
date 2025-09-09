#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>goal={{1,2,3},{4,5,6},{7,8,0}};

struct Node{
    Node* parent;
    vector<vector<int>>puzzle;
    int x,y;
    int mismatchings;
    int level;
};

int computeMismatchings(vector<vector<int>>&puzzle){
    int mismatchings=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(puzzle[i][j]!=goal[i][j])mismatchings++;
        }
    }
    return mismatchings;
}
Node* createNewNode(Node *parentNode,int newX,int newY){
    Node* node=new Node();
    if(!node){
        return NULL;
    }
    node->parent=parentNode;
    node->x=newX;
    node->y=newY;
    node->level=parentNode->level+1;
    vector<vector<int>>temp=parentNode->puzzle;
    swap(temp[parentNode->x][parentNode->y],temp[newX][newY]);
    node->puzzle=temp;
    node->mismatchings=computeMismatchings(temp);
    return node;

}
pair<vector<vector<int>>,pair<int,int>> randomPuzzleGenerator(){
    srand(time(NULL));
    vector<int>arr={0,1,2,3,4,5,6,7,8};
    for(int i=0;i<100;i++){
        int m=rand()%9;
        int n=rand()%9;
        swap(arr[m],arr[n]);
    }
    vector<int>m1(arr.begin(),arr.begin()+3);
    vector<int>m2(arr.begin()+3,arr.begin()+6);
    vector<int>m3(arr.begin()+6,arr.begin()+9);
    vector<vector<int>>ans={m1,m2,m3};
    
    int z=0;
    for(int i=0;i<8;i++){
        if(arr[i]==0){
            z=i;
            // cout<<"value of z:"<<z<<endl;
            break;
        }
    }
    // cout<<"value of z/3:"<<z/3<<endl;
    // cout<<"value of z%3:"<<z%3<<endl;
    return {ans,{z/3,z%3}};
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
bool valid(int x,int y,int n){
    if(x>=0 && y>=0 && x<n && y<n){
        return true;
    }
    return false;
}



struct comp{
    bool operator()(const Node* lhs,const Node* rhs)const{
        return (lhs->mismatchings+lhs->level)>(rhs->mismatchings+rhs->level);
    }
};
void BranchAndBound8Puzzle(vector<vector<int>>&puzzle,int i,int j){
    set<vector<vector<int>>>s;
    priority_queue<Node*,vector<Node*>,comp>q;
    int cnt=0;
    Node* node=new Node();
    node->puzzle=puzzle;
    node->x=i;
    node->y=j;
    node->parent=NULL;
    node->mismatchings=computeMismatchings(puzzle);
    node->level=0;
    vector<int>X={-1,1,0,0};
    vector<int>Y={0,0,-1,1};
    s.insert(puzzle);
    q.push(node);
    while(!q.empty()){
        Node* mainNode=q.top();
        q.pop();
        s.insert(mainNode->puzzle);
        cnt++;
        if(mainNode->puzzle==goal){
            cout<<"Found the answer at count:"<<cnt<<endl;
            while(!q.empty()){
                Node* n=q.top();
                q.pop();
                delete n;
            }
            return;
        }
        for(int i=0;i<4;i++){
        if(valid(mainNode->x+X[i],mainNode->y+Y[i],3)){
            // cout<<"here1"<<endl;
            vector<vector<int>>tempPuzzle=mainNode->puzzle;
            swap(tempPuzzle[mainNode->x][mainNode->y],tempPuzzle[mainNode->x+X[i]][mainNode->y+Y[i]]);
            if(s.find(tempPuzzle)==s.end()){
                // cout<<"here2"<<endl;
                Node* tempNode=createNewNode(mainNode,mainNode->x+X[i],mainNode->y+Y[i]);
                q.push(tempNode);
            }
        }
    }
        delete mainNode;
    }
    return;
}
int main(){
    int x,y;
    pair<vector<vector<int>>,pair<int,int>>temp=randomPuzzleGenerator();
    vector<vector<int>>puzzle=temp.first;
    x=temp.second.first;
    y=temp.second.second;
    // // printVectorOfVector(puzzle);

    // vector<vector<int>>initialPuzzle={{1, 2, 3}, {5,4,0}, {7, 6, 8}};
    // int x=1,y=2;
    if(!isSolvable(puzzle)){ 
        printVectorOfVector(puzzle);
        cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    }
    else{
        printVectorOfVector(puzzle);
        BranchAndBound8Puzzle(puzzle,x,y);
    }

}