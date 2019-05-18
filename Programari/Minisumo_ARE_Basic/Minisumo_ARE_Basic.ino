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

//MOTORES
#define MOTOR_DIR_ESQ 3   // Direcció del motor A IZQUIERDO (endavant=HIGH, endarrera=LOW)
#define MOTOR_DIR_DRE 4   // Direcció del motor B DERECHO (endavant=HIGH, endarrera=LOW)
#define MOTOR_PWM_ESQ 5   // Velocitat del motor A IZQ(pwm=0=aturat, pwm=255=màxima velocitat)
#define MOTOR_PWM_DRE 6   // Velocitat del motor B DER(pwm=0=aturat, pwm=255=màxima velocitat)
#define SET_MOTOR_DIR_AVANZA_DER      digitalWrite (MOTOR_DIR_DRE, HIGH)
#define SET_MOTOR_DIR_RETROCEDE_DER   digitalWrite (MOTOR_DIR_DRE, LOW)
#define SET_MOTOR_DIR_AVANZA_IZQ      digitalWrite (MOTOR_DIR_ESQ, HIGH)
#define SET_MOTOR_DIR_RETROCEDE_IZQ   digitalWrite (MOTOR_DIR_ESQ, LOW)

//COMUNICACIONES  BLUETOOTH
#define BT            Serial
#define BAUDRATE      38400

//BUZZER
#define BRUNZIDOR 13

//VELOCITATS (S'han de posar valors que facin anar al robot recte. Normalment un dels dos motors corre menys a mateix PWM)
#define VEL_GIR_D 100
#define VEL_GIR_E 100
#define VEL_RAS_D 150
#define VEL_RAS_E 150
#define VEL_MAX_D 255
#define VEL_MAX_E 255

//TEMPS (S'han d'ajustar els temps per a que faci els moviments correctament)
#define TEMPS_LINIA_P 100
#define TEMPS_LINIA_F 400
#define TEMPS_DISTANCIA_P 600
#define TEMPS_DISTANCIA_L 400
#define TEMPS_DISTANCIA_F 200

void setup() {
  //Entradas
  pinMode(SLFD,INPUT);pinMode(SLFE,INPUT);pinMode(SLP,INPUT);
  pinMode(SDFD,INPUT);pinMode(SDFC,INPUT);pinMode(SDFE,INPUT);
  pinMode(SDLD,INPUT);pinMode(SDLE,INPUT);pinMode(SDP,INPUT);
  pinMode(BOTO, INPUT);
  
  // Salidas
  pinMode(BRUNZIDOR,OUTPUT);
  pinMode(MOTOR_DIR_ESQ,OUTPUT);
  pinMode(MOTOR_DIR_DRE,OUTPUT);
  pinMode(MOTOR_PWM_ESQ,OUTPUT);
  pinMode(MOTOR_PWM_DRE,OUTPUT);

  
  BT.begin(BAUDRATE);
  BT.println("Iniciant robot minisumo!");
  BT.println();
  BT.println("Esperant botó per a compte enrere");
  while(digitalRead(BOTO)==0);    // Esperem a que pulsem el botó
  int temps=millis();
  while(millis()-temps < 5000);   // Fem una pausa de 5 segons (5000 milisegons)
}

void loop() {
  if(digitalRead(BOTO)) {       // S'ha apretat el botó -> Aturar el robot i acabar el programa.
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, 0);
    BT.println("Robot aturat!");
    while(1);
  }
  else if(digitalRead(SLP)) {   // Detectem línia posterior -> Endavant a màxima velocitat
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
  }
  else if(digitalRead(SLFD)) {  // Detectem línia frontal dreta -> Fer endarrera girant o pivotant a la dreta
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, LOW);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    delay(TEMPS_LINIA_F);
  }
  else if(digitalRead(SLFE)) {  // Detectem línia frontal esquerra -> Fer endarrera girant o pivotant a l'esquerra
    digitalWrite(MOTOR_DIR_DRE, LOW);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, 0);
    delay(TEMPS_LINIA_F);
  }
  else if(digitalRead(SDFC)) {  // Detectem enemic frontal centre -> Endavant a màxima velocitat recte
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
  }
  else if(digitalRead(SDFD)) {  // Detectem enemic frontal dreta -> Endavant girant o pivotant a la dreta
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_GIR_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    delay(TEMPS_DISTANCIA_F);
  }
  else if(digitalRead(SDFE)) {  // Detectem enemic frontal esquerra -> Endavant girant o pivotant a l'esquerra
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_GIR_E);
    delay(TEMPS_DISTANCIA_F);
  }
  else if(digitalRead(SDP)) {   // Detectem enemic posterior -> Girar o pivotar dreta o esquerra
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    delay(TEMPS_DISTANCIA_P);
  }
  else if(digitalRead(SDLD)) {  // Detectem enemic lateral dreta -> Girar o pivotar dreta
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, 0);
    analogWrite(MOTOR_PWM_ESQ, VEL_MAX_E);
    delay(TEMPS_DISTANCIA_L);
  }
  else if(digitalRead(SDLE)) {  // Detectem enemic lateral esquerra -> Girar o pivotar esquerra
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_MAX_D);
    analogWrite(MOTOR_PWM_ESQ, 0);
    delay(TEMPS_DISTANCIA_L);
  }
  else {                        // Si no ha detectat cap sensor de línia ni cap sensor de distància -> Endavant a velocitat rastreig
    digitalWrite(MOTOR_DIR_DRE, HIGH);
    digitalWrite(MOTOR_DIR_ESQ, HIGH);
    analogWrite(MOTOR_PWM_DRE, VEL_RAS_D);
    analogWrite(MOTOR_PWM_ESQ, VEL_RAS_E);
  }

 }
 
 
