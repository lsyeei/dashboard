/**
* This file is part of the dashboard library
* 
* Copyright 2025 lishiying  lsyeei@163.com
* 
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "snowflake.h"
#include "qdebug.h"

#include <QDateTime>

class SnowFlakePrivate
{
public:
    explicit SnowFlakePrivate(SnowFlake *parent):q_ptr(parent){
        QDateTime time{QDate{2020,1,1}, {0,0,0}};
        twepoch = time.toMSecsSinceEpoch();
    };
private:
    // 数据中心(机房) id
    long datacenterId;
    // 机器ID
    long workerId;
    // 同一时间的序列
    long sequence;
    // 开始时间戳
    qlonglong twepoch;

    // 机房号，的ID所占的位数 5个bit 最大:11111(2进制)--> 31(10进制)
    long datacenterIdBits = 5L;

    // 机器ID所占的位数 5个bit 最大:11111(2进制)--> 31(10进制)
    long workerIdBits = 5L;

    // 5 bit最多只能有31个数字，就是说机器id最多只能是32以内
    long maxWorkerId = -1L ^ (-1L << workerIdBits);

    // 5 bit最多只能有31个数字，机房id最多只能是32以内
    long maxDatacenterId = -1L ^ (-1L << datacenterIdBits);

    // 同一时间的序列所占的位数 12个bit 111111111111 = 4095  最多就是同一毫秒生成4096个
    long sequenceBits = 12L;

    // workerId的偏移量
    long workerIdShift = sequenceBits;

    // datacenterId的偏移量
    long datacenterIdShift = sequenceBits + workerIdBits;

    // timestampLeft的偏移量
    long timestampLeftShift = sequenceBits + workerIdBits + datacenterIdBits;

    // 序列号掩码 4095 (0b111111111111=0xfff=4095)
    // 用于序号的与运算，保证序号最大值在0-4095之间
    long sequenceMask = -1L ^ (-1L << sequenceBits);

    // 最近一次时间戳
    qint64 lastTimestamp = -1L;

    SnowFlake *q_ptr;
    Q_DECLARE_PUBLIC(SnowFlake)

    qint64 tilNextMillis(qint64 lastTimestamp);
    qint64 timeGen();
};

SnowFlake::SnowFlake():SnowFlake(0, 0) {

}

SnowFlake::SnowFlake(long workerId, long datacenterId)
    : SnowFlake(workerId, datacenterId, 0){

}

SnowFlake::SnowFlake(long workerId, long datacenterId, long sequence)
    : d_ptr(new SnowFlakePrivate(this))
{
    Q_D(SnowFlake);
    // 合法判断
    if (workerId > d->maxWorkerId || workerId < 0) {
        auto error = QString::asprintf("worker Id can't be greater than %d or less than 0", d->maxWorkerId);
        throw std::invalid_argument(error.toStdString());
    }
    if (datacenterId > d->maxDatacenterId || datacenterId < 0) {
        auto error = QString::asprintf("datacenter Id can't be greater than %d or less than 0", d->maxDatacenterId);
        throw std::invalid_argument(error.toStdString());
    }
    // qInfo() << QString::asprintf("worker starting. timestamp left shift %d, "
    //                              "datacenter id bits %d, worker id bits %d, "
    //                              "sequence bits %d, workerid %d",
    //                              d->timestampLeftShift, d->datacenterIdBits,
    //                              d->workerIdBits, d->sequenceBits, workerId);

    d->workerId = workerId;
    d->datacenterId = datacenterId;
    d->sequence = sequence;
}

SnowFlake::~SnowFlake()
{
    delete d_ptr;
}

qint64 SnowFlake::nextId()
{
    Q_D(SnowFlake);
    // 获取当前时间戳，单位毫秒
    auto timestamp = d->timeGen();

    if (timestamp < d->lastTimestamp) {
        qFatal() << QString::asprintf("clock is moving backwards.  "
                                      "Rejecting requests until %d.", d->lastTimestamp);
        auto error = QString::asprintf("Clock moved backwards.  "
                                       "Refusing to generate id for %1 milliseconds",
                                       d->lastTimestamp - timestamp);
        throw std::logic_error(error.toStdString());
    }

    // 去重
    if (d->lastTimestamp == timestamp) {

        d->sequence = (d->sequence + 1) & d->sequenceMask;

        // sequence序列大于4095
        if (d->sequence == 0) {
            // 调用到下一个时间戳的方法
            timestamp = d->tilNextMillis(d->lastTimestamp);
        }
    } else {
        // 如果是当前时间的第一次获取，那么就置为0
        d->sequence = 0;
    }

    // 记录上一次的时间戳
    d->lastTimestamp = timestamp;
    // 偏移计算
    return ((timestamp - d->twepoch) << d->timestampLeftShift) |
           (d->datacenterId << d->datacenterIdShift) |
           (d->workerId << d->workerIdShift) |
           d->sequence;
}

QString SnowFlake::nextIdString()
{
    return QString::number(nextId(),16).toUpper();
}

qint64 SnowFlakePrivate::tilNextMillis(qint64 lastTimestamp)
{
    // 获取最新时间戳
    qint64 timestamp = timeGen();
    // 如果发现最新的时间戳小于或者等于序列号已经超4095的那个时间戳
    while (timestamp <= lastTimestamp) {
        // 不符合则继续
        timestamp = timeGen();
    }
    return timestamp;
}

qint64 SnowFlakePrivate::timeGen()
{
    return QDateTime::currentMSecsSinceEpoch();
}
