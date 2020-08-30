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
    vector<boost::asio::io_context> io_contect_vec;
    thread_vec.reserve(THREAD_NUM);
    io_contect_vec.reserve(THREAD_NUM);
    users.reserve(USER_NUM);

    for(int i = 0 ; i<THREAD_NUM; ++i)
        io_contect_vec.emplace_back(boost::asio::io_context());

    for(int i = 0 ; i<THREAD_NUM; ++i)
    {   
        thread_vec.emplace_back([=](){
            // 유저 별 실행, 또는 일정 수 별로 잘라서 배열넘기기
            // 0~1000
            // 1000~2000
            // ... 9000~10000
            process((USER_NUM/THREAD_NUM)*i, (USER_NUM/THREAD_NUM)*(i+1));
        });

        // 전체 유저 수를 thread 수 만큼 나눠서 io_context 배정
        for(int user_num = i*(USER_NUM/THREAD_NUM); user_num < (i+1)*(USER_NUM/THREAD_NUM); ++user_num)
        {
            // 유저 초기화
            users.emplace_back(io_contect_vec[i], "accountId");
        }
    }

    for(auto& io_context : io_contect_vec)
        io_context.run();

    for(auto& th : thread_vec)
    {
        th.join();
    }

    return 0;
}