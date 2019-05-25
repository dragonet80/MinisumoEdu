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
//#define SDFC A1  // Sensor distancia frontal Centre
#define SDFE A0  // Sensor distancia delante Izquierdo
//#define SDLD 7   // Sensor distancia lateral Derecho
//#define SDLE 8   // Sensor distancia lateral Izquierdo
//#define SDP  9   // Sensor distancia posterior 
unsigned int Sensor_distancia_FD = 0;
//unsigned int Sensor_distancia_FC = 0;
unsigned int Sensor_distancia_FE = 0;
//unsigned int Sensor_distancia_LD = 0;
//unsigned int Sensor_distancia_LE = 0;
//unsigned int Sensor_distancia_P = 0;

//SENSORES DE LINEA
#define SLFD A6   // SENSOR DE LINEA Derecho
#define SLFE A3   // SENSOR DE LINEA Izquierdo
#define SLP  A2   // SENSOR DE LINEA Posterior
unsigned int Sensor_linia_FD = 0;
unsigned int Sensor_linia_FE = 0;
unsigned int Sensor_linia_P = 0;
#define Valor_mig_sensor_linia_FD 300   // Valor mig entre blanc i negre
#define Valor_mig_sensor_linia_FE 300   // Valor mig entre blanc i negre

//MOTORS
#define MOTOR_DIR_ESQ 3   // Direcció del motor A ESQUERRA (endavant=HIGH, endarrera=LOW)
#define MOTOR_DIR_DRE 4   // Direcció del motor B DRETA (endavant=HIGH, endarrera=LOW)
#define MOTOR_PWM_ESQ 5   // Velocitat del motor A ESQUERRA (pwm=0=aturat, pwm=255=màxima velocitat)
#define MOTOR_PWM_DRE 6   // Velocitat del motor B DRETA (pwm=0=aturat, pwm=255=màxima velocitat)

//PULSADOR
#define BOTO 12

//COMUNICACIONES  BLUETOOTH
#define BT            Serial
#define BAUDRATE      9600 //38400

//BUZZER
#define BRUNZIDOR 13

//VELOCITATS (S'han de posar valors que facin anar al robot recte. Normalment un dels dos motors corre menys a mateix PWM)
#define VEL_GIR_D 120
#define VEL_GIR_E 120
#define VEL_RAS_D 60 // Al robot físic el motor dreta anava més a poc a poc per això augmentem velocitat
#define VEL_RAS_E 60
#define VEL_MAX_D 180
#define VEL_MAX_E 180

//TEMPS (S'han d'ajustar els temps per a que faci els moviments correctament)
#define TEMPS_LINIA_P 100
#define TEMPS_LINIA_F 500
#define TEMPS_DISTANCIA_P 600
#define TEMPS_DISTANCIA_L 400
#define TEMPS_DISTANCIA_F 200

//Mode Debug per a enviar informació dels sensors per port sèrie
byte Debug;

void setup() {
  /* Entrades */
  //analogics: //pinMode(SLFD,INPUT);pinMode(SLFE,INPUT);pinMode(SLP,INPUT);
  pinMode(SDFD,INPUT);
  //pinMode(SDFC,INPUT);
  pinMode(SDFE,INPUT);
  //pinMode(SDLD,INPUT);pinMode(SDLE,INPUT);pinMode(SDP,INPUT);
  pinMode(BOTO, INPUT);
  /* Sortides */
  pinMode(MOTOR_DIR_ESQ,OUTPUT);
  pinMode(MOTOR_DIR_DRE,OUTPUT);
  pinMode(MOTOR_PWM_ESQ,OUTPUT);
  pinMode(MOTOR_PWM_DRE,OUTPUT);
    
  BT.begin(BAUDRATE);
  BT.println("Iniciant robot minisumo!");
  if(digitalRead(BOTO)) {
    Debug = 1;
    BT.println("[Mode Debug Activat]");
    while(digitalRead(BOTO));    // Esperem a que deixem de pulsar el botó
  }
  else Debug = 0;
  BT.println();
  BT.println("Esperant botó per a compte enrere");
  while(digitalRead(BOTO)==0);    // Esperem a que pulsem el botó
  int temps=millis();
  while(millis()-temps < 5000);   // Fem una pausa de 5 segons (5000 milisegons)
}

