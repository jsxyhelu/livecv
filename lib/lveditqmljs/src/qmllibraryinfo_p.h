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

#ifndef LVQMLLIBRARYINFO_H
#define LVQMLLIBRARYINFO_H

#include "languageutils/componentversion.h"
#include "qmljs/qmljsdocument.h"

#include <QMap>

namespace lv{

class QmlLibraryInfo{

public:
    enum ScanStatus{
        NotScanned = 0,
        ScanError,
        NoPrototypeLink,
        RequiresDependency,
        Done
    };

public:
    class ExportVersion{
    public:
        ExportVersion()
            : versionMajor(-1)
            , versionMinor(-1)
        {}
        ExportVersion(int vma, int vmi, LanguageUtils::FakeMetaObject::ConstPtr o)
            : versionMajor(vma)
            , versionMinor(vmi)
            , object(o)
        {}
        bool isValid() const{ return versionMinor != -1 && versionMajor != -1; }

        int versionMajor;
        int versionMinor;
        LanguageUtils::FakeMetaObject::ConstPtr object;
    };

    class Export{
    public:
        QList<ExportVersion> versions;
    };


public:
    typedef QSharedPointer<QmlLibraryInfo>       Ptr;
    typedef QSharedPointer<const QmlLibraryInfo> ConstPtr;

public:
    static Ptr create();
    static Ptr create(const QmlDirParser& parser);

    ~QmlLibraryInfo();

    QmlJS::LibraryInfo& data(){ return m_data; }
    const QmlJS::LibraryInfo& data() const{ return m_data; }
    QMap<QString, Export>& exports(){ return m_exports; }

    void updateExports();

    void listExports(QStringList* exports);
    ExportVersion findExport(const QString& name);
    ExportVersion findExportByClassName(const QString& name);
    LanguageUtils::FakeMetaObject::ConstPtr findObjectByClassName(const QString& name);

    void setDependencies(const QList<QString> &paths);
    const QList<QString>& dependencyPaths() const;

    void updateImportInfo(const QString& uri, int versionMajor, int versionMinor);

    ScanStatus status() const;
    void setStatus(ScanStatus status);

private:
    QmlLibraryInfo();
    QmlLibraryInfo(const QmlDirParser& parser);

private:
    void addExport();

    ScanStatus            m_status;
    QMap<QString, Export> m_exports;
    QmlJS::LibraryInfo    m_data;
    QList<QString>        m_dependencyPaths;
};

inline QmlLibraryInfo::Ptr QmlLibraryInfo::create(){
    return QmlLibraryInfo::Ptr(new QmlLibraryInfo);
}

inline QmlLibraryInfo::Ptr QmlLibraryInfo::create(const QmlDirParser &parser){
    return QmlLibraryInfo::Ptr(new QmlLibraryInfo(parser));
}

inline const QList<QString> &QmlLibraryInfo::dependencyPaths() const{
    return m_dependencyPaths;
}

inline QmlLibraryInfo::ScanStatus QmlLibraryInfo::status() const{
    return m_status;
}

inline void QmlLibraryInfo::setStatus(QmlLibraryInfo::ScanStatus status){
    m_status = status;
}

}// namespace

#endif // LVQMLLIBRARYINFO_H
