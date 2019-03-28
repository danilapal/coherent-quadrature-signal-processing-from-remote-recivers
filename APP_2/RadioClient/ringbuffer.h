#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <QObject>
#include <QWriteLocker>
#include <QWaitCondition>
#include <QReadLocker>
#include <radiotools.h>
class RingBuffer:public QObject
{
    Q_OBJECT
public:
    explicit RingBuffer(quint32 _size, QObject *parent = 0);
    ~RingBuffer();

    void clean();
    bool read(float *data, quint32 len);
    bool write(float *data, quint32 len);
    float getSample();
    void addSample(float sample);
    //void addSample(std::vector<UINT32> sample);
    quint32 availableRead(); // available size read data
    quint32 availableWrite(); // available size write data
    bool get(Packet &data, quint32 &index);
    void  push(Packet &data);
    bool pop(Packet &data);

private:
    quint32 size;
    quint32 mask;
    quint32 idxRead;
    quint32 idxWrite;
    quint32 dataCount; // available read data size
    float *fbuf = nullptr;
    std::vector<std::vector<INT32>> buffer;
    QReadWriteLock mutex;
    QWaitCondition notEmpty;
    Packet *array;
};


#endif // RINGBUFFER_H
