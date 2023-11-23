/*
 * qt-kiosk-browser
 * Copyright (C) 2018
 * O.S. Systems Sofware LTDA: contato@ossystems.com.br
 *
 * SPDX-License-Identifier:     GPL-3.0
 */


#ifndef PROXYHANDLER_HPP
#define PROXYHANDLER_HPP

#include <QObject>
#include <QNetworkProxy>
#include <QByteArray>
#include <QUrl>

class ProxyHandler : public QObject
{
    Q_OBJECT
public:
    explicit ProxyHandler(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE void useSystemProxy()
    {
        QByteArray proxyUrl = qgetenv("https_proxy");

        qDebug() << "Proxy URL: " << proxyUrl;
        if (!proxyUrl.isEmpty())
        {
            QUrl url{QString(proxyUrl)};
            qDebug() << "Proxy URL is not empty: " << url;

            QNetworkProxy proxy;
            proxy.setType(QNetworkProxy::HttpProxy);
            proxy.setHostName(url.host());
            proxy.setPort(url.port());

            if (!url.userName().isEmpty())
            {
                proxy.setUser(url.userName());
            }
            if (!url.password().isEmpty())
            {
                proxy.setPassword(url.password());
            }
            qDebug() << "Proxy: " << proxy;

            QNetworkProxy::setApplicationProxy(proxy);
        }
        qDebug() << "application proxy is" << QNetworkProxy::applicationProxy();
        qDebug() << "Done setting use system proxy to true";
    }
};

#endif // PROXYHANDLER_HPP
