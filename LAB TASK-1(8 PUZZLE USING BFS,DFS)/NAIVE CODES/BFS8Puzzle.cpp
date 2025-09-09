// #include<bits/stdc++.h>
// using namespace std;
// int cnt=0;

// void check(vector<vector<int>>&puzzle,vector<vector<int>>goal,int i,int j,int x,int y,int n,int &depth,bool &found,set<vector<vector<int>>>&s){
//     // cout<<"here3"<<endl;
//     if(valid(x,y,n)){
//         swap(puzzle[i][j],puzzle[x][y]);
//         if(puzzle==goal){
//             found=true;
//             cout<<"We have found our answer on Count: "<<cnt<<"and Depth:"<<depth<<endl;
//             printVectorOfVector(puzzle);
//         }
//         else{
//             // cout<<"here4"<<endl;
//             if(s.find(puzzle)==s.end()){
//                 s.insert(puzzle);
//                 cnt++;
                
//             }
//         }
//         cout<<"Depth:"<<depth<<endl;
//         cout<<"Count:"<<cnt<<endl;
//         printVectorOfVector(puzzle);
//     }
//     return;
// }
// void BFSPuzzle(vector<vector<int>>&puzzle,vector<vector<int>>goal,int n,int i,int j,int &depth,bool &found,set<vector<vector<int>>>&s){
//     if(found){
//         return;
//     }
    
//     // 
    
//     // printVectorOfVector(puzzle);
//     vector<vector<int>>temp;
//     check(puzzle,goal,i,j,i+1,j,n,depth,found,s);
//     check(puzzle,goal,i,j,i-1,j,n,depth,found,s);
//     check(puzzle,goal,i,j,i,j+1,n,depth,found,s);
//     check(puzzle,goal,i,j,i,j-1,n,depth,found,s);
//     if(valid(i+1,j,n)){
//         temp=puzzle;
//         swap(temp[i][j],temp[i+1][j]);
//         if(s.find(temp)!=s.end()){
//             depth++;
//             BFSPuzzle(puzzle,goal,n,i+1,j,depth,found,s);
//             depth--;
//         }
//     }
//     if(valid(i-1,j,n)){
//         temp=puzzle;
//         swap(temp[i][j],temp[i-1][j]);
//         if(s.find(temp)!=s.end()){
//             depth++;
//             BFSPuzzle(puzzle,goal,n,i-1,j,depth,found,s);
//             depth--;
//         }
//     }
//     if(valid(i,j+1,n)){
//         temp=puzzle;
//         swap(temp[i][j],temp[i][j+1]);
//         if(s.find(temp)!=s.end()){
//             depth++;
//             BFSPuzzle(puzzle,goal,n,i,j+1,depth,found,s);
//             depth--;
//         }
//     }
//     if(valid(i,j-1,n)){
//         temp=puzzle;
//         swap(temp[i][j],temp[i][j-1]);
//         if(s.find(temp)!=s.end()){
//             depth++;
//             BFSPuzzle(puzzle,goal,n,i,j-1,depth,found,s);
//             depth--;
//         }
//     }

//     // cout<<"here4"<<endl;

// }

// int main(){
    

//     //randomized generation of numbers
    
//     vector<vector<int>>goal={{0,1,2},{3,4,5},{6,7,8}};
//     vector<vector<int>>initialPuzzle={{1,0,2},{3,4,5},{6,7,8}};
//     cout<<isSolvable(initialPuzzle)<<endl;
//     int depth=0,n=3;
//     bool found=false;
//     set<vector<vector<int>>>s;
//     if(!isSolvable(initialPuzzle)){
//         cout<<"The following puzzle is not solvable"<<endl;
//         printVectorOfVector(initialPuzzle);
//     }
//     BFSPuzzle(initialPuzzle,goal,n,1,1,depth,found,s);
//     return 0;
// }



#include<bits/stdc++.h>
using namespace std;


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

void solve8puzzleBFS(vector<vector<int>>puzzle,int i,int j,vector<vector<int>>goal){ 
    set<pair<vector<vector<int>>,pair<int,int>>>s;//puzzle, {i,j}
    queue<pair<vector<vector<int>>,pair<int,int>>>q;
    q.push({puzzle,{i,j}});
    pair<vector<vector<int>>,pair<int,int>>temp;
    vector<vector<int>>temp2;
    int level=0,cnt=0;
    while(!q.empty()){
        int size=q.size();
        while(size--){
        temp=q.front();
        q.pop();
        s.insert(temp);
        cnt++;
        if(temp.first==goal){
            cout<<"Level:"<<level<<endl;
            cout<<"Count:"<<cnt<<endl;
            cout<<"FOUND THE ANSWER"<<endl;
            printVectorOfVector(temp.first);
            return;
        }
        // if(temp.first!=goal){
        //     cout<<"Level:"<<level<<endl;
        //     cout<<"Count:"<<cnt<<endl;
        //     printVectorOfVector(temp.first);
        // }
        
        if(valid(temp.second.first+1,temp.second.second,3)){
            int x=temp.second.first;
            int y=temp.second.second;
            temp2=temp.first;
            swap(temp2[x][y],temp2[x+1][y]);
            if(s.find({temp2,{x+1,y}})==s.end()){
                q.push({temp2,{x+1,y}});
            }
        }
        if(valid(temp.second.first-1,temp.second.second,3)){
            int x=temp.second.first;
            int y=temp.second.second;
            temp2=temp.first;
            swap(temp2[x][y],temp2[x-1][y]);
            if(s.find({temp2,{x-1,y}})==s.end()){
                q.push({temp2,{x-1,y}});
            }
        }
        if(valid(temp.second.first,temp.second.second+1,3)){
            int x=temp.second.first;
            int y=temp.second.second;
            temp2=temp.first;
            swap(temp2[x][y],temp2[x][y+1]);
            if(s.find({temp2,{x,y+1}})==s.end()){
                q.push({temp2,{x,y+1}});
            }
        }
        if(valid(temp.second.first,temp.second.second-1,3)){
            int x=temp.second.first;
            int y=temp.second.second;
            temp2=temp.first;
            swap(temp2[x][y],temp2[x][y-1]);
            if(s.find({temp2,{x,y-1}})==s.end()){
                q.push({temp2,{x,y-1}});
            }
        }
        }
        level++;
    }
    return;
}


int main(){

    //case:1
    // vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    // vector<vector<int>>initialPuzzle={{1, 2, 3}, {4, 0, 5}, {6, 7, 8}};
    // if(!isSolvable(initialPuzzle)){
    //     cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    // }
    // else{
    //     solve8puzzleBFS(initialPuzzle,1,1,goal);
    // }

    //case:2
    // vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
    // vector<vector<int>>initialPuzzle={{1, 2, 3}, {5,4,0}, {7, 6, 8}}; //SEG FAULT ON MINE ONLY
    // if(!isSolvable(initialPuzzle)){ 
    //     cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    // }
    // else{
    //     solve8puzzleBFS(initialPuzzle,1,2,goal);
    // }



    int x,y;
    pair<vector<vector<int>>,pair<int,int>>temp=randomPuzzleGenerator();
    vector<vector<int>>puzzle=temp.first;
    x=temp.second.first;
    y=temp.second.second;
    printVectorOfVector(puzzle);
    // cout<<x<<" "<<y<<endl;
    vector<vector<int>>goal={{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

    if(!isSolvable(puzzle)){ 
        cout<<"IMPOSSIBLE TO SOLVE"<<endl;
    }
    else{
        solve8puzzleBFS(puzzle,x,y,goal);
    }
    
    

    return 0;
}