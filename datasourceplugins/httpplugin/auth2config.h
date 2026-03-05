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
#ifndef AUTH2CONFIG_H
#define AUTH2CONFIG_H

#include "serializable.h"
#include "authlocation.h"
enum class TokenType{ID, Access};
enum class AuthModel{Code, Code_PKCE, Implicit,
                       Credentials_Password, Credentials_Client};
class Auth2Config : public Serializable
{
    Q_GADGET
    SERIALIZE(Auth2Config)
public:
    Auth2Config(){
        location = AuthLocation::Header;
        tokenType=TokenType::ID;
        authModel=AuthModel::Code;
    }
    static QList<QPair<QString, TokenType>> tokenTypeList(){
        return {{"ID token", TokenType::ID}, {"Access token", TokenType::Access}};
    }
    static QList<QPair<QString, AuthModel>> authModelList(){
        return {{"Authorization Code", AuthModel::Code},
                {"Authorization Code(With PKCE)", AuthModel::Code_PKCE},
                {"Implicit", AuthModel::Implicit},
                {"Password Credentials", AuthModel::Credentials_Password},
                {"Client Credentials", AuthModel::Credentials_Client}};
    }
private:
    AuthLocation location;
    TokenType tokenType;
    AuthModel authModel;
    QString authUrl;
    QString accessTokenUrl;
    QString callbackUrl;
    QString clientId;
    QString clientSecret;
    QString userName;
    QString password;

    JSONFIELD(location, Location)
    JSONFIELD(tokenType, TokenType)
    JSONFIELD(authModel, AuthModel)
    JSONFIELD(authUrl, AuthUrl)
    JSONFIELD(accessTokenUrl, AccessTokenUrl)
    JSONFIELD(callbackUrl, CallbackUrl)
    JSONFIELD(clientId, ClientId)
    JSONFIELD(clientSecret, ClientSecret)
    JSONFIELD(userName, UserName)
    JSONFIELD(password, Password)
};

#endif // AUTH2CONFIG_H
