   #include <SPI.h>

   #define SPI_SCK  18
   #define SPI_MISO 19
   #define SPI_MOSI 23
   #define SPI_CS   27

   SPIClass vspi(VSPI);

   void setup() {
     Serial.begin(115200);
     pinMode(SPI_CS, OUTPUT);
     digitalWrite(SPI_CS, HIGH);
     vspi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, -1);
   }

   void loop() {
     vspi.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
     digitalWrite(SPI_CS, LOW);
     uint8_t rx = vspi.transfer(0xA5);
     digitalWrite(SPI_CS, HIGH);
     vspi.endTransaction();

     Serial.printf("Sent 0xA5, received 0x%02X\n", rx);
     delay(1000);
   }