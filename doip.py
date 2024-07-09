from doipclient import DoIPClient
print("<<<<<<<<<<<<<<<<<<<<<<<<<<<<")
print("await_vehicle_announcement")
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

# ~ print("routing activation")
# ~ client = DoIPClient("10.0.2.15", 3614)
# ~ print(client.request_entity_status())
