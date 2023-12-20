#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server_address;
    char buffer[1024];
    
    // Создаем сокет
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }
    
    // Заполняем структуру server_address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(10000);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    while (1) {
        // Измеряем текущее время
        time_t current_time = time(NULL);
        sprintf(buffer, "%ld", current_time);
        
        // Отправляем значение времени по UDP
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *) &server_address, sizeof(server_address));
        
        // Ждем некоторое время перед следующим измерением
        sleep(1);
    }
    
    return 0;
}
