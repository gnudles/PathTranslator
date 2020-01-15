#include "PathTranslator.h"
#include <vector>

PathTranslator::PathTranslator()
{
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
            std:string token = getNextToken(path,seek_pos);
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
        if (out[out.size()] != '/')
            append_slash = true;

        std::vector::const_iterator<std::string> > it=tokens.begin();
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

    }
}
