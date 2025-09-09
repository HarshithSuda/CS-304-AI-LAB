#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>CreateGraph(){
    int n=10;
    vector<vector<int>>g(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            g[i][j]=rand()%9; //w=0(represents no edge)
        }
    }
    return g;
}

bool isConnected(vector<vector<int>>&graph){
    int n=graph.size();
    for(int i=0;i<n;i++){
        bool flag=false;
        for(int j=0;j<n;j++){
            if(graph[i][j]){
                flag=true;
            }
        }
        if(!flag){
            return false;
        }
    }
    return true;
}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    vector<vector<int>>g=CreateGraph();
    cout<<"Is the graph Connected:"<<isConnected(g)<<endl;
    for(int i=0;i<g.size();i++){
        cout<<"ith row:"<<i<<endl;
        for(int j=0;j<g.size();j++){
            cout<<g[i][j]<<" ";
        }
        cout<<endl;
    }
    return 0;
}