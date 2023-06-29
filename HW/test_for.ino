#include <TinyGPS++.h> // library for GPS module
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
TinyGPSPlus gps;  // The TinyGPS++ object
SoftwareSerial ss(4, 5); // The serial connection to the GPS device
const char* ssid = "DESKTOP-STFFJOO 1740"; //ssid of your wifi
const char* password = "bL7374?7"; //password of your wifi
float latitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  IPAddress ip(192, 168, 137, 203);
  IPAddress gateway(192, 168, 0, 1);
  IPAddress subnet(255, 255, 255, 0);

  WiFi.config (ip, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  ss.begin(9600);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password); //connecting to wifi
  while (WiFi.status() != WL_CONNECTED)// while wifi not connected
  {
    delay(500);
    Serial.print("."); //print "...."
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());  // Print the IP address
}


void loop()
{
  while (ss.available() > 0) //while data is available
    if (gps.encode(ss.read())) //read gps data
    {
      if (gps.location.isValid()) //check whether gps location is valid
      {
        latitude = gps.location.lat();
        lat_str = String(latitude , 6); // latitude location is stored in a string
        longitude = gps.location.lng();
        lng_str = String(longitude , 6); //longitude location is stored in a string
      }
      if (gps.date.isValid()) //check whether gps date is valid
      {
        date_str = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();
        if (date < 10)
          date_str = '0';
        date_str += String(date);// values of date,month and year are stored in a string
        date_str += " / ";

        if (month < 10)
          date_str += '0';
        date_str += String(month); // values of date,month and year are stored in a string
        date_str += " / ";
        if (year < 10)
          date_str += '0';
        date_str += String(year); // values of date,month and year are stored in a string
      }
      if (gps.time.isValid())  //check whether gps time is valid
      {
        time_str = "";
        hour = gps.time.hour();
        minute = gps.time.minute();
        second = gps.time.second(); // converting to IST
        if (minute > 59)
        {
          minute = minute - 60;
          hour = hour + 1;
        }
        hour = (hour + 9) ;
        if (hour > 23)
          hour = hour - 24;   // converting to IST
        if (hour >= 12)  // checking whether AM or PM
          pm = 1;
        else
          pm = 0;
        hour = hour % 12;
        if (hour < 10)
          time_str = '0';
        time_str += String(hour); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (minute < 10)
          time_str += '0';
        time_str += String(minute); //values of hour,minute and time are stored in a string
        time_str += " : ";
        if (second < 10)
          time_str += '0';
        time_str += String(second); //values of hour,minute and time are stored in a string
        if (pm == 1)
          time_str += " PM ";
        else
          time_str += " AM ";
      }
    }
 
 WiFiClient client = server.available(); // Check if a client has connected
  if (!client)
  {
    return;
  }
  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n <!DOCTYPE html> <html> <head> <title>GPS DATA</title> <style>";
  s += "a:link {background-color: YELLOW;text-decoration: none;}";
  s += "table, th, td </style> </head> <body>"; // 23.06.17 21:16 CSW h1이라는 제목 태그를 가지고, GPS DATA라는 제목을 삭제
  //s += "table, th, td </style> </head> <body> <h1  style=";
  //s += "font-size:300%;";
  //s += " ALIGN=CENTER> GPS DATA</h1>";
  s += "<p ALIGN=CENTER style=""font-size:150%;""";
  //s += "> <b>Location Details</b></p> <table ALIGN=CENTER style=";
  s += "> </p> <table ALIGN=CENTER style="; // 23.06.17 21:16 CSW Location Details라는 제목을 삭제
  s += "width:50%";
  // 위도, 경도, 시간, 날짜 중앙 정렬 해제[ALIGN=CENTER는 중앙 정렬하는 코드]-------------------------------------------------------------------------------------------
  s += "> <tr> <th>Latitude</th>";
//  s += "<td ALIGN=CENTER >";
  s += "<td >";
  s += lat_str;
  //s += "</td> </tr> <tr> <th>Longitude</th> <td ALIGN=CENTER >";
  s += "</td> </tr> <tr> <th>Longitude</th> ";
  s += lng_str;
  //s += "</td> </tr> <tr>  <th>Date</th> <td ALIGN=CENTER >";
  s += "</td> </tr> <tr>  <th>Date</th> ";
  s += date_str;
  //s += "</td></tr> <tr> <th>Time</th> <td ALIGN=CENTER >";
  s += "</td></tr> <tr> <th>Time</th> ";
  s += time_str;
  s += "</td>  </tr> </table> ";
 
  s += "</body> </html>" ;

  client.print(s); // all the values are send to the webpage
  delay(100);
}
