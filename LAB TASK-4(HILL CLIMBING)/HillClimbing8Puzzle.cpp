#include<bits/stdc++.h>
using namespace std;


vector<vector<int>>goal={{0,1,2},{3,4,5},{6,7,8}};
unordered_map<int,pair<int,int>>loc{{0,{0,0}},{1,{0,1}},{2,{0,2}},{3,{1,0}},{4,{1,1}},{5,{1,2}},{6,{2,0}},{7,{2,1}},{8,{2,2}}};


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

int costManhatten(vector<vector<int>>&puzzle){
    int cost=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cost+=abs(i-loc[puzzle[i][j]].first)+abs(j-loc[puzzle[i][j]].second);
        }
    }
    return cost;
}

vector<int>X={-1,1,0,0};
vector<int>Y={0,0,1,-1};

void hillClimbing8Puzzle(vector<vector<int>>&puzzle,int x,int y){
    int bestCost=costManhatten(puzzle);
    vector<vector<int>>bestState=puzzle;
    vector<vector<int>>current=puzzle;
    for(int i=0;i<20000;i++){
        int z=rand()%4;
        int newX=x+X[z];
        int newY=y+Y[z];

        if(valid(newX,newY,3)){
            vector<vector<int>>newPuzzle=current;
            swap(newPuzzle[x][y],newPuzzle[newX][newY]);
            if(costManhatten(newPuzzle)<bestCost){
                bestCost=costManhatten(newPuzzle);
                x=newX;y=newY;
                bestState=newPuzzle;
                current=bestState;
            }

        }
    }
    printVectorOfVector(bestState);
    cout<<bestCost<<endl;
    return;
    }

int main(){


    ios_base::sync_with_stdio(false);
    cin.tie(0);


    vector<vector<int>>puzzle={{1,4,2},{3,0,5},{6, 7, 8}};
    if(isSolvable(puzzle)){
        hillClimbing8Puzzle(puzzle,1,1);
    }
    else{
        printVectorOfVector(puzzle);
        cout<<"IMPOSSIBLE TO SOLVE";
    }

    return 0;
}