#include "Server/Server.hpp"

Server::Server(const ServerConfig& config)
    : listenSocket(ctx)
    , acceptor(ctx)
    , sslCtx(asio::ssl::context::tlsv12)
    , config(config)
{
    sslCtx.use_certificate_chain_file(this->config.certPemPath);
    sslCtx.use_private_key_file(this->config.certPemPath, asio::ssl::context::pem);
}

void Server::start()
{
    asio::ip::tcp::resolver resolver(ctx);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve(config.host, config.port);
    acceptor.open(endpoint.protocol());
    // TODO: Add error handling when address already use
    acceptor.bind(endpoint);
    acceptor.listen(asio::socket_base::max_connections);

    acceptor.async_accept(listenSocket, std::bind(&Server::handleAccept, this, std::placeholders::_1));

    std::cout << "server started" << std::endl;

    ctx.run();
}

void Server::handleAccept(const asio::error_code& ec)
{
    SecuredStream securedStream(std::move(listenSocket), sslCtx);
    auto connection = std::make_shared<Connection>(std::move(securedStream));
    connections.insert(connection);
    connection->start(std::bind(&Server::removeConnection, this, std::weak_ptr<Connection>(connection)));

    listenSocket.close();
    acceptor.async_accept(listenSocket, std::bind(&Server::handleAccept, this, std::placeholders::_1));
}

// Remove connection from list
void Server::removeConnection(std::weak_ptr<Connection> connectionRef)
{
    std::shared_ptr<Connection> connection = connectionRef.lock();
    if (connection != nullptr)
    {
        connections.erase(connection);
    }
}