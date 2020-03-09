from pynput.keyboard import Key, Controller
import serial
import time

global keyboard
global tecla

arquivo = open("./config.txt", 'r+')
texto = arquivo.read()
print(texto)
configs = texto.split("/")
print(configs[0])
print(configs[1])
# keyboard = Controller()
# ser = serial.Serial(porta,serial)
# tecla = ''
# while 1:
#     value = ser.read()
#     print(value)
#     tecla = tecla + str(value)
#     if value == '':
#         if tecla != '':
#             keyboard.press(chr(int(tecla)))
#             tecla = ''