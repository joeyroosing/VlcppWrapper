#include "vlcerror.h"

#include <vlc/vlc.h>

std::string VlcError::getErrorMessage()
{
    std::string error;
    if (libvlc_errmsg()) {
        error = libvlc_errmsg();
        clearError();
    }
    return error;
}

void VlcError::showErrorMessage()
{
    std::string error = getErrorMessage();
    if(!error.empty()) {
        std::cout << "libvlc" << "Error:" << error << std::endl;
    }
}

void VlcError::clearError()
{
    // Clears libvlc error message
    libvlc_clearerr();
}

