/**
 * Cliente de chat básico usando sockets TCP/IP
 * Permite la conexión a un servidor de chat y el intercambio de mensajes
 * con otros clientes conectados.
 */
 #include <arpa/inet.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <pthread.h>
 #include <signal.h>
 #include <errno.h>
 
 #define PORT 8080
 #define BUFFER_SIZE 1024
 #define SERVER_IP "127.0.0.1"
 
 // Variables globales
 int client_fd;
 volatile int running = 1;
 
 // Prototipos de funciones
 void *receive_messages(void *arg);
 void cleanup_and_exit(int sig);
 void print_usage();
 
 /**
  * Función principal
  */
 int main(int argc, char const* argv[]) {
     struct sockaddr_in serv_addr;
     char buffer[BUFFER_SIZE];
     char nickname[32] = "Anónimo";
     
     // Configurar manejador de señal para salida limpia
     signal(SIGINT, cleanup_and_exit);
     
     printf("=== Cliente de Chat ===\n");
     
     // Opcionalmente aceptar nickname como parámetro
     if (argc > 1) {
         strncpy(nickname, argv[1], sizeof(nickname) - 1);
         nickname[sizeof(nickname) - 1] = '\0';
     }
     
     // Crear socket
     if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
         perror("Error al crear el socket");
         return EXIT_FAILURE;
     }
     
     // Configurar dirección del servidor
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_port = htons(PORT);
     
     // Convertir dirección IP de texto a binario
     if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
         perror("Dirección inválida o no soportada");
         close(client_fd);
         return EXIT_FAILURE;
     }
     
     // Conectar al servidor
     printf("Conectando al servidor %s:%d...\n", SERVER_IP, PORT);
     if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
         perror("Error de conexión");
         close(client_fd);
         return EXIT_FAILURE;
     }
     
     printf("Conectado al servidor.\n");
     
     // Cambiar el nickname al conectarse
     if (strcmp(nickname, "Anónimo") != 0) {
         char nick_cmd[BUFFER_SIZE];
         sprintf(nick_cmd, "/nick %s\n", nickname);
         send(client_fd, nick_cmd, strlen(nick_cmd), 0);
     }
     
     // Crear hilo para recibir mensajes
     pthread_t tid;
     if (pthread_create(&tid, NULL, receive_messages, NULL) != 0) {
         perror("Error al crear hilo");
         close(client_fd);
         return EXIT_FAILURE;
     }
     
     // Mostrar instrucciones
     print_usage();
     
     // Bucle principal para leer la entrada del usuario y enviar mensajes
     while (running) {
         // Leer línea de entrada
         if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
             if (errno == EINTR) {
                 // Interrupción por señal (probablemente Ctrl+C)
                 continue;
             }
             break;
         }
         
         // Verificar si es un comando para salir
         if (strcmp(buffer, "/quit\n") == 0 || strcmp(buffer, "/exit\n") == 0) {
             break;
         }
         
         // Enviar mensaje al servidor
         if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
             perror("Error al enviar mensaje");
             break;
         }
     }
     
     // Limpiar y salir
     cleanup_and_exit(0);
     
     // Esperar a que el hilo termine
     pthread_join(tid, NULL);
     
     return EXIT_SUCCESS;
 }
 
 /**
  * Función para recibir mensajes en un hilo separado
  */
 void *receive_messages(void *arg) {
     char buffer[BUFFER_SIZE];
     int bytes_received;
     
     while (running) {
         // Recibir mensaje del servidor
         bytes_received = read(client_fd, buffer, BUFFER_SIZE - 1);
         
         if (bytes_received > 0) {
             // Asegurar que el buffer termina en null
             buffer[bytes_received] = '\0';
             printf("%s", buffer);  // Mostrar el mensaje recibido
         } else if (bytes_received == 0) {
             // Servidor cerró la conexión
             printf("Desconectado del servidor.\n");
             running = 0;
             break;
         } else {
             // Error
             if (errno != EINTR) {  // Ignorar si es por una señal
                 perror("Error al recibir mensaje");
                 running = 0;
                 break;
             }
         }
     }
     
     return NULL;
 }
 
 /**
  * Limpiar recursos y salir
  */
 void cleanup_and_exit(int sig) {
     printf("\nCerrando cliente...\n");
     running = 0;
     close(client_fd);
     if (sig == SIGINT) {
         exit(EXIT_SUCCESS);
     }
 }
 
 /**
  * Mostrar instrucciones de uso
  */
 void print_usage() {
     printf("\n--- Comandos disponibles ---\n");
     printf("/nick <nombre>  : Cambiar tu nombre en el chat\n");
     printf("/quit o /exit   : Salir del chat\n");
     printf("Cualquier otro texto se enviará como mensaje al chat\n");
     printf("--------------------------\n\n");
 }