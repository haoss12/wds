#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <QString>
#include <string>
#include <iostream>
#include <sstream>
#include <array>
#include "crc8.h"

class dataFrame
{
public:
    dataFrame(char _start): start(_start){};

    int parseData(const std::string &line);
    int parseData(const QString &line);

    void print() const;

    int getAcc(uint8_t ind) const;

    int getGyro(uint8_t ind) const;

private:
    char start;
    std::array <int, 3> acc;
    std::array <float, 3> gyro;

};

#endif // DATAFRAME_H
