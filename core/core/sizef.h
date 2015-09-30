#ifndef SIZEF_H
#define SIZEF_H


class SizeF
{
public:
    SizeF(const float width, const float height);

    float getWidth();
    void setWidth(const float width);
    float getHeight();
    void setHeight(const float height);
private:
    float _width;
    float _heigt;
};

#endif // SIZEF_H
