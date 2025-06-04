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
# Parte I - Integración de conceptos, actividades online e investigación

## 1) Investigar y elaborar reportes sobre los siguientes conceptos e información sobre AS:
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
    
## 2) Investigar y elaborar reportes sobre los siguientes conceptos e información sobre BGP:
- a) ¿Qué es el Border Gateway Protocol (BGP)?
- b) Resumir el funcionamiento del BGP a través de sus procedimientos funcionales: adquisición de
vecino, detección de vecino alcanzable, detección de red alcanzable. Explicar tipos de mensajes y
formato de paquetes en BGP.
- c) Explicar la diferencia entre BGP externo (eBGP) y BGP interno (iBGP) en función de la
información que se intercambia dentro de un AS. En el siguiente ejemplo ¿Cuál(es) AS son de
tránsito?
    <br>
    <p align="center">
        <img src="./imagenes/imagen01_2_C.png" alt="ISI" width="600"/>
    </p>
    <p align="center">Figura 1: ejemplo AS.</p>
    <br>
- d) Buscar las conexiones del AS en mi conexión actual. ¿Cuántas conexiones eBGP tiene mi AS?,incluir un gráfico de los AS a uno o dos grados de separación (Ejemplo).
- e) Buscar las conexiones del AS conectándome a alguna red distinta a la del punto anterior (puede ser 4G/5G de mi teléfono, alguna red en la facultad, etc.). ¿Qué diferencias/similitudes puedo identicar?
- f) Investigar algún problema en enrutamiento BGP que haya tenido un impacto en servicios de red a nivel nacional/internacional. Elaborar un resumen de las causas y las consecuencias.

## Respuestas:
- a) El BGP (Border Gateway Protocol) es un protocolo de enrutamiento de capa de aplicación (capa 7) que opera sobre TCP, es de tipo vector de ruta diseñado para intercambiar información de enrutamiento entre diferentes Sistemas Autónomos (AS) en Internet. Es el protocolo principal de enrutamiento interdominio, y permite construir la tabla de enrutamiento global de Internet, asegurando que los paquetes lleguen a su destino a través del mejor camino disponible.
- b) Funcionamiento del **BGP** y procedimientos funcionales
BGP funciona a través de sesiones entre pares o vecinos (peers) que intercambian rutas y atributos. Sus procedimientos funcionales clave son:
    - 1. **Adquisición de vecino (Neighbor Acquisition):**
        * Dos routers BGP (vecinos) establecen una **conexión TCP en el puerto 179**.
        * Una vez conectados, se intercambian mensajes **OPEN** para iniciar la sesión BGP.
        * Se definen parámetros como número de AS, ID del router, versión de BGP, etc.

    - 2. **Detección de vecino alcanzable (Keepalive):**
        * Los routers envían periódicamente mensajes **KEEPALIVE** para confirmar que la conexión está activa.
        * Si no se reciben mensajes en un tiempo definido (hold time), la sesión se considera caída.

    - 3. **Detección de red alcanzable (Route Advertisement):**
        * Una vez establecida la sesión, los routers BGP intercambian mensajes **UPDATE**, anunciando nuevas rutas o retirando rutas que ya no están disponibles.
        * Estas rutas incluyen atributos como el **AS\_PATH**, **NEXT\_HOP**, **MED**, **LOCAL\_PREF**, etc.

- **Tipos de mensajes en BGP:**
    1. **OPEN**: Inicia la sesión entre dos vecinos BGP.
    2. **UPDATE**: Anuncia nuevas rutas o elimina rutas obsoletas.
    3. **KEEPALIVE**: Mantiene activa la sesión entre routers.
    4. **NOTIFICATION**: Informa errores o condiciones excepcionales y termina la conexión.

- **Formato básico de un paquete BGP:**
Todos los mensajes BGP comienzan con un **header de 19 bytes**, que incluye:
    * **Marker** (16 bytes): para autenticación o compatibilidad.
    * **Length** (2 bytes): tamaño total del mensaje.
    * **Type** (1 byte): indica el tipo de mensaje (1=OPEN, 2=UPDATE, etc.).

Luego, cada tipo de mensaje tiene su propio formato específico (por ejemplo, los UPDATE incluyen prefijos IP, atributos de ruta, etc.).

- **c) Diferencia entre eBGP e iBGP**

| Característica           | **eBGP** (External BGP)                             | **iBGP** (Internal BGP)                           |
| ------------------------ | --------------------------------------------------- | ------------------------------------------------- |
| Ámbito                   | Entre **diferentes AS**                             | Dentro del **mismo AS**                           |
| Intercambio de rutas     | Rutas entre AS vecinos                              | Rutas aprendidas dentro del mismo AS              |
| Reescritura del AS\_PATH | Se agrega el número del AS local                    | No se modifica el AS\_PATH                        |
| TTL predeterminado       | 1 (router vecino debe estar directamente conectado) | 255 (se puede enrutar dentro del AS)              |
| Uso típico               | Conexiones entre ISPs o redes grandes               | Distribución interna de rutas aprendidas por eBGP |

- En nuestro ejemplo **AS2** es de transito. y sirve de pente entre AS1 y AS3.
---



---
#Parte II - Simulaciones y análisis