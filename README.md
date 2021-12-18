Utility for detecting duplicate files. Command line options:


-h [ --help ]             Help message.

-i [ --include_dirs ]     Directories for scanning, can be multiple. Default is current folder.

-e [ --exclude_dirs ]     Directories to be excluded, can be multiple.

-l [ --scan_level]        Scanning level, 1 - all directories, 0 - current folder only. Default value is 0.

-m [ --min_size]          Minimum file size for scanning in bytes. Default value is 1.

-f [ --file_masks]        File name masks allowed for comparison, case-insensitive.

-b [ --block_size ]       Block size used to read files, in bytes. Default value is 128.

-a [ --hash_algorithm]    Hash algorithm to hash file blocks. Default value is crc32.
