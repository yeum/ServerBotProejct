#include "User.h"

vector<User> users;


void process(int start_user_idx, int end_user_idx)
{
    for(int user_idx = start_user_idx; user_idx < end_user_idx; ++user_idx)
       users[user_idx].start_scenario();
       
    while(true)
    {
        // recv_queue_에 처리할 패킷이 있나 확인
        // 있으면 해당 패킷에 대한 process_packet실행
        // param: packet_header
        for(int user_idx = start_user_idx; user_idx < end_user_idx; ++user_idx)
            users[user_idx].process_packet(1, users[user_idx].recv_queue_[0]);
    }
}
int main()
{
    vector<thread> thread_vec;
    thread_vec.reserve(8);
    users.reserve(USER_NUM);

    for(int i = 0; i<USER_NUM; ++i)
    {
        // 유저 초기화
        users.emplace_back("accountId");
    }

    for(int i = 0 ; i<THREAD_NUM; ++i)
    {   
        thread_vec.emplace_back([=](){
            // 유저 별 실행, 또는 일정 수 별로 잘라서 배열넘기기
            // 0~1000
            // 1000~2000
            // ... 9000~10000
            process((USER_NUM/THREAD_NUM)*i, (USER_NUM/THREAD_NUM)*(i+1));
        });
    }

    for(auto& th : thread_vec)
    {
        th.join();
    }
    return 0;
}