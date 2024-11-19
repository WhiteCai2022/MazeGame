#ifndef MAPINFO_H
#define MAPINFO_H

class MapInfo
{
public:
    MapInfo(int width,int length,int seeds,int mode,bool isAllowNesting)
    {
        this->length=length;
        this->width=width;
        this->seeds=seeds;
        this->mode=mode;
        this->isAllowNesting=isAllowNesting;
    };

    MapInfo()
    {
        this->length=20;
        this->width=20;
        this->seeds=0;
        this->mode=0;
        this->isAllowNesting=false;
    };

    ~MapInfo()
    {

    }
    int getWidth()
    {
        return width;
    };
    int getLength()
    {
        return length;
    };
    int getSeeds()
    {
        return seeds;
    };
    int getMode()
    {
        return mode;
    }
    bool getNest()
    {
        return isAllowNesting;
    }
    void setWidth(int width)
    {
        this->width=width;
    };
    void setLength(int length)
    {
        this->length=length;
    };
    void setSeeds(int seeds)
    {
        this->seeds=seeds;
    };
    void setMode(int mode)
    {
        this->mode=mode;
    }
    void setNest(bool Nest)
    {
        this->isAllowNesting=Nest;
    }
private:
    int length;
    int width;
    int seeds;
    int mode;
    bool isAllowNesting;

};
#endif // MAPINFO_H
