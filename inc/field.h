#ifndef FIELD_H
#define FIELD_H

struct Field
{
    enum class Type
    {
        Empty,
        Wall,
        Start,
        Destination,
        Visited
    };
    Type type;

    struct Coordinates
    {
        unsigned int rowNum, colNum;
    };

    Field() : type(Type::Empty) {};
};

#endif // FIELD_H
