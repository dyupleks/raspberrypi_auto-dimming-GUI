import RPi.GPIO as GPIO
from tkinter import*
import time
led_pin=18 
GPIO.setmode(GPIO.BCM)
GPIO.setup(led_pin, GPIO.OUT)
pwm_led = GPIO.PWM(led_pin, 500)
class App:
   def __init__(self, master):
     frame = Frame(master)
     self.master = master
     frame.pack()
     Label(frame, text='Choose mode').grid(row=0,column=0)
     #radiobutton 1
     radio_frame = Frame(frame)
     radio_selection = IntVar()
     b1 = Radiobutton(radio_frame, text='Automode',variable=radio_selection,value=100,command=self.updateA)
     b1.pack(side=LEFT)
     ##radiobutton 2
     b2 = Radiobutton(radio_frame, text='Manual',variable=radio_selection,value=0,command=self.updateM)
     b2.pack(side=RIGHT)
     radio_frame.grid(row=0,column=1)
     ##scale for button 2
     scale=Scale(frame,from_= 0,to= 100,orient=HORIZONTAL,command=self.scaleAct)
     scale.grid(row=2,column=1)
     Label(frame,text='Select brightness').grid(row=2,column=0)
   def updateA(self):
     pwm_led.start(100)
   def updateM(self):
     pwm_led.stop()
   def scaleAct(self, duty):
     pwm_led.start(0)
     pwm_led.ChangeDutyCycle(float(duty))
root = Tk()
root.wm_title('Brightness')
app = App(root)
try:
   root.mainloop()
finally:
   print("Cleaning up")
   GPIO.cleanup()     
