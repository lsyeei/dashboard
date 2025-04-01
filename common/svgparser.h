/**
 * 源代码svgHelper地址：https://github.com/sorrowfeng/svgHelper
 */
#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <QDomElement>
#include <QPainterPath>
class SvgShape
{
public:
    QPainterPath path;
    bool fillFlag{false};
    QString fillColor{""};
    int strokeWidth{0};
    QString strokeColor{""};
};

#define ABSOLUTE_COORDINATES 1
#define RELATIVE_COORDINATES 2
class SvgParser
{
public:
    SvgParser();
    void parseSvgImage(QString filepath);
    QList<QPainterPath> getSvgPathList() const;
    QImage getSvgImage();

    QList<QList<QPointF> > getSvgPointList() const;
    /**
     * @brief getSize 获取画布大小
     * @return 画布大小
     */
    QSize getSize();
    /**
     * @brief getShapeList 获取Svg包含的所有图形信息
     * @return 图形列表
     */
    QList<SvgShape> getShapeList();

private:
    QList<QChar> cmdList = {'M', 'm', 'L', 'l', 'H', 'h', 'V', 'v', 'C', 'c', 'S', 's', 'Q', 'q', 'T', 't', 'A', 'a', 'Z', 'z'};
    QList<QChar> cmdTypeList = {'M', 'L', 'H', 'V', 'C', 'S', 'Q', 'T', 'A', 'Z'};
    QList<QChar> splitList = {' ', '-', ',', '\r', '\n', '\t'};
    QList<QString> unitList = {"em", "px", "%", "cm", "mm", "in", "pt", "pc"};
    QList<QString> typeList = {"path", "rect", "circle", "ellipse", "line", "polygon", "polyline", "text", "defs"};

    void parseSVGTag(QDomElement e, QString tagname);
    void parseSvgPath(QString path, QPainterPath &paintPath);
    void dealParsePainter(QPainterPath &path, QString line);
    QVector<float> segmentationCoordinates(QString value);
    float getValueWithoutUnit(QString input);
    double radian( double ux, double uy, double vx, double vy );
    int svgArcToCenterParam(double x1, double y1, double rx, double ry, double phi, double fA, double fS, double x2, double y2,
                            double &cx_out, double &cy_out, double &startAngle_out, double &deltaAngle_out);
    double get_angle_with_points(double x1, double y1, double x2, double y2, double x3, double y3);

    void parseNode(QDomNode n);
    /**
     * @brief parseStyle 解析字符串中的style
     * @param style style字符串
     * @return 属性集合
     */
    QMap<QString,QString> parseStyle(QString style);
    /**
     * @brief getShapeStyle 从DomElement中提取图形样式
     * @param e DomElement对象
     * @return SvgShape对象
     */
    SvgShape getShapeStyle(QDomElement e);


    QString filepath;
    QPainterPath paintPath;
    QList<QPointF> testpathlist;
    QPointF nowPositon = QPointF(0, 0);
    QPointF pathStartPosition = QPointF(0, 0);
    QPointF lastControlPosition = QPointF(0, 0);
    QList<QPainterPath> svgPathList;
    QList<QList<QPointF>> svgPointList;
    // SVG 画布宽度
    int width;
    // SVG 画布高度
    int height;
    QList<SvgShape> shapeList;
};

#endif // SVGPARSER_H
