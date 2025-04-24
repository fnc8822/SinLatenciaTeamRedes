# Trabajo Practico nº 2 - Topologías multi-path y evaluación de performance en redes

**Institucion: UNC - Facultad de Ciencias Exactas, Físicas y Naturales**  
**Materia: Redes de Computadoras**

**Profesores**
- Facundo Oliva Cuneo (Teórico).
- Santiago Martín Henn (Laboratorios).

**Fecha: 24-04-2025** 

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
## Introducción
En el contexto actual de redes de computadoras, la eficiencia, robustez y capacidad de adaptación del tráfico de datos son elementos fundamentales para el rendimiento general del sistema. Las topologías multi-path representan una solución moderna para mejorar la disponibilidad y el balanceo de carga en redes, permitiendo que múltiples caminos estén disponibles entre el origen y el destino de la información. En este laboratorio se propone no solo la comprensión teórica de estas topologías, sino también su implementación práctica y la evaluación de su performance en un entorno controlado. A través del uso de herramientas como iperf3 y Wireshark, se busca adquirir experiencia en la configuración de redes estáticas y dinámicas, tanto en entornos virtuales como físicos, analizando métricas clave del tráfico como el ancho de banda, latencia, tamaño de paquetes y pérdida de datos. El trabajo se realiza de forma colaborativa, permitiendo diseñar una red distribuida entre distintos grupos y evaluando el rendimiento mediante pruebas controladas.

---
## Resumen
El presente informe se centra en el estudio e implementación de topologías de red multi-path, con énfasis en la evaluación del rendimiento en un entorno físico de laboratorio. Se abordan objetivos como la configuración de enrutamiento estático y dinámico, y el uso de herramientas de análisis como iperf3 para pruebas de red TCP y UDP, así como Wireshark para la captura y filtrado de tráfico. Se diseñó una parte de la red, configurando equipos con IPs fijas y evaluando la conectividad y el rendimiento entre nodos tanto de nuestro grupo como de distintos grupos. Las pruebas incluyen parámetros como el tamaño y frecuencia de paquetes, ancho de banda y duración, comparando resultados entre protocolos y distintas configuraciones. Finalmente, se analizan los datos recolectados para extraer conclusiones sobre el comportamiento de la red y el impacto de las decisiones de configuración sobre su performance.

---
## Marco teórico

**Topologías Multi-path**

Las topologías multi-path se basan en la existencia de múltiples caminos físicos o lógicos entre un origen y un destino en una red. Esto permite balancear la carga de tráfico, mejorar la tolerancia a fallos y aumentar la disponibilidad, ya que si una ruta falla, otras pueden seguir operando. Se utilizan comúnmente en redes complejas como centros de datos o infraestructuras críticas.

**Enrutamiento Estático**

El enrutamiento estático implica configurar manualmente las rutas en cada dispositivo de red. Ofrece simplicidad y control total sobre el tráfico, pero carece de adaptabilidad ante cambios o fallos en la red. Es útil en redes pequeñas o para propósitos educativos, donde se desea controlar de forma explícita el comportamiento del tráfico.

**Enrutamiento Dinámico**

Este tipo de enrutamiento utiliza protocolos que descubren rutas automáticamente y se adaptan a cambios en la red. Protocolos como OSPF, RIP o BGP calculan la mejor ruta basada en métricas como costo, latencia o número de saltos. Aumenta la escalabilidad y la resiliencia, pero añade complejidad y puede generar tráfico adicional.

**iperf3**

iperf3 es una herramienta de código abierto para medir el rendimiento de la red entre dos hosts. Permite probar con TCP y UDP, definir el ancho de banda, duración de la prueba, tamaño y número de paquetes, entre otros parámetros. Es esencial para medir el throughput, jitter y pérdidas, y comparar el rendimiento entre configuraciones distintas.

**Protocolo TCP**

TCP (Transmission Control Protocol) es un protocolo orientado a la conexión que garantiza la entrega ordenada y completa de los datos. Implementa mecanismos de control de congestión y confirmación de paquetes, lo que lo hace confiable pero menos eficiente en situaciones donde la velocidad es prioritaria.

**Protocolo UDP**

UDP (User Datagram Protocol) es un protocolo no orientado a la conexión que envía paquetes sin verificar su llegada. Es útil para aplicaciones en tiempo real (como video o juegos), pero puede experimentar pérdida de datos si la red está sobrecargada, ya que no implementa retransmisión ni control de congestión.

**Wireshark**

Wireshark es un analizador de protocolos de red que permite capturar y visualizar el tráfico en tiempo real. Permite aplicar filtros por IP, protocolo, puerto, etc., lo que facilita el análisis detallado de las pruebas realizadas. Es útil para comprobar el funcionamiento de la red y diagnosticar problemas.

**ICMP y pruebas de conectividad**

El protocolo ICMP (Internet Control Message Protocol) se utiliza para diagnosticar problemas de red, siendo el más conocido el comando ping, que comprueba la conectividad entre dos nodos. Es útil para verificar si las rutas están bien configuradas y si los dispositivos responden correctamente.

**Balanceo de carga y redundancia**
En una topología multi-path, el tráfico puede ser distribuido entre múltiples rutas, lo que ayuda a balancear la carga de red y evita cuellos de botella. Además, en caso de fallo de una ruta, otras pueden asumir el tráfico, aumentando la disponibilidad del sistema.

---
## Desarrollo

