# IOT-based-health-monitoring


# Arduino Requirements
1-Connect serial cable to pin 6<br>

```
Install SoftwareSerial.h package
```

<h4>Blood Pressure Connections</h4></b><br>
1-Connect the Vcc and GND to the terminals of a 5v battery<br>
2-Connect Tx-OUT of the blood pressure sensor to pin 9<br>
<h4>Pulse Sensor Connections</h4><br>
1-Connect Vcc to 3.3v of the Arduino<br>
2-Connect GND to GND of the Arduino<br>
3-Connect the signal pin to A0 of the Arduino<br>
<h4>LM35 Connections</h4><br>
1-Connect Vcc to 5v of the Arduino<br>
2-Connect GND to GND of the Arduino<br>
3-Connect the signal pin to A2 of the Arduino<br>
<h4>Heartbeat Sensor Connections</h4><br>
1-Connect Vcc to 3.3v of the Arduino<br>
2-Connect GND to GND of the Arduino<br>
3-Connect the signal pin to A4 of the Arduino<br>


# Nodemcu Requirements

```
Install ESP8266WiFi.h
```

```
Install SoftwareSerial.h
```

```
Install PubSubClient.h
```

If error arrise, install the following packages<br>

```
Install Wire.h
```

```
Install Adafruit_Sensor.h
```

```
Install Adafruit_ADXL345_U.h
```

<h4>Nodemcu Connections</h4><br>
1-Replace the WiFi_AP value with the SSID of the WiFi hotspot<br>
2-Replace the WIFI_PASSWORD with the password of the WiFi hotspot<br>
3-Replace TOKEN value with Access Token of the device from the Thingsboard account<br> 
4-Connect the serial cable to D6 pin of the nodemcu<br>
<h4>ADXL345 Connections</h4><br>
1-Connect Vcc to 3V pin of the nodemcu<br>
2-Connect GND to GND of th nodemcu<br>
3-Connect SCL to D1 of the nodemcu<br>
4-Connect SDA to D2 of the nodemcu<br>

