import serial
import time

# send serial message
# Don't forget to establish the right serial port ******** ATTENTION
# SERIALPORT = "/dev/ttyUSB0" "/dev/tty.usbserial-DA00G4XZ"
SERIALPORT = "/dev/ttyACM0"
BAUDRATE = 115200
ser = serial.Serial()


def initUART():
    # ser = serial.Serial(SERIALPORT, BAUDRATE)
    ser.port = SERIALPORT
    ser.baudrate = BAUDRATE
    ser.bytesize = serial.EIGHTBITS  # number of bits per bytes
    ser.parity = serial.PARITY_NONE  # set parity check: no parity
    ser.stopbits = serial.STOPBITS_ONE  # number of stop bits
    ser.timeout = None  # block read

    # ser.timeout = 0             #non-block read
    # ser.timeout = 2              #timeout block read
    ser.xonxoff = False  # disable software flow control
    ser.rtscts = False  # disable hardware (RTS/CTS) flow control
    ser.dsrdtr = False  # disable hardware (DSR/DTR) flow control
    # ser.writeTimeout = 0     #timeout for write
    return tryConnectSerial()

def tryConnectSerial():
    attemps = 0
    while attemps < 5:
        print("Starting Up Serial")
        try:
            ser.open()
            
            return ser;
        except serial.SerialException as e:
            print("Serial {} port not available {}".format(SERIALPORT, e))
            print("Waiting before retry ...")
            attemps+=1
            time.sleep(5)




def sendUARTMessage(msg):
    ser.write(msg)
    print("Message <" + msg + "> sent to micro-controller." )