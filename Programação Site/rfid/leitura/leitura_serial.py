import serial  # Instalar biblioteca pyserial, responsavel pela comunicação do python com arduino

class Leitura_Serial:

    def ler_rfid():
        ser = serial.Serial('COM3',9600)
        rfid =""

        try:
            #if ser.in_waiting > 0:
            #    dado = ser.readline().decode('utf-8').strip()
            #    rfid = str(dado)
            #    print(ser.in_waiting)
            #else:
            #    print(ser.in_waiting)
            #    rfid = str(ser.in_waiting)

            rfid = str(ser.readline().decode('utf-8').strip())
            print(rfid)

        except Exception as ex:
            rfid = str(f"Erro: {ex}")

        return rfid