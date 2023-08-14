#ifndef __FILE_FORMAT_HPP__
#define __FILE_FORMAT_HPP__

#include <string>
#include <vector>

struct FileFormat {
    static FileFormat NOT_DEFINED;
    static FileFormat PDF;
    static FileFormat DOCX;
    static FileFormat DOC;
    static std::vector<FileFormat> formats;

    std::string name;
    std::string mimeType;

    FileFormat(std::string name, std::string mimeType): name(name), mimeType(mimeType) {}

    static FileFormat parse(std::string formatStr);

    bool operator==(const FileFormat& rhs);
};

#endif // __FILE_FORMAT_HPP__