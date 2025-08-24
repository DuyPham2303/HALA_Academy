#include "can_frame.h"
#include <stdio.h>
#include <stdint.h>
void packDoorStatus(Door *doors, CANFrame_t *frame)
{
    for (int i = 0; i < 4; i++)
    {
        frame->bytes[i] = doors[i].statusUnion.byte;
    }
    printf("packed frame\n"
           "door 0:\t%02X\n"
           "door 1:\t%02X\n"
           "door 2:\t%02X\n"
           "door 3:\t%02X\n",
           frame->door0, frame->door1, frame->door2, frame->door3);
}

void unpackDoorStatus(CANFrame_t *frame, Door *doors)
{
    printf("unpacked frame\n");
    for (int i = 0; i < 4; i++)
    {
        doors[i].statusUnion.byte = frame->bytes[i];
        unsigned int byte =  (unsigned int)doors[i].statusUnion.byte;
        printf("door %d:\t0x%X\n",i,byte);
    }
}