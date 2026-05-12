#include "fossil/io/output.h"
#include "fossil/io/cipher.h"

using fossil::io::Cipher;

/** 
 * @brief Example of using the fossil_io_cipher API to encode and decode text
 *
 * This example demonstrates how to use the fossil_io_cipher API to encode a string using a specified cipher (in this case, "rot13") and then decode it back to the original string.
 *
 * The example also emphasizes the importance of freeing the allocated memory for the encoded and decoded strings to prevent memory leaks.
 */
int main()
{
    // Original text and cipher to use
    std::string text = "Hello Fossil Logic";

    // Encode the text using the specified cipher
    std::string encoded = Cipher::encode(text, "rot13");
    fossil::io::Output::printf("Encoded: %s\n", encoded.c_str());

    // Decode the encoded text back to the original text
    std::string decoded = Cipher::decode(encoded, "rot13");
    fossil::io::Output::printf("Decoded: %s\n", decoded.c_str());

    // Additional examples with other ciphers
    std::string base64 = Cipher::encode(text, "base64");
    std::string morse  = Cipher::encode(text, "morse");
    std::string leet   = Cipher::encode(text, "leet");

    // Print the results of the additional ciphers
    fossil::io::Output::printf("Base64: %s\n", base64.c_str());
    fossil::io::Output::printf("Morse:  %s\n", morse.c_str());
    fossil::io::Output::printf("Leet:   %s\n", leet.c_str());

    // Round trip test
    std::string roundtrip = Cipher::decode(base64, "base64");
    fossil::io::Output::printf("Roundtrip: %s\n", roundtrip.c_str());

    return 0;
}