#pragma once
#include <QtCore>
#include <functional>

namespace RedisClient {

class Response;

class Command 
{    
public:
    Command();
    Command(const QList<QByteArray>& cmd, QObject * owner = nullptr, int db = -1);
    Command(const QStringList& cmd, QObject * m_owner = nullptr, int db = -1);
    Command(const QStringList& cmd, QObject * m_owner, std::function<void(Response)> callback, int db = -1);
    Command(const QStringList& cmd, int db);
    Command(int db);
    virtual ~Command();

    Command &operator <<(const QString&);
    Command &append(const QByteArray&part);

    /** @see http://redis.io/topics/protocol for more info **/    
    QByteArray  getByteRepresentation() const;
    QString     getRawString() const;
    QList<QByteArray> getSplitedRepresentattion() const;
    QString     getPartAsString(int i);
    int         getDbIndex() const;
    QObject*    getOwner() const;    

    void setCallBack(QObject* context, std::function<void(Response)> callback);
    std::function<void(Response)> getCallBack() const;

    void cancel();
    void markAsHiPriorityCommand();

    bool isCanceled() const;
    bool isValid() const;
    bool isScanCommand() const;
    bool hasCallback() const;
    bool isEmpty() const;
    bool hasDbIndex() const;
    bool isSelectCommand() const;
    bool isHiPriorityCommand() const;

public:
    static QList<QByteArray> splitCommandString(const QString &);

protected:
    QObject * m_owner;
    QList<QByteArray> m_commandWithArguments;
    int m_dbIndex;
    bool m_commandCanceled;
    bool m_hiPriorityCommand;
    std::function<void(Response)> m_callback;
};

QList<QByteArray> convertStringList(const QStringList&list);

}
