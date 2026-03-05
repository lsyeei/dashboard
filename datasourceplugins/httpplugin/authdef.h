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
#ifndef AUTHDEF_H
#define AUTHDEF_H
#include "abstractsubform.h"
#include "apikeyform.h"
#include "basicauthform.h"
#include "bearertokenform.h"
#include "jwtform.h"
#include "digestauthform.h"
#include "ntlmform.h"
#include "spnegoform.h"
#include "oauth2form.h"
#include "oauth1form.h"
#include "serializable.h"

#include <QString>
#include <QList>

// 授权方式
enum class AuthMethod{NoAuth, APIKey, BearToken, JWT, BasicAuth, DigestAuth,
                        NTLM, SPNEGO, OAuth1, OAuth2};

class AuthConfig : public Serializable
{
    Q_GADGET
    SERIALIZE(AuthConfig)
public:
    AuthConfig(){method = AuthMethod::NoAuth;}
private:
    // 授权方式
    AuthMethod method;
    // 授权配置
    QVariant config;

    JSONFIELD(method, Method)
    JSONFIELD(config, Config)
};

struct AuthMethodInfo{
    AuthMethod method;
    QString alias;
    QString note;
    std::function<AbstractSubForm *()> form;
};
namespace AuthDef {
    static AbstractSubForm *apiForm()
    {
        return new APIKeyForm();
    }
    static AbstractSubForm *basicAuthForm()
    {
        return new BasicAuthForm();
    }
    static AbstractSubForm *beareTokenForm()
    {
        return new BearerTokenForm();
    }
    static AbstractSubForm *oauth2Form()
    {
        return new OAuth2Form();
    }
    static AbstractSubForm *oauth1Form()
    {
        return new OAuth1Form();
    }
    static AbstractSubForm *jwtForm()
    {
        return new JWTForm();
    }
    static AbstractSubForm *digestAuthForm()
    {
        return new DigestAuthForm();
    }
    static AbstractSubForm *ntlmForm()
    {
        return new NTLMForm();
    }
    static AbstractSubForm *spnegoForm()
    {
        return new SPNEGOForm();
    }
    static QList<AuthMethodInfo> list{
    {AuthMethod::NoAuth, "No Auth","无授权", nullptr},
    {AuthMethod::APIKey,"API Key","API 密钥授权", apiForm},
    {AuthMethod::BearToken,"Bearer Token","Bearer Token授权", beareTokenForm},
    {AuthMethod::JWT,"JWT","JWT令牌", jwtForm},
    {AuthMethod::BasicAuth,"Basic Auth","Basic Auth授权", basicAuthForm},
    {AuthMethod::DigestAuth,"Digest Auth","摘要认证 Digest-MD5", digestAuthForm},
    {AuthMethod::NTLM,"NTLM","NT 本地身份验证, NTLM version 2", ntlmForm},
    {AuthMethod::SPNEGO,"SPNEGO/Negotiate","SPNEGO 授权 或 Negotiate 授权", spnegoForm},
    {AuthMethod::OAuth1,"OAuth 1.0","OAuth 1.0 授权", oauth1Form},
    {AuthMethod::OAuth2,"OAuth 2.0","OAuth 2.0 授权", oauth2Form}
    };
}
#endif // AUTHDEF_H
