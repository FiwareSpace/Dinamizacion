# FIWARE Space – Showcase
## 1. Objetivo
Actualizar el showcase del centro FIWARE Space, con maquetas inteligentes que representen las soluciones ya mostradas en el showcase. Estas deben poder conectarse a una única plataforma fiware, para la visualización de los datos recolectados. A nivel físico, todos los componentes no electronicos de las maquetas deben poder imprimirse usando la impresora 3d del centro, y deben por adaptarse a las peanas ya instaladas – aprox 35x35cm.
## 2. Soluciones a maquetar
- Monitorización de ganado
- Gestion de silos de pienso
- Control de riego
- Monitorización de residuos
- Control de Flota
- Parking inteligente
- Luminaria inteligente
- Respira (n/a)
- Videocamara de seguridad con control de luminaria/visión artificial para espacio inteligente (sin peana)
- Virtual Art (museística inteligente) (sin peana)
- Smart eco-bike (n/a)
### 2.1 Propuesta de cambio
Como parte de la renovación del Showcase de FIWARE, sería interesante considerar la posibilidad de cambiar algunos de las soluciones expuestas, cambiándolas por otras verticales. Así, podrían considerarse para sustitución aquellas maquetas que:
- Representen verticales con poco recorrido dentro de la plataforma Badajoz Es Más
- Tengan poco interés o aplicabilidad para el día a día de la ciudadanía 
- Se parezcan demasiado a otra solución del showcase, teniendo dos maquetas para una misma vertical
- Sean poco llamativas, poco interactivas, etc (i.e. poco apropiadas para una maqueta física)
De las verticales listadas más arriba, se podrían sustituir:
- Control de flota (Poco interactivo)
- Gestión de Silos (no es una aplicación de la que la diputación tenga casos activos)
- Monitorización de ganado (sin aplicación en territorio inteligente propiamente dicho)


