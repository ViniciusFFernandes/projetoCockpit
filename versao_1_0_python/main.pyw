from kivy.app import App
from kivy.uix.button import Button
from kivy.uix.boxlayout import BoxLayout
from kivy.uix.label import Label
import os

class WarThunderCockpit(App):
    def build(self):
        Container = BoxLayout(orientation='vertical')
        button = Button(text='Botao 1', font_size=25)
        label = Label(text='Texto 1', font_size=25)
        Container.add_widget(button)
        Container.add_widget(label)
       
        BtnConectarDesconectar = BoxLayout(spacing=5, padding=5)
        self.btnDesconectar = Button(text='Desconectar', size_hint=(.5, .2), on_press=self.desconectar)
        self.btnDesconectar.disabled = True
        self.btnConectar = Button(text='Conectar', size_hint=(.5, .2), on_press=self.conectar)
        BtnConectarDesconectar.add_widget(self.btnDesconectar)
        BtnConectarDesconectar.add_widget(self.btnConectar)

        Container.add_widget(BtnConectarDesconectar)
        return Container

    def conectar(self, btn):
        self.btnConectar.disabled = True
        self.btnDesconectar.disabled = False
        os.startfile()
    
    def desconectar(self, btn):
        self.btnConectar.disabled = False
        self.btnDesconectar.disabled = True

    def salvarConfig(self, btn):
        try:
            nome_arquivo = '../monitora_arduino/config.txt'
            arquivo = open(nome_arquivo, 'r+')
        except FileNotFoundError:
            arquivo = open(nome_arquivo, 'w+')
        arquivo.write('porta do arduino')
        arquivo.write('/')#Separador
        arquivo.write('Serial do arduino')
        arquivo.close()

WarThunderCockpit().run()
