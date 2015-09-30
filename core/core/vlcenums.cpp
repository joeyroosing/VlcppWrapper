#include "vlcenums.h"

std::vector<std::string> VlcEnums::getAudioCodec()
{
    std::vector<std::string> list;
    list.push_back("none");
    list.push_back("mpga");
    list.push_back("mp3");
    list.push_back("mp4a");
    list.push_back("vorb");
    list.push_back("flac");
    return list;
}

std::vector<std::string> VlcEnums::getAudioOutput()
{
    std::vector<std::string> list;
    list.push_back("default");
    return list;
}

std::vector<std::string> VlcEnums::getAudioOutputHuman()
{
    std::vector<std::string> list;
    list.push_back("default");
    return list;
}

std::vector<std::string> VlcEnums::getDeinterlacing()
{
    std::vector<std::string> list;
    list.push_back("");
    list.push_back("discard");
    list.push_back("blend");
    list.push_back("man");
    list.push_back("bob");
    list.push_back("linear");
    list.push_back("x");
    list.push_back("yadif");
    list.push_back("yadif2x");
    list.push_back("phosphor");
    list.push_back("ivtc");
    return list;
}

std::vector<std::string> VlcEnums::getMux()
{
    std::vector<std::string> list;
    list.push_back("ts");
    list.push_back("ps");
    list.push_back("mp4");
    list.push_back("ogg");
    list.push_back("avi");
    return list;
}

std::vector<std::string> VlcEnums::getRatio()
{
    std::vector<std::string> list;
    list.push_back("");
    list.push_back("16:9");
    list.push_back("16:10");
    list.push_back("185:100");
    list.push_back("221:100");
    list.push_back("235:100");
    list.push_back("239:100");
    list.push_back("4:3");
    list.push_back("5:4");
    list.push_back("5:3");
    list.push_back("1:1");
    return list;
}

std::vector<std::string> VlcEnums::getRatioHuman()
{
    std::vector<std::string> list;
    list.push_back("");
    list.push_back("16:9");
    list.push_back("16:10");
    list.push_back("1.85:1");
    list.push_back("2.21:1");
    list.push_back("2.35:1");
    list.push_back("2.39:1");
    list.push_back("4:3");
    list.push_back("5:4");
    list.push_back("5:3");
    list.push_back("1:1");
    return list;
}

SizeF VlcEnums::getRatioSize(const VlcEnums::Ratio &ratio)
{
    switch(ratio)
    {
    case VlcEnums::R_16_9:
        return SizeF(16,9);
        break;
    case VlcEnums::R_16_10:
        return SizeF(16,10);
        break;
    case VlcEnums::R_185_100:
        return SizeF(185,100);
        break;
    case VlcEnums::R_221_100:
        return SizeF(221,100);
        break;
    case VlcEnums::R_235_100:
        return SizeF(235,100);
        break;
    case VlcEnums::R_239_100:
        return SizeF(239,100);
        break;
    case VlcEnums::R_4_3:
        return SizeF(4,3);
        break;
    case VlcEnums::R_5_4:
        return SizeF(5,4);
        break;
    case VlcEnums::R_5_3:
        return SizeF(5,3);
        break;
    case VlcEnums::R_1_1:
        return SizeF(1,1);
        break;
    case VlcEnums::Original:
    default:
        return SizeF(0,0);
        break;
    }

    return SizeF(0,0);
}

std::vector<float> VlcEnums::getScale()
{
    std::vector<float> list;
    list.push_back((float)0);
    list.push_back((float)1.05);
    list.push_back((float)1.1);
    list.push_back((float)1.2);
    list.push_back((float)1.3);
    list.push_back((float)1.4);
    list.push_back((float)1.5);
    list.push_back((float)1.6);
    list.push_back((float)1.7);
    list.push_back((float)1.8);
    list.push_back((float)1.9);
    list.push_back((float)2.0);
    return list;
}

std::vector<std::string> VlcEnums::getVideoCodec()
{
    std::vector<std::string> list;
    list.push_back("none");
    list.push_back("mpgv");
    list.push_back("mp4v");
    list.push_back("h264");
    list.push_back("theora");
    return list;
}

std::vector<std::string> VlcEnums::getVideoOutput()
{
    std::vector<std::string> list;
#if defined _WIN32 || defined __CYGWIN__
    list.push_back("directx");
    list.push_back("direct3d");
    list.push_back("opengl");
#else
    list.push_back("x11");
    list.push_back("xvideo");
    list.push_back("glx");
#endif
    list.push_back("default");
    return list;
}

std::vector<std::string> VlcEnums::getVideoOutputHuman()
{
    std::vector<std::string> list;
#if defined _WIN32 || defined __CYGWIN__
    list.push_back("DirectX");
    list.push_back("Direct3D");
    list.push_back("OpenGL");
#else
    list.push_back("X11");
    list.push_back("XVideo");
    list.push_back("OpenGL");
#endif
    list.push_back("default");
    return list;
}


