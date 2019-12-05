# Robust Encoder and Decoder (C programming assignment)
This project consists of three parts, encoding, simulating bad transmission and decoding. It uses parity bits to ensure the integrity of the data in case it got corrupted during transmission. It can only handle one corrupted data bit, any more than that will not be fixed during the decoding process. The process of encoding, corrupting and decoding the data will be explained in detail below. This project was the final assignment of my "Programming in C" course.

## Encoding
Encoding works as follows:<br>
1. A byte is read in from the input file. Visually, the byte looks like this:
![Image of Yaktocat](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/input-byte.png)
