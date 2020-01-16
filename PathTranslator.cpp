#include "PathTranslator.h"
#include <vector>
#include <assert.h>

PathTranslator::PathTranslator(const std::string &root, const std::string &cwd)
{
    _root = root;
    if (_root.back() !='/') _root.append("/");
    setAbsPath(_cwd, cwd);
}
void PathTranslator::setAbsPath(std::string & dest, const std::string &src)
{
     assert (src.front() == '/');
     dest = src; if (dest.back() !='/') dest.append("/");
     assert (dest.find("/../",0) == std::string::npos);
}

std::string getNextToken(const std::string &path, size_t from)
{
    size_t found = 0;
    bool repeat = true;
    while(repeat)
    {
     found = path.find('/',from);
     if(found == from)
     {
         from++;
     }
    }

    if (found == std::string::npos)
    {
        return path.substr(from);
    }
    return path.substr(from,found-from);
}

std::string PathTranslator::virtualToReal(const std::string &path)
{
    if (path.size()==0)
        return "";
    if (path.at(0)=='/')
    {
        size_t seek_pos = 1;
        size_t depth = 0;
        std::vector<std::string> tokens;
        while (true)
        {
            std::string token = getNextToken(path,seek_pos);
            if (token=="")
            {
                break;
            }
            if (token == "..")
            {
                depth--;
                if (depth<0)
                    return "";
                tokens.pop_back();
            }
            else if (token != ".")
            {
                tokens.push_back(token);
                depth++;
            }
        }
        std::string out = _root;
        bool append_slash = false;

        std::vector<std::string>::const_iterator it=tokens.begin();
        for (;it!= tokens.end();++it)
        {
            if (append_slash)
                out+='/';
            out+=*it;
            append_slash = true;
        }
        return out;
    }
    else
    {
        virtualToReal(_cwd+path);
    }
}
