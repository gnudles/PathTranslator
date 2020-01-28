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

std::string getNextToken(const std::string &path, size_t & from)
{
    size_t found = 0;
    bool repeat = true;
    if (from >= path.length())
    {
        return "";
    }
    while(repeat)
    {
     found = path.find('/',from);
     if(found == from)
     {
         from++;
     }
     else
     {
         repeat = false;
     }
    }

    if (found == std::string::npos)
    {
        size_t subs_from = from;
        from = path.length();
        return path.substr(subs_from);
    }
    size_t len = found - from;
    size_t subs_from = from;
    from = found + 1;
    return path.substr(subs_from, len);
}

std::string PathTranslator::virtualToReal(const std::string &path)
{
    if (path.size()==0)
        return "";
    if (path.at(0)=='/')
    {
        size_t seek_pos = 1;
        int depth = 0;
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
        return virtualToReal(_cwd+path);
    }
}

std::string PathTranslator::realToVirtual(const std::string &path)
{

}
