
# Trabajo Practico nº 1 - Parte I - Conguración y Análisis de tráco IPv4/IPv6

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

## Resumen
En el presente trabajo se aborda la configuración de un entorno de red con soporte dual stack, implementando los protocolos IPv4 e IPv6 mediante el uso de emuladores o simuladores de redes. Se analizan las diferencias en la gestión del tráfico de red, incluyendo el comportamiento de protocolos clave como ARP (Address Resolution Protocol) en IPv4, NDP (Neighbor Discovery Protocol) en IPv6 e ICMP (Internet Control Message Protocol) en ambos casos. Además, se implementa la asignación dinámica de direcciones utilizando el protocolo DHCP, evaluando su funcionamiento tanto en IPv4 (DHCPv4) como en IPv6 (DHCPv6). A lo largo del estudio, se examinan las interacciones entre estos protocolos y su impacto en la conectividad y eficiencia de la red.

**Palabras clave**: Dual Stack IPv4, IPv6, ARP (Address Resolution Protocol), NDP (Neighbor Discovery Protocol), ICMP (Internet Control Message Protocol), DHCP (Dynamic Host Configuration Protocol), DHCPv4, DHCPv6, Emulador de red, Simulador de red, Tráfico de red, Direcciones IP, Subnetting, Router, Switch, Configuración de red, Topología de red, Paquetes de datos, Latencia, Seguridad en redes.

---

## Introducción
En el contexto actual de las redes de computadoras, la coexistencia de los protocolos **IPv4** e **IPv6** es una necesidad fundamental para garantizar la interoperabilidad y la transición entre ambas tecnologías. Este trabajo práctico tiene como objetivo explorar la **configuración de un entorno de red dual stack**, utilizando herramientas de **simulación y emulación** para analizar el tráfico de red y el comportamiento de diversos protocolos.  

A lo largo del desarrollo del trabajo, se estudiará el funcionamiento de **ARP** (*Address Resolution Protocol*) en **IPv4** y **NDP** (*Neighbor Discovery Protocol*) en **IPv6**, así como la comunicación a través de **ICMP** (*Internet Control Message Protocol*). Además, se implementará la **asignación dinámica de direcciones** mediante el uso de **DHCPv4** y **DHCPv6**, evaluando su impacto en la configuración y administración de redes.  

Para la implementación y análisis, se utilizarán herramientas como **GNS3**, **Packet Tracer** y **CORE**, que permiten la creación y prueba de escenarios de red de manera controlada. Finalmente, se realizarán pruebas de conectividad y capturas de tráfico para examinar el intercambio de información entre los dispositivos, comprendiendo mejor el proceso de resolución de direcciones y la gestión de los paquetes de datos en un entorno de **red dual stack**.  

---

### Para luego realizar las actividades, se planteo la siguiente red y Tabla de asignación de direcciones
<br>
<p align="center">
    <img src="./imagenes/01_red.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 1: Red de estudio.</p>
<br>
<br>
<p align="center">
    <img src="./imagenes/02_tabla.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura 2: Tabla de asignaciones de direcciones.</p>
<br>

---

## Desarrollo

## 1. Desarrollar un marco teórico resumido, suficiente para fundamentar los procedimientos a realizar.

## 2. Diagrama de red en el software Cisco Packet Tracer.
En este trabajo se ha realizó la construcción del diagrama de red propuesto utilizando el software de simulación Cisco Packet Tracer. Este software permite diseñar, configurar y probar redes de computadoras en un entorno virtual antes de implementarlas físicamente.
El diseño de la red incluye un router que actúa como intermediario entre los dispositivos, un switch que permite la conexión y comunicación entre múltiples dispositivos finales y tres hosts (h1, h2 y h3) que representan computadoras conectadas a la red.

<p align="center">
    <img src="./imagenes/03_diagrama_de_red.png" alt="ISI" width="600"/>
</p>

