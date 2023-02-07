int ENA = 8;
int ENB = 9;
const int IN1 = 10;
const int IN2 = 11;
const int IN3 = 12;
const int IN4 = 13;

const int LED =7;
const int BOTON1 = 4;
const int BOTON2 = 24;
const int BOTON3 = 26;
int val = 0; //val se emplea para almacenar el estado del boton
int state = 0; // 0 LED apagado, mientras que 1 encendido
int old_val = 0; // almacena el antiguo valor de val
const int triggerEmisor = 1;
const int echoReceptor = 0;
const int triggerEmisor1= 3;
const int echoReceptor1 = 2;
const int valorUmbral = 20; //valor de la distancia en cm para detenerse
long tiempoEntrada;
float distanciaEntrada;
long tiempoEntrada1;
float distanciaEntrada1;


const int s0 = 14;  
const int s1 = 15;  
const int s2 = 16;  
const int s3 = 17;  
const int out = 18;    
int rojo = 0;
int verde = 0;  
int azul = 0;  
void setup(){  // definir si la variable es de entrada // o salida.
  pinMode(LED,OUTPUT);
 pinMode(BOTON1,INPUT); // y BOTON como señal de entrada
  pinMode(BOTON2,INPUT); // y BOTON como señal de entrada
   pinMode(BOTON3,INPUT); // y BOTON como señal de entrada
      pinMode (ENA, OUTPUT);
 pinMode (ENB, OUTPUT);
 
pinMode (IN1, OUTPUT);
pinMode (IN2, OUTPUT);
pinMode (IN3, OUTPUT);
pinMode (IN4, OUTPUT);
pinMode(triggerEmisor,OUTPUT);
pinMode(echoReceptor,INPUT);
pinMode(triggerEmisor1,OUTPUT);
pinMode(echoReceptor1,INPUT);
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);   
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH);  

  Serial.begin(9600);
  delay(10);
}



void loop() {       // loop = realice un lazo continuamente

  color(); 
  Serial.print("   ");  
  Serial.print(rojo, DEC);  
  Serial.print("   ");  
  Serial.print(verde, DEC);  
  Serial.print("   ");  
  Serial.print(azul, DEC);  


val= digitalRead(BOTON1); // lee el estado del Boton++65
if ((val == HIGH) && (old_val == LOW)){
state=1-state;
delay(10);
}
old_val = val; // valor del antiguo estado
if (state==1){
 digitalWrite(LED, HIGH); // enciende el LED
 robotAvance();
 if (rojo < azul && verde > azul && rojo < 35) 
  {  
   Serial.println("   Rojo");    
    robotParar();
 delay (1000);
  }   
}
else{
 digitalWrite(LED,LOW); // apagar el LED
 robotParar();
}
if (distanciaEntrada==40){
 robotParar();
}
}

 
void color()  
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s3, HIGH);   
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  digitalWrite(s2, HIGH);    
  verde = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
}




void sensorUltrasonidos()
{
digitalWrite(triggerEmisor,LOW); digitalWrite(triggerEmisor1,LOW);
delayMicroseconds(10);
digitalWrite(triggerEmisor, HIGH); digitalWrite(triggerEmisor1, HIGH);
delayMicroseconds(10);
tiempoEntrada=pulseIn(echoReceptor, HIGH); tiempoEntrada1=pulseIn(echoReceptor1, HIGH);
distanciaEntrada= int(0.017*tiempoEntrada); distanciaEntrada1= int(0.017*tiempoEntrada1);// Fórmula para calcular la distancia en cm
Serial.println("El valor de la distancia es ");
Serial.println(distanciaEntrada);
Serial.println("El valor de la distancia es ");
Serial.println(distanciaEntrada1);
delay(200);
}
void robotAvance()
{
digitalWrite (IN1, HIGH);
digitalWrite (IN2, HIGH);
digitalWrite (IN3, HIGH);
digitalWrite (IN4, HIGH);
}
void robotParar()
{
digitalWrite (IN1, LOW);
digitalWrite (IN2, LOW);
digitalWrite (IN3, LOW);
digitalWrite (IN4, LOW);
}
