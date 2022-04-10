#include <iostream>
#include <vector>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.11
*난이도 : G1
*개인 풀이 시간 : 1.5hour
*개인 난이도 : 2/5 
*분류 : 스택, 자료구조
*풀이 : 주석 참조

*느낀점 : 히스토그램과 비슷함.
         스택을 사용하면서 같은 키를 처리하는 로직이 주요했음
         스택의 위에서부터 찾는 방식으로 했을때 시간 초과 발생
         => 스택 내에 큰 순서대로 정렬이 되어있기 때문에 이분 탐색을 사용한 Lower_bound로 같은 키의 수를 찾아냄
*/

int N;
vector<int> st;
typedef long long int lli;
lli cnt;

int lowerBound(int n){
	int ceiling = st.size()-1;
	int bottom = 0;
    //한번도 실행되지 않은 경우 Return -1
	int ret=-1;
	while(bottom <= ceiling){
		int mid = (ceiling + bottom)/2;
		if(st[mid] <= n){
			ceiling = mid - 1;
			ret = mid;
		}
		else
			bottom = mid + 1;
	}
	return ret;
}
int main(){
    cin>>N;
    int a;
    while(N--){
        scanf("%d",&a);
        //새로 들어온 키 보다 낮은 것은 모두 Pop, 그 과정에서 한쌍이 만들어짐 => cnt++
        while(!st.empty() && st.back() < a){
            st.pop_back();
            ++cnt;
        }
        //같은 키가 몇개 있는지 체크
    	int lb = lowerBound(a);
        //같은게 하나라도 있은 lb != -1임
    	if(lb != -1) 
            //찾은 lowerbound의 마지막에서 idx까지의 크기를 cnt에 더하기
    		cnt += st.size() - lb;
        //lb == 0인 경우는 스택에 다른 키가 있고, 같은 것으로 가득 찬 경우가 아닐때
        // 7 2 2 2 2 이렇게 키가 있는 경우 Lowerbound를 통해 같은 키를 모두 더했음
        // 여기서 새로 들어오는 2랑 가장 앞의 7이랑 볼 수 있기 때문에 가장 앞에 다른 것이 있는지 없는지 알아야함
        // lb == 0 이면 같은 것으로 가득 차있기 때문에 ++cnt 하면 안됨
        // 그리고 스택이 비어 있는 경우도 ++cnt 불가능
        if(st.size() && lb != 0)
        	cnt++;
        st.push_back(a);
    }
    cout<<cnt<<endl;
}