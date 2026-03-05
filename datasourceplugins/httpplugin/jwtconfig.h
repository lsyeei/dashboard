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
#ifndef JWTCONFIG_H
#define JWTCONFIG_H

#include "serializable.h"
#include "authlocation.h"

class JWTConfig : public Serializable
{
    Q_GADGET
    SERIALIZE(JWTConfig)
public:
    JWTConfig(){
        location = AuthLocation::Header;
        headerPrefix = "Bearer";
    }
private:
    AuthLocation location;
    QString token;
    QString headerPrefix;

    JSONFIELD(location, Location)
    JSONFIELD(token, Token)
    JSONFIELD(headerPrefix, HeaderPrefix)
};

#endif // JWTCONFIG_H
