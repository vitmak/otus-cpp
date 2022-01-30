#include "AsioAsyncServer.h"
#include <iostream>
#include <boost/asio.hpp>


int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3) {
            std::cerr << "Usage: bulk_server <port> <bulk_size>" << std::endl;
            return 1;
        }

        boost::asio::io_context context;

        Server server(context, std::atoi(argv[1]));

        context.run();
    }
    catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << "\n";
    }

    return 0;
}