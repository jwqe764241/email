#include "server.hpp"

Server::Server()
    : listenSocket(ctx), acceptor(ctx)
{
}

void Server::start(std::string host, std::string port)
{
    asio::ip::tcp::resolver resolver(ctx);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(host, port);

    acceptor.open(endpoint.protocol());
    acceptor.bind(endpoint);
    acceptor.listen(asio::socket_base::max_connections);

    acceptor.async_accept(listenSocket, std::bind(&Server::handleAccept, this, std::placeholders::_1));

    std::cout << "server started" << std::endl;

    ctx.run();
}

void Server::handleAccept(const asio::error_code &ec)
{
    std::cout << "connected" << std::endl;
    listenSocket.close();

    acceptor.async_accept(listenSocket, std::bind(&Server::handleAccept, this, std::placeholders::_1));
}