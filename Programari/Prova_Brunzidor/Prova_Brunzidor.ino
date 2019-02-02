/*
 * * * * * * * * * * * * PROVA DEL BRUNZIDOR * * * * * * * * * * * *
 * 
 * Prova del brunzidor per al robot de minisumo educatiu
 * 
 * Basat en el codi de: https://github.com/AbhishekGhosh/Arduino-Buzzer-Tone-Codes
 * en el de: https://gist.github.com/nicksort/4736535
 * i en el de: https://www.princetronics.com/supermariothemesong/
 * 
 * 2019 - Vicent Colomar
 * 
 */

/*
 * Definim els valors en freqüència de cada nota. Aquests valors els farà servir
 * la funció "tone"
 */
#define R     0
#define c3    131
#define d3    147
#define e3    165
#define f3    175
#define g3    196
#define a3    220
#define a3s   233
#define b3    247
#define c4    261
#define d4    294
#define d4s   311
#define e4    329 
#define f4    349
#define f4s   370 
#define g4    392
#define g4s   415 
#define a4    440
#define a4s   466
#define b4    493 
#define c5    523
#define c5s   554
#define d5    586
#define d5s   622
#define e5    659
#define f5    698
#define f5s   740
#define g5    784
#define g5s   830
#define a5    880
#define a5s   932
#define b5    988
#define c6    1047
#define c6s   1109
#define d6    1175
#define d6s   1245
#define e6    1319
#define f6    1397
#define f6s   1480
#define g6    1568
#define g6s   1661
#define a6    1760
#define a6s   1865
#define b6    1976
#define c7    2093
#define c7s   2217
#define d7    2349
#define d7s   2489
#define e7    2637
#define f7    2794
#define f7s   2960
#define g7    3136
#define g7s   3322
#define a7    3520
#define a7s   3729
#define b7    3951
#define c8    4186
#define c8s   4435
#define d8    4699
#define d8s   4978

/*
 * Posem nom als pins que utilitzarem i així recordar-ho millor
 */
#define brunzidor 13  // El brunzidor per a produir sorolls
#define boto 12       // El botó petit al costat del brunzidor

/*
 * Aquí definim les notes i el tempo de les cançons
 */
const int SWT_N[] = {
   f4, f4,  f4, a4s, f5, d5s, d5, c5, a5s, f5, 
   d5s,  d5, c5, a5s, f5, d5s, d5, d5s, c5
};
const int SWT_D[] = {
  210, 210, 210, 1280, 1280, 210, 210, 210, 1280, 640, 
  210, 210, 210, 1280, 640, 210, 210, 210, 1280
};
const int SWMI_N[] = {
  a4,   a4, a4,  f4,  c5,  a4,  f4, c5,  a4, R,
  e5,   e5, e5,  f5,  c5, g4s,  g4, c5,  a4, R,
  a5,   a4, a4,  a5, g5s,  g5, f5s, f5, f5s, R,
  a4s, d5s, d5, c5s,  c5, a4s,  c5,  R,
  f4,  g4s, f4,  a4,  c5,  a4,  c5, e5,   R,
  a5,   a4, a4 , a5, g5s,  g5, f5s, f5, f5s, R,
  a4s, d5s, d5, c5s,  c5, a4s,  c5,  R,
  f4,  g4s, f4,  c5,  a4,  f4,  c5, a4
};
const int SWMI_D[] = {
  500, 500, 500, 350, 150, 500, 350, 150, 650, 500,
  500, 500, 500, 350, 150, 500, 350, 150, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325,
  250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 350, 125, 500, 375, 125, 650, 500,
  500, 300, 150, 500, 325, 175, 125, 125, 250, 325,
  250, 500, 325, 175, 125, 125, 250, 350,
  250, 500, 375, 125, 500, 375, 125, 650
};
const int MB_N[] = {
  e7, e7,  R, e7,  R, c7, e7,  R, g7,  R,  R,  R, g6,  R,   R,  R,
  c7,  R,  R, g6,  R,  R, e6,  R,  R, a6,  R, b6,  R, a6s, a6,  R,
  g6, e7, g7, a7,  R, f7, g7,  R, e7,  R, c7, d7, b6,   R,  R,
  c7,  R,  R, g6,  R,  R, e6,  R,  R, a6,  R, b6,  R, a6s, a6,  R,
  g6, e7, g7, a7,  R, f7, g7,  R, e7,  R, c7, d7, b6,   R,  R
};
const int MB_D[] = {
   125,  125,  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
   125,  125,  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  166, 166, 166, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
   125,  125,  125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125,
  166, 166, 166, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125, 125
};

void setup()
{
  /*
   * El pin del brunzidor l'utilitzem com a sortida
   */
  pinMode(brunzidor, OUTPUT);
  /*
   * Els pins del botó els emprarem com a entrada
   */
  pinMode(boto, INPUT);
  /*
   * Activam el port sèrie per a enviar missatges a l'orginador. El configurem a una velocitat de 115200 bauds.
   */
  Serial.begin(115200);
}
 
void loop()
{
  int mida;   // Definim la variable mida de tipus int
  /*
   * Esperarem a pulsar el botó per a tornar a començar
   */
  Serial.println("Pulsa el botó per a començar.");
  while(digitalRead(boto)==LOW);  // No fem res, simplement tornem a llegir el botó
  Serial.println("Ok");
  while(digitalRead(boto)==HIGH); // Esperem a que el botó es deixi d'apretar
  Serial.println("");
  delay(250);
  /*
   * Tema d'Star Wars
   */
  Serial.println("Ara sona el tema d'Star Wars.");
  mida = sizeof(SWT_N) / sizeof(int);
  for(int i=0; i<mida; i++)
    beep(SWT_N[i], SWT_D[i]);
  delay(5000);

  /*
   * Mario: Tema principal
   */
  Serial.println("Ara sona el tema de Mario.");
  mida = sizeof(MB_N) / sizeof(int);
  for(int i=0; i<mida; i++)
    beep(MB_N[i], MB_D[i]);
  delay(5000);
  
  /*
   * Star Wars: Marxa Imperial
   */
  Serial.println("Ara sona la Xarxa Imperial d'Star Wars.");
  mida = sizeof(SWMI_N) / sizeof(int);
  for(int i=0; i<mida; i++)
    beep(SWMI_N[i], SWMI_D[i]);
  delay(5000);

  /*
   * Esperarem a pulsar el botó per a tornar a començar
   */
  Serial.println("");
  Serial.println("Pulsa el botó per a tornar a començar.");
  while(digitalRead(boto)==LOW);  // No fem res, simplement tornem a llegir el botó
  Serial.println("Ok");
  while(digitalRead(boto)==HIGH); // Esperem a que el botó es deixi d'apretar
  Serial.println("");
  delay(1000);
}
 
void beep(int nota, int duracio)
{
  /*
   * Aquesta funció produeix les notes musicals
   */
  tone(brunzidor, nota, duracio); // Enviem la nota al brunzidor
  delay(duracio * 1.30);          // La deixem sonar un temps específic
  noTone(brunzidor);              // Apaguem el brunzidor
}
