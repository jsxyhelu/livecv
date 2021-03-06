/****************************************************************************
**
** Copyright (C) 2014-2018 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV Application.
**
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
****************************************************************************/

#include "live/nativevaluecodeserializer.h"

#include <QVariant>
#include <QDebug>

namespace lv{

NativeValueCodeSerializer::NativeValueCodeSerializer(QObject *parent)
    : AbstractCodeSerializer(parent)
{
}

NativeValueCodeSerializer::~NativeValueCodeSerializer(){
}

QString NativeValueCodeSerializer::toCode(const QVariant &value, const DocumentEditFragment *){
    if ( value.type() >= QVariant::Bool && value.type() <= QVariant::Double )
        return value.toString();
    else if ( value.type() == QVariant::Char ||
              value.type() == QVariant::String ||
              value.type() == QVariant::ByteArray )
        return "\'" + value.toString() + "\'";
    else if ( value.type() == QVariant::Color )
        return "\'" + value.toString() + "\'";

    qWarning("Failed to convert value: %s", qPrintable(value.toString()));
    return "";
}

QVariant NativeValueCodeSerializer::fromCode(const QString &value, const DocumentEditFragment *){
    QString val = value.trimmed();
    if ( val.length() > 1 && (
             (val.startsWith('"') && val.endsWith('"')) ||
             (val.startsWith('\'') && val.endsWith('\'') )
        ))
    {
        return QVariant(val.mid(1, value.length() - 2));
    } else if ( val == "true" ){
        return QVariant(true);
    } else if ( val == "false" ){
        return QVariant(false);
    } else {
        bool ok;
        qint64 number = value.toLongLong(&ok);
        if (ok)
            return QVariant(number);

        return QVariant(val.toDouble());
    }

    return QVariant();
}

}// namespace
