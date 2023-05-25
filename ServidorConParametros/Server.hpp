WebServer server(80);

// Funcion al recibir petición GET
void getLED() 
{
   // devolver respuesta
   int Pin=server.arg(String("Id")).toInt();
   String Operacion=server.arg(String("Status"));
   Serial.println(Pin);
   Serial.println(Operacion);
     pinMode(Pin, OUTPUT);
   if(Operacion=="ON" || Operacion=="on" ){
    digitalWrite(Pin,1);
   }
   else if(Operacion=="OFF" || Operacion=="off")
   digitalWrite(Pin,0);
  
   server.send(200, "text/plain", String("GET ") + server.arg(String("Id"))+" "+server.arg(String("Status")));
}
 
// Funcion al recibir petición POST


// Funcion que se ejecutara en la URI '/'
void handleRoot() 
{
   server.send(200, "text/plain", "Hola mundo!");
}

void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}

void InitServer()
{
   // Ruteo para '/'
   server.on("/", handleRoot);
 
   // Definimos dos routeos
   server.on("/led", HTTP_GET, getLED);
 
   server.onNotFound(handleNotFound);
 
   server.begin();
   Serial.println("HTTP server started");
}
