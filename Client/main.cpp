#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <future>

using namespace std;

int main() {
    int status, valread, client_fd;
    struct sockaddr_in serv_addr{};
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    string message;
    cout << "What message you want to send? "<< endl;
    getline(cin,message);
    char* text = new char[message.length()+1];
    strcpy(text,message.c_str());

    send(client_fd,text, strlen(text), 0);
    printf("%s",buffer);
    valread = read(client_fd, buffer, 1024);
    printf("%s\n", buffer);

    delete[] text;
    close(client_fd);
    return 0;
}
