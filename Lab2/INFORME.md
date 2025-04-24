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

Primero se configuraron las notebooks con IPs fijas, se comprobó conexión con paquetes ICMP entre host conectados al mismo switch y otros dispositivos de otros grupos:

  <p align="center">
      <img src="./capturas/IP estatica.png" alt="ISI" width="600"/>
  </p>
  <p align="center">Figura 1: IP fija.</p>
  <br> 

---
## Resultados

---
## Conclusion

---
## Referencias

