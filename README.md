# Base de datos de temperaturas usando ESP32, sensor LM35 y conexión web a Google Sheets
Este proyecto tiene como objetivo crear una base de datos de temperaturas en Google Sheets, para esto se va utilizar la placa de desarrollo ESP32 junto con el sensor LM35 para poder enviar las lecturas del sensor a la web y guardarlas en una hoja de cálculo.

## Consideraciones teóricas
### Sensor LM35
El LM35 es un sensor de temperatura, tiene un rango de medición abarca desde -55 °C hasta 150 °C. La salida es lineal y cada grado Celsius equivale a 10 mV, por lo tanto:
1°C = 10 mV
2°C = 20 mV
…
150°C = 1500 mV

Es decir, la salida del sensor es Vout=10mV/°C.

La siguiente imagen muestra los pines de conexión de este sensor.

![Pines del sensor LM35](/img/fig1.png)

### ADC de la placa ESP32
La placa ESP32 de 38 pines tiene 16 entradas que se pueden usar como entradas analógicas, esto es posible debido a que la placa incorpora un conversor analógico a digital. Estas 16  entradas que pueden leer una señal analógica tienen una resolución de 12 bits, esto quiere decir que aquellos valores que se lean en los pines serán convertidos a valores entre 0 y 4095 (2^12=4096), sin embargo esta placa también se puede configurar otras resoluciones como 11, 10 y 9 bits.

Otra forma de ver la explicación anterior es: se está dividiendo el rango de 0 a 3.3V del ESP32 en 4096 partes (del 0 al 4095).

Otro aspecto relevante es que ESP32 divide el convertidor en 2 partes, ADC1_X y ADC2_X, cabe resaltar que ADC2 es usado por el controlador Wi-Fi de la placa, por tanto, solo se puede hacer uso de ADC2 cuando el controlador de Wi-Fi no se ha iniciado.

### Arquitectura cliente-servidor
La arquitectura **cliente-servidor** es un modelo de diseño de software en el que las aplicaciones se dividen en dos componentes principales: clientes y servidores. Esta separación facilita la gestión de recursos y permite que ambos interactúen de manera eficiente. El cliente realiza solicitudes de servicios o datos, mientras que el servidor proporciona esos recursos. Este sistema se basa en una comunicación constante mediante protocolos de red, lo que permite un flujo de información bidireccional entre ambos.

El **cliente** es una aplicación informática o un ordenador que consume un servicio remoto en otro ordenador conocido como servidor, normalmente a través de una red de telecomunicaciones.

Un **servidor** es un conjunto de computadoras capaces de atender las peticiones de un cliente y devolverle una respuesta en concordancia, además, un servidor almacena y gestiona diversos recursos, que pueden incluir bases de datos, archivos y aplicaciones. La capacidad de procesamiento del servidor es crucial, ya que debe manejar múltiples peticiones simultáneamente y devolver respuestas de manera eficiente. 

Una placa ESP32 se puede configurar en modo cliente para realizar solicitudes a un servidor que esté en la web, para esto se puede utilizar la biblioteca **HttpClient** del IDE de Arduino.

### Protocolo HTTP
El Protocolo de Transferencia de Hipertexto (HTTP) es un protocolo de capa de aplicación para la transmisión de documentos, como HTML. Fue diseñado para la comunicación entre navegadores web y servidores web, pero también puede utilizarse para otros fines, como la comunicación máquina a máquina, el acceso a APIs, etc. 

HTTP sigue un modelo clásico cliente-servidor: el cliente abre una conexión para realizar una solicitud y espera hasta recibir una respuesta del servidor. HTTP es un protocolo sin estado, lo que significa que el servidor no conserva datos de sesión entre dos solicitudes, aunque la posterior incorporación de cookies añade estado a algunas interacciones cliente-servidor. 

### Métodos de solicitud HTTP 
Métodos de solicitud HTTP HTTP define un conjunto de métodos de solicitud para indicar el propósito de la solicitud y qué se espera si esta se realiza correctamente. Aunque también pueden ser sustantivos, estos métodos de solicitud a veces se denominan verbos HTTP. 

