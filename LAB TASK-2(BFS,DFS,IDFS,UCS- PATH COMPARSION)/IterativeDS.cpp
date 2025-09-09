#include<bits/stdc++.h>

using namespace std;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;




vector<vector<int>>CreateGraph(){
    int n=1000;
    vector<vector<int>>g(n,vector<int>(n));
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            g[i][j]=rand()%1000; //w=0(represents no edge)
            g[j][i]=g[i][j];
        }
    }
    return g;
}










int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    vector<vector<int>>g=CreateGraph();
    // vector<vector<int>>storedGraph=g;
    // printVectorOfVector(g);
    double t;
    int edgesExplored,pathCost;
    unordered_set<int>s;
    // cout<<"here2"<<endl;

    



    return 0;

}