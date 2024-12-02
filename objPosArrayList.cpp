#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;

    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)
        return;
    for (int i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }
    aList[0].setObjPos(thisPos);

    listSize++;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::removeHead()
{
    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index < 0 || index >= listSize)
    {
        return objPos();
    }
    return aList[index];
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity)
        return;
    aList[listSize].setObjPos(thisPos);
    listSize++;
}
