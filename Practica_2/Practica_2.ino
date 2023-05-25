
#include <WiFi.h>

const char* ssid     = "Fam Sandoval Lizarraga";
const char* password = "Sandovallizarraga7275";
//const char* ssid     = "ccwifi";
//const char* password = "HP542003axsc";
 int Pin = 0;
String outputState = "off";
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  pinMode(Pin, OUTPUT);      // set the LED pin mode
  delay(10);

  Serial.print("Conectando a  ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(2,1);
    delay(500);
      digitalWrite(2,0);
    Serial.print(".");
  }
  Serial.println("Conectado al Wifi.");
  Serial.println("Direccion IP: ");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Nuevo Cliente.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {

          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println(R"====(<style> @import url('https://fonts.googleapis.com/css2?family=Poppins&display=swap');*{font-family: "Poppins",sans-serif;}     .btn{
            border-radius: 20px;
            width: 40%;
        
            font-size: 22px;
            font-weight: 400;
            border: none;

            }

            .btn:hover{
                background: gray;
                color: white;
                cursor:pointer;
            }
            .green{
                color: white;
                background-color: rgb(4, 201, 109);

            }
            .red{
                color: white;
                background-color: red;

            }</style>)====");
            client.println("<center><h1>Bienvenido al Servidor ESP-32 CARLITOS</h1>");
            if (outputState == "off")
              client.print("<a href=\"/H\"><button class=\"  btn green  \">Encender</button></a> <br>");
            else
              client.print("<a href=\"/L\"><button class=\" / btn red / \">Apagar</button></a> <br>");

            client.println("</center>");
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
        if (currentLine.endsWith("GET /H")) {
          outputState = "on";
          digitalWrite(Pin, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          outputState = "off";
          digitalWrite(Pin, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Cliente Desconectado.");
  }
}
