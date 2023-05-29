#ifndef _BLOCKS_H_
#define _BLOCKS_H_
//BlockShape is T,I,O,L
enum BlockShape {
    shapeT,
    shapeI,
    shapeO,
    shapeL
};
//Direction is front,right,behind,left
enum Direction
{
    FRONT,
    RIGTH,
    BEHIND,
    LEFT
};
//Four Point Position
typedef struct Tuple
{
    int first;
    int second;
    int third;
    int fourth;
}Tuple;
//Block's shape,width,height,point(bottom-left corner)
typedef struct Block
{
    BlockShape shape;
    int width;
    int height;
    int point;
}Block;
Tuple getBlockPosition(Block* block);
#endif /* _BLOCKS_H_ */