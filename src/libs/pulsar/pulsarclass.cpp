#include "pulsarclass.h"
#include <QtEndian>

/* Table of CRC values for high-order byte */
static const uint8_t table_crc_hi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
};

/* Table of CRC values for low-order byte */
static const uint8_t table_crc_lo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40
};

PulsarClass::PulsarClass(quint8 Type, QString server_com, quint16 port_props, quint16 timeout/* = 200*/):
    ioDriver (Type, server_com, port_props, timeout)
{
    connect(this, SIGNAL(write(QByteArray )), &ioDriver, SLOT(write(QByteArray)));
    connect(&ioDriver, SIGNAL(response(QByteArray)), this, SLOT(received(QByteArray)));
    connect(&ioDriver, SIGNAL(timeout()), this, SLOT(timeout()));

    receivedData = false;

//    bool ok;
//    QString str("01603846");
//    address = str.toInt(&ok, 16);
//    qDebug() << str;
//    if (!ok)
//        qFatal("Cannot convert address from string to BCD");

}

void PulsarClass::received(QByteArray buf_)
{
    Response = buf_;
    len = buf_.size();
//    qDebug() << "Receive buf = " << Response.toHex() << " with size = " << Response.size();
    receivedData = true;
}

void PulsarClass::timeout()
{
    len = 0;
    receivedData = true;
}

/*          Read Channel Command
 *       4        1   1      4      2      2
 * |   ADDR    | F | L | MASK_CH | ID | CRC16 |
 * |  HI..LOW  |   |   | LOW..HI |    |LOW..HI|
 *
 */

void PulsarClass::create_request(quint32 channelMask)
{
    Request.append(address >> 24);
    Request.append(address >> 16);
    Request.append(address >> 8);
    Request.append(address >> 0);

    Request.append(Cmd);

    quint16 crc = 0;

    switch (Cmd) {
    case READ_CHANNEL :

        Request.append(channelMask); // LOW
        Request.append(channelMask >> 8);
        Request.append(channelMask >> 16);
        Request.append(channelMask >> 24); // HI

        Request.append(ID);
        Request.append(ID);

        Request.insert(POS_L, Request.size() + 2 + 1);// +2 is CRC, +1 is Lenght

        crc = make_crc(&Request, Request.size());
//        qDebug() << "crc = " << QString::number(crc,16);

        Request.append(crc >> 8);
        Request.append(crc >> 0);

        break;
    default:
        break;
    }

}


quint16 PulsarClass::make_crc(QByteArray * buf, int size)
{
//    qDebug() << "make_crc() get buf" << buf->toHex();
//    qDebug() << "make_crc() buf size = " << size;

   char * data = buf->data();

   quint8 crc_hi = 0xFF; /* high CRC byte initialized */
   quint8 crc_lo = 0xFF; /* low CRC byte initialized */
   quint8 i; /* will index into CRC lookup */

   /* pass through message buffer */
   while (size--) {
       i = crc_hi ^ *data++; /* calculate the CRC  */
       crc_hi = crc_lo ^ table_crc_hi[i];
       crc_lo = table_crc_lo[i];
   }
   return (crc_hi << 8 | crc_lo);
}


bool PulsarClass::check_crc()
{
    bool flag = false;

    if (!Response.size()) {

    }
    else {
        QByteArray crc16, crc16_response;

        crc16_response.append(Response.at(Response.size() - 2));
        crc16_response.append(Response.at(Response.size() - 1));
//        qDebug() << "CRC16 get= " << crc16_response.toHex();

        quint16 crc = make_crc(&Response, Response.size() - 2);
        crc16.append(crc >> 8);
        crc16.append(crc >> 0);
//        qDebug() << "CRC16 calc= " << crc16.toHex() << endl;

        if (crc16 == crc16_response)
            flag = true;

        crc16_response.clear();
        crc16.clear();
    }

    return flag;
}

float PulsarClass::convert_data()
{
    QByteArray val;
    float ret;

    if (Cmd == READ_CHANNEL) {

        val.append(Response.at(POS_D));
        val.append(Response.at(POS_D + 1));
        val.append(Response.at(POS_D + 2));
        val.append(Response.at(POS_D + 3));

         ret = qFromLittleEndian<float>(val.data());
    }
    return ret;
}

bool PulsarClass::getP()
{
    bool flag = false;
    Cmd = READ_CHANNEL;
//    quint32 mask = ((CH1|CH7)) | ((CH9|CH12) << 8) ;

    quint32 mask = CH7;

    create_request(mask);

    // clear flag
    receivedData = false;

    emit write(Request);

    // wait flag in slots: timeout() or received()
    while (!receivedData) {};

    if (check_crc()) {
        energy = convert_data();
        flag = true;
    }
    else
        energy = 0;

    Request.clear();

    return flag;
}

Data PulsarClass::read_data(GuidClass* guid)
{
    Data retData;
    QStringList qsl;
    bool ok;

    address = guid->get_address().toInt(&ok, 16);
    if (!ok)
        qFatal("Cannot convert Pulsar address from string to BCD");

    if (getP()) {

        qsl.append(guid->get_guid());

        qsl.append(QString::number(energy));
        qsl.append(QString::number(DATA_VALUE_FLAG0));

        retData.append(qsl);

        qsl.clear();

        qDebug() << "Pulsar with Address = " << guid->get_address()
                 << " Values : " << retData << endl;
    } else
        qDebug() << "Pulsar with Address = " << guid->get_address()
                 << " Cannot read values "   << endl;

    return retData;
}
