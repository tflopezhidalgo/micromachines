#include "../common/Event.h"
#include "EventListener.h"
#include <iostream>
#include <zconf.h>
#include "ProtectedQueue.h"
#include "Car.h"
#include "Camera.h"
#include <vector>
#include "TileMap.h"
#include "Drawer.h"
#include "ProtectedModel.h"
#include "Receiver.h"
#include "Proxy.h"
#include "Socket.h"
#include "Dispatcher.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    Socket skt(argv[1], argv[2]);
    Proxy proxy(std::move(skt));

    std::cout << "Bienvenido a micromachines, está utilizando el modo CLI \n"
              << "Por favor, seleccione el modo de juego: join | create \n";

    std::string input;
    json initialMsg;
    std::cin >> input;
	std::string playerID;

    if (input == "create") {
        initialMsg["mode"] = "create";
        std::cout << "Seleccionado: create. Por favor ingrese los siguientes campos\n";

        std::cout << "Ingrese nombre de la partida a crear: ";
        std::cin >> input;
        initialMsg["matchName"] = input;

        std::cout << "Ingrese su nombre: ";
        std::cin >> playerID;
        initialMsg["clientId"] = playerID;

        std::cout << "Ingrese nombre del mapa en el cuál desea jugar: ";
        std::cin >> input;
        initialMsg["map"] = input;

        char a;
        std::cout << "Ingrese cantidad de jugadores: ";
        std::cin >> a;
        initialMsg["playersAmount"] = atoi(&a);

        std::cout << "Ingrese cantidad de vueltas: ";
        std::cin >> a;
        initialMsg["raceLaps"] = atoi(&a);

        std::string serializedInitialMsg = initialMsg.dump();
        proxy.sendMessage(serializedInitialMsg);

    } else if (input == "join") {

        initialMsg["mode"] = "join";
        std::string buffer = initialMsg.dump();
        proxy.sendMessage(buffer);

        std::cout << "Pidiendo la lista de partidas disponibles... \n";

        json recv = json::parse(proxy.receiveMessage());

        std::cout << "Se recibieron : " << recv.dump() << std::endl;

        if (recv.size() == 0) {
            std::cout << "No hay partidas para jugar :(\n";
            return 0;
        }

        int i = 0;
        for (json::iterator it = recv.begin(); it != recv.end(); ++it) {
            i++;
            std::cout << " ------ " << i << " Nombre de la partida: "
                      << *it
                      << " informacion: " ;
            for (auto& element : it.value())
                std::cout << "  " << element << " ";

            std::cout << " ------ \n";
        }

        json j;
        std::cout << std::endl;
        std::cout << "Ingrese su nombre y el nombre de la la partida a la que desea unirse \n";
        std::cout << "Alias: ";
		buffer.clear();
        std::cin >> playerID;
        j["clientId"] = playerID;
		buffer.clear();
        std::cout << "Partida: ";
        std::cin >> buffer;
        j["matchName"] = buffer;

        std::string msg = j.dump();

        proxy.sendMessage(msg);

    } else {
        std::cout << "Debe seleccionar modo join o modo create.. saliendo\n";
        return 0;
    }

    json response = json::parse(proxy.receiveMessage());

    Window main("Game", 900, 600);
    //Window main("game");

    ProtectedQueue<Event> q;
    ProtectedModel model(main, playerID);

    Receiver receiver(model, proxy);
    Drawer drawer(main, model);
    EventListener handler(playerID, q);
    Dispatcher dispatcher(q, proxy);

    receiver.start();
    dispatcher.start();
    drawer.start();
    handler.run();

    drawer.stop();
    dispatcher.stop();
    receiver.stop();
    drawer.join();
    dispatcher.join();
    receiver.join();

    SDL_Quit();
    return 0;
}