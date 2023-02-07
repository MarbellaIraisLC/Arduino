#include <SoftwareSerial.h>

#define DEBUG true

#include <SD.h>

File Archivo;
char* jj="holaaa";
SoftwareSerial esp8266(2,3); // make RX Arduino line is pin 2, make TX Arduino line is pin 3.
                             // This means that you need to connect the TX line from the esp to the Arduino's pin 2
                             // and the RX line from the esp to the Arduino's pin 3
  String idstring = ("\"INFINITUMxzzq\"");                               // enter ssid here Note the format
  String keystring = ("\"moden55respeta\"");             //enter key here    "            "
  String connectstring = "AT+CWJAP=";  
 String f="";   

void setup()
{

//sendData =( "data.txt" );
 // f = createWriter( "data.txt" );
 // output = createWriter( "data.txt" );
//f = open("C:/xampp/htdocs/WIFI-PRUEBA/con",'a')
//f.write("Valor de la variable")
//f.close()
  //File dataFile =("index.php", FILE_WRITE);
  Serial.begin(115200);
  esp8266.begin(115200); // your esp's baud rate might be different
  
 
  
  sendData("AT+RST\r\n",2000,DEBUG); // reset module
     delay(3000);
  sendData("AT+CWMODE=3\r\n",1000,DEBUG); // configure as access point
     delay(3000);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
     delay(3000);
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
     delay(3000);
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
   delay(3000);
  sendData(connectstring,1000,DEBUG); // turn on server on port 80
}
 
void loop()
{
  if(esp8266.available()) // check if the esp is sending a message 
  {
    /*
    while(esp8266.available())
    {
      // The esp has data so display its output to the serial window 
      char c = esp8266.read(); // read the next character.
      Serial.write(c);
    } */
    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
         Archivo.read("GET C:/xampp/htdocs/WIFI-PRUEBA/otroo/?", FILE_WRITE);
    Archivo.println("Esto es lo que se está escribiendo en el archivo");
 
     int connectionId = esp8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
     
    // String webpage = "<H1></H1>&lth2>World!</h2><button>LED1</button>";
     String webpage = "Access-Control-Allow-Origin: *<H1>conexión local</H1>&lth2>Prueba!</h2><label>PH</button>";
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
     //<button>LED2</button>
     webpage=jj;
     
     cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";
     
     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);
 
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,3000,DEBUG);

     
    }
  }


}
 
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
