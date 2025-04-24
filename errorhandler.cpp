#include "errorhandler.h"
bool bNoError = true;
bool bAbort = false;

ErrorHandler::ErrorHandler(QObject *parent)
    : QObject{parent}
{

}
/*
void ErrorHandler::AppendErrorToList(int NumOfError){
    //if (ErrorListSize > 0 && ErrorList[ErrorListSize - 1] == NumOfError) return;
    ErrorList[ErrorListSize] = NumOfError;
    ErrorListSize++;
}

QString reportLastError(){
    int size = ErrorHandler::error().ErrorListSize;
    QString error_;
    if (size > 0) {
        if (ErrorHandler::error().ErrorList[size-1] == 1) error_ = "No connection to VNA";
        if (ErrorHandler::error().ErrorList[size-1] == 2) error_ = "PowerOn Failed";
        if (ErrorHandler::error().ErrorList[size-1] == 3) error_ = "OPU connection Failed";
        if (ErrorHandler::error().ErrorList[size-1] == 5) error_ = "Error while write occured";
        if (ErrorHandler::error().ErrorList[size-1] == 6) error_ = "Params are not set";
        if (ErrorHandler::error().ErrorList[size-1] == 7) error_ = "Required sweep is not recorded yet";

        else error_ = "Unknown error";
        emit ErrorHandler::error().ErrorOccurred(error_);
    }
    else
    {
        error_ = "No error";

    }

    return error_;

}

void AppendError(int error_){
    ErrorHandler::error().AppendErrorToList(error_);
}
*/
//QList<QString> GetAllErrorsList(){
    //QList<QString> List =  ErrorHandler::error().ErrorList ;
    //return List;
//}
