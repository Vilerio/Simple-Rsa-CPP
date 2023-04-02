# RSA Encryption and Decryption using Crypto++
This project demonstrates RSA encryption and decryption using the Crypto++ library in C++.

## Compilation
To compile the project, you need to have the Crypto++ library installed on your system. If you are on Linux or macOS, you can install it using your system's package manager. On Windows, you can download the pre-built binaries from the Crypto++ website. <br/>

Once you have the library installed, you can compile the project by running the following command :


``g++ -o rsa rsa.cpp -lcryptopp``
This will create an executable named rsa in the current directory.<br/>

## Usage
To use the program, you need to provide a string as an argument to the executable. This string will be encrypted using RSA, then decrypted and printed to the console.<br/>

Here's an example :
<br/>
``./rsa "Hello, world !"``<br/> <br/>
This will output the following :


<br/> 
``Text to encrypt : Hello, world !``<br/>
``Generation ended.``<br/>
``Encoded ciphered : Vq3qHvGZL0gE8RmrDzH7jXTQ/g9XW1g8Q5S5sh5h5+vB+DJWw+sC4O4t4h4tYbY9TDgsTOtZrDmF7aLfvvPg==``<br/>
``Decoded cipher  : Hello, world !``<br/> <br/>
Note that the program generates a public and a private key in the current directory named rsa-public.key and rsa-private.key, respectively. These keys are used for the encryption and decryption operations.

