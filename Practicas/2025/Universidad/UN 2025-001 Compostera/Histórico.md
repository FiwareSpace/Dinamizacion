#### 20/02/25
El tfm sigue avanzando con Nacho Diestro. En paralelo, se sugiere a Antonio Gordillo aterrizar el concepto en composteras en la EPCC y al mismo tiempo en Diputación.
Se plantea reunión en Extremadura Tech (Antonio Gordillo, Antonio Hernández, Jorge Osuna), en la cual se aclaran algunos conceptos. Aprovechando el evento, se produce reunión con Jaime Gragera donde se propone la idea siguiendo un modelo similar a RESPIRA, bien centrada en lo educativo (que profesores tech con equipos de estudiantes lo monten), lo empresarial (ofrecer un modelo para que las empresas lo fabriquen, o vayan a un reto) o lo municipal. O todo junto y quizá con evento personalizado (Compost Day) o Arduino Week.  Se podría aprovechar el presupuesto (o parte) del Reto para crear un gran proyecto.

En paralelo, se envía información a Antonio Gordillo preparada para informar a sus estudiantes de la posibilidad de realizar tfm/tfg en FIWARE Space, para la cual además se ha creado un espacio en la web.

 
Comenta que lo difundirá adecuadamente.

Se dispone de información similar en la web bajo el apartado FIWARE Space Academy.

#### 10/03/25
Nacho Diestro envía un extenso informe detallando la situación de la compostera, ya en un estado de avance muy importante.


 
Antonio Gordillo comenta que todavía no se encuentran apartados más formales como estado del arte, hipótesis, etc.
Se comenta la importancia de encontrar la conexión con Diputación de Badajoz para desarrollar un proyecto paralelo/consecutivo. Estamos pensando opciones.

Se encuentran paralelismos con RESPIRA. Se plantean posibilidades basadas en su replicación en parte: un proyecto similar / añadir compostaje a la web original /fabricar una web nueva / fabricar una web nueva e importar el funcionamiento y datos de RESPIRA.
Se plantea videoconferencia el miércoles 12 para determinar siguientes pasos.


#### 11/03/25
Reunión con Antonio Gordillo y Nacho Diestro.
Gordillo comenta que quiere redactar un paper  para presentar en congreso en Portugal que se está preparando. Se redacta documento resumen con las últimas interacciones:
Gordillo señala los objetivos “locales” de Nacho:

 
El proyecto de Nacho Diestro es un primer paso en la estrategia global que se está discutiendo. Se continuará con otro tfm/tfg con la intención descrita a continuación tras unos párrafos de contexto:

### Concepto desde Diputación de Badajoz
Vamos a presentar un plan de desarrollo y estimar un presupuesto de manera urgente, además de decidir las líneas de desarrollo en la provincia (empresa, educación, etc).
Para la implantación general futura, aunque se consideren en el proyecto opciones de alimentación por baterías, paneles, etc., yopciones de conectividad, en principio el concepto aquí es alimentación desde edificio de Diputación, con fibra o WIFI.

### Concepto desde EPCC y factor social:
EPCC realiza el desarrollo del producto con el objetivo de campo de entregar esos tfg's/tfm's.
También la implantación de Gordillo en la red maker y presencia en eventos en los cuales puede tener un papel este proyecto.
Gordillo informa de que tiene la idea de que una vez las composteras ciudadanas en marcha, y ligado a la web colaborativa, se creen comunidades de compostaje. Lo que ve como una implicación más filosófica: reunir a sociólogos, otros universitarios, la sociedad, para crear un concepto al que se adhiera la gente uniendo lo tecnológico con lo verde, etc. Lo cual afecta a ese front end, que debería tener más vida que simplemente parámetros. De partida, indicando el estado del proceso, pero abundando en el tema.


#### Prototipo:
Académicamente es necesario terminar en junio con Nacho (aunque continúe vinculado en la medida que quiera), con lo cual va a quedar un proyecto muy bonito, útil y bien documentado, en el que se debería incluir la escalabilidad futura, es decir, comentar de manera general lo que hagamos después.
Nacho termina con un MVP que demostrará el código y los sensores, aunque queden cosas por hacer.
#### Piloto:
Se puede incorporar a Diego (un antiguo estudiante), que puede hacer un piloto con materiales y resultados finales, replicable, por ejemplo para septiembre.

#### Modelo de datos:
Una vez definido el modelo de datos, lo pasamos a revisión en FIWARE para convertirlo en un estándar mundial si no existe.

Aprovechamiento de experiencias:
Tenemos RESPIRA como modelo a seguir en el concepto de la web de sensores con colaboración ciudadana. Una web colaborativa y funcionando.
Pensamos en un web más global que incluya a Respira y Compostaje. Deberíamos construirlo desde Diputación para tener el control.

