#ifndef PATHTRANSLATOR_H
#define PATHTRANSLATOR_H

#include <string>
class  PathTranslator
{

public:
    PathTranslator(const std::string &root, const std::string &cwd);
    void setAbsPath(std::string & dest, const std::string &src);
    std::string virtualToReal(const std::string &path);
    std::string realToVirtual(const std::string &path);
private:
    std::string _root;
    std::string _cwd;

};

#endif // PATHTRANSLATOR_H
