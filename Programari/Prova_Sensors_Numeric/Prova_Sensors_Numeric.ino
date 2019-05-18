/* PROGRAMA DE PRUEBA DE SENSORES, MOTORES Y PULSADOR DEL MINISUMO edu
   Solo placa base.
  Componentes:
  - 6 sensores de distancia digitales (3 frontales,2 laterales, 1 trasero)
  - 3 Sensores de Linea (2 delante y uno trasero)
  - 2 Motores 
  - 1 pulsador
  - 1 Buzzer
  -Bluetooth
*/

//SENSORES DE DISTANCIA
#define SDFD 2   // Sensor distancia frontal Derecho
#define SDFC A1  // Sensor distancia frontal Centre
#define SDFE A0  // Sensor distancia delante Izquierdo
#define SDLD 7   // Sensor distancia lateral Derecho
#define SDLE 8   // Sensor distancia lateral Izquierdo
#define SDP  9   // Sensor distancia posterior 
unsigned int Sensor_distancia_FD = 0;
unsigned int Sensor_distancia_FC = 0;
unsigned int Sensor_distancia_FE = 0;
unsigned int Sensor_distancia_LD = 0;
unsigned int Sensor_distancia_LE = 0;
unsigned int Sensor_distancia_P = 0;

//SENSORES DE LINEA
#define SLFD A6   // SENSOR DE LINEA Derecho
#define SLFE A3   // SENSOR DE LINEA Izquierdo
#define SLP  A2   // SENSOR DE LINEA Posterior
unsigned int Sensor_linia_FD = 0;
unsigned int Sensor_linia_FE = 0;
unsigned int Sensor_linia_P = 0;

//PULSADOR
#define BOTO 12

//COMUNICACIONES  BLUETOOTH
#define BT            Serial
#define BAUDRATE      38400

//BUZZER
#define BRUNZIDOR 13

void setup() {
  //Entradas
  //analogics//pinMode(SLFD,INPUT);pinMode(SLFE,INPUT);pinMode(SLP,INPUT);
  pinMode(SDFD,INPUT);pinMode(SDFC,INPUT);pinMode(SDFE,INPUT);
  pinMode(SDLD,INPUT);pinMode(SDLE,INPUT);pinMode(SDP,INPUT);
  pinMode(BOTO, INPUT);
  
  BT.begin(BAUDRATE);
  BT.println("Iniciant robot minisumo!");
  BT.println();
  BT.println("Esperant botó per a compte enrere");
  while(digitalRead(BOTO)==0);    // Esperem a que pulsem el botó
  int temps=millis();
  while(millis()-temps < 5000);   // Fem una pausa de 5 segons (5000 milisegons)
}

void loop() {
  Sensor_distancia_FD = digitalRead(SDFD);
  Sensor_distancia_FC = digitalRead(SDFC);
  Sensor_distancia_FE = digitalRead(SDFE);
  Sensor_distancia_LD = digitalRead(SDLD);
  Sensor_distancia_LE = digitalRead(SDLE);
  Sensor_distancia_P = digitalRead(SDP);
  Sensor_linia_FD = analogRead(SLFD);
  Sensor_linia_FE = analogRead(SLFE);
  Sensor_linia_P = analogRead(SLP);

  if(Sensor_distancia_LE) BT.print("<1-["); else BT.print("<0-[");
  if(Sensor_distancia_FE) BT.print("1-"); else BT.print("0-");
  if(Sensor_distancia_FC) BT.print("1-"); else BT.print("0-");
  if(Sensor_distancia_FD) BT.print("1-"); else BT.print("0-");
  if(Sensor_distancia_LD) BT.print("]1->"); else BT.print("]0->");
  if(Sensor_distancia_P) BT.print("[1] * "); else BT.print("[0] * ");

  BT.print(Sensor_linia_FE);
  BT.print("-");
  BT.print(Sensor_linia_P);
  BT.print("-");
  BT.print(Sensor_linia_FD);
    
  if(digitalRead(BOTO)) BT.println(" B"); else BT.println("");
  
  delay(500);
 }
 
 
