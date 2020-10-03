#include <TFT_eSPI.h>
#include <SPI.h>
#include "AtWiFi.h"

#define TFT_GREY 0x5AEB // new colour

TFT_eSPI tft = TFT_eSPI();

String wifiSSID[10];
String wifiRSSI[10];
String wifiSEC[10];

void setup() {
    Serial.begin(115200);
tftStart();
    // Set WiFi to station mode and disconnect from an AP if it was previously connected
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    Serial.println("Setup done");
}

void loop() {
   wifiScan();
}

void tftStart () {
  tft.init();
  tft.setRotation(3);

   
}
void tftReset (){
  tft.fillScreen(TFT_GREY);
  tft.setCursor(10, 5, 2);
  tft.setTextColor(TFT_WHITE, TFT_BLACK); tft.setTextSize(1);
}

void wifiScan() {
  
  Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
        tftReset();
        tft.print("No network Found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        tftReset();
        tft.print("network Found !: ");
        tft.println(n);
        
        for (int i = 0; i < 9;++i) {
            // Print SSID and RSSI for each network found
        Serial.print(WiFi.SSID(i));
        Serial.print(" ");
        Serial.println(WiFi.encryptionType(i));
        if (WiFi.SSID(i) != 0) {
           wifiSSID[i] = WiFi.SSID(i);
           wifiRSSI[i] = WiFi.RSSI(i);
           wifiSEC[i] = WiFi.encryptionType(i);
           tft.print(wifiSSID[i]);
           tft.print(" > RSSI: ");
           tft.println(wifiRSSI[i]); 
        }
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
