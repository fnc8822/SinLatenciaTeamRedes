/**
 * Servidor de chat básico usando sockets TCP/IP
 * Permite la conexión de múltiples clientes simultáneamente
 * y redistribuye los mensajes a todos los clientes conectados.
 */
 #include <netinet/in.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <sys/socket.h>
 #include <unistd.h>
 #include <pthread.h>
 #include <signal.h>
 #include <arpa/inet.h>
 #include <errno.h>
 
 #define PORT 8080
 #define MAX_CLIENTS 10
 #define BUFFER_SIZE 1024
 
 // Estructura para almacenar información de clientes
 typedef struct {
     int socket_fd;
     struct sockaddr_in address;
     char name[32];
 } client_t;
 
 // Variables globales
 int server_fd;
 client_t *clients[MAX_CLIENTS];
 pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;
 
 // Prototipos de funciones
 void *handle_client(void *arg);
 void *server_message_handler(void *arg);
 void send_message_to_all(char *message, int sender_fd);
 void add_client(client_t *client, int index);
 void remove_client(int index);
 void cleanup_and_exit(int sig);
 
 // Función para leer mensajes del administrador del servidor
 void *server_message_handler(void *arg) {
     char buffer[BUFFER_SIZE];
     
     printf("Modo de chat del servidor activado. Escribe mensajes para enviar a todos los clientes.\n");
     printf("Usa '/quit' para cerrar el servidor.\n");
     
     while (1) {
         // Leer entrada del administrador del servidor
         if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
             if (errno == EINTR) {
                 continue;  // Ignorar si es interrupción por señal
             }
             break;
         }
         
         // Comprobar si el administrador quiere cerrar el servidor
         if (strcmp(buffer, "/quit\n") == 0) {
             printf("Cerrando servidor por solicitud del administrador...\n");
             cleanup_and_exit(0);
             break;
         }
         
         // Preparar mensaje del administrador
         char server_msg[BUFFER_SIZE + 32];
         sprintf(server_msg, "[SERVIDOR]: %s", buffer);
         
         // Enviar mensaje a todos los clientes
         send_message_to_all(server_msg, -1);
         
         // También mostrarlo en la consola del servidor
         printf("Mensaje enviado a todos los clientes.\n");
     }
     
     return NULL;
 }
 
 /**
  * Función principal
  */
 int main(int argc, char const* argv[]) {
     struct sockaddr_in address;
     int opt = 1;
     socklen_t addrlen = sizeof(address);
     pthread_t server_msg_thread;
     
     // Inicializar array de clientes
     for (int i = 0; i < MAX_CLIENTS; i++) {
         clients[i] = NULL;
     }
     
     // Configurar manejador de señal para la limpieza antes de salir
     signal(SIGINT, cleanup_and_exit);
     
     printf("Iniciando servidor de chat...\n");
     
     // Crear socket
     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
         perror("Error al crear el socket");
         exit(EXIT_FAILURE);
     }
     
     // Configurar opciones del socket
     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                   &opt, sizeof(opt))) {
         perror("Error en setsockopt");
         exit(EXIT_FAILURE);
     }
     
     // Configurar dirección del servidor
     address.sin_family = AF_INET;
     address.sin_addr.s_addr = INADDR_ANY;
     address.sin_port = htons(PORT);
     
     // Enlazar socket con la dirección
     if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
         perror("Error en bind");
         exit(EXIT_FAILURE);
     }
     
     // Escuchar conexiones entrantes
     if (listen(server_fd, 5) < 0) {
         perror("Error en listen");
         exit(EXIT_FAILURE);
     }
     
     printf("Servidor iniciado en el puerto %d\n", PORT);
     
     // Crear hilo para manejar los mensajes del servidor
     if (pthread_create(&server_msg_thread, NULL, server_message_handler, NULL) != 0) {
         perror("Error al crear hilo para mensajes del servidor");
         close(server_fd);
         exit(EXIT_FAILURE);
     }
     
     printf("Esperando conexiones...\n");
     
     // Bucle principal para aceptar conexiones
     while (1) {
         // Aceptar nueva conexión
         client_t *client = (client_t *)malloc(sizeof(client_t));
         if (!client) {
             perror("Error al asignar memoria para el cliente");
             continue;
         }
         
         addrlen = sizeof(client->address);
         if ((client->socket_fd = accept(server_fd, (struct sockaddr*)&(client->address), 
                                         &addrlen)) < 0) {
             perror("Error en accept");
             free(client);
             continue;
         }
         
         // Obtener y mostrar información del cliente
         char client_ip[INET_ADDRSTRLEN];
         inet_ntop(AF_INET, &(client->address.sin_addr), client_ip, INET_ADDRSTRLEN);
         printf("Nueva conexión desde %s:%d\n", client_ip, ntohs(client->address.sin_port));
         
         // Inicializar nombre del cliente (será actualizado después)
         sprintf(client->name, "Cliente-%d", client->socket_fd);
         
         // Buscar un slot libre para el cliente
         int client_index = -1;
         pthread_mutex_lock(&clients_mutex);
         for (int i = 0; i < MAX_CLIENTS; i++) {
             if (clients[i] == NULL) {
                 add_client(client, i);
                 client_index = i;
                 break;
             }
         }
         pthread_mutex_unlock(&clients_mutex);
         
         if (client_index == -1) {
             printf("Servidor lleno, rechazando cliente\n");
             char *message = "Lo sentimos, el servidor está lleno. Intente más tarde.\n";
             send(client->socket_fd, message, strlen(message), 0);
             close(client->socket_fd);
             free(client);
             continue;
         }
         
         // Mensaje de bienvenida
         char welcome[BUFFER_SIZE];
         sprintf(welcome, "Bienvenido al servidor de chat! Tu nombre es %s\n", client->name);
         send(client->socket_fd, welcome, strlen(welcome), 0);
         
         // Notificar a todos los clientes sobre la nueva conexión
         char notification[BUFFER_SIZE];
         sprintf(notification, "%s se ha unido al chat.\n", client->name);
         send_message_to_all(notification, -1);
         
         // Crear un hilo para manejar este cliente
         pthread_t tid;
         if (pthread_create(&tid, NULL, handle_client, (void*)&client_index) != 0) {
             perror("Error al crear hilo");
             pthread_mutex_lock(&clients_mutex);
             remove_client(client_index);
             pthread_mutex_unlock(&clients_mutex);
         } else {
             // Desasociar el hilo para que pueda liberarse automáticamente al terminar
             pthread_detach(tid);
         }
     }
     
     return 0;
 }
 
 /**
  * Función para manejar un cliente en un hilo separado
  */
 void *handle_client(void *arg) {
     int index = *((int*)arg);
     char buffer[BUFFER_SIZE];
     int bytes_received;
     
     pthread_mutex_lock(&clients_mutex);
     client_t *client = clients[index];
     pthread_mutex_unlock(&clients_mutex);
     
     if (!client) {
         return NULL;
     }
     
     // Bucle para recibir mensajes del cliente
     while ((bytes_received = read(client->socket_fd, buffer, BUFFER_SIZE - 1)) > 0) {
         buffer[bytes_received] = '\0';
         
         // Comprobar si es un comando para cambiar el nombre
         if (strncmp(buffer, "/nick ", 6) == 0) {
             char new_name[32];
             strncpy(new_name, buffer + 6, sizeof(new_name) - 1);
             new_name[sizeof(new_name) - 1] = '\0';
             
             // Remover salto de línea si existe
             char *newline = strchr(new_name, '\n');
             if (newline) *newline = '\0';
             
             pthread_mutex_lock(&clients_mutex);
             
             char notification[BUFFER_SIZE];
             sprintf(notification, "%s ahora es conocido como %s\n", client->name, new_name);
             strncpy(client->name, new_name, sizeof(client->name) - 1);
             client->name[sizeof(client->name) - 1] = '\0';
             
             pthread_mutex_unlock(&clients_mutex);
             
             send_message_to_all(notification, -1);
         } else {
             // Formato del mensaje: [nombre]: mensaje
             char message[BUFFER_SIZE + 64];
             pthread_mutex_lock(&clients_mutex);
             sprintf(message, "[%s]: %s", client->name, buffer);
             pthread_mutex_unlock(&clients_mutex);
             
             // Enviar el mensaje a todos los clientes
             send_message_to_all(message, client->socket_fd);
             
             printf("%s", message);  // Mostrar el mensaje en el servidor
         }
     }
     
     // Cliente desconectado o error
     if (bytes_received == 0) {
         printf("Cliente desconectado\n");
     } else {
         perror("Error al recibir datos");
     }
     
     // Notificar a todos sobre la desconexión
     pthread_mutex_lock(&clients_mutex);
     char notification[BUFFER_SIZE];
     sprintf(notification, "%s ha abandonado el chat.\n", client->name);
     send_message_to_all(notification, -1);
     
     // Remover y liberar cliente
     remove_client(index);
     pthread_mutex_unlock(&clients_mutex);
     
     return NULL;
 }
 
 /**
  * Enviar un mensaje a todos los clientes
  * Si sender_fd >= 0, el mensaje no se enviará al remitente
  */
 void send_message_to_all(char *message, int sender_fd) {
     pthread_mutex_lock(&clients_mutex);
     
     for (int i = 0; i < MAX_CLIENTS; i++) {
         if (clients[i] != NULL) {
             // No enviar al remitente si así se especifica
             if (sender_fd >= 0 && clients[i]->socket_fd == sender_fd) {
                 continue;
             }
             
             if (send(clients[i]->socket_fd, message, strlen(message), 0) < 0) {
                 perror("Error al enviar mensaje");
                 // Si hay error, probablemente el cliente se desconectó
                 // Lo manejamos cerrando el socket y marcando como disponible
                 close(clients[i]->socket_fd);
                 free(clients[i]);
                 clients[i] = NULL;
             }
         }
     }
     
     pthread_mutex_unlock(&clients_mutex);
 }
 
 /**
  * Agregar un cliente al array
  */
 void add_client(client_t *client, int index) {
     clients[index] = client;
 }
 
 /**
  * Remover un cliente del array y liberar recursos
  */
 void remove_client(int index) {
     if (clients[index] != NULL) {
         close(clients[index]->socket_fd);
         free(clients[index]);
         clients[index] = NULL;
     }
 }
 
 /**
  * Limpiar recursos y salir
  */
 void cleanup_and_exit(int sig) {
     printf("\nCerrando servidor...\n");
     
     // Cerrar todas las conexiones de clientes
     pthread_mutex_lock(&clients_mutex);
     for (int i = 0; i < MAX_CLIENTS; i++) {
         if (clients[i] != NULL) {
             close(clients[i]->socket_fd);
             free(clients[i]);
             clients[i] = NULL;
         }
     }
     pthread_mutex_unlock(&clients_mutex);
     
     // Cerrar socket del servidor
     close(server_fd);
     
     printf("Servidor cerrado.\n");
     exit(EXIT_SUCCESS);
 }