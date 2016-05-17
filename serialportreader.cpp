/****************************************************************************
**
** Copyright (C) 2013 Laszlo Papp <lpapp@kde.org>
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia. For licensing terms and
** conditions see http://qt.digia.com/licensing. For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "serialportreader.h"
#include "mainwindow.h"
#include <QApplication>

QT_USE_NAMESPACE

SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent)
    : QObject(parent)
    , m_serialPort(serialPort)
    , m_standardOutput(stdout)
{
    //qDebug("construct function");
    connect(m_serialPort, SIGNAL(readyRead()), SLOT(handleReadyRead()));
    connect(m_serialPort, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(handleError(QSerialPort::SerialPortError)));
}

SerialPortReader::~SerialPortReader()
{
}
//每当串口传来数据会触发该函数
void SerialPortReader::handleReadyRead()
{
    m_readData.append(m_serialPort->readAll());
    dataSender(m_readData);
}
//此函数实现从串口缓冲数组里解析出我们需要的数据功能，主要根据数据头[[
void SerialPortReader::dataSender(QByteArray & serialTemp)
{
            //refer to ascII
            //5b=[
            //5d=]

            //find head "[["
            if(serialTemp.count("[[") >=1)
            {
                //find tail ']'
                if(serialTemp.count(']')>=1)
                {
                    QByteArray serialData = dataProcessing(serialTemp);
                    serialTemp.clear();
                    emit mySignal(serialData);
                }
             }
}
//把数据头和尾去掉，只拿出x和y两个字节,这里应该没有处理按钮数据，需要你添加
QByteArray SerialPortReader::dataProcessing(QByteArray & serialTemp)
{
    //get the x and y two bytes
    serialTemp =  serialTemp.mid(serialTemp.indexOf(']')-2,2);
    return serialTemp;
}
//错误处理函数
void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError)
    {
        qDebug("handleError()");
    }
}
