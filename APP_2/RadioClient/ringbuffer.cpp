#include "ringbuffer.h"

RingBuffer::RingBuffer(quint32 _size, QObject *parent)
    : QObject(parent),
      size(_size),
      array(new Packet[_size])
{
    mask = size - 1;
    //fbuf = (float*) malloc(sizeof(float) * size);

    clean();
}

RingBuffer::~RingBuffer()
{
    free(fbuf);
}

void RingBuffer::clean()
{
    idxRead = 0;
    idxWrite = 0;
    dataCount = 0;
}

bool RingBuffer::write(float *data, quint32 len)
{
    if(availableWrite() < len)
        return false;

    dataCount += len;

    for(int i = 0; i < len; i++)
    {
        fbuf[idxWrite++] = data[i];
        idxWrite &= mask;
    }

    return true;
}

bool RingBuffer::read(float *data, quint32 len)
{
    if(availableRead() < len)
        return false;

    dataCount -= len;

    for(int i = 0; i < len; i++)
    {
        data[i] = fbuf[idxRead++];
        idxRead &= mask;
    }

    return true;
}

float RingBuffer::getSample()
{
    dataCount --;
    float sample = fbuf[idxRead++];
    idxRead &= mask;
    return sample;
}

void RingBuffer::addSample(float sample)
{
    dataCount ++;
    fbuf[idxWrite++] = sample;
    idxWrite &= mask;
}

quint32 RingBuffer::availableRead()
{
    return dataCount;
}

quint32 RingBuffer::availableWrite()
{
    return size - dataCount;
}

bool RingBuffer::get(Packet &data, quint32 &index)
{
    QReadLocker readLocker(&mutex);
    if(index<this->idxWrite){

        data=array[index++ &mask];
        //len++ ;idxWrite &= mask;
        return true;
    }
    else
    {
        notEmpty.wait(&mutex,2);
        return false;
    }
}

void RingBuffer::push(Packet &data)
{
    qDebug()<<"Push function";
    QWriteLocker writeLocker(&mutex);
    qDebug()<<"Mutex locked";
    array[this->idxWrite++ &mask]=data;
    //buffer.push_back(data);
    //this->idxWrite++;
    //idxWrite &= mask;

    notEmpty.wakeOne();
}

bool RingBuffer::pop(Packet &data)
{
    QReadLocker readLocker(&mutex);
    if( this->idxRead<this->idxWrite){
        //data=buffer[idxRead++ &mask];
        data=array[idxRead++ &mask];
        return true;
    }
    else{
        notEmpty.wait(&mutex,2);
        return false;
    }
}


//bool get(int &index,Packet&packet){
//    QReadLocker readLocker(&mutex);
//    if(index<writeCounter){
//        ///qDebug()<<"Comp"<<index<<writeCounter;
//        packet=array[index++ &mask];
//        return true;
//    }
//    else
//    {
//        notEmpty.wait(&mutex,2);
//        return false;
//    }
//}
//void push(const Packet &packet){
//    QWriteLocker writeLocker(&mutex);
//    array[writeCounter++ &mask]=packet;
//    notEmpty.wakeOne();
//}

//bool pop(Packet&packet){
//    QReadLocker readLocker(&mutex);
//    if( readCounter<writeCounter){
//        packet=array[readCounter++ &mask];
//        return true;
//    }
//    else{
//        notEmpty.wait(&mutex,2);
//        return false;
//    }
//}
