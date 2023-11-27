#pragma once
#include "Object.h"

class Platform :
    public Object
{
public:
    Platform();
    ~Platform();

public:
    void Update() override;
    void Render(HDC _dc) override;

};

