#include<bits/stdc++.h>
using namespace std;

int heuristic(vector<int>&queen){
    int cost=0;
    int n=queen.size();
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(queen[i]==queen[j] || abs(i-j)==abs(queen[i]-queen[j])){
                cost++;
            }
        }
    }
    return cost;
}


vector<int> hillClimbing8Queens(vector<int>&queen){
    int bestCost=heuristic(queen);
    vector<int>bestBoard=queen;
    vector<int>current=queen;
    for(int i=0;i<550000;i++){
        int x=rand()%8;
        int y=rand()%8;
        int previousValueX=current[y];
        current[y]=x;
        if(heuristic(current)<bestCost){
            bestCost=heuristic(current);
            bestBoard=current;
            continue;
        }
        current[y]=previousValueX;
    }
    cout<<"COST:"<<heuristic(bestBoard)<<endl;
    return bestBoard;
}
void printVector(vector<int>&v){
    for(auto &x : v){
        cout<<x<<" ";
    }
    cout<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    // srand(time(NULL));
    vector<int>result;
    vector<int>board(8);
    int ans=INT_MAX;
    for(int i=0;i<8;i++){
        board[i]=rand()%8;
    }
    result=hillClimbing8Queens(board);
    printVector(result);


    return 0;
}