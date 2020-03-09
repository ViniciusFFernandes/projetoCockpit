from pynput.keyboard import Key, Controller
import serial
import os.path

global keyboard
global tecla

scriptpath = os.path.dirname(__file__)
filename = os.path.join(scriptpath, 'config.txt')
arquivo = open(filename)
texto = arquivo.read()
configs = texto.split("/")
keyboard = Controller()
ser = serial.Serial(config[0],config[1])
tecla = ''
while 1:
    value = ser.read()
    print(value)
    tecla = tecla + str(value)
    if value == '':
        if tecla != '':
            keyboard.press(chr(int(tecla)))
            print("tecla precionada: " + chr(int(tecla)))
            tecla = ''