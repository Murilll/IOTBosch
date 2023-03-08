import pandas as pd
import matplotlib.pyplot as plt
import pyodbc
import time
import numpy as np
import seaborn as sns

server = 'CT-C-0013F\SQLEXPRESS'
database = 'tempdb'
conn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';Trusted_Connection=yes')
driver= '{ODBC Driver 17 for SQL Server}'
cursor = conn.cursor()
cursor.execute("SELECT Temperatura, DataHora FROM dbo.Sensor")
row = cursor.fetchone()

lista=[]
listatempo=[]

while row:
    lista.append(row[0])
    listatempo.append(str(row[1]))
    row = cursor.fetchone()
    
    
df = pd.DataFrame({"Temperatura":lista, "Tempo":listatempo})
df['Tempo'] = pd.to_datetime(df["Tempo"])
sns.relplot(x="Tempo", y="Temperatura", data=df, kind="line")
plt.title("Temperatura por Tempo")
plt.xticks(rotation=90)