#include "door.h"
#include <stdio.h>
void Door_Init(Door *d, ActuatorFunc open, ActuatorFunc close, ActuatorFunc lock, ActuatorFunc unlock)
{
    d->close = close;
    d->lock = lock;
    d->unlock = unlock;
    d->open = open;
}

void openDoor(Door *d)
{
    d->statusUnion.status.isOpen = 1;
}

void closeDoor(Door *d)
{
    d->statusUnion.status.isOpen = 0;
}

void lockDoor(Door *d)
{
    d->statusUnion.status.isLocked = 1;
}

void unlockDoor(Door *d)
{
    d->statusUnion.status.isLocked = 0;
}