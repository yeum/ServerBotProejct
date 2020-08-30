#include "config.h"

class User {
public:
    User(boost::asio::io_context& io_context);
    User(boost::asio::io_context& io_context, string account_id);
    ~User(){};

public:
    void connect_to_server(boost::asio::io_context& io_context);
    void resolve_handler (const boost::system::error_code & ec, tcp::resolver::results_type results);
    void post_receive();
    void handle_connect(const boost::system::error_code& ec, const tcp::endpoint& endpoint);
    void handle_send(boost::system::error_code ec, std::size_t byte_transffered);
    void handle_receive(boost::system::error_code ec, std::size_t byte_transffered);

    void try_start();
    void start_scenario();
    void process_packet(int packet_header, vector<uint8_t>& packet);

    void end_scenario();

public:
    void send_login_req();
    void send_account_info_req();
    void send_create_nickname_req();
    void send_item_list_req();

private:
    tcp::socket socket_;

public:
    string account_id_;

    vector<vector<uint8_t>> recv_queue_;
    array<uint8_t, MAX_RECV_QUEUE_LENGTH> recv_buff_;

    vector<vector<uint8_t>> send_queue_;
    array<uint8_t, MAX_SEND_QUEUE_LENGTH> send_buff_;
};