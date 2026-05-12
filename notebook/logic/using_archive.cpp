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
int main()
{
    // Open the archive for reading
    using fossil::io::Archive;

    Archive archive(
        "assets.zip",
        FOSSIL_IO_ARCHIVE_ZIP,
        FOSSIL_IO_ARCHIVE_READ,
        FOSSIL_IO_COMPRESSION_NORMAL
    );

    // Check if the archive was opened successfully
    if (!archive.is_valid())
    {
        fossil::io::Output::printf("Failed to open archive\n");
        return 1;
    }

    // Print the contents of the archive
    fossil::io::Output::printf("Archive contents:\n");
    archive.print();

    // Check if "readme.txt" exists in the archive
    if (archive.exists("readme.txt"))
    {
        fossil::io::Output::printf("readme.txt exists\n");
    }

    ssize_t size = archive.entry_size("readme.txt");

    // Print the size of the readme.txt entry
    fossil::io::Output::printf("Size: %zd bytes\n", size);

    return 0;
}
