#include "fossil/io/archive.h"
#include "fossil/io/output.h"

/** 
 * @brief Example of using the fossil_io_archive API to read an archive
 *
 * This example demonstrates how to open an archive, list its contents, check for the existence of an entry,
 * get the size of an entry, and close the archive.
 *
 * Make sure to have an "assets.zip" file in the same directory as the executable for this example to work.
 */
int main(void)
{
    // Open the archive for reading
    fossil_io_archive_t *archive =
        fossil_io_archive_open(
            "assets.zip",
            FOSSIL_IO_ARCHIVE_ZIP,
            FOSSIL_IO_ARCHIVE_READ,
            FOSSIL_IO_COMPRESSION_NORMAL
        );

    // Check if the archive was opened successfully
    if (!archive)
    {
        fossil_io_output_print("Failed to open archive\n");
        return 1;
    }

    // Print the contents of the archive
    fossil_io_output_print("Archive listing:\n");
    fossil_io_archive_print(archive);

    if (fossil_io_archive_exists(archive, "readme.txt"))
    {
        fossil_io_output_print("readme.txt exists\n");
    }

    // Get the size of the readme.txt entry
    ssize_t size = fossil_io_archive_entry_size(archive, "readme.txt");

    fossil_io_printf("Size: %zd bytes\n", size);

    // Close the archive
    fossil_io_archive_close(archive);

    return 0;
}
