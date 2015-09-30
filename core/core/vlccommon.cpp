#include "vlccommon.h"

std::vector<std::string> VlcCommon::args()
{
    std::vector<std::string> args;
    args.push_back("--intf=dummy");
    args.push_back("--no-media-library");
    args.push_back("--no-stats");
    args.push_back("--no-osd");
    args.push_back("--no-loop");
    args.push_back("--no-video-title-show");
    args.push_back("--drop-late-frames");

    return args;
}

int VlcCommon::indexOf(const std::string &text, const std::string &pattern)
{
    // where appears the pattern in the text?
    std::string::size_type loc = text.find(pattern, 0);
    if(loc != std::string::npos) {
        return loc;
    }
    else {
        return -1;
    }
}

std::string VlcCommon::toNativeSeparators(const std::string &location)
{
#if defined _WIN32 || defined __CYGWIN__
    unsigned int index = indexOf(location, "/");
    if (index != -1) {
        std::string temp(location);
        char* const data = const_cast<char *>(temp.data());
        data[index++] = '\\';

        for (; index < temp.length(); ++index) {
            if (data[index] == '/') {
                data[index] = '\\';
            }
        }

        return temp;
    }
#endif
    return location;
}
