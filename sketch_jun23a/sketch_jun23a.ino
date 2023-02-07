#include <ESP8266WiFi.h>
const char* ssid = "INFINITUMxzzq";
const char* password = "moden55respeta";

WiFiServer server(80);

void setup() {

 Serial.begin(9600);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Conectandose a red : ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password); //Conexión a la red
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  
  
  server.begin(); //Iniciamos el servidor
  Serial.println("Servidor Iniciado");


  Serial.println("Ingrese desde un navegador web usando la siguiente IP:");
  Serial.println(WiFi.localIP()); //Obtenemos la IP
}


void loop() {
 

  WiFiClient client = server.available();
  if (client) //Si hay un cliente presente
  { 
    Serial.println("Nuevo Cliente");
    
    //esperamos hasta que hayan datos disponibles
    while(!client.available()&&client.connected())
    {
    delay(1);
    }
    // Leemos la primera línea de la petición del cliente.
    String linea1 = client.readStringUntil('r');
    Serial.println(linea1);

        if (linea1.indexOf("LED=ON")>0) //Buscamos un LED=ON en la 1°Linea
    {

    }
    if (linea1.indexOf("LED=OFF")>0)//Buscamos un LED=OFF en la 1°Linea
    {
    
    }
    
    client.flush(); 
                
    Serial.println("Enviando respuesta...");   
    //Encabesado http    
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");// La conexión se cierra después de finalizar de la respuesta
    client.println();
    //Pagina html  para en el navegador
        client.println("<link rel='stylesheet' href='header.css'>");
    client.println("<!DOCTYPE HTML>");
 
    client.println("<html>");
       client.println("<style type='text/css'>{background-image: url('https://conocedores.com/wp-content/uploads/2017/08/avion-blanco-06082017.jpg');}</style>");
      client.println("<head><title>Guiame</title>");
      
        client.println("<div class='header'>");
  client.println("  <a href='#default' class='logo' >  <img src='https://scontent.fmex16-1.fna.fbcdn.net/v/t1.15752-9/101061054_586880151956455_5819141508770562048_n.png?_nc_cat=105&_nc_sid=b96e70&_nc_oc=AQlDEF1tHNVFODoPIi_nJ7uhClOdSaetPDAPY24NVL97GSvgYSxyArs8XLVmtjCqFcs&_nc_ht=scontent.fmex16-1.fna&oh=df3daa9559495a9a78eefd646ed51e49&oe=5F2635EE'alt='logounam' width='60' height='60'> </a>");

   
       client.println("<div style='float:right'>");
       client.println("<a href='#default' class='logo' >  <img src= 'https://cdn.pixabay.com/photo/2016/10/08/18/35/help-1724292_960_720.png'alt='logounam' width='60' height='60'> </a>");
         client.println("</div>");
  client.println("<body>");
    client.println("<h1 align='center'>GAOA-Guia</h1>");
    client.println("<div style='text-align:center;'>");
    client.println("<br />");            
        client.println("<center>");       
   client.println(" <img src='https://image.freepik.com/vector-gratis/icono-vuelo-boleto-avion_24877-5863.jpg' width='200' height='150' title='Compra boletos' onClick=location.href='./?LED=ON'>");
     client.println("</center>");  
 client.println("&nbsp");
   client.println("&nbsp");
   client.println("&nbsp");
        client.println("&nbsp");
             client.println("<center>");       
   client.println(" <img src='https://image.freepik.com/vector-gratis/composicion-area-facturacion-aeropuerto_1284-18710.jpg' width='200' height='150' title='Compra boletos' onClick=location.href='./?LED=ON'>");
     client.println("</center>");  
  client.println("&nbsp");
  client.println("&nbsp");
   client.println("&nbsp");
        client.println("&nbsp");
             client.println("<center>");       
   client.println(" <img src='https://image.flaticon.com/icons/svg/2114/2114905.svg' width='200' height='150' title='Compra boletos' onClick=location.href='./?LED=ON'>");
     client.println("</center>");  
     client.println("<button onClick=location.href='./?LED=ON'>Compra de boletos</button>");           
    client.println("<button onClick=location.href='./?LED=OFF'>Parar</button>");
    client.println("<br />");
    client.println("</div>");
    client.println("</body>");
    client.println("</html>");
    
    delay(1);
    Serial.println("respuesta enviada");
    Serial.println();

  }
}
