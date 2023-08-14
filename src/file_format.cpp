#include "file_format.hpp"

//<STATIC MEMBERS
FileFormat FileFormat::NOT_DEFINED{"NOT_DEFINED", "NOT_DEFINED"};
FileFormat FileFormat::PDF{"pdf", "application/pdf"};
FileFormat FileFormat::DOCX{"docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"};
FileFormat FileFormat::DOC{"doc", "application/msword"};

std::vector<FileFormat> FileFormat::formats{NOT_DEFINED, PDF, DOCX, DOC};

FileFormat FileFormat::parse(std::string formatStr)
{
    for(const FileFormat& format : formats)
    {
        if(format.name ==  formatStr)
            return format;
        
    }

    return NOT_DEFINED;
}

bool FileFormat::operator==(const FileFormat& other)
{
    return name == other.name;
}
// STATIC MEMBERS>