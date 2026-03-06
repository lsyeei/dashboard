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

#ifndef GRAPHICDOCUMENT_H
#define GRAPHICDOCUMENT_H

#include <QObject>
#include <QString>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class BIGraphicsView;
class MainWindow;

struct Document{
    QString project;
    QString page;
    QString shapes;
    QString animates;
    QString dataSource;
};

typedef std::function<bool()> callback;
/**
 * @brief GraphicDocument 文件管理类
 * 负责文件路径记忆、脏标记、保存和加载等功能
 */
class GraphicDocument : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief GraphicDocument 构造函数
     */
    GraphicDocument(QWidget *parent = nullptr);

    /**
     * @brief GraphicDocument 析构函数
     */
    ~GraphicDocument();
    /**
     * @brief setSaveWatcher 监控文档保存动作，回调方法内对文档进行最后更新
     * @param func 回调方法
     */
    void setSaveWatcher(callback func){docCheck = func;}
    /**
     * @brief markDirty 标记文件为已修改
     */
    void markDirty();

    /**
     * @brief clearDirty 清除脏标记
     */
    void clearDirty();

    /**
     * @brief isDirty 获取脏标记状态
     * @return true:文件已修改 false:文件未修改
     */
    bool isDirty() const;

    /**
     * @brief getFilePath 获取当前文件路径
     * @return 文件路径，如果未保存则为空字符串
     */
    QString getFilePath() const;

    /**
     * @brief getFileName 获取当前文件名
     * @return 文件名，如果未保存则为空字符串
     */
    QString getFileName() const;

    /**
     * @brief setFilePath 设置当前文件路径
     * @param filePath 文件路径
     */
    void setFilePath(const QString &filePath);

    /**
     * @brief updateWindowTitle 更新窗口标题
     */
    void updateWindowTitle();

    /**
     * @brief newFile 新建文件
     * @return true:成功 false:失败或用户取消
     */
    bool newFile();

    /**
     * @brief open 打开文件
     * @param filePath 文件路径，如果为空则弹出文件选择对话框
     * @return true:成功 false:失败或用户取消
     */
    bool open();

    /**
     * @brief openFile 打开文件
     * @param filePath 文件路径，如果为空则弹出文件选择对话框
     * @return true:成功 false:失败或用户取消
     */
    bool openFile(const QString &filePath = QString());

    /**
     * @brief save 保存文件
     * @return true:成功 false:失败
     */
    bool save();

    /**
     * @brief saveAs 另存为
     * @param filePath 文件路径，如果为空则弹出文件选择对话框
     * @return true:成功 false:失败或用户取消
     */
    bool saveAs(const QString &filePath = QString());

    /**
     * @brief checkSaveBeforeAction 在执行退出或打开新文件前检查是否需要保存
     * @return true:可以继续操作 false:用户取消操作
     */
    bool checkSaveBeforeAction();

    Document getDoc() const;
    void updateDoc(const Document &newDoc);

    QString getLastError() const;
    bool isNew(){return currentFilePath.isEmpty();}

Q_SIGNALS:
    /**
     * @brief dirtyChanged 脏标记状态改变信号
     * @param dirty 是否为脏
     */
    void dirtyChanged(bool dirty);

    /**
     * @brief filePathChanged 文件路径改变信号
     * @param filePath 新的文件路径
     */
    void filePathChanged(const QString &filePath);

    /**
     * @brief fileOpened 文件打开信号
     * @param filePath 打开的文件路径
     */
    void fileOpened(const QString &filePath);

    /**
     * @brief fileSaved 文件保存信号
     * @param filePath 保存的文件路径
     */
    void fileSaved(const QString &filePath);

private:

    /**
     * @brief writeToFile 写入文件内容
     * @param filePath 文件路径
     * @return true:成功 false:失败
     */
    bool writeToFile(const QString &filePath);

    /**
     * @brief readFromFile 从文件读取内容
     * @param filePath 文件路径
     * @return true:成功 false:失败
     */
    bool readFromFile(const QString &filePath);

    /**
     * @brief showSavePrompt 显示保存提示对话框
     * @return QMessageBox::StandardButton 用户选择
     */
    int showSavePrompt();

private:
    QWidget *parent;
    Document doc;
    QString lastError;
    QString currentFilePath;    // 当前文件路径
    bool dirty{false};           // 文件是否被修改
    callback docCheck;
};

#endif // GRAPHICDOCUMENT_H