####  CITLabs Aprovechamiento de recursos.
Podemos contar con los CITLabs para desarrollar carcasas y elementos físicos. Habría que darles pronto una idea de volúmenes, uso, etc.

#### 21/04/25
Nacho Diestro: Dispositivo programado y conectado a MQTT con sensores simulados.
Recibe datos y genera JSON.
A falta de conectar los sensores que han sido recibidos de Antonio Gordillo.

Establecemos reunión para viernes 25/04/25 12:00 para detallar el punto de avance de proyecto.

#### 05/05/25

Durante el Eco-Digithon de finales de Abril, contactamos con uno de los grupos, con un proyecto de composteras. Nos indican que el punto que les complementaría sería justo el de la digitalización de las composteras, por lo que se entiende que hay una oportunidad importante de colaboración con este proyecto. Les hemos vuelto a contactar, y estamos a la espera de respuesta.

#### 07/07/25
Se le indica a Nacho Diestro que debemos clarificar ya el fin de su etapa y los entregables. Comenta lo siguiente:

“Por mi parte, el M5Stack está funcionando, lo único que falta es recibir los sensores finales para poder conectarlos e implantarlo de verdad.
Puedo continuar con la pequeña memoria que os pasé y añadirle lo que falta y para el lunes tendríamos una documentación final más sólida (aunque no sea el formato tfm).

Checkpoint, hasta el momento:

•	M5Stack programado y enviando datos por MQTT
•	Sensores aun pendientes de conectar (porque aún no nos han llegado)
•	Docker compose preparado para instalar Mosquitto y Node-Red en cualquier dispositivo
•	Envío de datos a Fiware preparada, pero aun no se está enviando nada

Igualmente, que te confirme Antonio los hitos que él tiene anotados y les echamos un vistazo.

#### 19/05/25
Se les solicita actualización del proyecto.
Comentan que disponen ya de una Raspberri Pi para hacer de Gateway, pero que han tenido problemas en los envíos de M5Stack del modelo concreto empleado desde China, que han quedado cancelados. Mientras tanto se están usando otros M5 diferentes.
Antonio Gordillo comenta que no ha podido avanzar en un Convenio Marco Uex-Badajoz pero a medida que el curso finalice estará más desocupado.
Antonio Gordillo irá a La Albuera, buen momento para reunirnos y concretar más el futuro.

#### 25/05/25
Aprovechamos para hablar con A. Gordillo en el evento de La Albuera. Nos comentan que tienen todo el material para construir 2-3 prototipos, que irán con 3 cubos de compostaje para tener en cada uno diferentes fases de descomposición. Se comprometen a finalizardurante el verano para poder arrancar por nuestro lado en Septiembre.



#### 09/06/25
Se les solicita estado de avance del proyecto.
Antonio Gordillo contesta: “Nacho ya está con el montaje físico del prototipo soldando cables y buscando conectores buenos. Hemos hecho otro pedido de varios sensores conectores para seguir buscando la modularidad y poder hacer varios prototipos con el mismo hardware y software. Los sensores están en camino ya.

La idea sigue siendo tener una malla de ESP32 conectados a una Raspberry que se encarga de la comunicación con "el mundo exterior" usando Fiware, sea por cable o wifi.

Ya tengo unas composteras DIY en mi balcón de casa esperando ser llenadas. Para comenzar, además de materia orgánica seca (que es fácil en estas fechas), quiero tener un sistema mínimo a punto para poder medir desde el principio. En mi caso seguiré la aproximación de tres contenedores, que es muy utilizada, lo cual será curioso cuanto menos en las series de datos. Ya veremos. Os mando unas fotillos de las jaulas de grillos :-)

La idea es que debe circular el aire pero no los insectos…“

#### 16/06/25
Desde la EPCC nos informan que “Ya tenemos el proyecto 'terminado' a falta de poder meterlo en un sistema de compostaje real para poder empezar con la toma de datos.”

Quedamos a la espera de esta prueba real para comenzar a trabajar sobre ello por nuestro lado (generación de portal, compra de materiales, prueba de concepto en algún lugar público, etc.)

#### 25/06/25
Actualmente se cuenta con:
•	Programación para el M5Stack Tough. Conexion Wifi + MQTT, captación de datos con sensores (aunque falten algunos físicamente por conectar porque aun no los tenemos), envío de datos a Node-Red.
•	Sistema de despliegue en Raspi con Ubuntu/Linux utilizando docker y docker-compose. Además, hay un fichero 'deploy.sh' que al ejecutarlo se encarga de toda la instalación en la Raspi, desde docker hasta la configuración de node-red y mosquitto.
 
•	Además, desde node-red ya estamos obteniendo token de Fiware y enviando datos a una entidad previamente creada:
 



Todo esto está ya subido a un repositorio y documentado (readme.md):
## https://github.com/idiestro/TFM-IDG-SmartComposters
