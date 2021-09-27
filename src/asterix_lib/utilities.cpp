#include "hdr/asterix_lib/utilities.h"

namespace Utilities {


QVector<char> DataTools::GetFixedLengthDataItem(QVector<char> &message, int length) {

    int i = 0;
    QVector<char> dataItem(length);

    while (i < length) {
        dataItem[i] = message.at(0);
        message.remove(0);
        i++;
    }
    return dataItem;
}
}
