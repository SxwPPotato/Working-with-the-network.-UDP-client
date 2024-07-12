#ifndef UDPWORKER_H
#define UDPWORKER_H

#include <QUdpSocket>
#include <QNetworkDatagram>


#define BIND_PORT 12345

class UDPworker : public QObject
{
    Q_OBJECT
public:
    explicit UDPworker(QObject *parent = nullptr);

    void TimeInitSocket(void );
    void strInitSocket(void  );

    void TimeReadDatagram( QNetworkDatagram datagram);
    void strReadDatagram( QNetworkDatagram datagram);

    void SendTimeDatagram(QByteArray data );
    void SendStrDatagram(QByteArray data);


private slots:
    void time_readPendingDatagrams(void );
    void str_readPendingDatagrams(void );

private:
    QUdpSocket* timeserviceUdpSocket;
    QUdpSocket* strserviceUdpSocket;

signals:
    void sig_sendtimeDataToGUI( QByteArray time_data);
    void sig_sendstrDataToGUI( QByteArray str_data, QNetworkDatagram datagram);

    void sig1( void);
    void sig2( void);
};

#endif // UDPWORKER_H
