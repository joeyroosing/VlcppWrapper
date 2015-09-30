#ifndef VLCCOMMON_H
#define VLCCOMMON_H

#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include <cstdio>

namespace VlcCommon
{
    std::vector<std::string> args();
    std::string toNativeSeparators(const std::string &location);
    int indexOf(const std::string &text, const std::string &pattern);
}

#endif // VLCCOMMON_H
