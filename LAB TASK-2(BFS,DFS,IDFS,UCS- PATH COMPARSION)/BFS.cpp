#include<bits/stdc++.h>
#include<chrono>
using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


struct Node{
    Node* parent;
    int cost;
    int nodeNumber;
};

Node* initNode(int start,int cost){
    Node* node=new Node();
    node->cost=cost;
    node->nodeNumber=start;
    node->parent=NULL;
    return;
}

void RecursivePrintPath(Node* curr){
    vector<int>path;
    while(curr){
        path.push_back(curr->nodeNumber);
        curr=curr->parent;
    }
    for(int i=path.size()-1;i>0;i--){
        cout<<path[i]<<"->";
    }
    cout<<path[0]<<endl;
    // cout<<endl;
    return;
}

void BFS(vector<vector<int>>&graph,int start,int goal,double &timeTaken,int &totalCost,int &pathCost){
    totalCost=0;
    unordered_map<int,Node*>m;
    // unordered_set<int>expanded;
    queue<Node*>q;
    Node* startNode=initNode(start,0);
    q.push(startNode);
    m.insert({start,startNode});
    auto t1=high_resolution_clock::now();
    while(!q.empty()){
        Node* curr=q.front();
        q.pop();
        // if(expanded.find(curr->nodeNumber)!=expanded.end()){
        //     continue;
        // }
        if(curr->nodeNumber==goal){
            auto t2=high_resolution_clock::now();
            duration<double,std::milli>mil_double=t2-t1;
            timeTaken=mil_double.count();
            pathCost=curr->cost;
            RecursivePrintPath(curr);
            return;
        }
        for(int i=0;i<graph.size();i++){
            if(graph[curr->nodeNumber][i] && (m.find(i)==m.end()|| m[i]->cost>curr->cost+graph[curr->nodeNumber][i])){
                if(m.find(i)==m.end()){
                    Node* node=new Node();
                    node->nodeNumber=i;
                    m[i]=node;
                }
                m[i]->parent=curr;
                m[i]->cost=curr->cost+graph[curr->nodeNumber][i];
                totalCost+=graph[curr->nodeNumber][i];
                q.push(m[i]);
            }
        }
        // expanded.insert(curr->nodeNumber);
    }
    return;
}