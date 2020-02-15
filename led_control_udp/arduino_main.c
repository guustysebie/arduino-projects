#include <SPI.h>          // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>  // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <string.h>
#include <stdlib.h>


//COMMANDOS
#define CMD_ON "on"
#define CMD_OFF "off"


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168,1,201);

unsigned int localPort = 8888;              // local port to listen on

char packetBuffer[UDP_TX_PACKET_MAX_SIZE];  //buffer to hold incoming packet,
char ReplyBuffer[25];

int LED_STATUS = 0;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

void log_command(char* ip_addr)
{
   Serial.print("From: ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port: ");
    Serial.print(Udp.remotePort());
    Serial.print(", command: ");
    Serial.print(ip_addr);
    Serial.print("\n");
}


void setup() {
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  Serial.begin(9600);
  pinMode(8, OUTPUT);
}

void loop() {
  // if there's data available, read a packet
  if(Udp.parsePacket())
  {
    //clear previous responses
    memset(packetBuffer, 0, sizeof packetBuffer);
    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);

    char *str_command = (char*)malloc(UDP_TX_PACKET_MAX_SIZE * sizeof(char));
    strcpy(str_command, packetBuffer);

    //log for debug
    log_command(str_command);
    

    if(strcmp(str_command,CMD_ON)==0){
      LED_STATUS =1;
      strcpy(ReplyBuffer,"Light turned on");
    }else if(strcmp(str_command,CMD_OFF)==0){ 
      LED_STATUS =0;    
      strcpy(ReplyBuffer,"Light turned off") ;
    }else{
      strcpy(ReplyBuffer,"Command not known") ;
    }
 
    digitalWrite(8,LED_STATUS);

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }

}

