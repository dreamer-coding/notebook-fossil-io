#include "fossil/io/output.h"
#include "fossil/io/cipher.h"

/** 
 * @brief Example of using the fossil_io_cipher API to encode and decode text
 *
 * This example demonstrates how to use the fossil_io_cipher API to encode a string using a specified cipher (in this case, "rot13") and then decode it back to the original string.
 *
 * The example also emphasizes the importance of freeing the allocated memory for the encoded and decoded strings to prevent memory leaks.
 */
int main(void)
{
    // Original text and cipher to use
    const char *text = "Hello Fossil";
    const char *cipher = "rot13";

    // Encode the text using the specified cipher
    char *encoded = fossil_io_cipher_encode(text, cipher);

    if (!encoded)
    {
        fossil_io_printf("Encode failed\n");
        return 1;
    }

    fossil_io_printf("Encoded: %s\n", encoded);

    // Decode the encoded text back to the original text
    char *decoded = fossil_io_cipher_decode(encoded, cipher);

    if (!decoded)
    {
        fossil_io_printf("Decode failed\n");
        free(encoded);
        return 1;
    }

    fossil_io_printf("Decoded: %s\n", decoded);

    // Free the allocated memory for the encoded and decoded strings
    free(encoded);
    free(decoded);

    return 0;
}
