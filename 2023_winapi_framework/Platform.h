#pragma once
#include "Object.h"

class Platform :
    public Object
{
public:
    Platform();
    ~Platform();

public:
    void Render(HDC _dc) override;

};

