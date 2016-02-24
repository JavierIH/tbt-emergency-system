#include <SD.h>
#include <SPI.h>
#include <Ethernet.h>
#include <WebServer.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <anemometer.h>
#include <logger.h>
#include <temperature.h>
#include <humidity.h>
#include <switch.h>
#include <light.h>
#include <relay.h>

/*
  Definitions
*/

#define LOG_INTERVAL  60  // in seconds
#define LOOP_DELAY    1   // in seconds

/*
  Constraints
*/

#define CONSTR_WIND  30  
#define CONSTR_TEMP  40
#define CONSTR_RHUM  80
#define CONSTR_LIGHT 300

/*
  Sensors
*/

// pin 2, averaging for 1000ms
Anemometer w (2, CONSTR_WIND, 1000);

// Vaisala temperature -> A0
Temperature t (A0, CONSTR_TEMP);

// Vaisala relative humidity -> A1
Humidity rh (A1, CONSTR_RHUM);

// datalogger
Logger logger;

// switches (rain: Sontay -> 22, Thies -> 26)
Switch sw1(22);
Switch sw2(26);

// light
Light l (A3, CONSTR_LIGHT);

// relay
Relay r(7);

// GPS, TX -> 11, RX not connected
// warning: pin 10 is in the conflict with Ethernet
TinyGPS gps;
SoftwareSerial ss(11, 12);
static void smartdelay(unsigned long ms);
static String Epoch(TinyGPS &gps);
static String Filename(TinyGPS &gps, char * postfix);

char data[100];
unsigned long lastLog = 0;
bool violation = false;

static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
static uint8_t ip[] = { 10, 1, 214, 38 };

#define PREFIX ""
WebServer webserver(PREFIX, 80);

template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

void sendIndexContent (WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  server.httpSuccess();

  if (type != WebServer::HEAD)
  {
    sprintf (data, "light=%d  wind=%d temp=%d rhum=%d rain1=%d rain2=%d", l.val(), w.val(), t.val(), rh.val(), sw1.val(), sw2.val());
    server << String ("<p><b>current status: </b><span style='color: green'>" + Epoch (gps) + "</span> " + data + "</p>");
    if (violation) server << String ("<p style='color: red;'>violation</p>");
    if (!l.state()) server << "<p>light</p>";
    if (!w.state()) server << "<p>wind</p>";
    if (!t.state()) server << "<p>temperature</p>";
    if (!rh.state()) server << "<p>humidity</p>";
    if (!sw1.state()) server << "<p>rain 1</p>";
    if (!sw2.state()) server << "<p>rain 2</p>";
    server << String ("<p><a href='/violations.html'>violations</a></p>");
  }
}

void sendFileContent (WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type != WebServer::HEAD)
  {
    String filename = Filename (gps, "a");
    char fname[30];
    filename.toCharArray (fname, filename.length() + 1);

    File dataFile = SD.open(fname, FILE_READ);
       
    if (dataFile) {
      while (dataFile.available()) {
        server << (char)dataFile.read();
      }
      dataFile.close();
    }
  }
}

void setup()
{
  Serial.begin(9600);
  ss.begin (9600);
  logger.init ();
  Ethernet.begin(mac, ip);
  webserver.setDefaultCommand(&sendIndexContent);
  webserver.addCommand("index.html", &sendIndexContent);
  webserver.addCommand("violations.html", &sendFileContent);
  webserver.begin();
}

void loop()
{
  char buff[64];
  int len = 64;

  /* process incoming connections one at a time forever */
  webserver.processConnection(buff, &len);
  
  sprintf (data, "l=%02d;w=%02d;t=%02d;rh=%02d;r1=%d;r2=%d", l.val(), w.val(), t.val(), rh.val(), sw1.val(), sw2.val());

  if ((millis() - lastLog) > 1000*LOG_INTERVAL)
  {
    lastLog = millis();
    logger.write (Filename (gps, "l"), String (Epoch (gps) + ";" + data));
  }

  if (l.state () && w.state() && t.state() && rh.state() && sw1.state() && sw2.state() && violation)
  {
    // all states are true, incl. violation flag -> clean violation flag
    violation = false; 
  }

  if ((!l.state() || !w.state() || !t.state() || !rh.state() || !sw1.state() || !sw2.state()) && !violation)
  {
    // constrait violation
    violation = true;
    Serial.println (String (Epoch (gps) + ";" + data));
    logger.write (Filename (gps, "a"), String (Epoch (gps) + ";" + data));
  }

  smartdelay (1000 * LOOP_DELAY);
}

static String Epoch (TinyGPS &gps)
{
  // format: yyyy-mm-ddThh:mm:ss.sss
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  String ret;

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  
  if (age == TinyGPS::GPS_INVALID_AGE)
  {
    ret = "**********";
  }
  else
  {
    char sz[30];
    sprintf(sz, "%02d-%02d-%02dT%02d:%02d:%02d", year, month, day, hour, minute, second);
    ret = String (sz);
  }
  return ret;
}

static String Filename (TinyGPS &gps, char * postfix)
{
  // format: mm-dd-postfix.txt
  int year;
  byte month = 0, day = 0, hour, minute, second, hundredths;
  unsigned long age;
  char sz[30];

  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);

  sprintf(sz, "%02d%02d-%s.txt", month, day, postfix);
  return String (sz);
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
