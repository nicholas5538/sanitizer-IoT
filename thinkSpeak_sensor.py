import httplib2
import serial
import os
from dotenv import load_dotenv
os.load()
api_key = os.environ.get('API_KEY')

# Check whether your port is 'COM4' if not change it below
arduinoData = serial.Serial('COM8', 9600) 

while True:
    while arduinoData.inWaiting() == 0: #if no data, do nothing
        pass
    arduinoBytes = arduinoData.readline()
    arduinoString = arduinoBytes.decode('utf-8')
    if len(arduinoString) > 5: # If there are more than 5 elements in the string
        continue
    
    DispCount = 0
    DispCount = float(arduinoString)
    if arduinoString == "DispC":
        DispCount = DispCount + 1
        print(DispCount)
        continue
    conn = httplib2.Http()
    address1 = f"https://api.thingspeak.com/update?api_key={api_key}&field2={DispCount}" 
    conn.request(address1)

    # Most of our printing command in Arduino contains very lengthy word, so I use this len() method
    # Our sensorValue at most contain 5 elements. 
    sensorValue = float(arduinoString) 
    if sensorValue >= 675.0:
        print(f"Water Level: {sensorValue}, full")
    elif sensorValue < 675.0 and sensorValue >= 450.0:
        print(f"Water Level: {sensorValue}, medium")
    elif sensorValue < 450.0:
        print(f"Water Level: {sensorValue}, low, please refill the sanitizer!")
    conn = httplib2.Http()
    # Just replace this API address with your own
    address = f"https://api.thingspeak.com/update?api_key={api_key}X&field1={sensorValue}"
    conn.request(address)