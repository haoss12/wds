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
    /**
     * @brief Default constructor with start sign set to 'X'.
     *
     */
    dataFrame(): start('X'){};

    /**
     * @brief Constructor in which start sign can be set.
     *
     */
    dataFrame(char _start): start(_start){};

    /**
     * @brief Method to parse data from string to data stored in class.
     *
     * @param std::string containing line to process.
     *
     * @return 0 - data processed correctly, -1 - error when parsing data
     */
    int parseData(const std::string &line);

    /**
     * @brief Method to parse data from string to data stored in class.
     *
     * @param QString containing line to process.
     *
     * @return 0 - data processed correctly, -1 - error when parsing data
     */
    int parseData(const QString &line);

    /**
     * @brief Method to get data from array
     * @param index of element
     * @return choosen value
     */
    int getAcc(uint8_t ind) const;

    /**
     * @brief Method to get data from array
     * @param index of element
     * @return choosen value
     */
    float getGyro(uint8_t ind) const;

private:
    char start; /**< Sign which starts data frame */
    std::array <int, 3> acc; /**< Array with readings from accelerometer */
    std::array <float, 3> gyro; /**< Array with readings from gyroscope */

};

#endif // DATAFRAME_H
