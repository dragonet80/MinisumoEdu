/*
 * * * * * * * * * * * * PROVA DE MOTORS * * * * * * * * * * * *
 * 
 * Prova dels motors per al robot de minisumo educatiu
 * 
 * 2019 - Vicent Colomar
 * 
 */


/*
 * Posem nom als pins que utilitzarem i així recordar-ho millor
 */
#define dirMotorE 3   // Direcció del motor A (endavant=HIGH, endarrera=LOW)
#define dirMotorD 4   // Direcció del motor B (endavant=HIGH, endarrera=LOW)
#define pwmMotorE 5   // Velocitat del motor A (pwm=0=aturat, pwm=255=màxima velocitat)
#define pwmMotorD 6   // Velocitat del motor B (pwm=0=aturat, pwm=255=màxima velocitat)
#define boto 12       // El botó petit al costat del brunzidor
/*
 * Aquests valors l'utilitzarem per a controlar els motors i les pauses
 */
#define duracio 2000
#define pausa 4000
#define velo 127
 /*
  * Definim les direccions del motor. Dependrà de com hem col·locat els cables
  */
#define AVANT HIGH
#define ARRERE LOW
  
void setup() {
  /*
   * Els pins de control dels motors els emprarem com a sortida
   */
  pinMode(dirMotorE, OUTPUT);
  pinMode(dirMotorD, OUTPUT);
  pinMode(pwmMotorE, OUTPUT);
  pinMode(pwmMotorD, OUTPUT);
  /*
   * Els pins del botó els emprarem com a entrada
   */
  pinMode(boto, INPUT);
  /*
   * Activam el port sèrie per a enviar missatges a l'orginador. El configurem a una velocitat de 115200 bauds.
   */
  Serial.begin(115200);
}

void loop() {
  /*
   * Esperarem a pulsar el botó per a tornar a començar
   */
  Serial.println("Pulsa el botó per a començar.");
  while(digitalRead(boto)==LOW);  // No fem res, simplement tornem a llegir el botó
  Serial.println("Ok");
  while(digitalRead(boto)==HIGH); // Esperem a que el botó es deixi d'apretar
  Serial.println("");
  delay(pausa);
  /*
   * Fem anar el robot endavant i després l'aturem
   */
  Serial.println("*El Robot va ENDAVANT.");
  Serial.println(" Si alguna roda gira en sentit contrari hi ha que canviar els cables");
  Serial.println(" del motor al connector del driver");
  Serial.println(" Si el robot no va recte és que un motor va més forçat que l'altre i");
  Serial.println(" més endavant haurem de adjustar cada velocitat individualment");
  MotorE_Moviment(AVANT, velo);
  MotorD_Moviment(AVANT, velo);
  delay(duracio);
  MotorE_Moviment(AVANT, 0);
  MotorD_Moviment(AVANT, 0);
  delay(pausa);
  /*
   * Fem anar el robot endarrere i després l'aturem
   */
  Serial.println("*El Robot va ENDARRERE.");
  Serial.println(" Si el robot no va recte és que un motor va més forçat que l'altre i");
  Serial.println(" més endavant haurem de adjustar cada velocitat individualment");
  MotorE_Moviment(ARRERE, velo);
  MotorD_Moviment(ARRERE, velo);
  delay(duracio);
  MotorE_Moviment(ARRERE, 0);
  MotorD_Moviment(ARRERE, 0);
  delay(pausa);
  /*
   * Fem rotar el robot cap a l'esquerra i després l'aturem
   */
  Serial.println("*El Robot ROTA a l'ESQUERRA.");
  Serial.println(" Si el robot rota a la dreta hi ha que canviar els cables del motor");
  Serial.println(" Esquerra pels del Dret.");
  MotorE_Moviment(ARRERE, velo);
  MotorD_Moviment(AVANT, velo);
  delay(duracio);
  MotorE_Moviment(ARRERE, 0);
  MotorD_Moviment(AVANT, 0);
  delay(pausa);
  /*
   * Fem rotar el robot cap a la dreta i després l'aturem
   */
  Serial.println("*El Robot ROTA a la DRETA.");
  MotorE_Moviment(AVANT, velo);
  MotorD_Moviment(ARRERE, velo);
  delay(duracio);
  MotorE_Moviment(AVANT, 0);
  MotorD_Moviment(ARRERE, 0);
  delay(pausa);
  /*
   * Esperarem a pulsar el botó per a tornar a començar
   */
  Serial.println("");
  Serial.println("Pulsa el botó per a tornar a començar.");
  while(digitalRead(boto)==LOW);  // No fem res, simplement tornem a llegir el botó
  Serial.println("Ok");
  while(digitalRead(boto)==HIGH); // Esperem a que el botó es deixi d'apretar
  Serial.println("");
  delay(pausa);
}

/*
 * Funcions que controlen els paràmetres de direcció i velocitat del motors.
 *  direccio: 0=endarrera, 1=endavant
 *  velocitat: 0=aturat, 255=màxima velocitat
 */
void MotorE_Moviment(byte  direccio, byte velocitat)
{
  digitalWrite(dirMotorE, direccio);
  analogWrite(pwmMotorE, velocitat);
}
void MotorD_Moviment(byte  direccio, byte velocitat)
{
  digitalWrite(dirMotorD, direccio);
  analogWrite(pwmMotorD, velocitat);
}
