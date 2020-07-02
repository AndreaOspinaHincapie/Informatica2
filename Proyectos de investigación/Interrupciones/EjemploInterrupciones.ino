/*
Ejemplo de interrupciones:
En el siguiente programa se mostrará una implementación de las interrupciones en la que se tendrá un programa principal que consiste en
encender y apagar dos LEDs de manera que se observe una oscilación y por medio de dos pulsadores conectados con resistencias pull-down 
a los pines 2 y 3 de arduino se utilizarán interrupciones para variar el periodo de oscilamiento de los LEDs (en el caso del pulsador 
conectado al pin 2) y ecender durante tres segundos un tercer LED (en el caso del pulsador conectado al pin 3).
Pines usados:
2- (interrupción) Pulsador para variar periodo de oscilamiento entre los LEDs
3- (interrupción) Pulsador para activar el tercer LED
5 y 6- LEDs que oscilarán
7- LED activado por pulsador conectado al pin 3.
Nota: Este programa fue implementado usando arduino uno.
*/ 
volatile int reposo=2000; //Variable que se modificará por medio de una interrupción para variar el periodo de oscilamiento entre los dos LEDs
volatile int estado=0; //Variable que se modificará por medio de una interrupción para proceder a encender el LED conectado al pin 7.
const int reposoMax=2000; //Máximo delay de la oscilación
const int reposoMin=10; //Mínimo delay de la oscilación
void setup() {
  for(int i=5;i<=7;i++){
    //Inicializando pines de los LEDs como OUTPUT y estado LOW
    pinMode(i,OUTPUT);
    digitalWrite(i,LOW);
  }
  /*
  Inicializando interrupciones:
  -Se definen los pines a usar (2 y 3, pines que pueden ser utilizados para interrupciones en arduino uno)
  -Se definen los nombres de las ISR que se ejecutarán cuando el los pines se detecte un cambio de bajo a alto(RISING), es decir,
  cuando se presione el pulsador.
  */
  attachInterrupt(digitalPinToInterrupt(2),DisminuirTiempoEspera,RISING);
  attachInterrupt(digitalPinToInterrupt(3),CambiarEstado,RISING);

}

void loop() {

 //Programa principal: encender y apagar sucesivamente los LEDs conectado a los pines 5 y 6 con un delay dado por la variable reposo y 
 //solamente cuando la variable estado sea cero.
 if(estado==0){
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  delay(reposo);
  digitalWrite(6,HIGH);
  digitalWrite(5,LOW);
  delay(reposo);
 }
 else{
  //Cuando se ha presentado la interrupción del pin 3 se encenderá el tercer LED durante tres segundos. Al finalizar se retornará la variable
  //estado a su valor original (0).
  digitalWrite(6,LOW);
  digitalWrite(5,LOW);
  digitalWrite(7,HIGH);
  delay(3000);
  digitalWrite(7,LOW);
  estado=0;
  
 }

}

//ISR pin 2: disminuir periodo de oscilamiento.
void DisminuirTiempoEspera(){
  //Si el periodo de oscilamiento que se tendrá es menor al periodo mínimo entonces se retornará al periodo máximo, de lo contrario se disminuye
  //100 milisegundos.
  if(reposo-100<reposoMin){
    reposo=reposoMax;
  }
  else{
    reposo-=100;
  }
}
//ISR pin 3: Cambiar variable estado para encender el tercer LED.
void CambiarEstado(){
  estado=1;
}