## 3. Maquetas
### 3.1. Monitorización de Ganado
### 3.2 Gestion de silos de pienso
#### a) Descripción física:
Varios silos (de los cuales solo uno estaría sensorizado), ubicado en un entorno agrícola (pueden ser campos, sin más, o varios edificios de una granja, por ejemplo). El silo principal contaría con una tapa articulada, y una entrada y una salida, ambas conectadas a sendos tornillos de arquimedes: uno en la base del silo, para dispensar el contenido, y otro en la parte superior, bajando en un tubo (abierto) hasta una estación de carga. Para simular el grano, puede usarse arena o, mejor, semolina (si no se considera un problema de cara a plagas. Un camión con una caja posterior de carga puede servir como entrada: un comedero alargado, como salida; ambos móviles.
#### b) Sensores/actuadores: 
- El sensor principal sería un sensor de ultrasonidos situado en la tapa del silo. Este medirá la altura desde el punto superior del contenido, y extrapolará el nivel de llenado. HC-SR04.
- También se contará con una pantalla indicadora, que se usará para mostrar el nivel de llenado y, puntualmente, el estado de los motores de carga/descarga. Pantalla TFT o LCD.
- Dos motores, que harán girar los tornillos de arquímedes. Motor DC o, alternativamente, MicroServos SG90 (360º).
- Un botón que cierre circuito al cerrar la tapa del silo. Esto asegura que el sensor HC solo tome mediciones mientras la tapa esté cerrada.
- Sendos botones que permitan activar los tornillos manualmente
#### c) Datos enviados: 
Datos de llenado de silo (cada X segundos) y, alternativamente, estatus de los motores.
#### d) Esquema de conexión: 
- [Diagrama visual](https://github.com/FiwareSpace/Dinamizacion/blob/main/Proyectos/PR%202026-001%20Smart%20Showcase/FSS02%20-%20Silo%20Inteligente/FSS02%20-%20Esquema%201.png)
- [Esquema de conexiones](https://github.com/FiwareSpace/Dinamizacion/blob/main/Proyectos/PR%202026-001%20Smart%20Showcase/FSS02%20-%20Silo%20Inteligente/FSS02%20-%20Silo%20Inteligente%20-%20Esquema.pdf)
#### e) Código:
### 3.3 Control de riego
#### a) Descripción física:
La maqueta mostraría un parque público, con caminos, bancos, viandantes, etc. la zona verde (la mayor parte de la maqueta) sería real, con tierra, hierba y alguna planta mayor, de bajo mantenimiento (Cinta/Chlorophytum). En esta zona se incorporaría un sensor de humedad, y un sistema de riego que llevase agua desde un deposito aparte: bien mediante una bomba de agua, bien mediante un motor que abriese una válvula (si el depósito está por encima del nivel de la maqueta: algo viable, y que podría incorporarse al propio diseño).
El actuador (la bomba de agua) se activaria automáticamente cuando la humedad bajase de cierto punto.
#### b) Sensores/actuadores:
- Sensor de humedad en suelo, idealmente resistente a la corrosión: por ejemplo, DFRobot SEN0193
- Bomba de agua. No es necesaria mucha capacidad, se trataría de un volumen de agua pequeño.
- - Alternativamente, un MicroServo SG90
- (Opcional) Sensor de medida de nivel de agua, para el depósito
- (Opcional) Suite de sensores de calidad medioambiental: RESPIRA
#### c) Datos enviados:
Datos de humedad de suelo y de consumo de agua: opcionalmente, nivel de agua y datos de calidad medioambiental.
#### d) Esquema de conexión:
### 3.4 Monitorización de residuos
#### a) Descripción física:
Maqueta de varias papeleras, idealmente todas ellas sensorizadas (aunque se podría limitar el número según disponibilidad de sensores). Los sensores incluirían nivel de llenado, temperatura, y quizá estado de inclinación. También podría incorporarse una maqueta de compostera, con sus respectivos sensores. Finalmente, una pantalla, en un lateral de la maqueta, podría mostrar alternativamente los datos captados.
Alternativamente, la maqueta podría representar no unos contenedores, si no una ciudad, con varios contenedores con datos emulados y mostrados por pantalla, y un camión de recogida.
#### b) Sensores/actuadores:
Por cada contenedor:
- Sensor de llenado (HC-SR04, en la tapa del contenedor)
- Sensor de temperatura (DHT11 o equivalente)
- Sensor de inclinación (SW520D)
Para compostera, los sensores propuestos (versión reducida de los usados para las composteras del proyecto correspondiente de la Diputación de Badajoz):
- Temperatura
- Humedad
- CO2
- PH
Para la maqueta en general:
- Al menos una pantalla, TFT, OLED o LCD
#### c) Datos enviados:
Los datos captados por los sensores. También sería interesante notificar específicamente el momento en el nivel de llenado pasase de estar lleno a vacío, es decir, un timestamp del último vaciado.
#### d) Esquema de conexión:
### 3.5 Control de Flota
n/a - pendiente de ver si se mantiene
### 3.6 Parking inteligente
#### a) Descripción física:
Un parking a pie de calle, con unas 5-10 plazas de aparcamiento, y una pantalla indicadora. Opcionalmente, se podría cambiar por un parking cerrado, que también tuviese barrera movil de entrada y salida, y luces indicadoras de ocupación.
#### b) Sensores/actuadores:
Para abaratar costes, se pueden usar fotoresistores para determinar la ocupación de cada plaza (asumiendo que siempre habrá luz sobre la maqueta. Se podrían incorporar farolas a la maqueta). Puesto que el esp32 cuenta con 7 entradas analógicas, se usarían estas, limitando a 7 el número de posibles . Es posible que se pudiese conectar 2 fotoresistores por entrada, aunque sería un circuito mucho más complejo. En ese caso, sobrarían puertos gpio para LEDs indicadores. Así:
- 7 fotoresistores
- 7 LEDs RGB (o 14 leds rojos y verdes)
- 1 pantalla: LCD, OLED, TFT, 8 segmentos
- (Opcionalmente) Motor para barrera movil
#### c) Datos enviados:
- Estado del parking, acorde al modelo usado por la Diputación de Badajoz, así como (opcionalmente) el estado de la barrera.
#### d) Esquema de conexión:
### 3.7 Luminaria inteligente
### 3.8 Videocamara de seguridad con control de luminaria/visión artificial para espacio inteligente (sin peana)
### 3.9 Virtual Art (museística inteligente) (sin peana)
#### a) Descripción física:
#### b) Sensores/actuadores:
#### c) Datos enviados:
#### d) Esquema de conexión:
