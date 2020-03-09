from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
from kivy.uix.textinput import TextInput
import os

class WarThunderCockpit(App):
    def build(self):
        Container = BoxLayout(orientation='vertical')
        labelInform = Label(text='Informe os dados para conectar-se com o arduino', font_size=20)
        Container.add_widget(labelInform)
        global valuetextCOM
        global valuetextSerial
        global valuetextMonitora
        try:
            nome_arquivo = './config.txt'
            arquivo = open(nome_arquivo, 'r+')
            texto = arquivo.read()
            configs = texto.split("/")
        except FileNotFoundError:
            valuetextCOM = ''
            valuetextSerial = ''
            valuetextMonitora = ''
        
        # campos com valores para serem salvos
        inputsValores = BoxLayout(spacing=5, padding=5)
        labelCOM = Label(text='Porta COM', font_size=20, size_hint=(.5, .3))
        self.textinputCOM = TextInput(text='', multiline=False, size_hint=(.5, .3))
        labelSerial = Label(text='Serial', font_size=20, size_hint=(.5, .3))
        self.textinputSerial = TextInput(text='', multiline=False, size_hint=(.5, .3))
        inputsValores.add_widget(labelCOM)
        inputsValores.add_widget(self.textinputCOM)
        inputsValores.add_widget(labelSerial)
        inputsValores.add_widget(self.textinputSerial)

        # campos com valores para serem salvos
        programaMonitora = BoxLayout(spacing=5, padding=5)
        labelMonitora = Label(text='Programa de monitoramento', font_size=20, size_hint=(.4, .3))
        self.textMonitora = TextInput(text='', multiline=False, size_hint=(.5, .3))
        programaMonitora.add_widget(labelMonitora)
        programaMonitora.add_widget(self.textMonitora)

         # campos com valores para serem salvos
        boxbtnSalva = BoxLayout(spacing=5, padding=5)
        btnSalva = Button(text='Salvar', size_hint=(1, .3), on_press=self.salvarConfig)
        boxbtnSalva.add_widget(btnSalva)

        # btn para conectar e desconectar
        BtnConectarDesconectar = BoxLayout(spacing=5, padding=5)
        self.btnDesconectar = Button(text='Desconectar', size_hint=(.5, .3), on_press=self.desconectar)
        self.btnDesconectar.disabled = True
        self.btnConectar = Button(text='Conectar', size_hint=(.5, .3), on_press=self.conectar)
        BtnConectarDesconectar.add_widget(self.btnDesconectar)
        BtnConectarDesconectar.add_widget(self.btnConectar)

        Container.add_widget(inputsValores)
        Container.add_widget(programaMonitora)
        Container.add_widget(boxbtnSalva)
        Container.add_widget(BtnConectarDesconectar)
        return Container

    def conectar(self, btn):
        self.btnConectar.disabled = True
        self.btnDesconectar.disabled = False
        os.startfile("../monitora_arduino/monitora_arduino.exe")
    
    def desconectar(self, btn):
        self.btnConectar.disabled = False
        self.btnDesconectar.disabled = True

    def salvarConfig(self, btn):
        try:
            nome_arquivo = 'config.txt'
            arquivo = open(nome_arquivo, 'r+')
        except FileNotFoundError:
            arquivo = open(nome_arquivo, 'w+')
        arquivo.write(self.textinputCOM.text)
        arquivo.write('/')#Separador
        arquivo.write(self.textinputCOM.text)
        arquivo.write('/')#Separador
        arquivo.write(self.textMonitora.text)
        arquivo.close()

WarThunderCockpit().run()
