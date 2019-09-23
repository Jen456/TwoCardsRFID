/*
 * --------------------------------------------------------------------------------------------------------------------
 * Ejemplo de dos tarjetas rfid
 * --------------------------------------------------------------------------------------------------------------------
 *
 *
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             rfid_1      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10


 
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN_1         44          // rst para la tarjeta rfid 1
#define SS_PIN_1          53         // sda para la tarjeta rfid 1

#define RST_PIN_2         49           // rst para la tarjeta rfid 2
#define SS_PIN_2          47         // sda para la tarjeta rfid 2

int seleccion=1; // selecciona q tarjeta esta operativa

MFRC522 rfid_1(SS_PIN_1, RST_PIN_1);  // Crear instancia para la rfid_1
MFRC522 rfid_2(SS_PIN_2, RST_PIN_2);  // Crear instancia para la rfid_2

void tarjeta();
// TARJETA 1 ES PARA ENTRADA, TARJETA 2 ES PARA Salida


void setup() {
Serial.begin(9600);  // Inicializar comunicaciones en serie con la PC
while (!Serial);  // No haga nada si no se abre un puerto serie
SPI.begin();   // Inicia bus SPI
rfid_1.PCD_Init();  // inicia tarjeta rfid1
rfid_1.PCD_DumpVersionToSerial(); // Mostrar detalles de PCD - Detalles del lector de tarjetas MFRC522

  rfid_2.PCD_Init();    // inicia tarjeta rfid1
  rfid_2.PCD_DumpVersionToSerial(); // Mostrar detalles de PCD - Detalles del lector de tarjetas MFRC522

 
Serial.println(F("Escanee PICC para ver bloques UID, SAK, tipo y datos..."));
}

void loop() {
tarjeta();
}


void tarjeta()
{
   
  // Reinicie el bucle si no hay una nueva tarjeta presente en el sensor / lector. Esto guarda todo el proceso cuando está inactivo.
  if ( rfid_1.PICC_IsNewCardPresent() || rfid_2.PICC_IsNewCardPresent() ) {
     Serial.println("Read...");}
  // Selecciona una de las cartas
  if ( rfid_1.PICC_ReadCardSerial()>0) {
    rfid_1.PICC_DumpToSerial(&(rfid_1.uid));
    delay(1000);
  }
  if ( rfid_2.PICC_ReadCardSerial()>0) {
    rfid_2.PICC_DumpToSerial(&(rfid_2.uid));
    delay(1000);
  }
 
  // Volcar información de depuración sobre la tarjeta; PICC_HaltA () se llama automáticamente
 
  //rfid_2.PICC_DumpToSerial(&(rfid_2.uid));
}

