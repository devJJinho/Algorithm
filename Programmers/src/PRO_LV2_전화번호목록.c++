#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
@author  :  Jinho Jeong
@date    :  2022.04.23

*난이도 : Level2
*개인 풀이 시간 : 3 Hour
*개인 난이도 : 2/5 
*분류 : 트라이
*풀이 : 알고리즘 자체를 n^2으로 풀면 시간 초과
       1. 첫 시도 : str.find() 사용했음. Return 값이 0이면 0부터 겹치는 것 => return false; 시간 초과
       2. 두번째 시도 : 시작위치를 반환하는 find 대신 첫 자리부터 겹치는게 있는지만 체크하는 함수 만들었음 : 효율성에서 실패
       3. 세번째 시도 : 트라이 만들어서 해결 

*느낀점 : 시간 초과는 예상하지 못함
*/

struct NODE{
    NODE* ptr[10];
    bool isEnd;
    NODE(){
        isEnd = false;
        for(int i = 0 ; i < 10 ; i++)
            ptr[i] = NULL;
    }
    ~NODE(){
        for(int i = 0 ; i < 10 ; i++){
            if(ptr[i] != NULL)
                delete(ptr[i]);
        }
    }
    bool push(string& str, int len , int idx){
        //만약 진행 도중 완성된 문자열이 있으면 겹치는 것이기 때문에 return false;
        if(isEnd) return false;
        //끝이면 IsEnd = true;
        if(len == idx){
            isEnd = true; 
            return true;
        }
        int num = str[idx] - '0';
        //비어있으면 새로 생성 후 진행
        if(ptr[num] == NULL){
            ptr[num] = new NODE();
        }
        //다음 인덱스로 전달
        return ptr[num] -> push(str , len , idx + 1);
    }
};

NODE root;

bool cmp(string& a, string& b){
    return a.length() < b.length();
}

bool solution(vector<string> phone_book) {
    //정렬 후 시도 : 작은 것 부터 시도해야함. 큰 것 부터 시도하면 놓치는 부분이 있을 수 있음
    sort(phone_book.begin() , phone_book.end() , cmp);
    for(string str : phone_book){
        if(!root.push(str , str.length() , 0)) return false;
    }
    return true;
}