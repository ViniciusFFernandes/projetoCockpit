import serial

portaUSB = serial.Serial(aux, 9600)
portaUSB.write(aux.encode())
    

