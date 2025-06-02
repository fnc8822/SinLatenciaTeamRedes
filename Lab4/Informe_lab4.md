# Trabajo Práctico N°4: Ruteo externo dinámico y sistemas autónomos
**Institucion: UNC - Facultad de Ciencias Exactas, Físicas y Naturales**  
**Materia: Redes de Computadoras**
**Profesores**
- Facundo Oliva Cuneo (Teorico).
- Santiago Martín Henn (Laboratorios).

---

**Nombre del grupo: Sin Latencia Team**

**Nombres de los integrantes**
- Efrain G. Veliz S.
- Elio N. Ludueña
- Juan I. Sassi 
- Franco L. Cirrincione

**Información de los autores**
- efrain.veliz@mi.unc.edu.ar
- nicoluduena@mi.unc.edu.ar
- juan.sassi@mi.unc.edu.ar
- francocirrincione@mi.unc.edu.ar

---
## Parte I - Integración de conceptos, actividades online e investigación

1) Investigar y elaborar reportes sobre los siguientes conceptos e información sobre AS:
- a) ¿Qué es un Autonomous System (AS)?
- b) ¿Qué es un Autonomous System Number (ASN) y cómo está conformado?
- c) Buscar 3 ejemplos de ASN de empresas, universidades u organizaciones.
- d) ¿Cual es el ASN de tu conexión actual? Averigualo. Recopilar la información que consideres más
relevante sobre tu ASN ¿Qué protocolos soporta (IPv4/6, multicast, etc)?
### Respuestas:
- a) Un Autonomous System (AS), o Sistema Autónomo, es un conjunto de direcciones IP (IPv4 o IPv6) agrupadas bajo una misma política de enrutamiento y que están administradas por una única entidad u organización. Este conjunto de redes funciona como una unidad coherente desde el punto de vista del enrutamiento exterior, y se comunica con otros sistemas autónomos mediante protocolos de enrutamiento de tipo interdominio, como el BGP (Border Gateway Protocol).
- b) Un Autonomous System Number (ASN) es un identificador numérico único asignado a cada Sistema Autónomo (AS). Este número permite a los sistemas autónomos intercambiar información de enrutamiento a través del protocolo BGP (Border Gateway Protocol), que es el protocolo estándar para el enrutamiento entre dominios en Internet.Pueden ser publicos o privados, expresarse como decimal simple (ej: 13335) o con punto (ej: 1.10 para 65546) y tiene dos formatos 16 bits (clasico de 1 al 65535) y el de 32 bits(expandido de 65536 hasta 4294967295).
- c) ejemplos de ASN:
    - Google Inc -> ASN:15169 -> nombre:GOOGLE -> Estados unidos, servicios en la nube,busquedas, etc.
    - Universidad Nacional de Córdoba(Argentina) -> ASN:262236 -> nombre:UNC-AS -> Argentina,Red academica y administrativa de la unuiversidad.
    - Netflix Inc -> ASN:2906 -> nombre:NETFLIX -> Estados unidos, transmision de contenido multimedia.
- d) Estas pruebas se realizaron en la computadora de un compañero dle grupo y dio los siguientes resultados:
    ASN: AS7303 (Telecom Argentina SA), ubicado en argentina y es un tipo de red ISP (Proveedor de Servicios de Internet) con una asignacion de IP aproximadamente de 8.4 millones.Rango de IP asociado: 190.16.0.0/14. Soporta IPv4 e IPv6 (Multicast: Generalmente no disponible para usuarios residenciales).
    
2) 

---

## Parte II - Simulaciones y análisis