A continuación se describen los diferentes métodos HTTP.
* **GET**: El método GET solicita una representación de un recurso específico. Las peticiones que usan el método GET sólo deben recuperar datos.
* **POST**: El método POST se utiliza para enviar una entidad a un recurso en específico, causando a menudo un cambio en el estado o efectos secundarios en el servidor.
* **PUT**: El modo PUT reemplaza todas las representaciones actuales del recurso de destino de acuerdo con la petición enviada.
* **DELETE**: El método DELETE borra un recurso en específico.

### La biblioteca Wi-Fi de Arduino
Esta biblioteca permite la conexión de red (local e Internet) mediante una placa de Arduino. Con esta biblioteca, se pueden instanciar servidores y clientes, y enviar y recibir paquetes UDP a través de WiFi. La placa de desarrollo puede conectarse a redes abiertas o cifradas (WEP, WPA). La dirección IP se puede asignar estáticamente o mediante DHCP.

### La biblioteca HTTPClient de Arduino
Esta biblioteca permite realizar fácilmente solicitudes HTTP GET, POST y PUT a un servidor web.

### JSON
JSON (JavaScript Object Notation) es un formato basado en texto para almacenar e intercambiar datos de una manera que es legible por humanos y analizable por máquina.

Ventajas
* JSON es utilizado a menudo por los desarrolladores web para transferir datos entre un servidor y una aplicación web.
* La naturaleza independiente del lenguaje de JSON lo convierte en un formato ideal para intercambiar datos a través de diferentes lenguajes de programación y plataformas.

### Apps Script 
Google Apps Script es un lenguaje de programación basado en JavaScript que permite ampliar las funcionalidades de las aplicaciones de Google, entre ellas, Google Sheets.

## Diagrama de conexiones
La siguiente tabla muestra el diagrama de conexiones necesario para la implementación de este proyecto.

![Diagrama de conexiones ESP32 y LM35](/img/fig2.png)

La placa de desarrollo utilizada ESP tiene 38 pines en este caso.

## Código de programación para la placa
El código de programación necesario para la placa ESP32 se puede observar en el siguiente [enlace](/codigos/lm35_sheets.ino).

## Código de programación para Google Sheets
El código de programación requerido para Apps Script (Google Sheets) se puede observar en el siguiente [enlace](/codigos/lm35_sheets.ino).

## Pruebas de implementación.
Las siguientes imagen muestran un fragmento del monitor serie de Arduino IDE y de una hoja de cálculo con las temperaturas (en grados Celsius y Fahrenheit) obtenidas por medio de la placa ESP32 y el sensor LM35.

![Monitor serie con temperaturas](/img/fig3.png)

![Hoja de cálculo con temperaturas](/img/fig4.png)

## Referencias
* [Hoja de datos de LM35](https://www.ti.com/product/es-mx/LM35)
* [Protocolo HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP)
* [Cabeceras HTTP](https://developer.mozilla.org/es/docs/Web/HTTP/Reference/Headers)
* [Métodos de petición HTTP](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Methods)
* [Encabezado de solicitud HTTP](https://developer.mozilla.org/en-US/docs/Glossary/Request_header)
* [Propiedad Content-Type](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Headers/Content-Type)
* [Cadena MIME type](https://developer.mozilla.org/en-US/docs/Glossary/MIME_type)
* [Carga útil de una transmisión](https://es.wikipedia.org/wiki/Carga_%C3%BAtil_(inform%C3%A1tica))
* [Bibioteca HTTPClient para ESP32](https://github.com/espressif/arduino-esp32/tree/master)
* [Biblioteca Wi-Fi para Arduino](hhttps://docs.arduino.cc/libraries/wifi/)
* [Activadores simples de Apps Script (Google Sheets)](https://developers.google.com/apps-script/guides/triggers?hl=es-419)
* [Clase SpreadsheetApp de Apps Script](https://developers.google.com/apps-script/reference/spreadsheet/spreadsheet-app?hl=es-419)
* [Aplicaciones Web con Apps Script](https://developers.google.com/apps-script/guides/web?hl=es-419)
* [Formato JSON](https://www.oracle.com/mx/database/what-is-json/)






