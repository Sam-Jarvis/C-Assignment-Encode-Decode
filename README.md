# Robust Encoder and Decoder (C programming assignment)
This project consists of three parts, encoding, simulating bad transmission and decoding. It uses parity bits to ensure the integrity of the data in case it got corrupted during transmission. It can only handle one corrupted data bit, any more than that will not be fixed during the decoding process. The process of encoding, corrupting and decoding the data will be explained in detail below. This project was the final assignment of my "Programming in C" course.

## Encoding
Encoding works as follows:<br>
1. A byte is read in from the input file. Visually, the byte looks like this:
![Image of input-byte](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/input-byte.png)
"d3" represents data bit 3, "d2" represents data bit 2 etc.
2. The input byte is split into the most significant nibble (MSN or MSB) and least significant nibble (LSN or LSB). The MSN is the first 4 bits of the input byte and the LSN is the last 4 bits of the input byte.
![Image of msn-lsn](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/msb-lsb.png)
3. Two new bytes are created with the MSN and LSN of the original input byte. Yes, this is not efficient but it is somewhat robust. The output of this is two bytes as visualized below:<br>
MSN <br>
![Image of msn-parity](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/msb-parity.png)
<LSN <br>
![Image of lsn-parity](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/lsb-parity.png)

