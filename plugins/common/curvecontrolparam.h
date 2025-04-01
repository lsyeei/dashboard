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

#ifndef CURVECONTROLPARAM_H
#define CURVECONTROLPARAM_H
#include "serializable.h"

// 描述曲线控制点的参数
class CurveControlParam : public Serializable
{
    Q_GADGET
    SERIALIZE(CurveControlParam)
public:
    CurveControlParam() : Serializable(){};
    CurveControlParam(qreal angle, qreal len, bool attach);
    bool isEmpty() const;

private:
    // 角度
    qreal m_angle{0};
    // 长度
    qreal m_len{-1};
    // 是否与临近控制点关联，关联的控制点角度联动变换
    bool m_attach{true};

    JSONFIELD(m_angle, Angle)
    JSONFIELD(m_len, Len)
    JSONFIELD(m_attach, Attach)
};

inline CurveControlParam::CurveControlParam(qreal angle, qreal len, bool attach)
     : Serializable(), m_angle(angle), m_len(len), m_attach(attach)
{}

inline bool CurveControlParam::isEmpty() const
{
    return m_len <= 0;
}

#endif // CURVECONTROLPARAM_H
