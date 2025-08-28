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

#ifndef CURSORLIB_H
#define CURSORLIB_H

#include "qcursor.h"
#include <QObject>

class PathImage;
class CursorLibPrivate;
class CursorLib{
public:
    enum CustomShape{
        SizeHorCursor
    };
    /**
     * @brief instance 获取单一实例
     * @return CursorLib对象
     */
    static CursorLib *instance();
    /**
     * @brief getShape 获取预置光标
     * @param shape 光标形状
     * @param size 大小
     * @param angle 调整的角度
     * @return 光标
     */
    QCursor getShape(CustomShape shape, qreal angle = 0, const QSize &size = QSize{});
    using DataPtr = QExplicitlySharedDataPointer<CursorLibPrivate>;
private:
    CursorLib();
    /**
     * @brief createSizeHorCursor 创建 SizeHorCursor 光标
     * @return
     */
    PathImage createSizeHorCursor();
    static CursorLib *lib;
    DataPtr d;

    Q_DISABLE_COPY_MOVE(CursorLib)
};

#endif // CURSORLIB_H
