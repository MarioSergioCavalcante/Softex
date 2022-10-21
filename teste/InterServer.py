from flask import Flask, render_template, request
import flask_cors 
import socket
setpoint_ant = "0" 
app = Flask(__name__)

#criar a primeira página do site

app.static_folder = 'static'

if __name__ == "__main__":
    app.run()

@app.route("/")
def home():
    return render_template("Conectar.html")
#@app.route("/Conectar", methods= ['GET','POST'])
@app.route("/Conectar", methods= ['GET','POST'])
def ConectarPagina():
    setpoint = request.form["Setpoint"]
    print(setpoint.encode())
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect(('172.20.9.110',8080))
    sock.send(setpoint.encode())
    from_server = sock.recv(4096)
    from_server = sock.recv(4096)
    aux = str(from_server).split("|")
    print(aux)
    sock.close()
    
    return render_template("Conectar.html",tank1 = aux[1],tank2 = aux[3])

@app.route("/Conectar", methods= ['GET','POST'])
def Teste(Valores):
    
    return Valores