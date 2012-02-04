/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2012  David Rosca <nowrep@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef DOWNLOADFILEHELPER_H
#define DOWNLOADFILEHELPER_H

#include <QObject>
#include <QTime>
#include <QNetworkReply>
#include <QPixmap>
#include <QListWidget>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QFileIconProvider>
#include <QFileDialog>

#include "downloadmanager.h"

class DownloadItem;
class DownloadManager;
class WebPage;
class DownloadFileHelper : public QObject
{
    Q_OBJECT
public:
    explicit DownloadFileHelper(const QString &lastDownloadPath, const QString &downloadPath, bool useNativeDialog, WebPage* page);
    ~DownloadFileHelper();

    void setListWidget(QListWidget* tw) { m_listWidget = tw; }
    void setDownloadManager(DownloadManager* m) { m_manager = m; }
    void setLastDownloadOption(const DownloadManager::DownloadOption &option) { m_lastDownloadOption = option; }

    void handleUnsupportedContent(QNetworkReply* reply, bool askWhatToDo);

signals:
    void itemCreated(QListWidgetItem* item, DownloadItem* downItem);

private slots:
    void optionsDialogAccepted(int finish = -1);
    void fileNameChoosed(const QString &name, bool fileNameAutoGenerated = false);

private:
    QString getFileName(QNetworkReply* reply);

    DownloadManager::DownloadOption m_lastDownloadOption;
    QString m_lastDownloadPath;
    QString m_downloadPath;
    bool m_useNativeDialog;

    QTime* m_timer;
    QString m_path;
    QString m_fileName;
    QString m_userFileName;
    QString m_h_fileName;
    QNetworkReply* m_reply;
    QPixmap m_fileIcon;
    QUrl m_downloadPage;
    bool m_openFileChoosed;

    QListWidget* m_listWidget;
    QFileIconProvider* m_iconProvider;
    DownloadManager* m_manager;
    WebPage* m_webPage;
};

#endif // DOWNLOADFILEHELPER_H
