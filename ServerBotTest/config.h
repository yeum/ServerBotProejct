#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

constexpr int THREAD_NUM = 10;
constexpr int USER_NUM = 1000;
const string IP_ADDR = "127.0.0.1";
const string PORT = "12345";

enum MAX_SIZE{
    MAX_RECV_BUFF_LENGTH = 1024,
    MAX_RECV_QUEUE_LENGTH = 65536,
    MAX_SEND_BUFF_LENGTH = 1024,
    MAX_SEND_QUEUE_LENGTH = 65536,

    PACKET_HEADER_SIZE = 4
};

enum class PACKET_HEADER {
    CG_Login_REQ,
    GC_Login_RES,

    CG_AccountInfo_REQ,
    GC_AccountInfo_RES,

    CG_CreateNickname_REQ,
    GC_CreateNickname_RES,

    CG_ItemList_REQ,
    GC_ItemList_RES
};