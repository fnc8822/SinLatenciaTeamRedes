# Trabajo Practico nº 1 - Parte II - Manejo de equipamiento físico, recuperación de contraseñas de equipos de red y establecimiento de red y análisis de tráfico.

**Institucion: UNC - Facultad de Ciencias Exactas, Físicas y Naturales**  
**Materia: Redes de Computadoras**

**Profesores**
- Facundo Oliva Cuneo (Teorico).
- Santiago Martín Henn (Laboratorios).

**Fecha: 27-03-2025** 

---
## Nombre del grupo: Sin Latencia Team

## Nombres de los integrantes
- Efrain G. Veliz S.
- Elio N. Ludueña
- Juan I. Sassi 
- Franco L. Cirrincione

## Información de los autores
- efrain.veliz@mi.unc.edu.ar
- nicoluduena@mi.unc.edu.ar
- juan.sassi@mi.unc.edu.ar
- francocirrincione@mi.unc.edu.ar

---

### Switch WS-C2950
- Modelos y Puertos
  - **WS-C2950-12:** 12 puertos 10/100 Mbps  
  - **WS-C2950-24:** 24 puertos 10/100 Mbps  
  - **WS-C2950SX-24:** 24 puertos 10/100 Mbps con 2 uplinks 1000BASE-SX  
  - **WS-C2950T-48:** 48 puertos 10/100 Mbps con 2 puertos 10/100/1000BASE-T  
  - **WS-C2950SX-48:** 48 puertos 10/100 Mbps con 2 uplinks 1000BASE-SX  

- Rendimiento
  - **Ancho de banda de conmutación:**  
    - Entre 8.8 Gbps y 13.6 Gbps según el modelo.
  - **Tasas de reenvío:**  
    - Desde 1.8 Mpps hasta 10.1 Mpps (basado en paquetes de 64 bytes).

- Memoria y Capacidad
  - 16 MB de DRAM y 8 MB de Flash.
  - 8 MB de buffer compartido entre puertos.
  - Capacidad de hasta 8000 direcciones MAC.

- Gestión y Protocolos
  - **Gestión:**  
    - Cisco Device Manager (interfaz web) y Cisco Network Assistant.
  - **Protocolos de administración:**  
    - Soporte para SNMP (v1, v2 y v3 no criptográfico) y Telnet.
    - Amplia variedad de MIBs para integración en plataformas de gestión.

- Seguridad
  - **Autenticación y Acceso:**  
    - 802.1x para control de acceso.
    - Integración con TACACS+ y RADIUS.
  - **Cifrado y Protección:**  
    - SSH versión 2 (SSHv2) para sesiones seguras.
    - Port security y Private VLAN Edge para segmentación y protección de puertos.

- Calidad de Servicio (QoS)
  - Soporta clasificación de tramas basada en IEEE 802.1p y re-clasificación con valores predeterminados.
  - Cuatro colas por puerto con:
    - **Strict Priority Scheduling:** Para aplicaciones sensibles como VoIP.
    - **Weighted Round Robin (WRR):** Garantiza atención a tráfico de baja prioridad.

- Conectividad Física y Estándares
  - **Factor de forma:**  
    - 1RU, para montaje en racks estándar.
  - **Conectores:**  
    - RJ-45 para 10BASE-T/100BASE-TX.
    - MT-RJ para los modelos SX (1000BASE-SX).
  - **Estándares soportados:**  
    - IEEE 802.1x, 802.3x, 802.1D, 802.1p, 802.1Q, 802.3u, 802.3ad, y 1000BASE-X.
  - **Redundancia de energía:**  
    - Compatibilidad con sistemas redundantes (Cisco RPS 675).

---

### Procedimiento
- a. Conectar una PC al puerto de consola del switch Cisco a 9600 baudios utilizando PUTTY.
  - Conectar el puerto de consola a una conversor a interfaz serial.

  <p align="center">
      <img src="./capturas/Puerto.png" alt="ISI" width="600"/>
  </p>
  <p align="center">Figura 1: Puerto del conversor USB-RS232.</p>
  <br>  

  - (Opcional) En caso de no tener interfaz serial, utilizar un conversor a USB. 
  - Conectar a la computadora para la conexion.
  - Utilizar administrador de dispositivos (Windows) o setserial (Linux) para determinar el puerto
  - Abrir putty, utilizar la siguiente configuracion:
    - Connection type: Serial
    - Serial line: el puerto determinado en el paso anterior.
    - Speed: 9600
  - (Opcional) Guardar la configuracion para uso en el futuro.
  - Open

- b. Acceder a las opciones de administración del switch y modificar claves de acceso.
  - Se accedió a las opciones de administración y se modificaron las claves de acceso. Luego se ingresó al modo privilegiado. Se accedió al modo de configuración global. Se configuró la clave para el modo privilegiado. Finalmente se estableció una clave de acceso por consola:
  
<br>
<p align="center">
    <img src="./capturas/Passwords.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 2: User Access Verification en PuTTY.</p>
<br>

<p align="center">
    <img src="./capturas/Passwords2.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 3: Enable Secret en PuTTY.</p>
<br>

- c.Conectar dos computadoras al switch, configurar una red y testear conectividad.
Se asignaron direcciones IP manualmente en cada computadora y se realizó una prueba de conectividad con ping

<p align="center">
    <img src="./capturas/Ping.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 4: Ping entre dos computadoras conectadas al switch.</p>
