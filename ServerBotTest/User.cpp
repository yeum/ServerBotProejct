#include "User.h"

User::User(boost::asio::io_context& io_context) : 
socket_(io_context)
{
    connect_to_server(io_context);
}

User::User(boost::asio::io_context& io_context, string account_id) : 
socket_(io_context), 
account_id_(account_id)
{
    connect_to_server(io_context);
}

void User::connect_to_server(boost::asio::io_context& io_context)
{
        // connect 시도
    boost::asio::ip::tcp::resolver resolver(io_context);
    boost::asio::ip::tcp::resolver::query query(IP_ADDR, PORT);
 
    resolver.async_resolve(query, &User::resolve_handler);
}

void User::resolve_handler (const boost::system::error_code & ec, tcp::resolver::results_type results)
{
    if (ec)
        return;

    boost::asio::async_connect(socket_, results, &User::handle_connect);
}

void User::post_receive()
{
    recv_buff_.fill(0);
    // async_recv 요청
    socket_.async_read_some(boost::asio::buffer(recv_buff_, MAX_RECV_BUFF_LENGTH), &User::handle_receive);
}

void User::handle_connect(const boost::system::error_code& ec, const tcp::endpoint& endpoint)
{
    // 실패 시 프로그램 종료
    if(ec)
        return;
    
    // connect 성공
    cout<<"Connect Succeed!\n";
    post_receive();
}

void User::handle_send(boost::system::error_code ec, std::size_t byte_transffered)
{
    int packet_size_len = 0;
    memcpy(&packet_size_len, &send_buff_[0], PACKET_SIZE_LENGTH);

    if(packet_size_len > byte_transffered)
    {
        array<uint8_t, MAX_SEND_BUFF_LENGTH> temp_buff;
        memcpy(&temp_buff[0], &send_buff_[0], packet_size_len - byte_transffered);
        send_buff_.fill(0);
        memcpy(&send_buff_[0], &temp_buff[0], packet_size_len - byte_transffered);

        socket_.async_send(boost::asio::buffer(send_buff_, MAX_SEND_BUFF_LENGTH), &User::handle_send);
        return;
    }
    send_buff_.fill(0);
}

void User::handle_receive(boost::system::error_code ec, std::size_t byte_transffered)
{
    // 패킷 조립
    // 패킷전체 사이즈 가져오기
    int packet_size_len = 0;
    memcpy(&packet_size_len, &recv_buff_[0], PACKET_SIZE_LENGTH);

    // 덜 들어왔으면 넘기기
    if(packet_size_len > recv_buff_.size())
    {
        post_receive();
        return;
    }

    // 패킷헤더를 분리해서 process_packet에 인자로 넘겨 실행

    post_receive();
    // 패킷 완성 시 recv_queue_에 recv_buff_내용 복사
    // ...
}

void User::start_scenario()
{
    // 첫 번째 시나리오 프로토콜 전송
    send_login_req();
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