void loop() {
  /* Llegim els sensors de distància i de línia */
  Sensor_distancia_FD = digitalRead(SDFD);
//  Sensor_distancia_FC = digitalRead(SDFC);
  Sensor_distancia_FE = digitalRead(SDFE);
//  Sensor_distancia_LD = digitalRead(SDLD);
//  Sensor_distancia_LE = digitalRead(SDLE);
//  Sensor_distancia_P = digitalRead(SDP);
  Sensor_linia_FD = analogRead(SLFD);
  Sensor_linia_FE = analogRead(SLFE);
  Sensor_linia_P = analogRead(SLP);
  /* Enviem els valors dels sensors al port sèrie per a visualitzar a l'ordinar */
  /* En competició convé llevar-ho tot per a no ralentitzar el programa */
    if(Debug) {
    //  if(Sensor_distancia_LE) BT.print("<1-["); else BT.print("<0-[");
      if(Sensor_distancia_FE) BT.print("1-"); else BT.print("0-");
    //  if(Sensor_distancia_FC) BT.print("1-"); else BT.print("0-");
      if(Sensor_distancia_FD) BT.print("1-"); else BT.print("0-");
    //  if(Sensor_distancia_LD) BT.print("]1->"); else BT.print("]0->");
    //  if(Sensor_distancia_P) BT.print("[1] * "); else BT.print("[0] * ");
      BT.print(Sensor_linia_FE);
      BT.print("-");
    //  BT.print(Sensor_linia_P);
    //  BT.print("-");
      BT.print(Sensor_linia_FD);  
      if(digitalRead(BOTO)) BT.println(" B"); else BT.println("");
    //  delay(500);
    }

  /* Programa principal de minisumo */
  if(Sensor_linia_FD < Valor_mig_sensor_linia_FD) {   // Si trobem línia al sensor FD
    /* Fer endarrera girant o pivotant a la dreta */
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, LOW);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    if(Debug) BT.println("Línia FD");
    delay(TEMPS_LINIA_F);
  }
  else if(Sensor_linia_FE < Valor_mig_sensor_linia_FE) {  // Si trobem línia al sensor FE
    /* Fer endarrera girant o pivotant a l'esquerra */
    digitalWrite(MOTOR_DIR_DRE, LOW);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, 0);
    if(Debug) BT.println("Línia FE");
    delay(TEMPS_LINIA_F);
  }
  else if(Sensor_distancia_FD && Sensor_distancia_FE) {   // Si tenim enemic just al front
    /* Endavant a màxima velocitat */
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    if(Debug) BT.println("Enemic Davant");
  }
  else if(Sensor_distancia_FD) {                          // Si tenim enemic davant a la dreta
    /* Endavant girant o pivotant a la dreta */
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_RAS_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    if(Debug) BT.println("Enemic Frontal Dreta");
    delay(TEMPS_DISTANCIA_F);
  }
  else if(Sensor_distancia_FE) {                          // Si tenim enemic davant a l'esquerra
    /* Endavant girant o pivotant a l'esquerra */
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_RAS_E);
    if(Debug) BT.println("Enemic Frontal Esquerra");
    delay(TEMPS_DISTANCIA_F);
  }
  else if(digitalRead(BOTO)) {                            // Si s'ha apretat el botó per aturar el robot
    /* Aturar el robot i ficar el programa en bucle infinit. Per sortir fer RESET. */
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, 0);
    BT.println("Robot aturat!");
    while(1);
  }
  else {                                                  // Si no trobem ni línia ni enemic
    /* Endavant a velocitat rastreig */
    if(Debug) BT.print(".");
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_RAS_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_RAS_E);
  }
 }
