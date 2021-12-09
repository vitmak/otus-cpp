#include "Config.h"
#include <boost/program_options.hpp>
#include <string>
#include <vector>
#include <sstream>

namespace po = boost::program_options;


/*static*/ Config Config::ParseCmdArguments(int argc, const char* argv[]) {
    Config config;

    po::options_description desc{ "Utility for detecting duplicate files. Command-line options" };
    desc.add_options()
        ("help,h", "Help message")
        ("include_dirs,i",
            po::value<std::vector<std::string>>()->default_value(std::vector<std::string>{"."}, ".")->multitoken()->composing(),
            "Directories for scanning, can be multiple. Default is current folder.")
        ("exclude_dirs,e",
            po::value<std::vector<std::string>>()->multitoken()->composing(),
            "Directories to be excluded, can be multiple.")
        ("scan_level,l",
            po::value<unsigned char>()->default_value(0),
            "Scanning level, 1 - all directories, 0 - current folder only. Default value is 0.")
        ("min_size,m",
            po::value<unsigned int>()->default_value(1),
            "Minimum file size for scanning in bytes. Default value is 1.")
        ("file_masks,f",
            po::value<std::vector<std::string>>()->multitoken()->composing(),
            "File name masks allowed for comparison, case-insensitive.")
        ("block_size,b",
            po::value<unsigned int>()->default_value(128),
            "Block size used to read files, in bytes. Default value is 128.")
        ("hash_algorithm,a",
            po::value<std::string>()->default_value("crc32"),
            "Hash algorithm to hash file blocks. Default value is crc32.")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    notify(vm);
    
    std::stringstream helpInfo;
    helpInfo << desc << std::endl;
    config.m_helpText = helpInfo.str();
    config.m_showHelp = vm.count("help");

    if (vm.count("include_dirs"))
        config.m_includeDirs = vm["include_dirs"].as<std::vector<std::string>>();
    if (vm.count("exclude_dirs"))
        config.m_excludeDirs = vm["exclude_dirs"].as<std::vector<std::string>>();
    if (vm.count("scan_level"))
        config.m_scanLevel = static_cast<ScanLevel>(vm["scan_level"].as<unsigned char>() - 48);
    if (vm.count("min_size"))
        config.m_minFileSize = vm["min_size"].as<unsigned int>();
    if (vm.count("file_masks"))
        config.m_fileMasks = vm["file_masks"].as<std::vector<std::string>>();
    if (vm.count("block_size"))
        config.m_blockSize = vm["block_size"].as<unsigned int>();
    if (vm.count("hash_algorithm"))
        config.m_hashAlgorithm = vm["hash_algorithm"].as<std::string>();

    return config;
}
    