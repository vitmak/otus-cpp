#include "Config.h"
#include "FileSeacher.h"
#include "DirectoryTraversal.h"
#include <iostream>
#include <filesystem>
#include <memory>


int main(int argc, const char* argv[]) {
	auto config = Config::ParseCmdArguments(argc, argv);

    if (config.m_showHelp) {
        std::cout << config.m_helpText << std::endl;
        return 0;
    }

    std::unique_ptr<DirectoryTraversalBase> dirTraversalPtr;
    if (config.m_scanLevel == ScanLevel::Current) {
        dirTraversalPtr = std::make_unique<DirectoryTraversal<std::filesystem::directory_iterator>>(config);
    }
    else {
        dirTraversalPtr = std::make_unique<DirectoryTraversal<std::filesystem::recursive_directory_iterator>>(config);
    }

    FileSeacher seacher{std::move(dirTraversalPtr)};
    auto allFilesToCmp = seacher.GetAllFilePath();

	return 0;
}