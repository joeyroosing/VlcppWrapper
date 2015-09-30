#include "vlcinstance.h"
#include "vlcerror.h"

#include "cstddef"

#include <vlc/libvlc.h>

#include <iostream>

struct libvlc_instance_t;

VlcInstance::VlcInstance(const std::vector<std::string> &args)
    : _nativeVlcInstance(nullptr)
{
    // Convert arguments to required format
    char **argv = (char **)malloc(sizeof(char **) * args.size());

    for (size_t i = 0; i < args.size(); i++) {
        std::string arg = args.at(i);
        argv[i] = (char *)strdup(arg.data());
    }

    // Create new libvlc instance
    _nativeVlcInstance = libvlc_new(args.size(), argv);

    VlcError::showErrorMessage();

    if (_nativeVlcInstance) {
        std::cout << "VLC Wrapper 0.0.1 initialized";
    } else {
        abort();
    }
}

libvlc_instance_t* VlcInstance::getNativeVlcInstance()
{
    return _nativeVlcInstance;
}

int VlcInstance::getLibVersionMajor()
{
    return 1;
}

int VlcInstance::getLibVersionMinor()
{
    return 1;
}

std::string VlcInstance::getChangeSet()
{
    return std::string(libvlc_get_changeset());
}

std::string VlcInstance::getVlcCompiler()
{
    return std::string(libvlc_get_compiler());
}

void VlcInstance::setUserAgent(const std::string &application, const std::string &version)
{
    std::string applicationOutput = application + " " + version;
    std::string httpOutput = application + "/" + version + "VlcWrapper/0.0.1";
    libvlc_set_user_agent(_nativeVlcInstance, applicationOutput.data(), httpOutput.data());
}

VlcInstance::~VlcInstance()
{
    libvlc_release(_nativeVlcInstance);
}

