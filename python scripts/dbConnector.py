import mysql.connector


from API.models.Electricity import Electricity  
config = {
  'user': 'elmarouf_iot',
  'password': '2RiGt;6j*~-U',
  'host': 'elmaroufi.com',
  'database': 'elmarouf_HomeData',
  'raise_on_warnings': True
}

cnx = mysql.connector.connect(**config)
cursor = cnx.cursor()

add_record = ("INSERT INTO `powerInfo`(`voltage`, `current`, `power`, `energy`, `frequency`, `powerfactor`, `date`) "
                "VALUES(%s, %s, %s, %s,%s, %s,CURRENT_TIMESTAMP)")


print("connection established")
       
def add_one_record(v, a, b, c,d ,e):
    data_record = (v, a, b, c,d ,e)
    cursor.execute(add_record, data_record)
    cnx.commit()
    print("data inserted")

def get_Latest_Record():
    cnx = mysql.connector.connect(**config)
    cursor = cnx.cursor()
    query = ("SELECT `powerInfoID`,`voltage`,`current`,`power`,`energy`,`frequency`,`powerfactor` FROM `powerInfo` WHERE `powerInfoID`=( SELECT max(`powerInfoID`) FROM `powerInfo`)")
    cursor.execute(query)
    print("aminefmkjsdlkmflsdqkjqmsldk")
    myresult = cursor.fetchone()
    print(myresult)
    cursor.close()
    cnx.close() 

    return Electricity(myresult[0],myresult[1],myresult[2],
    myresult[3],myresult[4],myresult[5],myresult[6]).__dict__




def close_connection():
    cursor.close()
   
