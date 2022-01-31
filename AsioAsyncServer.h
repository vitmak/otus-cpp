#pragma once

#include "async.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, int bulkSize) : m_socket(std::move(socket)) {
        m_context = async::connect(bulkSize);
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
                    async::receive(m_context, m_data, length);
                    DoRead();
                }
                else {
                    async::disconnect(m_context);
                    m_socket.close();
                }
            });
    }

    tcp::socket m_socket;
    enum { MaxLength = 1024 };
    char m_data[MaxLength];
    async::handle_t m_context;
};

class Server {
public:
    Server(boost::asio::io_context& io_context, short port, int bulkSize)
        : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_bulkSize { bulkSize }
    {
        DoAccept();
    }

private:
    void DoAccept() {
        m_acceptor.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::make_shared<Session>(std::move(socket), m_bulkSize)->Start();
                }

                DoAccept();
            });
    }

    tcp::acceptor m_acceptor;

    int m_bulkSize; // TODO: use pointer to Config
};
