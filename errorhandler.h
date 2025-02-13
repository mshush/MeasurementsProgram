#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>


extern bool bNoError;
extern bool bAbort;
extern QString DebugStr;

class ErrorHandler : public QObject
{
    Q_OBJECT
private:
    ErrorHandler(QObject *parent = nullptr);
    ErrorHandler(const ErrorHandler&) = delete;
    ErrorHandler& operator=(const ErrorHandler&) = delete;
public:
    void AppendErrorToList(int NumOfError);
    int ErrorList[100];
    int ErrorListSize = 0;

    static ErrorHandler& error() {
        static ErrorHandler instance;
        return instance;
    }
signals:
    void ErrorOccurred(QString errorMessage);
//public slots:
   // void ReportError(QString errorMessage){
   //   ErrorOccurred(errorMessage);
    //}
};

QString reportLastError();
void AppendError(int error_);
QList<QString> GetAllErrorsList();
#endif // ERRORHANDLER_H
