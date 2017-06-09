#pragma once

class SnakePart
{
    public:
        int x;
        int y;
        int prevx;
        int prevy;

        SnakePart(int x, int y);
        ~SnakePart();
};