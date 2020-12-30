import socket

result = socket.getfqdn()
print (result[result.find(".") + 1 : result.__len__()])