#include <Wire.h> //Incluimos la librería para comunicación I2C

int estado = 0; //Asignamos el valor 0 a la variable estado
int pulsador = 9; //Asignamos el valor 9 a la variable pulsador

void setup() 
{
  Wire.begin(); 
  //Empezamos la comunicación I2C, el paréntesis está vacío porque es el master
}

void loop()
{
  estado = digitalRead(pulsador); //Comprobamos el estado del pulsador

  if(estado == 1)
  { //Si el estado del botón es igual a 1
    Wire.beginTransmission(4); //Empezamos la transmisión con el dispositivo 4
    Wire.write(1); //Escribimos un 1 a este dispositivo
    Wire.endTransmission();  //Paramos la transmisión
  }
  else
  { //de lo contrario
    Wire.beginTransmission(4); //Empezamos la transmisión con el dispositivo 4
    Wire.write(2); //Escribimos un 2 a este dispositivo
    Wire.endTransmission(); //Paramos la transmisión
  }
}
