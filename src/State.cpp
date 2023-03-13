#include "State.hpp"

IdleState::IdleState(std::weak_ptr<Connection> connection)
    : connection(connection)
{
    std::shared_ptr<Connection> conn = connection.lock();
    if(conn != nullptr) {
        asio::ip::tcp::socket& sock = conn->getSocket();
        sock.write_some(asio::buffer("220 Hello\r\n"));
    }
}

std::shared_ptr<State> IdleState::processEvent(const Request &request)
{
    if(request.getCommand() == "HELO") 
    {
        std::string domain = request.getParameters()[0];
        std::shared_ptr<Connection> conn = connection.lock();
        if(conn != nullptr) {
            conn->setDomain(domain);
            asio::ip::tcp::socket& sock = conn->getSocket();
            sock.write_some(asio::buffer("250 Hello " + domain + "\r\n"));
            return std::make_shared<HeloState>();
        }
        else
        {
            //something wrong
            return getPtr();
        }
    }
    else 
    {
        //not allowed
        return getPtr();
    }
}

std::shared_ptr<IdleState> IdleState::getPtr()
{
    return shared_from_this();
}

HeloState::HeloState()
{
}

std::shared_ptr<State> HeloState::processEvent(const Request &request)
{
    if(request.getCommand() == "MAIL")
    {
        std::cout << "transit to MailState" << std::endl;
        return std::make_shared<MailState>();
    }
    else 
    {
        //not allowed
        return getPtr();
    }
}

std::shared_ptr<HeloState> HeloState::getPtr()
{
    return shared_from_this();
}

MailState::MailState()
{
}

std::shared_ptr<State> MailState::processEvent(const Request &request)
{
    return getPtr();
}

std::shared_ptr<MailState> MailState::getPtr()
{
    return shared_from_this();
}
