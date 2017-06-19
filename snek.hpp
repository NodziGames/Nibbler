#pragma once

class SnakePart
{
    public:
        int x;
        int y;
        int prevx;
        int prevy;

        SnakePart();
        SnakePart(int x, int y);
        SnakePart(SnakePart const & src);
        ~SnakePart();

        SnakePart &       operator=(SnakePart const & rhs);
};