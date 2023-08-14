#ifndef __LIBREOFFICE_SERVICE_HPP__
#define __LIBREOFFICE_SERVICE_HPP__

#include "logger.hpp"
#include "file_format.hpp"

using byte = unsigned char;

class LibreOfficeService
{
private:
    const char* systemUsername = "azureuser";
    const char* libreBin = "lowriter";
    const char* serviceDir = ".DocConvertService";
    Logger logger;

    int executeBash(std::string command);

public:
    std::string convert(const std::string& docData, FileFormat fromFormat, FileFormat toFormat);
};

#endif // __LIBREOFFICE_SERVICE_HPP__