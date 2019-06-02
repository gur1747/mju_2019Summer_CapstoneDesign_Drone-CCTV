import socket

 DEFAULT_PROTOCOL = 0
 PORT = 8702

 sock = socket.socket (socket.AF_INET, socket.SOCK_STREAM,
 DEFAULT_PROTOCOL)
 sock.bind (('', PORT))
 sock.listen (5)

 # wait for a connection
 try:
     while True:
         newSocket, address = sock.accept ()
         print "connected from", address
         while True:
             receivedData = newSocket.recv (8192)
             if not receivedData:
                 break
                 print "received: ", receivedData
                 newSocket.sendall (receivedData)
                 newSocket.close()
                 print "disconnected from", address
 finally:
     sock.close ()
