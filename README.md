# Robust Encoder and Decoder (C programming assignment)
This project consists of three parts, encoding, simulating bad transmission and decoding. It uses parity bits to ensure the integrity of the data in case it got corrupted during transmission. It can only handle one corrupted data bit, any more than that will not be fixed during the decoding process. The process of encoding, corrupting and decoding the data will be explained in detail below. This project was the final assignment of my "Programming in C" course.

## Encoding
Encoding works as follows:
1. A byte is read in from the input file. Visually, the byte looks like this:
![Image of input-byte](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/input-byte.png)<br/>
"d3" represents data bit 3, "d2" represents data bit 2 etc.
2. The input byte is split into the most significant nibble (MSN or MSB) and least significant nibble (LSN or LSB). The MSN is the first 4 bits of the input byte and the LSN is the last 4 bits of the input byte.
![Image of msn-lsn](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/msb-lsb.png)
3. Two new bytes are created with the MSN and LSN of the original input byte. The reason for this is to create space for the parity bits. The parity will be described below. Yes, this is not efficient but it is somewhat robust. The output of this is two bytes as visualized below:<br/>

![Image of msn-parity](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/msb-parity.png)<br/>
_MSN of original bit inbetween parity bits_

![Image of lsn-parity](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/lsb-parity.png)<br/>
_LSN of original bit inbetween parity bits_
"p2" represents parity bit 2, "p1" represents parity bit 1 etc.

### Parity
The roubstness of this encoder/decoder is based on the theory of parity bits. This can be visualized by these parity circles (venn diagram).<br/>
![Image of parity-temp](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/parity-template.png)<br/>
The 4 data bits, either the MSN or LSN of the original input byte, are stored in the overlapping segments of the circles. The outer bit in each circle is the parity bit for that specific circle. The parity value is decided upon before hand, in this case, the parity must be even. What this means is, in each circle, there must be an even number of zeros and and ones. Both the encoder and decoder know this.<br/>
For example, if the MSN of the input byte was __0__, __1__, __1__, __0__, the encoder will set the parity circles for the MSN's output byte to:</br>
![Image of parity-eg](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/parity-example.png)<br/>
As evident in the example above, each circle has two 1s and 2 zeros. This is how the decoder can detect errors. If a circle has an odd parity, that is, an odd number of zeros and ones, then it knows there is an incorrect bit somewhere. Not only can the decoder identify that there is a mistake, it can deduce where the mistake is.<br/>
If one of the outer-circle bits is flipped, for example:<br/>
![Image of odd-parity1](https://github.com/Sam-Jarvis/C-Assignment-Encode-Decode/blob/master/images-for-documentation/odd-parity-1.png)
