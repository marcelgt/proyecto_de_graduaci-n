#include <OneWire.h>
#include <DallasTemperature.h>

const int CALENTAR=22;
const int ENFRIAR=23;
int ESTADO=0;

const byte PinSensorTemperatura = 9;
String NivelTemperatura= "NORMAL";

OneWire oneWireObjeto (PinSensorTemperatura);
DallasTemperature sensorDS18B20 (&oneWireObjeto);

void setup() {

 
  //pinMode(ENFRIAR, OUTPUT);
  Serial.begin(9600);
  sensorDS18B20.begin();
  

}

void loop() {
 //  put your main code here, to run repeatedly:
  delay(20000);
  sensorDS18B20.requestTemperatures();       //Se obtiene la temperatura en ºC

Serial.println("Temperatura del Acuario:");
Serial.println(sensorDS18B20.getTempCByIndex(0));

if (sensorDS18B20.getTempCByIndex(0) <= 21 ){
    NivelTemperatura = "BAJA";
    
   if (ESTADO != CALENTAR){
    ENCENDER (CALENTAR);
   }
}
  
  if(sensorDS18B20.getTempCByIndex(0) >= 29){
    NivelTemperatura = "ALTA" ;
    if (ESTADO != ENFRIAR){
      ENCENDER (ENFRIAR);
     }
   }

 if(sensorDS18B20.getTempCByIndex(0) < 29 & sensorDS18B20.getTempCByIndex(0) >= 22){
    NivelTemperatura = "NORMAL" ;
    if(ESTADO !=0){
        APAGAR();
    }
 }
     Serial.println("NIVEL DE TEMPERATURA ES:" + NivelTemperatura);  
 
}

int ENCENDER(int PIN){
   pinMode(PIN,OUTPUT);
   delay(5000);
   digitalWrite(PIN,  LOW);
   Serial.println("encender");
   ESTADO = PIN;
   return ESTADO;
   
 }

void APAGAR(){
  digitalWrite(ESTADO, HIGH );
  //delay(5000);
  ESTADO=0;
  Serial.println("apagar");
}
