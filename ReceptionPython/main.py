import sendUtil
import json
import requests
import sys

API_URL = sys.argv[0]
ser = sendUtil.initUART()
while ser.isOpen() :
    if(ser.inWaiting() > 100):
        # Réception du message
        data = ser.read(ser.inWaiting())
        data_str = data.decode('utf-8')
        print("Receive data from UART :  {}".format(data_str))

        # Découpe du message par le délimiteur
        datas = data.split(";")

        # Parse la partie json du message
        jsonAlert = json.loads(datas[1])

        # Ajout de l'id du capteur dans le message
        jsonAlert['id'] = datas[0]

        # Appel de l'API
        r = requests.post(API_URL, data = jsonAlert)
        print(r.json())