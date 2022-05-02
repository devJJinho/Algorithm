#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#define INF 99999
#define MAX 101

using namespace std;

int R , C , K;
int mWidth , mHeight;
int map[MAX][MAX];

void calRow(){
    int nextWidth = 0 ;
    for(int i = 0 ; i < mHeight ; i++){
        unordered_map<int,int> mp;
        vector<pair<int,int> > arr;
        for(int j = 0 ; j < mWidth ; j++){
            int num = map[i][j];
            if(num == 0) continue;
            if(mp.find(num) == mp.end()){
                mp.insert(make_pair(num , 1));
            }
            else
                mp[num]++;
        }
        unordered_map<int,int>::iterator iter;
        for(iter = mp.begin() ; iter != mp.end() ; iter++){
            arr.push_back(make_pair(iter->second , iter->first));
        }
        sort(arr.begin() , arr.end());
        nextWidth = max(nextWidth , (int)(arr.size() * 2 > 100 ? 100 : arr.size() * 2));
        int k;
        for(k = 0 ; k < arr.size() * 2 && k < 100 ; k++){
            if(k % 2) map[i][k] = arr[k / 2].first;
            else map[i][k] = arr[k / 2].second;
        }
        for( ; k < mWidth ; k++)
            map[i][k] = 0;
    }
    mWidth = max(mWidth , nextWidth);
}

void calCol(){
    int nextHeight = 0 ;
    for(int j = 0 ; j < mWidth ; j++){
        unordered_map<int,int> mp;
        vector<pair<int,int> > arr;
        for(int i = 0 ; i < mHeight ; i++){
            int num = map[i][j];
            if(num == 0) continue;
            if(mp.find(num) == mp.end()){
                mp.insert(make_pair(num , 1));
            }
            else
                mp[num]++;
        }
        unordered_map<int,int>::iterator iter;
        for(iter = mp.begin() ; iter != mp.end() ; iter++){
            arr.push_back(make_pair(iter->second , iter->first));
        }
        sort(arr.begin() , arr.end());
        nextHeight = max(nextHeight , (int)(arr.size() * 2 > 100 ? 100 : arr.size() * 2));
        int k;
        for(k = 0 ; k < arr.size() * 2 && k < 100 ; k++){
            if(k % 2) map[k][j] = arr[k / 2].first;
            else map[k][j] = arr[k / 2].second;
        }
        for( ; k < mHeight ; k++)
            map[k][j] = 0;
    }
    mHeight = max(mHeight , nextHeight);
}

void func(){
    if(mHeight >= mWidth)
       calRow();
    else
        calCol();
    for(int i = 0 ; i < mHeight ; i++){
        for(int j = 0 ; j < mWidth ; j++){
            cout<<map[i][j] << " ";

        }
        cout<<endl;
    }
    cout<<"------"<<endl;
}
bool check(){
    if(mWidth >= C && mHeight >= R)
        return map[R - 1][C - 1] == K;
    return false;
}
int main(){
    freopen("input.txt" , "r" , stdin);
    cin >> R >> C >> K;
    mWidth = mHeight = 3;
    for(int i = 0 ; i < 3 ; i++){
        for(int j = 0 ; j < 3 ; j++)
            cin >> map[i][j];
    }
    int cnt = 0 ;
    while(true){
        if(check()) break;
        if(++cnt == 101) break;
        // cout<<mWidth<<" "<<mHeight<<endl;
        func();
    }
    cout << (cnt == 101 ? -1 : cnt) << endl;
}