Se configuró un router Cisco con direcciones IPv4 e IPv6, habilitando el enrutamiento entre subredes. Se asignaron IP a las interfaces GigabitEthernet0/0 y 0/1, conectando h1, h2 y h3. Se activó el enrutamiento IPv6 con ipv6 unicast-routing y se habilitaron las interfaces con no shutdown. Luego, se guardó la configuración en NVRAM (copy running-config startup-config). Finalmente, se verificó la asignación de direcciones con show ipv6 interface brief. Esto permitió la comunicación entre los hosts en IPv4 e IPv6.
Aquí la configuración:
```
Router(config-if)#exit
Router(config)#interface gigabit0/1
Router(config-if)#ip address 192.168.2.12 255.255.255.0
Router(config-if)#no shutdown
Router(config-if)#
%LINK-5-CHANGED: Interface GigabitEthernet0/1, changed state to up
%LINEPROTO-5-UPDOWN: Line protocol on Interface GigabitEthernet0/1, changed state to up
Router(config-if)#exit
Router(config)#end
Router#
%SYS-5-CONFIG_I: Configured from console by console
Router#copy running-config startup-config 
Destination filename [startup-config]? 
Building configuration...
[OK]
Router#configure terminal
Enter configuration commands, one per line.  End with CNTL/Z.
Router(config)#ipv6 unicast-routing
Router(config)#interface gigabitEthernet0/0
Router(config-if)#ipv6 address 2001:aaaa:bbbb:1::11/64
Router(config-if)#no shutdown
Router(config-if)#exit
Router(config)#interface gigabitEthernet0/1
Router(config-if)#ipv6 address 2001:aaaa:cccc:1::12/64
Router(config-if)#no shutdown
Router(config-if)#exit
Router(config)#end
Router#
%SYS-5-CONFIG_I: Configured from console by console
Router#copy running-config startup-config
Destination filename [startup-config]? 
Building configuration...
[OK]
Router#show ipv6 interface brief
GigabitEthernet0/0         [up/up]
    FE80::201:C9FF:FE50:301
    2001:AAAA:BBBB:1::11
GigabitEthernet0/1         [up/up]
    FE80::201:C9FF:FE50:302
    2001:AAAA:CCCC:1::12
GigabitEthernet0/2         [administratively down/down]
    unassigned
Vlan1                      [administratively down/down]
    unassigned
Router#
```

## 3. Diferencias entre un simulador y un emulador.
Los emuladores y simuladores son herramientas de prueba en entornos virtuales utilizadas para recrear escenarios de red, con diferencias importantes en funcionamiento y casos de uso.

**Simulador:**  

Modelado abstracto: Recrea el comportamiento de la red a traves de modelos matematicos o logicos, permitiendo analizar el comportamiento teorico de protocolos y topologias sin implementacion en el entorno fisico.
Son particularmente utiles para el estudio de rendimiento, escalabilidad y el impacto de cambios en la red en condiciones controladas, asi como tambien para la investigacion y el diseño, dado que permiten experimentar con distintos escenarios sin los costos asociados a la implementacion fisica ni recrear cada etapa del hardware.

**Emulador:**

Recreación Fiel del Entorno Real: Intenta replicar tanto el hardware como el software de los dispositivos de la red, permitiendo pruebas mucho mas fieles a los sistemas reales.
Se utilizan para probar interoperabilidad, rendimiento y funcionalidad de equipos o servicios en condiciones cercanas a las reales, lo que es un paso clave en la validacion de sistemas antes de su despliegue en produccion. 
Debido a la emulacion de componentes reales en forma fisica, en general requieren mas recursos y son mas complejos que los simuladores, con el beneficio de una presicion mayor.

| Característica | Emuladores | Simuladores |
| ----------- | ----------- | ----------- |
| **Nivel de Abstracción** | Replica entorno real | Modela comportamiento |
| **Precisión** | Alta precisión real | Aproximacion teórica |
| **Recursos** | Más recursos requeridos | Menos recursos |
| **Velocidad** | Lento por emulación | Rápido en simulación |
| **Uso** | Validación y depuración | Análisis y diseño |
| **Tráfico Real** | Soporta tráfico real | Sin tráfico real |
| **Ejemplos** | Mininet, CORE, GNS3 | OMNeT++, Packet Tracer |

## 4. Evaluación de conectividad entre todos los host para IPv4.

Para evaluar la conectividad entre todos los hosts, se envió tres paquetes ICMPv4 utilizando el comando ping en cada uno de ellos. Se verificó que las respuestas fueran exitosas, confirmando la comunicación en la red. Este procedimiento permitió comprobar que el enrutamiento y la configuración de direcciones IPv4 fueran correctos, asegurando que h1, h2 y h3 pudieran intercambiar datos sin interrupciones.

<p align="center">
    <img src="./imagenes/04_h1_IPv4.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/05_h2_IPv4.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/06_h3_IPv4.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/07_router_IPv4.png" alt="ISI" width="600"/>
</p>

