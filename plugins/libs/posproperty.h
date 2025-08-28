/**
* This file is part of the dashboard library
* 
* Copyright 2025 lishiying  lsyeei@163.com
* 
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
* 
* http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#ifndef POSPROPERTY_H
#define POSPROPERTY_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QWidget>

class PosPropertyForm;
class QDESIGNER_WIDGET_EXPORT PosProperty : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qint32 left READ left WRITE setLeft NOTIFY leftChanged FINAL)
    Q_PROPERTY(qint32 top READ top WRITE setTop NOTIFY topChanged FINAL)
    Q_PROPERTY(qint32 width READ width WRITE setWidth NOTIFY widthChanged FINAL)
    Q_PROPERTY(qint32 height READ height WRITE setHeight NOTIFY heightChanged FINAL)
    Q_PROPERTY(bool aspectRatio READ aspectRatio WRITE setAspectRatio NOTIFY aspectRatioChanged FINAL)

public:
    explicit PosProperty(QWidget *parent = nullptr);
    ~PosProperty();
    qint32 left() const;
    void setLeft(qint32 newLeft);

    qint32 top() const;
    void setTop(qint32 newTop);

    qint32 width() const;
    void setWidth(qint32 newWidth);

    qint32 height() const;
    void setHeight(qint32 newHeight);

    bool aspectRatio() const;
    void setAspectRatio(bool newAspectRatio);

Q_SIGNALS:
    void propertyChanged(qint32 left, qint32 top, qint32 width, qint32 height, bool aspectRatio);

    void leftChanged();

    void topChanged();

    void widthChanged();

    void heightChanged();

    void aspectRatioChanged();
protected:
    void resizeEvent(QResizeEvent *event) override;

private Q_SLOTS:
    /**
     * @brief 处理form值改变事件
     */
    void valueChangeHandler();
private:
    QScopedPointer<PosPropertyForm> form;
};

#endif // POSPROPERTY_H
