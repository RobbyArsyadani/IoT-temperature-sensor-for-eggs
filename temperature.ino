#include <DHT.h>
#include<ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#define DHT_PIN 2  // this is D4 on NodeMCU
#define DHTTYPE DHT11
#define led 13 // define the led pin 
#define photo A0 // define the photosensor pin
#define piezo 4
 
const char *ssid = "realme 8"; //name of ssid
const char *password = "robby02062002"; // the password from that ssid
 
ESP8266WebServer server(80);  // create a server with port 80
 
DHT dht(DHT_PIN, DHTTYPE);

//function to coonect NodeMcu to wifi
void initConnection() {
  Serial.print("Connecting to: ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi Connected");
 
  server.begin();
  Serial.println("Server Started");
 
  Serial.print("Connected on ");
  Serial.println(WiFi.localIP());
}
//function set the route
void setupRoute() {
  server.on("/", handleRoot);
  server.on("/status", handleStatusCheck);
  server.on("/led_off",handleturnoff);
  server.on("/led_on",handleturnon);
  server.onNotFound(handleNotFound);
}

//function when the program first run
void handleRoot() {
  float temp = dht.readTemperature(); //read the temperature
  int photosensor = analogRead(photo); // read the photo
  if (isnan(temp)) {
    Serial.println("Failed to read temperature"); // when the value temp isnan
    return;
  }
  if (temp <= 35 || temp >= 38){
    digitalWrite(led,HIGH); // when the temperature below 30C, turn on the led 
  }
  Serial.println(temp); 
  Serial.println(photosensor);
  server.send(200, "text/html", SendHTML(temp, photosensor)); // send the html with the temp and photosensor value
}


//function when we click the update status
void handleStatusCheck() {
  float temp = dht.readTemperature(); // read the temperature
  int photosensor = analogRead(photo); // read the photosensor
  if (isnan(temp)) {
    Serial.println("Failed to read temperature");  // when the value temp isnan
    return;
    return;
  }
  if (temp <= 35 || temp >= 38){
    digitalWrite(led,HIGH); // when the temperature below 30C, turn on the led 
  }
  
  Serial.println(temp);
  Serial.println(photosensor);
  server.send(200, "text/html", SendHTML(temp, photosensor));
}

void handleNotFound() {
  server.send(404, "text/plain", "Route not found");
}

// function when we click button turn off, to turn off led manually 
void handleturnoff(){
  digitalWrite(led, LOW);
  float temp = dht.readTemperature();
  int photosensor = analogRead(photo);
  if (isnan(temp)) {
    Serial.println("Failed to read temperature");
    return;
  }
  server.send(200, "text/html", SendHTML(temp, photosensor));
  
  
}

//function when we click button turn non, to turn on manually
void handleturnon(){
  
  digitalWrite(led, HIGH);
  float temp = dht.readTemperature();
  int photosensor = analogRead(photo);
  if (isnan(temp)) {
    Serial.println("Failed to read temperature");
    return;
  }
  server.send(200, "text/html", SendHTML(temp, photosensor));
  
  
  
}
 
