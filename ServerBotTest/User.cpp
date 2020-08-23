#include "User.h"

void User::post_receive()
{
    // async_recv 요청
    return;
}

void User::handle_connect()
{
    // 실패 시 프로그램 종료

    // connect 성공
    send_login_req();
}

void User::handle_send()
{

}

void User::handle_receive()
{
    // 패킷 조립
    // ...
    post_receive();
    // 패킷 완성 시 recv_queue_에 recv_buff_내용 복사
    // ...
}

void User::start_scenario()
{
    // connect 시도
}

void User::process_packet(int packet_header, vector<uint8_t>& packet)
{
    // 현재는 case 안에서 다음 시나리오 함수를 호출하며 시나리오 처리
    // 시나리오 함수포인터를 value로 갖는 map을 만들어서 처리해도 좋을 듯
    switch(packet_header)
    {
        case (int)PACKET_HEADER::GC_Login_RES:
        {
            // 실패 시 재시도 or 종료
            // 성공 시 accountinfo 요청
            send_account_info_req();
        }
        break;
        case (int)PACKET_HEADER::GC_AccountInfo_RES:
        {
            // 실패 시 캐릭터생성
            send_create_nickname_req();
            // 성공 시 item list 요청
            send_item_list_req();
        }
        break;
        case (int)PACKET_HEADER::GC_CreateNickname_RES:
        {
            // 실패 시 재시도
            send_create_nickname_req();
            // 성공 시 accountinfo 요청
            send_account_info_req();
        }
        break;
        case (int)PACKET_HEADER::GC_ItemList_RES:
        {
            // 시나리오 종료
        }
        break;
    }
}

void User::end_scenario()
{
    // 종료 처리
}

void User::send_login_req()
{

}
void User::send_account_info_req()
{

}
void User::send_create_nickname_req()
{

}
void User::send_item_list_req()
{

}