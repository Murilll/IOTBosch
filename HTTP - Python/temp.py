import requests
import json
import time
import pyodbc
import seaborn as sns
from datetime import datetime


def sinal():
    data_e_hora_atuais = datetime.now()
    data_e_hora_em_texto = data_e_hora_atuais.strftime("%d/%m/%Y %H:%M")
    proxies = {'https':"https://disrct:etsds10243110@10.224.200.26:8080"}
    urlTemperatura = 'https://iotbosch-default-rtdb.firebaseio.com/Sensor/Temperatura.json'
    urlUmidade = 'https://iotbosch-default-rtdb.firebaseio.com/Sensor/Umidade.json'
    temperatura = float(requests.get(urlTemperatura,proxies=proxies).content)
    umidade = float(requests.get(urlUmidade,proxies=proxies).content)
    
    return temperatura, umidade, data_e_hora_em_texto


def InserirBD(sinal):

    server = 'CT-C-0013F\SQLEXPRESS'
    database = 'tempdb'
    cnxn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
    cursor = cnxn.cursor()
    #cursor.execute("create table dbo.Sensor (Temperatura float, Umidade float, DataHora varchar(100))")
    cursor.execute(f"INSERT dbo.Sensor (Temperatura, Umidade, DataHora) VALUES ({sinal[0]},{sinal[1]},'{sinal[2]}')")
    cursor.commit()
    print("Inserido com sucesso!")         


def apresentar(temp):
    print(f"Temperatura: {temp[0]}")
    print(f"Umidade: {temp[1]}")
    print(f"Umidade: {temp[2]}")
 
 
while True:
    valores=sinal()
    apresentar(valores)
    InserirBD(valores)
    time.sleep(10)  
        
    
                          
    

#nome = input("Digite seu nome para saber quando você vai morrer: ")

#proxies = {'https':"https://disrct:etsds10243110@10.224.200.26:8080"}
#url = 'https://api.agify.io/?name=' + nome

#whomorte = (requests.get(url,proxies=proxies).content)
#ulrJson = json.loads(whomorte)
#print(ulrJson['age'])

