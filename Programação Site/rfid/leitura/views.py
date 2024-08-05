from django.shortcuts import render
#from django.http import JsonResponse
from .leitura_serial import Leitura_Serial as ler 
import serial

# Create your views here.

def leitura(request):

    context = {
        'title':'Leitura',
    }
    return render(request, 'index.html', context)

def leitura_rfid(request):
    
    #ser = serial.Serial('COM3', 9600)
    #
    #if not (ser.is_open):
    #    ser.open()
    #    print("TRUE")
        
    context = {
        'title':'Leitura',
        'rfid': ler.ler_rfid()
    }
    return render(request, 'index.html', context)