# Aplicación de Chat usando Sockets TCP/IP

## Descripción General

Esta aplicación implementa un sistema de chat básico utilizando sockets TCP/IP para la comunicación en red. El sistema consta de un servidor que puede manejar múltiples clientes simultáneamente, permitiendo que los mensajes enviados por un cliente sean retransmitidos a todos los demás clientes conectados.

## Componentes de la Aplicación

### 1. Servidor (`server.c`)

El servidor es el componente central de la aplicación que:
- Acepta y gestiona múltiples conexiones de clientes simultáneas
- Recibe mensajes de los clientes
- Retransmite los mensajes a todos los demás clientes conectados
- Maneja eventos de conexión y desconexión de clientes
- Permite a los clientes cambiar sus nombres mediante comandos

### 2. Cliente (`client.c`)

El cliente es el programa que permite a los usuarios:
- Conectarse al servidor de chat
- Enviar mensajes al servidor (que luego los reenvía a todos los demás clientes)
- Recibir mensajes de otros clientes a través del servidor
- Cambiar su nombre de usuario usando el comando `/nick`
- Salir del chat usando los comandos `/quit` o `/exit`

## Cómo Funciona la Aplicación

### Arquitectura Cliente-Servidor

El sistema implementa una arquitectura cliente-servidor clásica, donde:
- El servidor actúa como punto central para la comunicación
- Los clientes se conectan al servidor
- Toda la comunicación entre clientes pasa a través del servidor
- El administrador del servidor puede enviar mensajes a todos los clientes conectados

### Protocolo de Comunicación

La aplicación utiliza un protocolo de comunicación simple basado en texto:
1. Mensajes normales se envían como texto plano
2. Comandos especiales comienzan con `/` (por ejemplo, `/nick` para cambiar el nombre)
3. El servidor añade el nombre del remitente a los mensajes antes de reenviarlos

### Manejo de Múltiples Clientes

El servidor utiliza la programación multihilo para manejar múltiples clientes simultáneamente:
- Cada conexión de cliente es gestionada por un hilo separado
- Se utiliza un mutex para proteger el acceso concurrente a la lista de clientes
- El servidor puede manejar hasta un máximo definido de clientes (por defecto, 10)

### Manejo de Desconexiones

La aplicación maneja adecuadamente las desconexiones:
- Detecta cuando un cliente se desconecta abruptamente
- Libera recursos asociados con clientes desconectados
- Notifica a los demás clientes cuando alguien se une o abandona el chat

## Detalles de Implementación

### Funciones Principales del Servidor

1. `main()`: Inicializa el servidor, configura el socket, y acepta conexiones entrantes
2. `handle_client()`: Maneja la comunicación con un cliente específico en un hilo separado
3. `server_message_handler()`: Procesa los mensajes ingresados por el administrador del servidor
4. `send_message_to_all()`: Envía un mensaje a todos los clientes conectados
5. `add_client()` y `remove_client()`: Gestiona la lista de clientes conectados
6. `cleanup_and_exit()`: Cierra todas las conexiones y libera recursos al terminar

### Funciones Principales del Cliente

1. `main()`: Establece la conexión con el servidor y gestiona la entrada del usuario
2. `receive_messages()`: Recibe mensajes del servidor en un hilo separado
3. `cleanup_and_exit()`: Cierra la conexión y libera recursos al terminar
4. `print_usage()`: Muestra instrucciones de uso al usuario

### Aspectos de Seguridad y Robustez

- **Validación de entrada**: Se verifica la longitud de los mensajes y nombres
- **Manejo de errores**: Se detectan y reportan errores de conexión y comunicación
- **Liberación de recursos**: Se liberan correctamente todos los recursos al terminar
- **Manejo de señales**: Se captura SIGINT (Ctrl+C) para cerrar limpiamente

## Compilación y Ejecución

### Requisitos

- Sistema Unix/Linux
- Compilador GCC
- Librería POSIX Threads (pthread)

### Compilación

Se proporciona un Makefile para facilitar la compilación:

```bash
make all    # Compila servidor y cliente
make server # Compila solo el servidor
make client # Compila solo el cliente
make clean  # Elimina los archivos compilados
```

### Ejecución

1. Inicie el servidor:
   ```bash
   ./server
   ```
   Una vez iniciado, el administrador del servidor puede escribir mensajes en la consola que serán enviados a todos los clientes. Use `/quit` para cerrar el servidor.

2. En otra(s) terminal(es), inicie el(los) cliente(s):
   ```bash
   ./client [nombre_usuario]
   ```
   Donde `[nombre_usuario]` es opcional.

## Comandos Disponibles

### Comandos del Cliente
- `/nick <nombre>`: Cambia el nombre de usuario
- `/quit` o `/exit`: Desconecta del servidor y cierra el cliente

### Comandos del Servidor
- `/quit`: Cierra el servidor y finaliza todas las conexiones

## Limitaciones y Posibles Mejoras Futuras

- **Autenticación**: No hay sistema de autenticación de usuarios
- **Cifrado**: La comunicación se realiza en texto plano
- **Persistencia**: Los mensajes no se almacenan después de ser enviados
- **Mensajes privados**: No hay soporte para mensajes directos entre usuarios
- **Interfaz gráfica**: Se podría implementar una GUI para mejorar la experiencia de usuario