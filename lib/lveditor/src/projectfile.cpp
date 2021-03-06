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

#include "live/projectfile.h"
#include <QFileInfo>

namespace lv{

ProjectFile::ProjectFile(const QString &path, ProjectEntry *parent)
    : ProjectEntry(QFileInfo(path).path(), QFileInfo(path).fileName(), true, parent)
    , m_document(0)
{
}

ProjectFile::ProjectFile(const QString &path, const QString &name, ProjectEntry *parent)
    : ProjectEntry(path, name, true, parent)
    , m_document(0)
{
}

ProjectFile::~ProjectFile(){
}

void ProjectFile::setDocument(ProjectDocument *document){
    if ( document == m_document )
        return;

    m_document = document;
    emit documentChanged();
}

}// namespace
