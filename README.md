# arts-in-computing
final project 

## Artist’s statement

The way we dance alone in our room listening to music is significantly different from how we dance out in public. The fear of being judged hinders us from being ourselves. 

Our project is an interactive experience that challenges the participant to enjoy a moment without judgment. Our project captures free flowing movements and produces sound as a response. Depending how one moves, the sound will change accordingly. 

Participants are blindfolded. By taking away the ability to see, we encourage our participants to focus on senses other than sight, be vulnerable, and enjoy their own presence. Participants are also given headphones in order to fully immerse themselves in the moment and hear the sounds correlated to their movements. This experience is truly for the participant. It is creating a candid moment in a public space. We are giving you, the participant, the power to create, and capture your truest moments. 

## What it does

![tp-whiteboard-1](https://user-images.githubusercontent.com/42789360/146461391-65b976e7-4666-4854-9963-ca8b37f9d982.jpg)

The program plays a sine wave that changes in frequency as the user’s acceleration changes in 3D by calculating the pitch and roll of their movement using accelerometer data. Once the user wears a jacket with the sensors and arduino, and as they move, rotation and acceleration data is sent over WiFi. My program reads the data, parses the input, creates a JSON object with relevant information, pipes that data to a web server, and opens a WebAudio program that listens to the port. The Web Audio program receives that information, and the frequency changes as a real-time response.

## How we built it

Hardwork, collaboration, and obstinate persistence :’) 

## Challenges I ran into



The challenging part of this project was connecting two Python scripts, where the first was reading the MPU-6050 data (“reader.py”) and the second was sending data to a web server (“server.py”). I had to pipe this data from script one to script two in real-time.

My intuitive approach was to output the accelerometer data to a .txt file, and pass that .txt file as an input to the “server.py” file. However, the file did not update in real-time, and though it sent the information correctly, it did not achieve our aim of the sound changing as the user moves.

My second approach was to use an OS module in Python for reading and writing to and from processes, called Pipe(). This did not work for me because I repeatedly got an OSError, that one part of the pipe that received the data was broken. 

In the middle, I decided to experiment by combining the two reader and server files into one, so that the file could receive input and send it to the server at the same time. This worked!

I also faced a series of trivial errors but found it joyful to discover new things. An error I faced when trying to create the JSON object for 3D acceleration by parsing the string to extract the integer values was a TypeError. I was using a bytes object instead of an int. I noticed that the MPU-6050 would always print the values with the “b’” appended to the beginning, and I wasn’t sure why. I began to investigate this error. I realized that it means that we were receiving the data as a byte object! So I converted it.
 
## Accomplishments that I'm proud of

I’m proud that I was able to send the data in real-time to the server and calculate the roll and pitch of the user’s movements! 

## What I learned

I got to apply my theoretical understanding of networking terms like TCP, UDP, and IP to this project when I sent data from the ESP32 to the server and then listened to it using WebAudio. In addition, I understood the Physics behind how the roll, yaw, and pitch is calculated, and that helped me determine how to interpret the angle changes.

## What's next?

Our next goal is to play .mp3 files that change as the user moves, or have the user select what music they want to play and have that change in frequency as the user moves.


## Citations: 

## Hardware:
https://randomnerdtutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
## Software:
https://docs.google.com/presentation/d/1TT20AihRZXimoyys1HHNua_1hlYzRdfADn4O9edzj44/edit#slide=id.g97e38bed86_11_49
https://www.youtube.com/watch?v=p7tjtLkIlFo
https://developer.mozilla.org/en-US/docs/Web/API/Web_Audio_API