String SendHTML(float temp, int photosensor) {
  String html = "<!DOCTYPE html> <html>\n";
 html += "<head>";
html += "    <meta charset='UTF-8'>";
html += "";
html += "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>";
html += "    <meta name='viewport' content='width=device-width, initial-scale=1.0'>";
html += "    <title>Smart Chicken Lamp - IoT Project</title>";
html += "    <link rel='preconnect' href='https://fonts.googleapis.com'>";
html += "    <link rel='preconnect' href='https://fonts.gstatic.com' crossorigin>";
html += "    <link href='https://fonts.googleapis.com/css2?family=Bruno+Ace+SC&display=swap' rel='stylesheet'>";
html += "    <style>";
html += "        :root {";
html += "            --color1: #FFD93D;";
html += "            --color2: #F6F1E9;";
html += "            --color3: #f1ad64;";
html += "            --color4: #4F200D;";
html += "            --bs-breakpoint-xs: 0;";
html += "            --bs-breakpoint-sm: 576px;";
html += "            --bs-breakpoint-md: 768px;";
html += "            --bs-breakpoint-lg: 992px;";
html += "            --bs-breakpoint-xl: 1200px;";
html += "            --bs-breakpoint-xxl: 1400px;";
html += "        }";
html += "";
html += "        .container,";
html += "        .container-fluid,";
html += "        .container-xxl,";
html += "        .container-xl,";
html += "        .container-lg,";
html += "        .container-md,";
html += "        .container-sm {";
html += "            --bs-gutter-x: 1.5rem;";
html += "            --bs-gutter-y: 0;";
html += "            width: 100%;";
html += "            padding-right: calc(var(--bs-gutter-x) * 0.5);";
html += "            padding-left: calc(var(--bs-gutter-x) * 0.5);";
html += "            margin-right: auto;";
html += "            margin-left: auto;";
html += "        }";
html += "";
html += "";
html += "";
html += "        .row {";
html += "            --bs-gutter-x: 1.5rem;";
html += "            --bs-gutter-y: 0;";
html += "            display: flex;";
html += "            flex-wrap: wrap;";
html += "            margin-top: calc(-1 * var(--bs-gutter-y));";
html += "            margin-right: calc(-0.5 * var(--bs-gutter-x));";
html += "            margin-left: calc(-0.5 * var(--bs-gutter-x));";
html += "        }";
html += "";
html += "        .row>* {";
html += "            box-sizing: border-box;";
html += "            flex-shrink: 0;";
html += "            width: 100%;";
html += "            max-width: 100%;";
html += "            padding-right: calc(var(--bs-gutter-x) * 0.5);";
html += "            padding-left: calc(var(--bs-gutter-x) * 0.5);";
html += "            margin-top: var(--bs-gutter-y);";
html += "        }";
html += "";
html += "        .col {";
html += "            flex: 1 0 0%;";
html += "        }";
html += "";
html += "        .row-cols-auto>* {";
html += "            flex: 0 0 auto;";
html += "            width: auto;";
html += "        }";
html += "";
html += "        .row-cols-1>* {";
html += "            flex: 0 0 auto;";
html += "            width: 100%;";
html += "        }";
html += "";
html += "        .row-cols-2>* {";
html += "            flex: 0 0 auto;";
html += "            width: 50%;";
html += "        }";
html += "";
html += "        .row-cols-3>* {";
html += "            flex: 0 0 auto;";
html += "            width: 33.3333333333%;";
html += "        }";
html += "";
html += "        .row-cols-4>* {";
html += "            flex: 0 0 auto;";
html += "            width: 25%;";
html += "        }";
html += "";
html += "        .row-cols-5>* {";
html += "            flex: 0 0 auto;";
html += "            width: 20%;";
html += "        }";
html += "";
html += "        .row-cols-6>* {";
html += "            flex: 0 0 auto;";
html += "            width: 16.6666666667%;";
html += "        }";
html += "";
html += "        .col-auto {";
html += "            flex: 0 0 auto;";
html += "            width: auto;";
html += "        }";
html += "";
html += "        .col-1 {";
html += "            flex: 0 0 auto;";
html += "            width: 8.33333333%;";
html += "        }";
html += "";
html += "        .col-2 {";
html += "            flex: 0 0 auto;";
html += "            width: 16.66666667%;";
html += "        }";
html += "";
html += "        .col-3 {";
html += "            flex: 0 0 auto;";
html += "            width: 25%;";
html += "        }";
html += "";
html += "        .col-4 {";
html += "            flex: 0 0 auto;";
html += "            width: 33.33333333%;";
html += "        }";
html += "";
html += "        .col-5 {";
html += "            flex: 0 0 auto;";
html += "            width: 41.66666667%;";
html += "        }";
html += "";
html += "        .col-6 {";
html += "            flex: 0 0 auto;";
html += "            width: 50%;";
html += "        }";
html += "";
html += "        .col-7 {";
html += "            flex: 0 0 auto;";
html += "            width: 58.33333333%;";
html += "        }";
html += "";
html += "        .col-8 {";
html += "            flex: 0 0 auto;";
html += "            width: 66.66666667%;";
html += "        }";
html += "";
html += "        .col-9 {";
html += "            flex: 0 0 auto;";
html += "            width: 75%;";
html += "        }";
html += "";
html += "        .col-10 {";
html += "            flex: 0 0 auto;";
html += "            width: 83.33333333%;";
html += "        }";
html += "";
html += "        .col-11 {";
html += "            flex: 0 0 auto;";
html += "            width: 91.66666667%;";
html += "        }";
html += "";
html += "        .col-12 {";
html += "            flex: 0 0 auto;";
html += "            width: 100%;";
html += "        }";
html += "";
html += "        .btn-primary {";
html += "            background-color: var(--color1);";
html += "            color: black;";
html += "            border-color: var(--color2);";
html += "        }";
html += "";
html += "        .btn-primary:hover {";
html += "            background-color: var(--color2);";
html += "            color: black;";
html += "            border-color: var(--color3);";
html += "            transition: 0.3s;";
html += "        }";
html += "";
html += "        body {";
html += "            background-color: var(--color3);";
html += "            font-family: 'Bruno Ace SC', cursive;";
html += "        }";
html += "";
html += "        .form-border {";
html += "            border-width: 10px !important;";
html += "            border-color: var(--color4);";
html += "            border: solid var(--color4);";
html += "            background-color: var(--color2);";
html += "";
html += "        }";
html += "";
html += "        a {";
html += "            text-decoration: none;";
html += "        }";
html += "";
   html += ".box-on {";
        html += "    padding: 10px;";
        html += "    margin-top: 50px;";
        html += "    border-color: black;";
        html += "    border-style: solid;";
        html += "    width: 180px;";
        html += "    height: 180px;";
        html += "    margin-left: 20%;";
        html += "    background-color: yellow;";
        html += "    box-shadow: 0 0 30px var(--color1);";
html += "";
        html += "}";
html += "";
        html += ".box-off {";
        html += "    padding: 10px;";
        html += "    margin-top: 50px;";
        html += "    border-color: black;";
        html += "    border-style: solid;";
        html += "    width: 180px;";
        html += "    height: 180px;";
        html += "    margin-left: 20%;";
        html += "    background-color: white;";
        html += "}";
html += "";
        html += ".handle-lamp {";
        html += "    width: 50px;";
        html += "    height: 95px;";
        html += "    border: solid black 5px;";
        html += "    margin-left: 39%;";
        html += "    border-top: none;";
        html += "    margin-bottom: 30px;";
        html += "    border-radius: 0 0 10px 10px;";
        html += "    background-color: var(--color4);";
html += "";
        html += "}";
html += "";
html += "        .white-background {";
html += "            width: 85%;";
html += "            height: 100%;";
html += "            margin-top: 10px;";
html += "            margin-bottom: 10px;";
html += "";
html += "        }";
html += "";
html += "        .btn {";
html += "            border: solid;";
html += "            border-radius: 10px;";
html += "            background-color: none;";
html += "            display: inline-block;";
html += "            padding: 5px;";
html += "            text-align: center;";
html += "            margin-bottom: 10px;";
html += "        }";
html += "";
html += "        .text-center {";
html += "            text-align: center !important;";
html += "        }";
html += "    </style>";
html += "";
html += "</head>";
html += "";
html += "<body class="">";
html += "    <div class='container white-background'>";
html += "        <div class='text-center m-4'>";
html += "            <h1>Smart Chicken Heat Lamp</h1>";
html += "        </div>";
html += "        <div class='form-border'>";
html += "            <div class='container'>";
html += "                <h3 class='mt-3'>Current Temperature</h3>";
html += "                <p>";
html +=                  (String)temp + " C ";
html += "                </p>";
html += "";
html += "            </div>";
html += "";
html += "";
html += "            <div class='container'>";
html += "                <h3 class='mt-3'>Photoresistor</h3>";
html += "                <p>";
html +=              (String)photosensor;
html += "                </p>";
html += "                <div class='row'>";
html += "                    <div class='col-4'>";

html += "                    </div>";
//if the led turn on
int lamp = digitalRead(led);
html += "                    <div class='col'>";
if (lamp == 1){
html += "                        <div class='text-center'>";
html += "                            <div class='box-on'>";
html += "                            </div>";
html += "                            <div class='handle-lamp'>";
html += "                            </div>";
html += "                        </div>";
}

//if the led turn off
if (lamp == 0){
html += "                        <div class='text-center'>";
html += "                            <div class='box-off'>";
html += "                            </div>";
html += "                            <div class='handle-lamp'>";
html += "                            </div>";
html += "                        </div>";
}
html += "";
html += "                    </div>";



html += "                    <div class='col-4'>";
html += "";
html += "                    </div>";
html += "";
html += "                </div>";
html += "";
html += "";
html += "";
html += "";
html += "";
html += "            </div>";
html += "            <div class='mt-5 mb-4 text-center'>";
html += "                <a href='/led_on' class='btn btn-primary btn-lg'>Turn On Lamp</a>";
html += "                <a href='/led_off' class='btn btn-primary btn-lg'>Turn Off Lamp</a>";
html += "                <a href='/' class='btn btn-primary btn-lg'>Update Status</a>";
html += "";
html += "            </div>";
html += "";
html += "";
html += "        </div>";
html += "";
html += "    </div>";
html += "";
html += "";
html += "</body>";
html += "";
html += "</html>";

  return html;
}
 
void setup() {
  Serial.begin(9600);
  dht.begin();
  initConnection();
  setupRoute();
  pinMode(led, OUTPUT);
  pinMode(photo, OUTPUT);
}
 
void loop() {
  server.handleClient();
  float temp = dht.readTemperature();
  int photosensor = analogRead(photo);
  
  if (temp <= 35 || temp >= 38){
    tone (piezo,300);
  }
  else{
    tone (piezo, 0);
  }
}
 