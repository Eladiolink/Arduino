#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 05 

#define DHTTYPE    DHT11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
typedef struct TU TU;
typedef struct Info Info;

#define LDR 16 //PINO DIGITAL UTILIZADO PELA SAÍDA DO SENSOR
#define pinoLed 05 //PINO DIGITAL UTILIZADO PELO LED

struct TU{
  float Temperatura;
  float Umidade;
};

struct Info{
  float Temperatura;
  float Umidade;
  int luz;
};

void setup() {
  Serial.begin(9600);
  dht_init();

  pinMode (LDR, INPUT); //DEFINE O PINO COMO ENTRADA
  pinMode(pinoLed, OUTPUT); //DEFINE O PINO COMO SAÍDA
  digitalWrite(pinoLed, LOW); //LED INICIA DESLIGADO
}

void dht_init(){
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  dht.humidity().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;
}

TU Temperatura_Humidade(){
  delay(delayMS);
  static float dados[2];
  TU d;
  
  // TEMPERATURA
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    //SE DER NA TEMPERATURA RUIM VEM PARA CÁ
    Serial.println(F("Error reading temperature!"));
  }
  else {
    dados[0] = event.temperature;
    d.Temperatura = event.temperature;
  }
  
  // HUMIDADE
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
     //SE DER NA HUMIDADE RUIM VEM PARA CÁ
    Serial.println(F("Error reading humidity!"));
  }
  else {
    dados[1] = event.relative_humidity;
    d.Umidade = event.relative_humidity;
  }
  return d;
}

void loop() {
//      TU dados = Temperatura_Humidade();
//    Serial.print("Temperatura: ");
//    Serial.print(dados.Temperatura);
//    Serial.print(" - Umidade: ");
//    Serial.println(dados.Umidade);
    Info info;
    
 //   info.Temperatura = dados.Temperatura;
 //   info.Umidade = dados.Umidade;
    info.luz = digitalRead(LDR);
    
    if(digitalRead(LDR) == HIGH){ //SE LEITURA DO PINO FOR IGUAL A 1 (HIGH), FAZ
    digitalWrite(pinoLed, HIGH); //ACENDE O LED
  }
  else{ //SENÃO, FAZ
    digitalWrite(pinoLed, LOW); //ACENDE O LED
  }
  Serial.println(info.luz);
}
