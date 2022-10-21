import socket
import threading
def printit():
  threading.Timer(1.0, printit).start()
  sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  sock.connect(('172.20.9.110',8080))
  sock.send('20'.encode())
  from_server = sock.recv(4096)
  from_server = sock.recv(4096)
  print(from_server)
  sock.close()
  print(from_server)
  aux = str(from_server).split("|")
  print(aux)
  print(aux[1])
  print(aux[3])
printit()