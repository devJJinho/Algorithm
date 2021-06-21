#include <vector>
#include <algorithm>

/*
@author  :  Jinho Jeong
@date    :  2021.06.21

*난이도 : Level 2
*개인 풀이 시간 : 3hr 
*개인 난이도 : 2/5
*분류 : 이분 탐색
*풀이 : 최악의 시간(가장 느린 직원*총 입국자)을 최대값으로 잡고 이분 탐색을 통해 최소 시간을 찾는다.
*느낀점 : 정렬된 곳에서의 이분 탐색이 아니기 때문에 정확히 한 배열의 값을 찾고 끝나지 않는다.
        답이 가능한 경우에 대해서 answer을 업데이트하는 것이 주요했다.
        
*/

using namespace std;

long long solution(int n, vector<int> times) {
    long long answer = 0;
    int max=*max_element(times.begin(),times.end());

    long long start = 1;
    long long end = (long long) max* n;
    long long mid;

    while(start <= end) {
        mid = (start + end) / 2;
        long long cnt = 0;
        for(auto k: times)
            cnt+=mid/k;

        /*
        if(cnt==n) break;
        위 코드는 위험하다. 최소값 보장이 없다.
        */

       // (cnt>n) else 로 할 경우 오답이다. (cnt>=n) else로 해야됨.
        if(cnt < n) {
            start = mid + 1;
        }
        else {
            answer = mid;
            end = mid - 1;
        }
    }

    return answer;
}