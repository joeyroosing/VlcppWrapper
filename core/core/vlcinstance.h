#ifndef VLCINSTANCE_H
#define VLCINSTANCE_H

#include "vlc/vlc.h"
#include <vector>
#include <string>

class VlcInstance
{
public:
    /*!
            \brief VlcInstance constructor.
            This is mandatory for using VLC-Qt and all its other classes.
            \param args libvlc arguments (QStringList)
            \param parent Instance's parent object (QObject *)
        */
    explicit VlcInstance(const std::vector<std::string> &args);
    ~VlcInstance();
    libvlc_instance_t* getNativeVlcInstance();

    static int getLibVersionMajor();
    static int getLibVersionMinor();
    static std::string getVlcCompiler();
    static std::string getChangeSet();

    void setUserAgent(const std::string &application, const std::string &version);
private:
    libvlc_instance_t *_nativeVlcInstance;
};

#endif // VLCINSTANCE_H
