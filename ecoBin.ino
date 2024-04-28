#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *ssid = "Atharva";
const char *password = "1234567890";
const char *mqtt_server = "broker.emqx.io";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

// Ultrasonic sensor pins
const int trigPin = D5;
const int echoPin = D6;
int buzz = D1;
const int gled = D2;
const int yled = D3;

void setup_wifi()
{
    delay(10);
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str()))
        {
            Serial.println("connected");
            client.publish("device/status", "MQTT Server is connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(BUILTIN_LED, OUTPUT);
    pinMode(buzz, OUTPUT);
    pinMode(gled, OUTPUT);
    pinMode(yled, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2000)
    {
        lastMsg = now;

        // Trigger ultrasonic sensor
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Read ultrasonic sensor echo
        long duration = pulseIn(echoPin, HIGH);
        // Calculate distance in centimeters
        float distance_cm = duration * 0.034 / 2;

        // Publish distance to MQTT server
        snprintf(msg, MSG_BUFFER_SIZE, "Distance is: %.2f cm", distance_cm);
        if (distance_cm >= 15 && distance_cm <= 30)
        {
            digitalWrite(gled, HIGH);
            digitalWrite(yled, LOW);
            noTone(buzz);
        }
        else if (distance_cm >= 10 && distance_cm < 15)
        {
            digitalWrite(yled, HIGH);
            digitalWrite(gled, LOW);
            noTone(buzz);
        }
        else if (distance_cm < 10)
        {
            digitalWrite(yled, LOW);
            digitalWrite(gled, LOW);
            tone(buzz, 1000);
        }
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish("device/distance", msg);
    }
}