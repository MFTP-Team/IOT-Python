#include "MicroBit.h"
#include "security.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nxjson.h"

MicroBit uBit;

char* strdup (const char* s)
{
  size_t slen = strlen(s) + 1;
  char* result = (char *) malloc(slen);
  if(result == NULL)
  {
    return NULL;
  }

  memcpy(result, s, slen+1);
  return result;
}


void onData(MicroBitEvent e)
{
    ManagedString s = uBit.radio.datagram.recv();
    // Les 8 premiers caracteres sont l'id
    char* receivedMsg = strdup(s.toCharArray());
    decrypt(receivedMsg, 4);
    uBit.serial.send(receivedMsg);
}


int main()
{
    uBit.init();
    uBit.radio.enable();
    uBit.radio.setGroup(17);
    uBit.radio.setTransmitPower(7);
    uBit.serial.setTxBufferSize(128);
    uBit.serial.setRxBufferSize(128);

    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);

    while (true) {
        ManagedString message = uBit.serial.readUntil('}');
        if (message.length() > 0) {
            uBit.display.scroll(message);
        }
        uBit.sleep(100);
    }
}