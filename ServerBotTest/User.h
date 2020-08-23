#include "config.h"

class User {
public:
    User(){};
    User(string account_id) {account_id_ = account_id;};
    ~User(){};

public:
    void post_receive();
    void handle_connect();
    void handle_send();
    void handle_receive();

    void try_start();
    void start_scenario();
    void process_packet(int packet_header, vector<uint8_t>& packet);

    void end_scenario();

public:
    void send_login_req();
    void send_account_info_req();
    void send_create_nickname_req();
    void send_item_list_req();

public:
    string account_id_;

    vector<vector<uint8_t>> recv_queue_;
    array<uint8_t, 65536> recv_buff_;

    vector<vector<uint8_t>> send_queue_;
    array<uint8_t, 1024> send_buff_;
};