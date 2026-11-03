Laboratory Activity 8: Wired Communication



Name: Pansoy, Kate Alexia Pansoy


Course / Section: BCA188/B186



 1. Pin table

| Interface | Signal | GPIO used | Connection |
|---|---|---|---|
| UART (Serial2) | TX | 17 | Jumper to GPIO16 (RX) |
| UART (Serial2) | RX | 16 | Jumper from GPIO17 (TX) |
| I²C (Wire) | SDA | 21 | Module SDA |
| I²C (Wire) | SCL | 22 | Module SCL |
| SPI (VSPI) | SCK | 18 | No wire needed |
| SPI (VSPI) | MOSI | 23 | Jumper to GPIO19 (MISO) |
| SPI (VSPI) | MISO | 19 | Jumper from GPIO23 (MOSI) |
| SPI (VSPI) | CS | 27 | No wire needed |

Pin choices: every signal has its own pin. None are strapping pins (0, 2, 5, 12, 15), onboard flash pins (6 to 11), or input-only pins (34 to 39). A WROOM-32 board is used because WROVER boards reserve GPIO16 and 17 for PSRAM. The default VSPI CS (GPIO5) is a strapping pin, so GPIO27 is used instead.



2. Wiring

| Interface | Connection |
|---|---|
| UART loopback | GPIO17 (TX) to GPIO16 (RX) |
| I²C module | SDA to GPIO21, SCL to GPIO22, VCC to 3V3, GND to GND |
| SPI loopback | GPIO23 (MOSI) to GPIO19 (MISO) |

The I²C module is powered from 3V3. The USB cable was unplugged before every wiring change.

<img width="444" height="471" alt="image" src="https://github.com/user-attachments/assets/1670f86c-5545-4f5d-89a3-d6fc8e3461d3" />


3. Serial Monitor output


 Test 1: UART with jumper

 
<img width="1069" height="1848" alt="fdd075d9-95cc-4406-a8e3-390220f340a4 (1)" src="https://github.com/user-attachments/assets/50a7903e-04e4-49b7-822c-b8165b664607" />


 Test 2: UART without jumper


<img width="1070" height="1109" alt="3f9d452e-eed1-4c14-bb43-126960f695a6 (1)" src="https://github.com/user-attachments/assets/e7d1e5a2-0705-4a11-a8a7-2eb609dd833a" />


Test 3: I²C with module



<img width="1070" height="1407" alt="a85dc75e-637b-482a-a029-a06660e80bb4" src="https://github.com/user-attachments/assets/3d764d7d-ba24-404b-b72f-6f9f58dc38f9" />



Test 4: I²C without module



<img width="1070" height="872" alt="2fc3b078-6830-4abd-842a-b07b33c3273c" src="https://github.com/user-attachments/assets/f5008e3a-8241-401e-99be-4b64e7833382" />



Test 5: SPI with jumper



<img width="1070" height="1626" alt="c37fdf5a-f123-4dfd-bbfa-12244faee7dd" src="https://github.com/user-attachments/assets/9e6786fd-ab6f-4b1d-bf92-3d672c9612a3" />



Test 6: SPI without jumper



<img width="1070" height="1430" alt="5413a132-eb1c-44ba-aa4a-0ca268a2b4ca" src="https://github.com/user-attachments/assets/6ed1eb80-9275-4d8c-ae95-75d829312c74" />


 
 Test 7: Sketch at 9600, monitor at 11520



<img width="1070" height="1107" alt="db8adaf5-4a83-468e-89ac-81be956c4cbc" src="https://github.com/user-attachments/assets/9f79cff3-062f-4da1-934c-51ba07374676" />



Test 8: Sketch at 9600, monitor at 9600



<img width="1059" height="1428" alt="60935020-6b51-44b2-a982-9e0da9d5fa15" src="https://github.com/user-attachments/assets/9eed48b0-565a-48c8-82d7-485d4382b7c7" />



4. Expected vs. observed

| Interface | Test | Expected | Observed |
|:---|:---|:---|:---|
| UART | With jumper | `PING` once per second, because TX is wired back to RX | `PING` printed every ___ second(s) after `UART loopback test`. |
| UART | Without jumper | Nothing received, apart from possible stray characters from the floating RX pin | After `UART loopback test`, ___ (nothing / stray characters: ___) was printed. |
| I²C | With module | `Found device at 0x3C` (OLED) or `0x76`/`0x77` (BME/BMP280) | The scan printed `Found device at 0x__` for my ___ module. |
| I²C | Without module | `No I2C devices found`, because nothing answers any address | The scan printed `No I2C devices found`. |
| SPI | With jumper | `Sent 0xA5, received 0xA5`, because MOSI is wired to MISO | Printed `Sent 0xA5, received 0x__` every second. |
| SPI | Without jumper | A value other than 0xA5, often `0xFF` or `0x00`, because MISO floats | Printed `Sent 0xA5, received 0x__`, and the value (stayed the same / changed to ___). |
| Baud rate | Sketch 9600, monitor 115200 | Garbled or unreadable characters, because the baud rates do not match | Boot messages were readable, but the sketch output appeared as rows of unreadable boxes instead of `UART loopback test` and `PING`, because the baud rates did not match. |
| Baud rate | Sketch 9600, monitor 9600 | Readable text again, because the baud rates match | After switching the monitor to 9600, the output was ___ (readable `UART loopback test` and `PING`). |

 
 
5. Answers to questions

1. Why does UART need both sides to use the same baud rate, while SPI uses a clock line?
   UART has no clock line, so each side times the bits with its own timer and both must agree on the bit duration or the samples land in the wrong places. SPI sends a clock alongside the data, so the receiver samples on the clock edges and needs no pre-agreed rate.

2. Why can two devices with the same address not share one I²C bus?
   The controller picks a device only by its address, so two devices with the same address would both respond and drive SDA at the same time. That corrupts the data and the devices cannot be addressed separately.

3. Why is CS set HIGH between SPI transfers?
   CS LOW selects the device and starts a transfer, and CS HIGH deselects it so it ignores the bus and resets its internal state for the next transfer. It also lets several devices share SCK, MOSI, and MISO.
