#include <stdlib.h>

#include <fossil/io/cstring.h>
#include <fossil/io/error.h>
#include <fossil/io/output.h>

/** 
 * @brief Example of using the fossil_io_cstring API for various string operations
 *
 * This example demonstrates how to use the fossil_io_cstring API to perform a variety of string operations, including trimming, case conversion, reversal, safe appending, money formatting, pig latin conversion, leetspeak conversion, and more.
 *
 * The example also shows how to use the fossil_io_output library for formatted output and error reporting.
 */
int main(void)
{
    // Create a cstring and perform various operations on it
    cstring greeting = fossil_io_cstring_create("  Hello Fossil IO  ");
    if (!greeting)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
        return EXIT_FAILURE;
    }

    fossil_io_cstring_trim(greeting);

    // Convert to uppercase and reverse the string
    cstring upper = fossil_io_cstring_copy(greeting);
    fossil_io_cstring_to_upper(upper);

    cstring reversed = fossil_io_cstring_reverse(
        fossil_io_cstring_copy(greeting));


    // Print the results
    fossil_io_print("{green}Original:{reset} %s\n", greeting);
    fossil_io_print("{cyan}Upper:{reset} %s\n", upper);
    fossil_io_print("{magenta}Reverse:{reset} %s\n", reversed);

    // Safe append example
    cstring message = fossil_io_cstring_create_safe("Status", 64);
    if (!message)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
        return EXIT_FAILURE;
    }

    // Attempt to append a string safely, checking for errors
    if (fossil_io_cstring_append_safe(&message, ": OK", 64) != 0)
    {
        fossil_io_error("[%s] %s",
                        "memory.alloc",
                        fossil_io_what("memory.alloc"));
    }
    else
    {
        fossil_io_print("{bold}{green}%s{reset}\n", message);
    }

    // Money formatting and parsing example
    char money[64];
    if (fossil_io_cstring_money_to_string(1234567.89,
                                          money,
                                          sizeof(money)) == 0)
    {
        fossil_io_print("{yellow}Money:{reset} %s\n", money);
    }
    else
    {
        fossil_io_error("[%s] %s",
                        "format.invalid",
                        fossil_io_what("format.invalid"));
    }

    // Parse a money string back to a double
    double amount = 0.0;
    if (fossil_io_cstring_string_to_money("$1,234.56", &amount) == 0)
    {
        fossil_io_print("{blue}Parsed amount:{reset} %.2f\n", amount);
    }
    else
    {
        fossil_io_error("[%s] %s",
                        "parse.invalid",
                        fossil_io_what("parse.invalid"));
    }

    // Pig Latin and Leetspeak examples
    cstring piglatin = fossil_io_cstring_create("hello world");
    char piglatin_out[128];

    if (fossil_io_cstring_piglatin(piglatin,
                                   piglatin_out,
                                   sizeof(piglatin_out)) == 0)
    {
        fossil_io_print("{magenta}Pig Latin:{reset} %s\n", piglatin_out);
    }

    // Leetspeak example with error handling
    cstring leet_input = fossil_io_cstring_create("Fossil Logic");
    char leet_out[128];

    if (fossil_io_cstring_leetspeak(leet_input,
                                    leet_out,
                                    sizeof(leet_out)) == 0)
    {
        fossil_io_print("{red}Leet:{reset} %s\n", leet_out);
    }

    // Additional string manipulation examples
    cstring mocking = fossil_io_cstring_mocking("this is serious");
    cstring rot13 = fossil_io_cstring_rot13("hello world");
    cstring snake = fossil_io_cstring_upper_snake("Fossil Logic SDK");

    fossil_io_print("{yellow}Mocking:{reset} %s\n", mocking);
    fossil_io_print("{yellow}ROT13:{reset} %s\n", rot13);
    fossil_io_print("{yellow}UPPER_SNAKE:{reset} %s\n", snake);

    // Number parsing and formatting examples
    int value = 0;
    if (fossil_io_cstring_number_from_words("twenty-three", &value) == 0)
    {
        fossil_io_print("{green}Words -> Number:{reset} %d\n", value);
    }

    char words[128];
    if (fossil_io_cstring_number_to_words(42,
                                          words,
                                          sizeof(words)) == 0)
    {
        fossil_io_print("{green}Number -> Words:{reset} %s\n", words);
    }

    cstring replaced = fossil_io_cstring_case_replace(
        "The Fossil SDK is powerful",
        "fossil",
        "Jellyfish");

    fossil_io_print("{cyan}Replaced:{reset} %s\n", replaced);

    // Error code lookup example with formatted output
    const char *code = "network.timeout";
    int code_id = fossil_io_code(code);
    const char *description = fossil_io_what(code);

    fossil_io_print(
        "{bold}{red}Error Lookup{reset}\n"
        "  Code: %s\n"
        "  ID:   %d\n"
        "  What: %s\n",
        code,
        code_id,
        description);

    fossil_io_error("[%s] %s", code, description);

    // JSON escaping and unescaping example
    cstring escaped =
        fossil_io_cstring_escape_json("Hello \"World\"\n");

    cstring unescaped =
        fossil_io_cstring_unescape_json(escaped);

    fossil_io_print("{blue}Escaped JSON:{reset} %s\n", escaped);
    fossil_io_print("{blue}Unescaped JSON:{reset} %s\n", unescaped);

    // Free all allocated cstrings to prevent memory leaks
    fossil_io_cstring_free(greeting);
    fossil_io_cstring_free(upper);
    fossil_io_cstring_free(reversed);
    fossil_io_cstring_free(message);
    fossil_io_cstring_free(piglatin);
    fossil_io_cstring_free(leet_input);
    fossil_io_cstring_free(mocking);
    fossil_io_cstring_free(rot13);
    fossil_io_cstring_free(snake);
    fossil_io_cstring_free(replaced);
    fossil_io_cstring_free(escaped);
    fossil_io_cstring_free(unescaped);

    return EXIT_SUCCESS;
}
