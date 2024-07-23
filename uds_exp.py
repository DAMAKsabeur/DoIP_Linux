from doipclient import DoIPClient
from doipclient.connectors import DoIPClientUDSConnector
from udsoncan.client import Client
from udsoncan.services import *

address, announcement = DoIPClient.get_entity()
logical_address = announcement.logical_address
ip, port = address
print("ip" , ip)
print("port" , port)
print("logical_address" , logical_address)

client = DoIPClient(ip, logical_address)
print(client.request_entity_status())
uds_connection = DoIPClientUDSConnector(client)
with Client(uds_connection) as uds_client:
    client.send_diagnostic(ECUReset.ResetType.hardReset)
