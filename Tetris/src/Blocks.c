#include "Blocks.h"

Tuple getBlockPosition(Block *block)
{
    Tuple tuple;
    switch (block->shape)
    {
    case shapeT:
        //Default Dirction:BEHIND
        tuple.first=block->point;
        //tuple.second=block->point;
        break;
    case shapeI:
        //Default Dirction:FRONT
        break;
    case shapeO:
        //Default Dirction:FRONT
        break;
    case shapeL:
        //Default Dirction:RIGHT
        break;
    
    default:
        break;
    }
    return tuple;
}
