### Aplicacion para controlar el manipulador de la EETP N 466
### mediante un modulo Bluetooth.

from jnius import autoclass
BluetoothAdapter = autoclass('android.bluetooth.BluetoothAdapter') #
BluetoothDevice = autoclass('android.bluetooth.BluetoothDevice') #
BluetoothSocket = autoclass('android.bluetooth.BluetoothSocket') #
UUID = autoclass('java.util.UUID') #

def get_socket_stream(name):
    paired_devices = BluetoothAdapter.getDefaultAdapter().getBondedDevices().toArray()
    socket = None
    for device in paired_devices:
        if device.getName() == name:
            socket = device.createRfcommSocketToServiceRecord(
                UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"))
            recv_stream = socket.getInputStream()
            send_stream = socket.getOutputStream()
            break
    socket.connect()
    return recv_stream, send_stream

recv_stream = 0
send_stream = 0

import kivy
kivy.require("1.9.1")
from kivy.app import App
from kivy.properties import ObjectProperty, StringProperty
from kivy.uix.screenmanager import ScreenManager, Screen, NoTransition
from kivy.uix.floatlayout import FloatLayout
from kivy.uix.gridlayout import GridLayout
from kivy.uix.scrollview import ScrollView
from kivy.uix.label import Label
from kivy.uix.button import Button
from kivy.uix.behaviors import ButtonBehavior
from kivy.uix.image import Image
from kivy.effects.scroll import ScrollEffect
from kivy.clock import Clock
from kivy.animation import Animation

class ManipuladorApp(App):
    def build(self):
        return sm()

class Main_Screen(Screen):
    connect_button = ObjectProperty
    avance_btn = ObjectProperty
    retr_btn = ObjectProperty
    giro_negativo_btn = ObjectProperty
    giro_positivo_btn = ObjectProperty
    zaxis_btn = ObjectProperty
    vacuum_btn = ObjectProperty
    instructions_label = ObjectProperty
    notification_label = ObjectProperty
    
    def connect(self):
        self.connect_button.disabled = True
        self.connect_button.text = "Conectando..."
        Clock.schedule_once(self.connect_PHASE_TWO, 0.5)
    def connect_PHASE_TWO(self, no_se):
        global recv_stream
        global send_stream
        try:
            #pass
            recv_stream, send_stream = get_socket_stream('TP ELC Manipulator')
        except Exception:
            self.notification_label.color = [1,1,0,1]
            self.notification_label.text = "Error al conectar."
            self.notification_label.opacity = 1
            Clock.schedule_once(self.enable_connect, 3)
            anim = Animation(opacity = 1, duration = 2) + Animation(opacity = 0, duration = 0.66)
            anim.start(self.notification_label)
            return
        self.connect_button.text = "Conectado"
        self.avance_btn.disabled = False
        self.avance_btn.pos_hint = { "x": 0.35, "y": 0.725}
        self.retr_btn.disabled = False
        self.retr_btn.pos_hint = { "x": 0.35, "y": 0.375 }
        self.giro_negativo_btn.disabled = False
        self.giro_negativo_btn.pos_hint = { "x": 0.2, "y": 0.55 }
        self.giro_positivo_btn.disabled = False
        self.giro_positivo_btn.pos_hint = { "x": 0.5, "y": 0.55 }
        self.zaxis_btn.disabled = False
        self.zaxis_btn.pos_hint = { "x": 0.55, "y": 0.125 }
        self.vacuum_btn.disabled = False
        self.vacuum_btn.pos_hint = { "x": 0.55, "y": 0.0 }
        self.instructions_label.pos_hint = { "x": 1.05 , "y": 0.1 }

        self.notification_label.color = [0,1,0,1]
        self.notification_label.text = "Conectado!"
        self.notification_label.opacity = 1
        anim = Animation(opacity = 1, duration = 2) + Animation(opacity = 0, duration = 0.66)
        anim.start(self.notification_label)

    def enable_connect(self, dt):
        self.connect_button.disabled = False
        self.connect_button.text = "Conectar"

    def enviar_orden(self, orden):
        if orden == 0:
            self.avance_btn.disabled = False
            self.retr_btn.disabled = False
            self.giro_negativo_btn.disabled = False
            self.giro_positivo_btn.disabled = False
            self.zaxis_btn.disabled = False
            self.vacuum_btn.disabled = False
        elif orden == 1:
            self.retr_btn.disabled = True
            self.giro_negativo_btn.disabled = True
            self.giro_positivo_btn.disabled = True
            self.zaxis_btn.disabled = True
            self.vacuum_btn.disabled = True
        elif orden == 2:
            self.avance_btn.disabled = True
            self.giro_negativo_btn.disabled = True
            self.giro_positivo_btn.disabled = True
            self.zaxis_btn.disabled = True
            self.vacuum_btn.disabled = True
        elif orden == 3:
            self.avance_btn.disabled = True
            self.retr_btn.disabled = True
            self.giro_positivo_btn.disabled = True
            self.zaxis_btn.disabled = True
            self.vacuum_btn.disabled = True
        elif orden == 4:
            self.avance_btn.disabled = True
            self.retr_btn.disabled = True
            self.giro_negativo_btn.disabled = True
            self.zaxis_btn.disabled = True
            self.vacuum_btn.disabled = True
        elif orden == 5:
            self.avance_btn.disabled = True
            self.retr_btn.disabled = True
            self.giro_negativo_btn.disabled = True
            self.giro_positivo_btn.disabled = True
            self.vacuum_btn.disabled = True
        elif orden == 6:
            self.avance_btn.disabled = True
            self.retr_btn.disabled = True
            self.giro_negativo_btn.disabled = True
            self.giro_positivo_btn.disabled = True
            self.zaxis_btn.disabled = True
        global send_stream
        try:
            #pass
            send_stream.write(str(orden))#
            send_stream.write("\n")#
            send_stream.flush()#
        except Exception:
            self.notification_label.color = [1,0,0,1]
            self.notification_label.text = "Conexion interrumpida."
            self.notification_label.opacity = 1
            Clock.schedule_once(self.enable_connect, 3)
            anim = Animation(opacity = 1, duration = 2) + Animation(opacity = 0, duration = 0.66)
            anim.start(self.notification_label)

            self.connect_button.text = "Conectar"
            self.avance_btn.disabled = True
            self.avance_btn.pos_hint = { "x": 1.35, "y": 0.725}
            self.retr_btn.disabled = True
            self.retr_btn.pos_hint = { "x": 1.35, "y": 0.375 }
            self.giro_negativo_btn.disabled = True
            self.giro_negativo_btn.pos_hint = { "x": 1.2, "y": 0.55 }
            self.giro_positivo_btn.disabled = True
            self.giro_positivo_btn.pos_hint = { "x": 1.5, "y": 0.55 }
            self.zaxis_btn.disabled = True
            self.zaxis_btn.pos_hint = { "x": 1.55, "y": 0.125 }
            self.vacuum_btn.disabled = True
            self.vacuum_btn.pos_hint = { "x": 1.55, "y": 0.0 }
            self.instructions_label.pos_hint = { "x": 0.05 , "y": 0.1 }

class sm(ScreenManager):
    pass

class BackButton(Button):
    pass

class ScrollableLabel(ScrollView):
    text = StringProperty('')

if __name__ == "__main__":
    ManipuladorApp().run()
