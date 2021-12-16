import asyncio
from aiohttp import web
from aiohttp.web import Response
from aiohttp_sse import sse_response

from cors_helper import enableCORS
import json



import socket
# use ifconfig -a to find this IP. If your pi is the first and only device connected to the ESP32, 
# this should be the correct IP by default on the raspberry pi
LOCAL_UDP_IP = "192.168.1.2"
SHARED_UDP_PORT = 4210
#global last_message

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Internet  # UDP
sock.bind((LOCAL_UDP_IP, SHARED_UDP_PORT))
def loop():
    while True:
        data, addr = sock.recvfrom(2048)
        last_message = data
        web.run_app(main(), port=8889)
        print(data)
#if __name__ == "__main__":
#    loop()
#    web.run_app(main(), port=8889)

#last_message = "b'Acceleration X: -0.404620, Y: 3.136404, Z: 3.596091 m/s^2 Rotation X: -0.967259, Y: 0.684542, Z: -0.520668 rad/s"

async def handle_echo(reader, writer):
    while True:
      data = await reader.read(1000) #num of bytes to read - just make it big enough
      message = data.decode()
      last_message = message
      addr = writer.get_extra_info('peername')
      if (message == ''):
        writer.close()
        break
      #else:
        #print(f"Received {message!r} from {addr!r}")


async def main():
    server = await asyncio.start_server(
        handle_echo, '', 8888)

    addrs = ', '.join(str(sock.getsockname()) for sock in server.sockets)
    print(f'Serving on {addrs}')

    app = web.Application()
    app.router.add_route('GET', '/', index)
    enableCORS(app)
    return app

async def index(request):
    global last_message
    loop = request.app.loop
    async with sse_response(request) as resp:
        while True:
            data, addr = sock.recvfrom(2048)
            print(data)
            #console.log(data)
            last_message = data
            line = last_message.decode("utf-8")
            arr = line.split()
            #buggy_name = arr[2]
            #name = buggy_name.rstrip(buggy_name[-1])
            #print(name)
            # extracting the coordinate values
            #data = arr[2][:-1]
            #x_val = 648658;
            x_val = arr[2][:-1]
            y_val = arr[4][:-1]
            print(y_val)
            z_val = arr[6]
            print(z_val)
            # making a JSON object
            #values = {'x' : x_val, 'y': y_val, 'z': z_val}
            values = {'x' : x_val, 'y': y_val, 'z': z_val}
            print(values)
            obj_data = json.dumps(values)
            #print(data)
            await resp.send(obj_data)
            await asyncio.sleep(0.5)
    return resp

if __name__ == "__main__":
    web.run_app(main(), port=8889)



