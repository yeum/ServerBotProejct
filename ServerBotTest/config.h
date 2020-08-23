#include <iostream>
#include <thread>
#include <vector>
#include <array>
#include <string>

using namespace std;

constexpr int THREAD_NUM = 10;
constexpr int USER_NUM = 1000;

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