#include "libreoffice_service.hpp"
#include <filesystem>
#include <fstream>
#include "crossguid/guid.hpp"
#include "fmt/format.h"
#include "prim_exception.hpp"
#include <sstream>


int LibreOfficeService::executeBash(std::string command)
{
    return system(command.c_str());
}

std::string LibreOfficeService::convert(const std::string& docData, FileFormat fromFormat, FileFormat toFormat)
{
    namespace fs = std::filesystem;
    static const char* tempFilename = "LibreOfficeServiceTempFile";

    std::string processDir = xg::newGuid().str();
    std::string tempDir = fmt::format("/home/{}/{}/{}", systemUsername, serviceDir, processDir);
    if(!fs::create_directories(tempDir)) throw PRIM_EXCEPTION(fmt::format("Failed to create directory. Path: '{}'", tempDir).c_str());

    std::string fromTempFilepath = fmt::format("{}/{}.{}", tempDir, tempFilename, fromFormat.name);
    std::string toTempFilepath = fmt::format("{}/{}.{}", tempDir, tempFilename, toFormat.name);

    std::ofstream file(fromTempFilepath);
    if(!file.good()) throw PRIM_EXCEPTION(fmt::format("Failed to create temp file. Path: {}", fromTempFilepath).c_str());

    file << docData;
    file.close();

    std::string command = fmt::format("{} -env:SingleAppInstance=false -env:UserInstallation=file//{} --headless --convert-to {} --outdir {} {}",
        libreBin, tempDir, toFormat.name, tempDir, fromFormat.name);

    int commandResult = executeBash(command);

    if(commandResult != 0) throw PRIM_EXCEPTION(fmt::format("Failed to execute bash command (code: {}). Command: '{}'", commandResult, command).c_str());

    std::ifstream outFile(toTempFilepath);
    if(!outFile.good()) throw PRIM_EXCEPTION(fmt::format("Failed to open out file. Path: {}", toTempFilepath).c_str());

    std::stringstream outFileStream;
    outFileStream << outFile.rdbuf();
    outFile.close();

    fs::remove_all(tempDir);

    return outFileStream.str();
}