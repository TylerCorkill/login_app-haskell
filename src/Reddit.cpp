#include <boost/network/protocol/http/client.hpp>
#include <string>
#include <iostream>

int getReddit()
{
    using namespace boost::network;
    using namespace boost::network::http;
    
    std::string server = "http://redsms.herokuapp.com/askreddit";
    client::request request(server)
    request << header("Connection", "close");
    client client;
    client::response response = client.get(request);
    std::string body = body(response);
}
