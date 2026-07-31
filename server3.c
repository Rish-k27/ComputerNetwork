#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#define PORT 8081
#define BUFFER_SIZE 1024
// Convert to uppercase using ASCII
void to_upper(char *str) {

         while(*str!='\0')
           {  if(*str>='a' && *str<='z')
                {*str=*str - 32;
}
str++;
}
}
// Convert to lowercase using ASCII
void to_lower(char *str) {
 while(*str!='\0')
           {  if(*str>='A' && *str<='Z')
                {*str=*str +  32;
}
str++;
}
}
// Function to reverse string
void reverse(char *str) {
    int l = strlen(str);
    int le = 0, ri = l - 1;
    
    while (le < ri) {
        char temp = *(str + le);
        *(str + le) = *(str + ri);
        *(str + ri) = temp;
        
        le++; 
        ri--; 
    }
}
int main() {
int server_fd, new_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[BUFFER_SIZE];
// Create socket
server_fd = socket(AF_INET, SOCK_STREAM, 0);
if (server_fd == 0) {
perror("Socket␣failed");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);


// Bind

bind(server_fd ,(struct sockadder *)&address, sizeof(address));
// Listen
listen(server_fd,3);
printf("Abe jaldi aa %d...\n", PORT);
printf("Server␣listening␣on␣port␣%d...\n", PORT);
// Accept connection
new_socket = accept(server_fd, (struct sockaddr )&address, (socklen_t)&addrle);

printf("Client␣connected.\n");
while (1) {
memset(buffer, 0, BUFFER_SIZE);
int valread = read(new_socket, buffer,
BUFFER_SIZE);
if (valread <= 0) break;
// Remove newline if present
buffer[strcspn(buffer, "\n")] = 0;
// Check for termination
char command[10], text[BUFFER_SIZE];
// Parse input
sscanf(buffer, "%[^|]|%[^\n]", command, text);
if (strcmp(command, "UP") == 0) {
to_upper(text);
} else if (strcmp(command, "LOW") == 0) {
to_lower(text);
} else if (strcmp(command, "REV") == 0) {
reverse(text);
} else {
strcpy(text, "Invalid␣Command");
}
send(new_socket, text, strlen(text), 0);
}
close(new_socket);
close(server_fd);
printf("Server␣terminated.\n");
return 0;
}
