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
### 3.4 Monitorización de residuos
### 3.5 Control de Flota
### 3.6 Parking inteligente
### 3.7 Luminaria inteligente
### 3.8 Videocamara de seguridad con control de luminaria/visión artificial para espacio inteligente (sin peana)
### 3.9 Virtual Art (museística inteligente) (sin peana)