## 5. Evaluación de conectividad entre todos los host para IPv6.
Para comprobar la conectividad entre todos los hosts, se enviaron tres paquetes ICMPv6 con el comando ping6 desde cada uno. Se verificó que todas las respuestas fueran satisfactorias, asegurando una comunicación estable en la red. Con este proceso, se confirmó que la configuración de IPv6 y el enrutamiento funcionaban correctamente, permitiendo la comunicación sin problemas entre h1, h2 y h3.

<p align="center">
    <img src="./imagenes/08_h1_IPv6.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/09_h2_IPv6.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/10_h3_IPv6.png" alt="ISI" width="600"/>
</p>
<p align="center">
    <img src="./imagenes/11_router_IPv6.png" alt="ISI" width="600"/>
</p>

## 6.  Análisis de Comunicaciones en la Red
 a) Comunicaciones ARP observadas
Durante la comunicación ICMP, se observan mensajes ARP (Address Resolution Protocol) que son cruciales para la resolución de direcciones IP a direcciones MAC. Este proceso ocurre cuando un dispositivo necesita conocer la dirección MAC de otro dispositivo dentro de la misma red local.
Por ejemplo, cuando PC0 quiere enviar un mensaje a PC1 (que tiene la IP 192.168.2.10), primero envía un ARP Request preguntando "¿Quién tiene 192.168.2.10?". PC1, al recibir este ARP Request, responde con su dirección MAC a través de un ARP Reply. Este mecanismo es fundamental para que los dispositivos se comuniquen dentro de una red.

 b) Direcciones IP en los datagramas
En los paquetes ICMP (como los generados por los comandos de ping), podemos observar las direcciones IP de origen y destino. En este caso específico, cuando PC0 realiza un ping a PC1, se verá un paquete ICMP donde la dirección de origen es la de PC0 (192.168.1.10) y la dirección de destino es la de PC1 (192.168.2.10). Las direcciones IP son esenciales para la correcta entrega del paquete a través de diferentes redes.

 c) Determinación de la comunicación entre hosts por parte del enrutador
El enrutador juega un papel crucial en la comunicación entre redes distintas. Para determinar cómo se debe enviar un paquete de un host a otro, el enrutador consulta su tabla de enrutamiento. En este caso, PC0 y PC1 están en redes diferentes (192.168.1.x y 192.168.2.x), por lo que el enrutador debe tomar decisiones basadas en la dirección IP de destino. El enrutador sabe que debe reenviar el tráfico de PC0 hacia la red de PC1, ya que la IP de destino (192.168.2.10) pertenece a la red 192.168.2.x.

 d) Función del switch y por qué no tiene direcciones IP
El switch es un dispositivo que opera en la capa 2 del modelo OSI, es decir, en la capa de enlace de datos. Su principal función es conectar dispositivos dentro de la misma red local (LAN) y reenviar tramas de datos entre ellos. No necesita direcciones IP porque no está involucrado en la toma de decisiones sobre el enrutamiento de paquetes entre diferentes redes. El switch utiliza las direcciones MAC de los dispositivos para determinar cómo reenviar las tramas de manera eficiente dentro de la misma red.

 e, f, g) Contenido de las tablas ARP en cada equipo
Las tablas ARP son esenciales para la comunicación dentro de una red local, ya que permiten mapear direcciones IP a direcciones MAC. Al analizar las tablas ARP en los dispositivos, podemos ver qué direcciones MAC conocen los diferentes equipos y cómo estas están asociadas con direcciones IP específicas.
PC0 solo conoce la dirección MAC de su gateway (el router en la dirección 192.168.1.11), ya que no ha tenido necesidad de comunicarse directamente con otros dispositivos en la red.
PC1, por otro lado, conoce tanto la dirección MAC de PC2 (192.168.2.11) como la del router (192.168.2.12), dado que ambas son necesarias para su funcionamiento dentro de la red.
PC2 solo tiene registrada la dirección MAC de PC1 (192.168.2.10) porque se ha comunicado directamente con él, pero aún no ha enviado tráfico hacia fuera de su red, por lo que no tiene la MAC del router registrada.

 h) Direcciones de broadcast en IPv4
Las direcciones de broadcast en IPv4 son direcciones especiales utilizadas para enviar mensajes a todos los dispositivos dentro de una red local. Por ejemplo, la dirección 192.168.1.255 es una dirección de broadcast en la red 192.168.1.0/24. Esto permite que los paquetes se distribuyan a todos los dispositivos dentro de esa red, lo cual es útil para servicios como ARP y DHCP.

 i) Direcciones multicast en IPv4
