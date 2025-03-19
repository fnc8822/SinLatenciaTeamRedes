
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

## 6. 

## 7.


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