#include <string>

std::string handleTextOverflow(const std::string &txt, int maxLength)
{
    if (txt.length() >= maxLength)
    {
        std::string result;
        result.reserve(maxLength + 3);

        result.append(txt, 0, maxLength);
        result.append("...");

        return result;
    }

    return txt;
}
