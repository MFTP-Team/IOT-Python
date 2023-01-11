#include "MicroBit.h"
#include "security.c"

MicroBit uBit;

int MAX_SIZE = 100;

int main()
{
    uBit.init();
    uBit.radio.enable();
    uBit.radio.setGroup(17);
    uBit.radio.setTransmitPower(7);
    uBit.serial.setTxBufferSize(128);
    uBit.serial.setRxBufferSize(128);


    char* UID = generate_uid();

    while (true) {
        ManagedString message = uBit.serial.readUntil('}');
        if (message.length() > 0) {
            // Réception d'une simulation de capteur
            // Envoi par du message de simulation
            char* finalMessage = (char*) malloc(MAX_SIZE);
            strcpy(finalMessage, UID);
            strcat(finalMessage, ";");
            // Concaténer message à la fin
            strcat(finalMessage, (char*) message.toCharArray());
            strcat(finalMessage, "}");
            strcat(finalMessage, ";");
            int messSize = strlen(UID) + message.length() + 3;
            if(messSize < MAX_SIZE) {
                for(int i = messSize+2; i<MAX_SIZE; i++) {
                    strcat(finalMessage, "#");
                }
            }
            ManagedString n((int) strlen(finalMessage));
            uBit.display.scroll(n);
            encrypt(finalMessage, 4);
            uBit.radio.datagram.send(finalMessage);
            // uBit.display.scroll(finalMessage);
            uBit.sleep(100);
            free(finalMessage);
        }
        uBit.sleep(100);
    }
}