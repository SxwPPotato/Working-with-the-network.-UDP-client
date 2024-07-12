#include "udpworker.h"

UDPworker::UDPworker(QObject *parent) : QObject(parent)
{



}

void UDPworker::TimeInitSocket( )
{

    timeserviceUdpSocket = new QUdpSocket(this);

    timeserviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT);

    connect(timeserviceUdpSocket,  &QUdpSocket::readyRead, this, &UDPworker::time_readPendingDatagrams);

}

void UDPworker::strInitSocket( )
{

    strserviceUdpSocket = new QUdpSocket(this);

    strserviceUdpSocket->bind(QHostAddress::LocalHost, BIND_PORT2);

    connect(strserviceUdpSocket,  &QUdpSocket::readyRead, this, &UDPworker::str_readPendingDatagrams);

}

void UDPworker::TimeReadDatagram(QNetworkDatagram datagram)
{

    QByteArray time_data;

    time_data.resize(datagram.data().size());
    time_data = datagram.data();

    emit sig_sendtimeDataToGUI(time_data);

}

void UDPworker::strReadDatagram(QNetworkDatagram datagram)
{

    QByteArray str_data;

    str_data.resize(datagram.data().size());
    str_data = datagram.data();

    emit sig_sendstrDataToGUI(str_data,datagram);

}

void UDPworker::SendTimeDatagram(QByteArray data)
{
    timeserviceUdpSocket->writeDatagram(data, QHostAddress::LocalHost, BIND_PORT);
}

void UDPworker::SendStrDatagram(QByteArray datas)
{
    strserviceUdpSocket->writeDatagram(datas, QHostAddress::LocalHost, BIND_PORT2);
}

void UDPworker::time_readPendingDatagrams( void )
{
    while(timeserviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = timeserviceUdpSocket->receiveDatagram();

            TimeReadDatagram(datagram);
    }

}

void UDPworker::str_readPendingDatagrams( void )
{
    while(strserviceUdpSocket->hasPendingDatagrams()){
            QNetworkDatagram datagram = strserviceUdpSocket->receiveDatagram();

            strReadDatagram(datagram);
    }

}