Como primer paso en el desarrollo del laboratorio, se procedió a la configuración manual de direcciones IP estáticas en las notebooks del grupo. Las IPs fueron asignadas respetando el rango de red definido para cada grupo, asegurando que no existieran conflictos de direcciones duplicadas:

  <p align="center">
      <img src="./Capturas/IP estatica.png" alt="ISI" width="600"/>
  </p>
  <p align="center">Configuración IP fija.</p>
  <br> 

Una vez configuradas las IPs en cada notebook, se realizaron pruebas de conectividad mediante el protocolo ICMP, utilizando el comando ping. Inicialmente, se comprobó la conexión entre hosts pertenecientes al mismo grupo y conectados al mismo switch. Esta prueba permitió verificar la correcta configuración de la interfaz de red, el estado operativo del cableado y la funcionalidad básica del switch. Posteriormente, se amplió la prueba a la comunicación entre hosts de distintos grupos, conectados a través de switches y routers intermedios. Esto permitió validar la interoperabilidad entre subredes y comprobar que las rutas necesarias estaban correctamente definidas o disponibles para el paso de paquetes entre diferentes segmentos de la red. 

Para llevar a cabo las pruebas de rendimiento de red, se utilizó la herramienta iperf3, descargada desde https://iperf.fr. Esta herramienta permite medir parámetros clave como el ancho de banda, la latencia y la estabilidad de la conexión, mediante una arquitectura cliente-servidor. En nuestro caso, se ejecutó sobre sistemas Windows, desde la línea de comandos, usando la versión iperf3.exe.
Durante el trabajo, se utilizaron varios servidores públicos disponibles en Internet para realizar pruebas reales desde los equipos del laboratorio. En todos los casos, se configuró iperf3 como cliente, con distintos parámetros de configuración. A continuación se describen los principales aspectos explorados:

### **Protocolos TCP y UDP**

Por defecto, iperf3 utiliza el protocolo TCP. Para realizar pruebas con UDP, se empleó el parámetro -u.

```
TCP: ./iperf3.exe -c iperf.he.net -p 5201
```

En la siguiente imagen se observa el resultado de una prueba TCP, con un ancho de banda estable de aproximadamente 41.2 Mbits/sec:

  <p align="center">
      <img src="./Capturas/Iperf 1.png" alt="ISI" width="600"/>
  </p>
  <p align="center">texto??.</p>
  <br> 

```
UDP: ./iperf3.exe -u -c iperf.he.net -p 5201
```

En esta prueba UDP se solicitó un ancho de banda de 100 Mbits/sec. El resultado muestra una tasa efectiva de 98.7 Mbits/sec con una pérdida muy baja de paquetes (0.1%):

  <p align="center">
      <img src="./Capturas/Iperf 2.png" alt="ISI" width="600"/>
  </p>
  <p align="center">texto??.</p>
  <br> 

**Número y tamaño de paquetes**: Aunque en las pruebas realizadas no se modificó explícitamente el tamaño de los paquetes, iperf3 permite configurar el tamaño del buffer (y por ende el tamaño de los paquetes) con el parámetro -l. Este aspecto podría explorarse más a fondo en pruebas futuras.

**Frecuencia/tiempo**: Las pruebas por defecto duran 10 segundos, pero pueden ajustarse con el parámetro -t. En este caso, se mantuvo la duración por defecto. Este valor determina la cantidad total de datos transmitidos durante la prueba.

**Ancho de banda**: En las pruebas con protocolo UDP, se especificó el ancho de banda deseado utilizando el parámetro -b. Por ejemplo, -b 0 solicita el mayor ancho de banda posible dentro de los límites de la red.
./iperf3.exe -b 0 -u -c iperf.he.net -p 5201 → prueba UDP con ancho de banda ilimitado.
./iperf3.exe -b 0 -c iperf.he.net -p 5201 → prueba TCP (el -b se ignora en este caso, ya que TCP ajusta automáticamente la tasa de envío).

Puerto personalizado (-p): Se realizaron pruebas contra distintos servidores escuchando en puertos específicos, utilizando el parámetro -p. Esto permitió conectarse a servicios alternativos de iperf y evitar conflictos en el entorno.
Ejemplos:
./iperf3.exe -c ping.online.net -p 5201
./iperf3.exe -c 34.176.225.102 -p 2222

Estas pruebas permitieron observar diferencias claras entre los comportamientos de TCP y UDP, así como evaluar el desempeño de los enlaces bajo distintas configuraciones. Se obtuvieron resultados realistas al utilizar servidores externos, con los que se pudo medir el impacto de la latencia, la congestión y la variabilidad del tráfico en Internet.


3) Configurar Wireshark (o algún software de sniffing similar) para filtrar tráfico basándose en las IPs de partida/destino. Capturar tráfi co y ejecutar pruebas con un host (pc) como servidor y otro como cliente, con distintas configuraciones de protocolos y configuraciones entre:
a) Dos computadoras en un mismo grupo (no olvidar configurar el capturador en loopback)
b) Una computadora de un grupo y computadoras de al menos otros 2 (dos) grupos
Documentar capturas de wireshark y las consolas corriendo iperf.

4) Elaborar conclusiones sobre los siguientes aspectos: ¿Cuál es el ancho de banda promedio de la prueba? ¿Cuánto duró la prueba? ¿Cuál es el tamaño promedio de paquetes? ¿Observas alguna diferencia entre UDP y TCP? ¿Observamos relación entre alguno de los parámetros de la prueba y la pérdida de paquetes?

5) Ejecutar una prueba como cliente desde una computadora del grupo hacia un servidor propuesto en clase. Documentar los resultados y elaborar conclusiones sobre los aspectos del punto 4, además de comparar con los resultados de las pruebas del punto 3)

---
## Resultados

---
## Conclusion

---
## Referencias

