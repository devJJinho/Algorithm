#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

/*
@author  :  Jinho Jeong
@date    :  2021.06.23

*난이도 : Level 4
*개인 풀이 시간 : 4hr 
*개인 난이도 : 3/5
*분류 : 이분 탐색
*풀이 : 가능한 돌 조합을 만들고 거기서 간격을 구하는 것이 아닌, 
        특정 간격(mid)이 최소값이 되려면 돌 몇개를 지워야되는지를 찾는다.
        Brute force를 사용하지만 이분 탐색을 사용해서 효율성을 높힘.
*느낀점 : 이분 탐색의 조건을 정확히 이해해야 된다.
        
*/

using namespace std;
vector<int> dis;
int solution(int distance, vector<int> rocks, int n) {
    rocks.push_back(distance);
    int high=distance;
    int answer = 0;
    int low=1;
    int mid;
    
    sort(rocks.begin(),rocks.end());
    
    while(low<=high){
        int cnt=0;
        int prev=0;
        //미드가 가능한 최대값
        mid=(high+low)/2;
        for(int i=0;i<rocks.size();i++){
            if(rocks[i]-prev<mid) cnt++;
            else{
                prev=rocks[i];
            }
        }
        /*
        cnt>n의 경우 => mid값이 최소간격이 되기 위해 n 보다 많은 돌을 제거했다. 
        => mid(최소간격을) 줄인다. => cnt 감소
        cnt>n 에서 cnt==n 조건을 추가하면 mid값이 최소일 때 cnt==n임
        */
        if(cnt>n){
            high=mid-1;
        }
        /*
        cnt<n의 경우 => mid값이 최소간격이 되기 위해 n 보다 적을 돌을 제거했다. 
        => mid(최소간격을) 늘린다. => cnt 증가
        cnt<n 에서 cnt==n 조건을 추가하면 mid값이 최대일 때 cnt==n임
        */

        /*
        양 조건 중에서 에서 우리는 '최소값이 최대인 경우'를 찾기 때문에 
        mid 범위를 올려서 다시 탐색하는 else문에 answer=answer<mid?mid:answer을 삽입.
        */
        else{
            answer=answer<mid?mid:answer;
            low=mid+1;
        }
    }
    return answer;
}