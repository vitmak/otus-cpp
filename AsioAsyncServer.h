#pragma once

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket) : m_socket(std::move(socket)) {
    }

    void Start() {
        DoRead();
    }

private:
    void DoRead() {
        auto self(shared_from_this());
        m_socket.async_read_some(boost::asio::buffer(m_data, MaxLength),
            [this, self](boost::system::error_code ec, std::size_t length)
            {
                if (!ec) {
                    std::cout << "receive " << length << "=" << std::string{ m_data, length } << std::endl;
                    DoRead();
                }
            });
    }

    tcp::socket m_socket;
    enum { MaxLength = 1024 };
    char m_data[MaxLength];
};

class Server {
public:
    Server(boost::asio::io_context& io_context, short port)
        : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        DoAccept();
    }

private:
    void DoAccept() {
        m_acceptor.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket))->Start();
                }

                DoAccept();
            });
    }

    tcp::acceptor m_acceptor;
};
