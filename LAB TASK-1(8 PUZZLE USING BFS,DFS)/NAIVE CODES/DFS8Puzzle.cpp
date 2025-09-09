#include<bits/stdc++.h>
using namespace std;

int cnt=0;

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
    for(int i=0;i<=8;i++){
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

void solve8puzzleDFS(vector<vector<int>>&puzzle,int i,int j,vector<vector<int>>&goal,set<vector<vector<int>>>&s,bool &found){
    // cout<<"here1"<<endl;
    if(puzzle==goal){
        printVectorOfVector(puzzle);
        cout<<"Count:"<<cnt<<endl;
        cout<<"Found the answer"<<endl;
        found=true;
        return;
    }
    cnt++;
    // cout<<"here2"<<endl;
    // printVectorOfVector(puzzle);
    // cout<<"Count:"<<cnt<<endl;
    
    vector<vector<int>>temp;
    if(valid(i+1,j,3)){
        temp=puzzle;
        swap(temp[i][j],temp[i+1][j]);
        if(s.find(temp)==s.end()){
            s.insert(temp);
            solve8puzzleDFS(temp,i+1,j,goal,s,found);
            if(found)return;
        }
    }
    if(valid(i-1,j,3)){
        temp=puzzle;
        swap(temp[i][j],temp[i-1][j]);
        if(s.find(temp)==s.end()){
            s.insert(temp);
            solve8puzzleDFS(temp,i-1,j,goal,s,found);
            if(found)return;
        }
    }
    if(valid(i,j+1,3)){
        temp=puzzle;
        swap(temp[i][j],temp[i][j+1]);
        if(s.find(temp)==s.end()){
            s.insert(temp);
            solve8puzzleDFS(temp,i,j+1,goal,s,found);
            if(found)return;
        }
    }
    // cout<<"here3"<<endl;
    if(valid(i,j-1,3)){
        temp=puzzle;
        swap(temp[i][j],temp[i][j-1]);
        if(s.find(temp)==s.end()){
            s.insert(temp);
            solve8puzzleDFS(temp,i,j-1,goal,s,found);
            if(found)return;
        }
    }
    
    return;
}

int main(){
    //CASE:1
    // vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    // vector<vector<int>>initialPuzzle={{1, 2, 3}, {4,5,6}, {7, 0, 8}};

    // if(!isSolvable(initialPuzzle)){ 
    //     cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    // }
    // else{
    //     set<vector<vector<int>>>s;
    //     bool found=false;
    //     solve8puzzleDFS(initialPuzzle,2,1,goal,s,found);
    // }

    //CASE:2
    // vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    // vector<vector<int>>initialPuzzle={{1, 2, 3}, {5,4,0}, {7, 6, 8}}; //SEG FAULT ON MINE ONLY
    // if(!isSolvable(initialPuzzle)){ 
    //     cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    // }
    // else{
    //     set<vector<vector<int>>>s;
    //     bool found=false;
    //     solve8puzzleDFS(initialPuzzle,1,2,goal,s,found);
    // }
    int x,y;
    pair<vector<vector<int>>,pair<int,int>>temp=randomPuzzleGenerator();
    vector<vector<int>>puzzle=temp.first;
    x=temp.second.first;
    y=temp.second.second;
    printVectorOfVector(puzzle);
    // cout<<x<<" "<<y<<endl;
    vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    // printVectorOfVector(puzzle);
    if(!isSolvable(puzzle)){ 
        cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    }
    else{
        set<vector<vector<int>>>s;
        bool found=false;
        solve8puzzleDFS(puzzle,x,y,goal,s,found);
    }
    return 0;
}