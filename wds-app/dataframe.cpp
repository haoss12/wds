#include "dataframe.h"
#include <QDebug>

int dataFrame::parseData(const QString &line)
{
    return parseData(line.toStdString());
}

int dataFrame::parseData(const std::string &line) {

    //check if start sign is ok
    if (line[0] != this->start) {
        return -1;
    }

    //calculate crc and compare with one that was sent
    std::string trimmed = line.substr(0, line.find('\r', 0));
    uint8_t crcCalculated = crc8(trimmed.substr(0, trimmed.length() - 5));

    int crc;
    std::istringstream lineStream(line);
    char start;
    char dump;
    std::array <int, 3> _acc;
    std::array <float, 3> _gyro;

    lineStream >> start >> _gyro[0] >> _gyro[1] >> _gyro[2] >> _acc[0] >> _acc[1] >> _acc[2] >> dump >> dump >> std::hex >> crc;

    if (crc != crcCalculated) {
        return -1; //maybe change to throw exeptions instead
    }

    acc = _acc;
    gyro = _gyro;
    return 0;
}

int dataFrame::getAcc(uint8_t ind) const {

    if (ind > (acc.size() - 1)) {
        throw std::out_of_range("dataFrame::getAcc - Index out of range.");
    }

    return acc[ind];
}

float dataFrame::getGyro(uint8_t ind) const {

    if (ind > (gyro.size() - 1)) {
        throw std::out_of_range("dataFrame::getGyro - Index out of range.");
    }

    return gyro[ind];
}
