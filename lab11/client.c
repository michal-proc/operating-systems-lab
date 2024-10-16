#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

int client_connection = 1;
int sock = 0;
char client_id[BUFFER_SIZE];

void handle_exit() {
    if (client_connection) {
        send(sock, "STOP", strlen("STOP"), 0);
        close(sock);
        client_connection = 0;
    }
    printf("Client exiting...\n");
    exit(0);
}

void *receive_messages(void *arg) {
    char buffer[BUFFER_SIZE];
    while (1) {
        int bytes_received = recv(sock, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            printf("Server disconnected.\n");
            handle_exit();
            break;
        }
        buffer[bytes_received] = '\0';

        if (strncmp(buffer, "ALIVE", 5) == 0) {
            send(sock, "ALIVE", strlen("ALIVE"), 0);
        } else {
            printf("%s\n", buffer);
        }
    }
    return NULL;
}

int main(int argc, char const *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <client_id> <server_ip> <server_port>\n", argv[0]);
        return -1;
    }

    struct sockaddr_in serv_addr;
    pthread_t thread;

    strcpy(client_id, argv[1]);
    const char *server_ip = argv[2];
    int server_port = atoi(argv[3]);

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/Address not supported");
        return -1;
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    // Send client ID to server
    send(sock, client_id, strlen(client_id), 0);

    // Handle Ctrl + C Exit
    signal(SIGINT, handle_exit);

    // Create thread to receive messages
    if (pthread_create(&thread, NULL, receive_messages, NULL) != 0) {
        perror("pthread_create failed");
        return -1;
    }

    // Main loop to send messages
    char buffer[BUFFER_SIZE];
    while (client_connection) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp(buffer, "STOP", 4) == 0) {
            handle_exit();
        }
        send(sock, buffer, strlen(buffer), 0);
    }

    // Wait for the receive thread to finish
    pthread_join(thread, NULL);

    return 0;
}
