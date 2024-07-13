from doipclient import DoIPClient
# ~ from doipclient.connectors import DoIPClientUDSConnector
# ~ from udsoncan.client import Client
# ~ from udsoncan.services import *

print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
# ~ print("await_vehicle_announcement")
# ~ address, announcement = DoIPClient.await_vehicle_announcement()

# ~ # Power cycle your ECU and wait for a few seconds for the broadcast to be
# ~ # received
# ~ logical_address = announcement.logical_address
# ~ ip, port = address
# ~ print(ip, port, logical_address)
# ~ print("ip" , ip)
# ~ print("port" , port)
# ~ print("logical_address" , logical_address)
# ~ print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>")

print("get_entity")
address, announcement = DoIPClient.get_entity()
logical_address = announcement.logical_address
ip, port = address
print("ip" , ip)
print("port" , port)
print("logical_address" , logical_address)

print("routing activation")
client = DoIPClient("10.0.2.15", 13400)
print(client.request_entity_status())
print(client.request_diagnostic_power_mode())
print(client.request_alive_check())

key = bytes([0x10, 0x01])

print(client.send_diagnostic(key))
