#include "Socket.h"
#include "../../nlohmann/json.hpp"
#include "Protocol.h"

int main() {
    Socket skt("localhost", "7777");
    Protocol protocol(skt);
    nlohmann::json json;
    json["mode"] = "create";
    std::string json_dump = json.dump();
    protocol.sendMessage(json_dump);
    return 0;
}
