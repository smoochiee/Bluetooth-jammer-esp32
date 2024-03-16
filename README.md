# **WARNING!!! JAMMING IS ILLEGAL**

#OPEN SOURCE FOR BETTER CODING..

# Ble-jammer 
**JAMMING BLUETOOTH AND WIFI USING NRF24L01 AND ESP32 IN RANGE 
2.4GHZ DEVICES**        
---
`NOT TESTED ON 2.4GHZ DRONE I DONT HAVE ONE` 
---


---
## REQUIRED DEVICES AND LIBRARY:
1. 1 OR 2 NRF24
2. 1 ESP32
3. 10UF-100UF CAPACITOR DEPEND ON YOUR NRF
4. LIBRARY USE: https://github.com/nRF24/RF24
---

## DEMO

**THE EFFECT : DEPEND ON DEVICE BLUETOOTH AND RANGE...
IF YOU WANT BETTER PERFORMANCE YOU CAN ADD 2.4GHZ RF AMPLIFIER.**

https://github.com/smoochiee/Ble-jammer/assets/30816448/16f0c1f8-6f23-4cca-a352-f6ff64fe5a90




## SOME NOTES

* NRF24 CAN DO 125 CHANNELS YOU CAN EDIT IT IN CODE
- BLUETOOTH CLASSIC 80 CHANNELS
+ BLE USES 40 CHANNELS
* WIFI USES 1-14 CHANNELS
---
YOU CAN EDIT PAYLOAD SIZE DIRECTLY ON RF24 LIBRARY  `RF24.CPP LINE # 1972`

```
/****************************************************************************/
void RF24::startConstCarrier(rf24_pa_dbm_e level, uint8_t channel)
{
    stopListening();
    write_register(RF_SETUP, read_register(RF_SETUP) | _BV(CONT_WAVE) | _BV(PLL_LOCK));
    if (isPVariant()) {
        setAutoAck(0);
        setRetries(0, 0);
        uint8_t dummy_buf[5];
        for (uint8_t i = 0; i < 5; ++i)
            dummy_buf[i] = 0x00;

        // use write_register() instead of openWritingPipe() to bypass
        // truncation of the address with the current RF24::addr_width value
        write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&dummy_buf), 5);
        flush_tx(); // so we can write to top level

        // use write_register() instead of write_payload() to bypass
        // truncation of the payload with the current RF24::payload_size value
        write_register(W_TX_PAYLOAD, reinterpret_cast<const uint8_t*>(&dummy_buf), 5);

        disableCRC();
    }
    setPALevel(level);
    setChannel(channel);
    IF_SERIAL_DEBUG(printf_P(PSTR("RF_SETUP=%02x\r\n"), read_register(RF_SETUP)));
    ce(HIGH);
    if (isPVariant()) {
        delay(1); // datasheet says 1 ms is ok in this instance
        ce(LOW);
        reUseTX();
    }
}

/****************************************************************************/

```
---


## WEBFLASHER FOR EASY UPLOAD CODE ON ESP32
---
 [WEBFLASHER](https://smoochiee.github.io/Ble-jammer/flash1) HERE.....


---


## SCHEMATIC DIAGRAM:

### FOR DUAL NRF24L01 PINS
+ ` HSPI=SCK = 14, MISO = 12, MOSI = 13, CS = 15 , CE = 16`
+ ` VSPI=SCK = 18, MISO =19, MOSI = 23 ,CS =21 ,CE = 22`

### FOR SINGLE 
 - `VSPI=SCK = 18, MISO =19, MOSI = 23 ,CS =21 ,CE = 22`
 - OR YOU CAN USE
- `HSPI=SCK = 14, MISO = 12, MOSI = 13, CS = 15 , CE = 16` YOU NEED TO EDIT VALUES ON CODE IF YOU USE HSPI

---
![NRF24 ESP32 CONNECTION](https://github.com/smoochiee/Ble-jammer/assets/30816448/c91b6a59-aeb8-4a0b-a8df-8f3030d4506d)
![NRF24L01 PIN](https://github.com/smoochiee/Ble-jammer/assets/30816448/e41779d4-565a-4044-9b88-c0acbea0e93e)
![ESP32 PIN](https://github.com/smoochiee/Ble-jammer/assets/30816448/56cecea4-67da-4e5a-b540-1eb2b53da43b)
![NRF24 CAPACITOR](https://github.com/smoochiee/Ble-jammer/assets/30816448/bf24b643-7b70-4d73-962a-38fa0bffe30f)


--- 
### NOT PRO IN CODING FEEL FREE TO ADD SOME FUNCTIONS

# DONATION
**If you like you can donate to MY PAYPAL ACCOUNT :**


https://paypal.me/smoochieelee?country.x=PH&locale.x=en_US
or

**GCASH
09615018673**
