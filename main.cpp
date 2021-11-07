#include "Client.h"
#include "Serveur.h"

#include <iostream>

int main(int argc, char *argv[])
{
    // usage : 
    // client : ./client <ip> <port>
    // serveur : ./serveur -s <port>

    if(argc != 3)
    {
        std::cout << "Usage : ./client <ip> <port>" << std::endl;
        std::cout << "Usage : ./serveur -s <port>" << std::endl;
        return 0;
    }

    if(strcmp(argv[1], "-s") == 0)
    {
        Serveur s(argv[2]);
        while(s.Update());
    }
    else
    {
        Client c(argv[1], argv[2]);
        while(c.Update());
    }

    return 0;
}