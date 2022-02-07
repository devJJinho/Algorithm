#include <iostream>
#include <vector>
#define SWAP(a,b,t) (((t)=(a)),((a)=(b)),((b)=(t)))
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.02.07

*난이도 : G3
*개인 풀이 시간 : 3hr
*개인 난이도 : 2/5 
*분류 : 백트래킹, 그리디, 재귀
*풀이 : 그리디를 베이스로 작성한 이유 : 
        가장 큰 수는 가장 높은 곳에 가는게 무조건 좋음.
        나중을 위해 현재 희생할게 없다고 생각함. 
        큰 수는 한자리라도 더 높은 곳에 있는게 나음.

        => 큰 수가 여러개일 경우, 이때부터 경우의 수가 생김 => 백트래킹으로 전부 순회

*느낀점 : 전체 로직은 신기하게도 맞았지만 세세한 곳에서 실수가 있었음.
        백트래킹을 포함한 재귀 구조는 수월하게 짤 수 있었음.
        그래프 탐색 또는 정렬 알고리즘으로 다시 풀 용의가 있음.

*디버깅 순서 : 
        1. (문제) 같은 수가 나왔을때 아래부터 바꿨음 (해결) 백트래킹으로 같은 수 내에서 모두 swap하고 최대값만 보관
        2. (문제) 3자리수 이상 수에서 첫자리 외에 모두 0이면 -1처리 함. (해결) 100000 4 의 경우 100000이 나와야함. 0,0 사이에서 switching도 가능
        3. (문제) 같은 수가 짝수일때만 생각함 (해결) 짝수가 아니라 2개 이상이면 됨
*/

int num[7];
int res[7];
int digitCnt[10];
int len;
pair<int,vector<int>> findMax(int startIndex){
    int max=0;
    vector<int> indexs;
    for(int i=startIndex;i>=0;i--){
        if(num[i]>=max) max=num[i];
    }
    for(int i=0;i<=startIndex;i++)
        if(num[i]==max) indexs.push_back(i);
    return {max,indexs};
}

void recul(int k,int start){
    if(start<=0||!k){
        if(k){
            bool hasEvenNum=false;
            for(int i=1;i<10;i++)
                if(digitCnt[i]>=2){
                    hasEvenNum=true; break;
                }
            if(!hasEvenNum){
                int temp;
                if(k%2) SWAP(num[0],num[1],temp);
            }
        }
        bool isBigger=false;
        for(int i=len-1;i>=0;i--){
            if(num[i]<res[i]) break;
            if(num[i]>res[i]) {
                isBigger=true;
                break;
            }
        }
        if(isBigger){
            for(int i=len-1;i>=0;i--)
                res[i]=num[i];
        }
        return;
    }
    pair<int,vector<int>> res=findMax(start);
    if(res.first==num[start]){
        recul(k,start-1);
        return;
    }
    int temp;
    for(int index:res.second){
        SWAP(num[start],num[index],temp);
        recul(k-1,start-1);
        SWAP(num[start],num[index],temp);
    }
}

int main(){
    int n,k;
    cin>>n>>k;
    int index=0;
    while(n>0){
        num[index]=n%10;
        digitCnt[num[index]]++;
        n/=10;
        index++;
        len++;
    }
    if(len==1||(len==2&&digitCnt[0]==1)){
       cout<<"-1"<<endl;
       return 0;
    }
    recul(k,len-1);
    for(int i=len-1;i>=0;i--)
        cout<<res[i];
}




// 아래 코드와 로직은 같으나 코드가 완성도가 완전히 다름. 다시 풀어볼 필요가 있음


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

int ans;
char str[10];

void go(int idx, int n, int k) {
	if (idx >= n || k == 0) {
		if (k & 1) {
			int cnt[10]{}, flg = 0;
			for (int i = 0; str[i]; ++i)
				if (++cnt[str[i] - 48] == 2) flg = 1;

			if (flg) ans = max(ans, atoi(str));
			else {
				swap(str[idx - 1], str[idx - 2]);
				ans = max(ans, atoi(str));
				swap(str[idx - 1], str[idx - 2]);
			}
		}
		else ans = max(ans, atoi(str));
		return;
	}

	for (int i = idx + 1; i < n; ++i) {
		if (idx == i || idx == 0 && str[i] == '0') continue;
		swap(str[idx], str[i]);
		go(idx + 1, n, k - 1);
		swap(str[idx], str[i]);
	}

	go(idx + 1, n, k);
}
int main() {
	int k;
	scanf("%s %d", str, &k);

	if (strlen(str) == 1 || strlen(str) == 2 && str[1] == '0') return !printf("-1");

	ans = -1;
	go(0, strlen(str), k);

	printf("%d", ans);

	return 0;
}