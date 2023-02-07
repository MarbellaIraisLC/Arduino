// Motor A
int ENA = 15;
int IN1 = 14;
int IN2 = 13;

// Motor B
int ENB = 12;
int IN3 = 11;
int IN4 = 10;



const int triggerEmisor = 1;
const int echoReceptor = 0;
const int triggerEmisor1= 3;
const int echoReceptor1 = 2;
const int valorUmbral = 20; //valor de la distancia en cm para detenerse
long tiempoEntrada;
float distanciaEntrada;
long tiempoEntrada1;
float distanciaEntrada1;

int pinR = A0, pinL = 4, followerR, followerL; // PINS DE LOS SENSORES SEGUIDORES DE LÍNEA



const int s0 = 5;  
const int s1 = 6;  
const int s2 = 7;  
const int s3 = 8;  
const int out = 9;    
int rojo = 0; 
int verde = 0;  
int azul = 0;  



void setup ()
{
 // Declaramos todos los pines como salidas
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
  pinMode (pinR, INPUT);
  pinMode (pinL, INPUT);
  pinMode(s0,OUTPUT);  
  pinMode(s1,OUTPUT);  
  pinMode(s2,OUTPUT);  
  pinMode(s3,OUTPUT);  
  pinMode(out,INPUT);   
  digitalWrite(s0,HIGH);  
  digitalWrite(s1,HIGH);  
Serial.begin(9600);
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
Serial.println("El valor de la distancia es 1");
Serial.println(distanciaEntrada1);
delay(200);
}
void Adelante ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor B
}
void Atras ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255); //Velocidad motor B
}
void Derecha ()
{
 //Direccion motor A
 digitalWrite (IN1, HIGH);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, HIGH);
 analogWrite (ENB, 255); //Velocidad motor A
}

void Izquierda ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, HIGH);
 analogWrite (ENA, 255); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, HIGH);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 255); //Velocidad motor A
}
void Parar ()
{
 //Direccion motor A
 digitalWrite (IN1, LOW);
 digitalWrite (IN2, LOW);
 analogWrite (ENA, 0); //Velocidad motor A
 //Direccion motor B
 digitalWrite (IN3, LOW);
 digitalWrite (IN4, LOW);
 analogWrite (ENB, 0); //Velocidad motor A
}
void loop ()
{
  color(); 
  Serial.print("   ");  
  Serial.print(rojo, DEC);  
  Serial.print("   ");  
  Serial.print(verde, DEC);  
  Serial.print("   ");  
  Serial.print(azul, DEC);  
followerR = digitalRead (pinR);
followerL = digitalRead (pinL);
sensorUltrasonidos();

// Si el valor de la distancia es menor que 5 cm se para y sigue recto en caso contrario
if(distanciaEntrada>valorUmbral&&distanciaEntrada1<valorUmbral)//&&(followerR == 0)&(followerL == 0)
{
 Adelante ();
 delay (1000);
}
//if ((followerR == 0)& (followerL == 1)) //RIGHT - DERECHA
//{
// Derecha ();
 //delay (1000);

//}

//if ((followerR == 1)& (followerL == 0)) //LEFT - IZQUIERDA
//{
 // Izquierda ();
// delay (1000);
//}
if(distanciaEntrada1>valorUmbral)
{
 Atras ();
 delay (1000);
}

//if((followerR == 1)&&(followerL == 1))
//{
 //Parar ();
 //delay (1000);
//}

if(distanciaEntrada<valorUmbral&&distanciaEntrada1>valorUmbral)//&&(followerR == 0)&(followerL == 0)
{
 Parar ();
 delay (1000);
}

  if (rojo < azul && verde > azul && rojo < 35) 
  {  
   Serial.println("   Rojo");    
    Parar ();
 delay (1000);
  }   
  else if (azul < rojo && azul < verde && verde < rojo)  
  {  
   Serial.println("   Azul");        
  }  

  else if (rojo > verde && azul > verde )  
  {  
   Serial.println("   Verde");       
  }  
  else{
  Serial.println("  ");  
  }
}
