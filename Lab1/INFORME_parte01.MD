
# Trabajo Practico nº 1 - Parte I - Conguración y Análisis de tráco IPv4/IPv6

**Institucion: UNC - Facultad de Ciencias Exactas, Físicas y Naturales**  
**Materia: Redes de Computadoras**

**Profesores**
- Facundo Oliva Cuneo (Teorico).
- Santiago Martín Henn (Laboratorios).

**Fecha: 27-03-2025** 

---
## Nombre del grupo: Sin Latencia Team** 

## Nombres de los integrantes**  
- Efrain G. Veliz S.
- Elio N. Ludueña
- Juan I. Sassi 

## Información de los autores
- efrain.veliz@mi.unc.edu.ar
- nicoluduena@mi.unc.edu.ar
- juan.sassi@mi.unc.edu.ar

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

# Marco teórico / Modelo / Metodología

## Nivel de título 2

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed tempor, mauris sit amet aliquet vestibulum, enim ante consectetur enim, vel sollicitudin odio risus vel libero. Integer eget ipsum sed eros luctus laoreet vel vel leo. Fusce ut dapibus nisl. Aliquam erat volutpat. Donec in elit non justo convallis vestibulum.

`codigo`

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