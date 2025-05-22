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
#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QItemDelegate>
#include <QPainter>
class ImageDelegate : public QItemDelegate {
public:
    enum ImageType{PATH, CONTENT};
    ImageDelegate(ImageType type):QItemDelegate(), type(type){}
    void setImageType(ImageType type);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override {

        QPixmap pixmap;
        switch (type) {
        case PATH:
            pixmap.load(index.data().toString());
            break;
        case CONTENT:
            pixmap.loadFromData(index.data().toByteArray());
            break;
        default:
            break;
        }
        painter->drawPixmap(option.rect, pixmap);
    }
private:
    ImageType type{PATH};
};
#endif // IMAGEDELEGATE_H