Las direcciones multicast en IPv4 se utilizan para enviar tráfico a un grupo de dispositivos en lugar de a un único dispositivo. Estas direcciones pertenecen al rango 224.0.0.0 a 239.255.255.255. Un ejemplo común de una dirección multicast es 224.0.0.1, que se usa para enviar tráfico a todos los hosts en la red local.

El análisis del tráfico ICMP y las tablas ARP nos muestra cómo los dispositivos dentro de una red se comunican y cómo los mecanismos de ARP y enrutamiento facilitan esta comunicación. Las direcciones IP y MAC, junto con los conceptos de broadcast y multicast, son esenciales para el funcionamiento eficiente de la red.


## 7.
Los tipos de mensajes NDP observados son:
- Neighbor Solicitation (NS): Enviado por el host que quiere conocer la dirección física de otro nodo.
- Neighbor Advertisement (NA): Respuesta al NS, proporcionando la dirección física.
<br>
<p align="center">
    <img src="./imagenes/NDPh1.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura x: Datagrama NDP en h1.</p>
<br>
<br>
<p align="center">
    <img src="./imagenes/NDPh3.png" alt="ISI" width="600"/>
</p>
<p align="center">Figura x: Datagrama NDP en h3.</p>
<br>
En IPv6 el protocolo NDP (Neighbor Discovery Protocol) reemplaza al ARP usado en IPv4. NDP utiliza mensajes ICMPv6 para descubrir nodos en la red, resolver direcciones de enlace y realizar el resto de sus funciones.

Funciones Principales de NDP:
- Descubrimiento de vecinos: Permite que los nodos descubran la dirección de enlace (MAC) de otros dispositivos en la misma red.
- Detección de direcciones duplicadas (DAD): Verifica que una dirección IPv6 asignada no esté ya en uso.
- Descubrimiento de routers: Los hosts pueden encontrar routers en la red mediante mensajes RS y RA.
- Redirección: Permite a los routers redirigir el tráfico a rutas más óptimas.

En IPv6 no existe el concepto de broadcast, por lo que se utiliza el mecanismo de multicast para reemplazar esa función. En lugar de enviar un paquete a todas las direcciones de la red, se envía a un grupo específico de direcciones multicast, lo que permite dirigir el tráfico solo a los dispositivos interesados en recibirlo, como es el caso de la dirección multicast ff02::1 para todos los nodos en el enlace. Este enfoque optimiza el uso de la red y reduce el tráfico innecesario.

- Direcciones Link-local:
Se utilizan para la comunicación entre dispositivos en el mismo segmento de red. Se configuran automáticamente y tienen el prefijo fe80::/10. Estas direcciones no son ruteables fuera del enlace local y son esenciales para funciones básicas como el descubrimiento de vecinos.
- Direcciones Unique-local:
Las direcciones unique-local son análogas a las direcciones privadas en IPv4. Definidas en el rango fc00::/7, se usan en redes internas o corporativas. No se rutean en Internet, lo que permite que los dispositivos se comuniquen de forma segura dentro de una red privada sin exponer información a la red pública.
- Direcciones Globales:
Las direcciones globales son ruteables a nivel mundial y permiten la comunicación a través de Internet. Generalmente se asignan con el prefijo 2000::/3 y son asignadas por proveedores de servicios de Internet. Estas direcciones facilitan la identificación única de dispositivos en cualquier parte del mundo.

| Característica   | Link-Local | Unique-Local | Global |
| --------- | ---------- | ---------- | ---------- |
| **Prefijo** | fe80::/10 | fc00::/7 | 2000::/3 |
| **Ruteabilidad** | Solo en el enlace local | Solo en redes privadas | Ruteable en Internet |
| **Configuración**| Automática (SLAAC) | Manual o automática | Asignada por ISP o administrativamente |
| **Uso** | Comunicación en el mismo segmento | Redes internas, comunicación privada | Comunicación global, acceso a Internet  |


--- 

### Nivel de título 3

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

| Ejemplo | Tabla |
| ----------- | ----------- |
| Header | Title |
| Paragraph | Text |

```
// Más código
{
  "firstName": "John",
  "lastName": "Smith",
  "age": 25
}
```

---

## Resultados

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

---

## Discusión y conclusiones

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

## Referencias

[1] Consultar [Normas APA](https://normas-apa.org/referencias/)

[2] ...

[3] ...
