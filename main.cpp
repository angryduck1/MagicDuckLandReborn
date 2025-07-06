#include <iostream>
#include <boost/asio.hpp>
#include <thread>
#include "Connection.h"

using namespace boost::asio;
using ip::tcp;

using namespace std;

int main()
{
    io_context io_ctx;
    tcp::endpoint endpoint(ip::address_v4::any(), 9339);

    tcp::acceptor acceptor(io_ctx, endpoint);

    while (true) {
        try {
        tcp::socket socket(io_ctx);

        acceptor.accept(socket);

        auto sock_ptr = make_shared<tcp::socket>(std::move(socket));
        auto remote_ep = sock_ptr->remote_endpoint();

        std::cout << "Accepted new connection " << remote_ep.address().to_string() << ":" << remote_ep.port() << std::endl;

        thread session([sock_ptr](){
            Connection sess(sock_ptr, "fhsd6f86f67rt8fw78fw789we78r9789wer6re");
            sess.run();
        });

        session.join();
        } catch (const boost::system::system_error& e) {
            cerr << e.code() << " " << e.what() << endl;
        }
    }

    return 0;
}