<br>
- d. Configuración del puerto en modo mirroring y monitoreo del tráfico

1- Conectar las computadoras y el switch

En primer lugar debemos tener las dos computadoras (PC1 y PC2) conectadas al switch. Luego, conectar la tercera (PC3) al switch en el puerto que será utilizado como puerto espejo (mirroring).

2- Acceder al switch mediante consola.

Usar el cable de consola (RJ-45) y conectar el switch a una computadora con PuTTY.

3- Configurar el puerto en modo mirroring (SPAN - Switched Port Analyzer)

 -Ingresar en modo de configuración global:
 
      enable
      configure terminal
      
 -Configura el puerto de origen (los puertos donde están conectadas PC1 y PC2) para que sean monitoreados:
 
      monitor session 1 source interface fastethernet 0/X - both
      monitor session 1 source interface fastethernet 0/Y - both
      
 -Configura el puerto de destino (donde está conectada PC3) para recibir el tráfico duplicado:
 
      monitor session 1 destination interface fastethernet 0/Z
      
 -Guardar la configuración:
 
      write memory
    
4. Capturar el tráfico con Wireshark.
   
    En la PC3, instalar y abrir el programa.

    Seleccionar la interfaz de red conectada al switch.

    Iniciar la captura de paquetes y observar el tráfico entre PC1 y PC2.

5. Finalizar la sesión de monitoreo
   
    no monitor session 1
   
    write memory
   
   De esta forma configuramos correctamente el mirroring del tráfico y pudimos analizar la comunicación entre las computadoras en tiempo real.
---

### Actividades de parte 1 - Análisis de tráfico de la red

- Ejecutando arp -n en Cliente 1 (Miembro del equipo), se verá la dirección IP y la dirección MAC de los dispositivos con los que se ha comunicado.
- En Cliente 2 (Miembro de otro equipo), al ejecutar arp -n, se listarán las direcciones IP y MAC aprendidas.
- En el router, arp -n mostrará las direcciones IP y MAC de los hosts conectados a sus interfaces activas.

- Tablas arp:
<br>
<p align="center">
    <img src="./capturas/arp.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 5: Tabla de ARP.</p>
<br>

---

## Resultados
Durante el proceso de configuración y prueba de conectividad del switch WS-C2950, se lograron obtener los siguientes resultados:

### - Acceso a la consola del switch:

Utilizando el software PuTTY, se logró acceder a las opciones de administración del switch. La conexión fue establecida a través de un conversor USB-RS232, asegurando la correcta transmisión de datos a 9600 baudios.

### - Modificación de claves de acceso:

Se modificaron con éxito las claves de acceso para el modo privilegiado y el acceso por consola, lo cual asegura una mayor seguridad en el acceso al dispositivo.

### - Prueba de conectividad entre dos computadoras:

Tras asignar direcciones IP manualmente en las computadoras, se realizó una prueba de conectividad con el comando ping y se obtuvo una respuesta exitosa, confirmando que las máquinas podían comunicarse entre sí a través del switch.

### - Monitoreo de tráfico mediante mirroring (SPAN):

Se configuró correctamente el puerto de mirroring (SPAN) para capturar el tráfico entre las dos computadoras conectadas al switch y se utilizó Wireshark para analizar el tráfico en tiempo real. Esto permitió observar la transmisión de datos entre las computadoras.

### - Análisis de tráfico de red con ARP:

Se ejecutó con éxito el comando arp -n en diferentes dispositivos (Cliente 1, Cliente 2 y el router), obteniendo las direcciones IP y MAC de los dispositivos conectados, lo cual proporcionó información valiosa sobre las relaciones de conectividad en la red.

---

## Conclusión
Este ejercicio proporcionó una comprensión práctica y detallada del funcionamiento y la configuración de un switch Cisco WS-C2950, así como de sus capacidades de administración, seguridad y monitoreo de tráfico. 
Se encontraron trabas a la hora de generar comunicaciones entre computadoras que usaban el sistema operativo Windows, ya sea utilizando el switch como tambien conectandolas de forma directa. Estas dificultades fueron superadas al utilizar otras con distintas distribuciones de GNU/Linux.
Los siguientes puntos destacan las conclusiones clave:
- Seguridad y administración: El proceso de modificación de contraseñas y configuración de acceso por consola es fundamental para asegurar la integridad del sistema de red. El uso de SSH y la integración con TACACS+ y RADIUS proporcionan un control robusto sobre el acceso al dispositivo.

- Conectividad y rendimiento: El switch demostró un rendimiento adecuado en cuanto a conectividad, alcanzando una buena respuesta en las pruebas de ping y soportando adecuadamente las conexiones de múltiples dispositivos. La capacidad de manejar hasta 8000 direcciones MAC y las opciones de QoS ofrecieron una sólida infraestructura para redes de tamaño medio.

- Monitoreo de tráfico: La configuración del puerto en modo mirroring (SPAN) permitió observar el tráfico de la red, lo que es esencial para análisis de seguridad y optimización de rendimiento. El uso de herramientas como Wireshark resultó muy efectivo para capturar y analizar el tráfico en tiempo real.

- Confiabilidad y facilidad de uso: La configuración y administración del switch fueron relativamente sencillas gracias a las interfaces como Cisco Device Manager y la interfaz de línea de comandos (CLI), lo que facilita la gestión a administradores con diferentes niveles de experiencia.