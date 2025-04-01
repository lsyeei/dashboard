#include "svgparser.h"
// #include "QtWidgets/qwidget.h"

#include <QFile>
#include <QImage>
#include <QMap>
#include <QPainter>
#include <QSvgRenderer>

SvgParser::SvgParser() {}

void SvgParser::parseSvgImage(QString filepath)
{
    this->filepath = filepath;

    QFile svgFile(filepath);
    if(svgFile.open(QFile::ReadOnly)) {
        QDomDocument doc;
        if(doc.setContent(&svgFile))
        {
            svgFile.close();
                // 返回根节点
            QDomElement root = doc.documentElement();
            if (root.hasAttribute("width")){
                width = root.attribute("width", "0").toInt();
            }
            if (root.hasAttribute("height")){
                height = root.attribute("height", "0").toInt();
            }
            // 获得第一个子节点
            QDomNode node = root.firstChild();
            while(!node.isNull())   //如果节点不空
            {
                parseNode(node);
                // if(node.isElement())  //如果节点是元素
                // {
                    // //转换为元素
                    // QDomElement e = node.toElement();
                    // QString tagname = e.tagName();
                    // if(typeList.contains(tagname)) {
                    //     parseSVGTag(e, tagname);
                    // } else {
                    //     foreach (QString type, typeList) {
                    //         QDomNodeList list = e.elementsByTagName(type);
                    //         if(list.length()>0) {
                    //             for(int i=0; i<list.count(); i++) {
                    //                 QDomNode n=list.at(i);
                    //                 parseSVGTag(n.toElement(), n.nodeName());
                    //             }
                    //         }
                    //     }
                    // }
                // }
                // 下一个兄弟节点
                node = node.nextSibling();
            }
        }
    }
}

void SvgParser::parseNode(QDomNode n)
{
    if(!n.isElement()){
        return;
    }
    auto e = n.toElement();
    QString tagname = e.tagName();
    if(typeList.contains(tagname)) {
        parseSVGTag(e, tagname);
    } else {
        auto childs = e.childNodes();
        for (int i = 0; i < childs.count(); ++i) {
            parseNode(childs.item(i));
        }
    }
}

QList<QPainterPath> SvgParser::getSvgPathList() const
{
     return svgPathList;
}

// QSize matchSize(QString path)
// {
    // QSvgWidget svgWidget(path);
    // QSvgRenderer* render = svgWidget.renderer();
    // QSize size = render->defaultSize();
    // QRect rect = render->viewBox();
    // if(rect.size() != size) {
    //     size = rect.size();
    // }
    // return size;
//     return QSize();
// }

QImage SvgParser::getSvgImage()
{
    QImage image(getSize(), QImage::Format_ARGB32);
    image.fill(QColor(255,255,255,255));
    QPainter p;
    p.begin(&image);
    p.setPen(Qt::black);
    foreach (QPainterPath ppath, svgPathList) {
        p.drawPath(ppath);
    }
    p.end();
    return image;
}

QList<QList<QPointF> > SvgParser::getSvgPointList() const
{
     return svgPointList;
}

QSize SvgParser::getSize()
{
    if (width <= 0 || height <= 0) {
        QSvgRenderer render(filepath);
        return render.viewBox().size();
    }else{
        return {width, height};
    }
}

QList<SvgShape> SvgParser::getShapeList()
{
    return shapeList;
}
QMap<QString,QString> SvgParser::parseStyle(QString style){
    QMap<QString,QString> attr;
    auto attrList = style.split(";", Qt::SkipEmptyParts);
    foreach (auto item, attrList) {
        auto data = item.split(":");
        if (data.count() != 2) {
            continue;
        }
        attr[data[0].trimmed().toLower()] = data[1].trimmed();
    }
    return attr;
}

SvgShape SvgParser::getShapeStyle(QDomElement e)
{
    SvgShape shape;
    if (e.hasAttribute("stroke")) {
        shape.strokeColor = e.attribute("stroke");
    }
    if (e.hasAttribute("stroke-width")) {
        shape.strokeWidth = e.attribute("stroke-width").toInt();
    }
    if (e.hasAttribute("fill")) {
        auto fill = e.attribute("fill");
        if (fill.compare("none", Qt::CaseInsensitive) == 0 ||
            fill.compare("NaN", Qt::CaseInsensitive) == 0) {
            shape.fillFlag = false;
        }else{
            shape.fillColor = fill;
            shape.fillFlag = true;
        }
    }
    if (e.hasAttribute("style")) {
        auto style = e.attribute("style");
        auto attrList = parseStyle(style);
        if (attrList.contains("stroke")) {
            shape.strokeColor = attrList["stroke"];
        }
        if (attrList.contains("stroke-width")) {
            shape.strokeWidth = attrList["stroke-width"].toInt();
        }
        if (attrList.contains("fill")) {
            auto fill = attrList["fill"];
            if (fill.compare("none", Qt::CaseInsensitive) == 0 ||
                fill.compare("NaN", Qt::CaseInsensitive) == 0) {
                shape.fillFlag = false;
            }else{
                shape.fillColor = fill;
                shape.fillFlag = true;
            }
        }
    }
    return shape;
}

void SvgParser::parseSVGTag(QDomElement e, QString tagname)
{
    SvgShape shape = getShapeStyle(e);
    if(QString::compare(tagname, "path", Qt::CaseInsensitive) == 0) {   // 路径
        QString pathvalue = e.attribute("d");
        parseSvgPath(pathvalue, paintPath);
    } else if(QString::compare(tagname, "rect", Qt::CaseInsensitive) == 0) {
        float x = getValueWithoutUnit(e.attribute("x"));
        float y = getValueWithoutUnit(e.attribute("y"));
        float width = getValueWithoutUnit(e.attribute("width"));
        float height = getValueWithoutUnit(e.attribute("height"));
        float rx = getValueWithoutUnit(e.attribute("rx"));
        float ry = getValueWithoutUnit(e.attribute("rx"));

        if(rx<0||ry<0) {
            paintPath.moveTo(x, y);
            paintPath.lineTo(x+width, y);
            paintPath.lineTo(x+width, y+height);
            paintPath.lineTo(x, y+height);
            paintPath.lineTo(x, y);
            paintPath.moveTo(x, y);
            {
                QList<QPointF> list;
                list.append(QPointF(x,y));
                list.append(QPointF(x+width,y));
                list.append(QPointF(x+width,y+height));
                list.append(QPointF(x,y));
                svgPointList.append(list);
            }
        } else {
            float r = qMax(rx, ry);
            paintPath.moveTo(x+r, y);
            paintPath.lineTo(x+width-r, y);
            QRectF rect(x+width-2*r, y, 2*r, 2*r);
            paintPath.arcTo(rect, 90, -90);
            paintPath.lineTo(x+width, y+height-r);
            rect = QRectF(x+width-2*r, y+height-2*r, 2*r, 2*r);
            paintPath.arcTo(rect, 0, -90);
            paintPath.lineTo(x+r, y+height);
            rect = QRectF(x, y+height-2*r, 2*r, 2*r);
            paintPath.arcTo(rect, -90, -90);
            paintPath.lineTo(x, y+r);
            rect = QRectF(x, y, 2*r, 2*r);
            paintPath.arcTo(rect, 180, -90);
            paintPath.moveTo(x+r, y);
            {
                QPainterPath path;
                QList<QPointF> list;
                list.append(QPointF(x+r,y));
                list.append(QPointF(x+width-r,y));

                QRectF rect(x+width-2*r, y, 2*r, 2*r);
                path.moveTo(x+width-r,y);
                path.arcTo(rect, 90, -90);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));

                list.append(QPointF(x+width, y+height-r));

                path.clear();
                rect = QRectF(x+width-2*r, y+height-2*r, 2*r, 2*r);
                path.arcTo(rect, 0, -90);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));

                list.append(QPointF(x+r, y+height));

                path.clear();
                rect = QRectF(x, y+height-2*r, 2*r, 2*r);
                path.arcTo(rect, -90, -90);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));

                list.append(QPointF(x, y+r));

                path.clear();
                rect = QRectF(x, y, 2*r, 2*r);
                path.arcTo(rect, 180, -90);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));

                list.append(QPointF(x+r, y));

                svgPointList.append(list);
            }
        }
    } else if(QString::compare(tagname, "circle", Qt::CaseInsensitive) == 0) {
        float cx = getValueWithoutUnit(e.attribute("cx"));
        float cy = getValueWithoutUnit(e.attribute("cy"));
        float r = getValueWithoutUnit(e.attribute("r"));

        cx = cx<0 ? 0 : cx;
        cy = cy<0 ? 0 : cy;

        if(r>0) {
            paintPath.moveTo(cx+r, cy);
            paintPath.arcTo(cx-r, cy-r, 2*r, 2*r, 0, 360);
            paintPath.moveTo(cx+r, cy);
            {
                QPainterPath path;
                QList<QPointF> list;

                path.moveTo(cx+r, cy);
                path.arcTo(cx-r, cy-r, 2*r, 2*r, 0, 360);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));
                svgPointList.append(list);
            }
        }
    } else if(QString::compare(tagname, "ellipse", Qt::CaseInsensitive) == 0) {
        float cx = getValueWithoutUnit(e.attribute("cx"));
        float cy = getValueWithoutUnit(e.attribute("cy"));
        float rx = getValueWithoutUnit(e.attribute("rx"));
        float ry = getValueWithoutUnit(e.attribute("ry"));

        cx = cx<0 ? 0 : cx;
        cy = cy<0 ? 0 : cy;

        if(rx>0&&ry>0) {
            paintPath.moveTo(cx+rx, cy);
            paintPath.arcTo(cx-rx, cy-ry, 2*rx, 2*ry, 0, 360);
            paintPath.moveTo(cx+rx, cy);
            {
                QPainterPath path;
                QList<QPointF> list;

                path.moveTo(cx+rx, cy);
                path.arcTo(cx-rx, cy-ry, 2*rx, 2*ry, 0, 360);
                for(double i = 0; i < 1; i+=1.0/path.length()) list.append(path.pointAtPercent(i));
                list.append(path.pointAtPercent(1));
                svgPointList.append(list);
            }
        }
    } else if(QString::compare(tagname, "line", Qt::CaseInsensitive) == 0) {
        float x1 = getValueWithoutUnit(e.attribute("x1"));
        float y1 = getValueWithoutUnit(e.attribute("y1"));
        float x2 = getValueWithoutUnit(e.attribute("x2"));
        float y2 = getValueWithoutUnit(e.attribute("y2"));

        paintPath.moveTo(x1, y1);
        paintPath.lineTo(x2, y2);
        paintPath.moveTo(x2, y2);
        {
            QList<QPointF> list;
            list.append(QPointF(x1,y1));
            list.append(QPointF(x2,y2));
            svgPointList.append(list);
        }
    } else if(QString::compare(tagname, "polygon", Qt::CaseInsensitive) == 0) {
        QString value = e.attribute("points");
        QVector<float> vPos = segmentationCoordinates(value);

        QPointF startPoint;
        QList<QPointF> list;
        if(vPos.length()>1) {
            startPoint = QPointF(vPos[0], vPos[1]);
            paintPath.moveTo(startPoint);
            list.append(startPoint);
            vPos.removeFirst(); vPos.removeFirst();
        }

        while(vPos.length()/2>=1) {
            paintPath.lineTo(vPos[0], vPos[1]);
            list.append(QPointF(vPos[0], vPos[1]));
            vPos.removeFirst(); vPos.removeFirst();
        }

        if(!startPoint.isNull()) {
            paintPath.lineTo(startPoint);
            paintPath.moveTo(startPoint);
            list.append(startPoint);
        }
        if(!list.isEmpty()) svgPointList.append(list);

    } else if(QString::compare(tagname, "polyline", Qt::CaseInsensitive) == 0) {
        QString value = e.attribute("points");
        QVector<float> vPos = segmentationCoordinates(value);

        QPointF startPoint;
        QList<QPointF> list;
        if(vPos.length()>1) {
            startPoint = QPointF(vPos[0], vPos[1]);
            paintPath.moveTo(startPoint);
            list.append(startPoint);
            vPos.removeFirst(); vPos.removeFirst();
        }

        while(vPos.length()/2>=1) {
            paintPath.lineTo(vPos[0], vPos[1]);
            list.append(QPointF(vPos[0], vPos[1]));
            vPos.removeFirst(); vPos.removeFirst();
        }

        if(!startPoint.isNull()) {
            paintPath.moveTo(startPoint);
            //            list.append(startPoint);
        }
        if(!list.isEmpty()) svgPointList.append(list);

    }else if(QString::compare(tagname, "text", Qt::CaseInsensitive) == 0) {
        // text
        auto text = e.text();
        if (!text.isEmpty()) {
            qreal x = 0;
            auto attr = e.attribute("x");
            if (!attr.isEmpty()) {
                x = attr.toFloat();
            }
            qreal y = 0;
            attr = e.attribute("y");
            if (!attr.isEmpty()) {
                y = attr.toFloat();
            }
            QFont font;
            attr = e.attribute("font-family");
            if (!attr.isEmpty()) {
                font.setFamily(attr);
            }
            attr = e.attribute("font-size");
            if (!attr.isEmpty()) {
                font.setPointSizeF(attr.toFloat());
            }
            attr = e.attribute("font-style");
            if (!attr.isEmpty()) {
                if (attr.compare("italic") == 0){
                    font.setStyle(QFont::StyleItalic);
                }
            }
            attr = e.attribute("font-weight");
            if (!attr.isEmpty()) {
                if (attr.compare("bold") == 0){
                    font.setBold(true);
                }else if(attr.compare("thin") == 0){
                    font.setWeight(QFont::Thin);
                }else if(attr.compare("light") == 0){
                    font.setWeight(QFont::Light);
                }else if(attr.compare("medium") == 0){
                    font.setWeight(QFont::Medium);
                }
            }

            paintPath.addText(x, y, font, text);
        }
    }else if(QString::compare(tagname, "defs", Qt::CaseInsensitive) == 0) {
        // 丢弃
    }

    if(!paintPath.isEmpty()) {
        svgPathList.append(paintPath);
        shape.path = paintPath;
        shapeList.append(shape);
    }
    paintPath.clear();
    if(!testpathlist.isEmpty()) {
        svgPointList.append(testpathlist);
    }
    testpathlist.clear();
}

void SvgParser::parseSvgPath(QString path, QPainterPath &paintPath)
{
    QString cmdLine = "";
    foreach(QChar c, path) {
        if(cmdList.contains(c)) {
            if(!cmdLine.isEmpty()){
                dealParsePainter(paintPath, cmdLine);
                cmdLine.clear();
            }
        }
        cmdLine += c;
    }
    if(!cmdLine.isEmpty()){
        dealParsePainter(paintPath, cmdLine);
        cmdLine.clear();
    }
}

void SvgParser::dealParsePainter(QPainterPath &path, QString line)
{
    line = line.trimmed();
    int coordinates;
    QString cmd = line.mid(0, 1);
    QString value = line.mid(1);

    if(cmd.isUpper()) coordinates = ABSOLUTE_COORDINATES;
    else coordinates = RELATIVE_COORDINATES;


    QVector<float> vNum = segmentationCoordinates(value);

    switch(cmdTypeList.indexOf(cmd.toUpper().at(0))) {
    case 0:  // m
    {
        bool hasLineflag = vNum.length()>2;
        bool lineto = false;

        if(!path.isEmpty()) svgPathList.append(path);
        path.clear();
        if(!testpathlist.isEmpty()) svgPointList.append(testpathlist);
        testpathlist.clear();

        while(vNum.length()/2>=1) {

            QPointF point(vNum.at(0), vNum.at(1));
            if(coordinates == ABSOLUTE_COORDINATES){
                nowPositon = point;
                if(lineto) path.lineTo(nowPositon);
                else path.moveTo(nowPositon);
                testpathlist.append(nowPositon);
            } else {
                nowPositon = nowPositon + point;
                if(lineto) path.lineTo(nowPositon);
                else path.moveTo(nowPositon);
                testpathlist.append(nowPositon);
            }
            if(!lineto) pathStartPosition = nowPositon;



            for(int i=0; i<2; i++) vNum.removeFirst();
            if(hasLineflag) lineto = true;
        }
        break;
    }
    case 1:  // l
    {
        while(vNum.length()/2>=1) {
            QPointF point(vNum.at(0), vNum.at(1));
            if(coordinates == ABSOLUTE_COORDINATES){
                path.lineTo(point);
                testpathlist.append(point);
                nowPositon = point;
            } else {
                QPointF targetPoint = nowPositon + point;
                path.lineTo(targetPoint);
                testpathlist.append(targetPoint);
                nowPositon = targetPoint;
            }
            path.moveTo(nowPositon);
            for(int i=0; i<2; i++) vNum.removeFirst();
        }
        break;
    }
    case 2:  // h
    {
        while(vNum.length()>=1) {
            if(coordinates == ABSOLUTE_COORDINATES){
                QPointF point(vNum.at(0), nowPositon.y());
                path.lineTo(point);
                testpathlist.append(point);
                nowPositon = point;
            } else {
                QPointF point(nowPositon.x() + vNum.at(0), nowPositon.y());
                path.lineTo(point);
                testpathlist.append(point);
                nowPositon = point;
            }
            path.moveTo(nowPositon);
            vNum.removeFirst();
        }
        break;
    }
    case 3:  // v
    {
        while(vNum.length()>=1) {
            if(coordinates == ABSOLUTE_COORDINATES) {
                QPointF point(nowPositon.x(), vNum.at(0));
                path.lineTo(point);
                testpathlist.append(point);
                nowPositon = point;
            } else {
                QPointF point(nowPositon.x(), nowPositon.y() + vNum.at(0));
                path.lineTo(point);
                testpathlist.append(point);
                nowPositon = point;
            }
            path.moveTo(nowPositon);
            vNum.removeFirst();
        }
        break;
    }
    case 4:  // c
    {
        while(vNum.length()/6>=1) {
            QPointF startPoint = nowPositon;
            QPointF c1, c2, endPoint;
            if(coordinates == ABSOLUTE_COORDINATES){
                c1 = QPointF(vNum.at(0), vNum.at(1));
                c2 = QPointF(vNum.at(2), vNum.at(3));
                endPoint = QPointF(vNum.at(4), vNum.at(5));
            } else {
                float x = startPoint.x();
                float y = startPoint.y();
                c1 = QPointF(x + vNum.at(0), y + vNum.at(1));
                c2 = QPointF(x + vNum.at(2), y + vNum.at(3));
                endPoint = QPointF(x + vNum.at(4), y + vNum.at(5));
            }
            lastControlPosition = c2;
            path.moveTo(startPoint);
            path.cubicTo(c1, c2, endPoint);  // 三次贝塞尔曲线
            path.moveTo(endPoint);

            {
                QPainterPath testpath;

                testpath.moveTo(startPoint);
                testpath.cubicTo(c1, c2, endPoint);  // 三次贝塞尔曲线
                testpath.moveTo(endPoint);
                for(double i = 0; i <= 1; i+=1.0/testpath.length()) testpathlist.append(testpath.pointAtPercent(i));
            }

            nowPositon = endPoint;

            for(int i=0; i<6; i++) vNum.removeFirst();
        }
        break;
    }
    case 5:  // s
    {
        while(vNum.length()/4>=1) {
            QPointF startPoint = nowPositon;
            QPointF c1, c2, endPoint;
            if(coordinates == ABSOLUTE_COORDINATES){
                float x = startPoint.x();
                float y = startPoint.y();
                c1 = QPointF(2*x-lastControlPosition.x(), 2*y-lastControlPosition.y());
                c2 = QPointF(vNum.at(0), vNum.at(1));
                endPoint = QPointF(vNum.at(2), vNum.at(3));
            } else {
                float x = startPoint.x();
                float y = startPoint.y();
                c1 = QPointF(x+x-lastControlPosition.x(), y+y-lastControlPosition.y());
                c2 = QPointF(x + vNum.at(0), y + vNum.at(1));
                endPoint = QPointF(x + vNum.at(2), y + vNum.at(3));
            }
            lastControlPosition = c2;
            path.moveTo(startPoint);
            path.cubicTo(c1, c2, endPoint);  // 三次贝塞尔曲线
            path.moveTo(endPoint);

            {
                QPainterPath testpath;

                testpath.moveTo(startPoint);
                testpath.cubicTo(c1, c2, endPoint);  // 三次贝塞尔曲线
                testpath.moveTo(endPoint);
                for(double i = 0; i <= 1; i+=1.0/testpath.length()) testpathlist.append(testpath.pointAtPercent(i));
            }

            nowPositon = endPoint;

            for(int i=0; i<4; i++) vNum.removeFirst();
        }

        break;
    }
    case 6:  // q
    {
        while(vNum.length()/4>=1) {
            QPointF startPoint = nowPositon;
            QPointF cPoint;
            QPointF endPoint;
            if(coordinates == ABSOLUTE_COORDINATES) {
                cPoint = QPointF(vNum.at(0), vNum.at(1));
                endPoint = QPointF(vNum.at(2), vNum.at(3));
            } else {
                float x = startPoint.x();
                float y = startPoint.y();
                cPoint = QPointF(x + vNum.at(0), y + vNum.at(1));
                endPoint = QPointF(x + vNum.at(2), y + vNum.at(3));
            }
            lastControlPosition = cPoint;
            path.moveTo(startPoint);
            path.quadTo(cPoint, endPoint);    // 二次贝塞尔曲线
            path.moveTo(endPoint);

            {
                QPainterPath testpath;

                testpath.moveTo(startPoint);
                testpath.quadTo(cPoint, endPoint);    // 二次贝塞尔曲线
                testpath.moveTo(endPoint);
                for(double i = 0; i <= 1; i+=1.0/testpath.length()) testpathlist.append(testpath.pointAtPercent(i));
            }

            nowPositon = endPoint;

            for(int i=0; i<4; i++) vNum.removeFirst();
        }
        break;
    }
    case 7:  // t
    {
        while(vNum.length()/2>=1) {
            QPointF startPoint = nowPositon;
            QPointF cPoint;
            QPointF endPoint;
            if(coordinates == ABSOLUTE_COORDINATES){
                float x = startPoint.x();
                float y = startPoint.y();
                cPoint = QPointF(2*x-lastControlPosition.x(), 2*y-lastControlPosition.y());
                endPoint = QPointF(vNum.at(0), vNum.at(1));
            } else {
                float x = startPoint.x();
                float y = startPoint.y();
                cPoint = QPointF(x+x-lastControlPosition.x(), y+y-lastControlPosition.y());
                endPoint = QPointF(x + vNum.at(0), y + vNum.at(1));
            }
            lastControlPosition = cPoint;
            path.moveTo(startPoint);
            path.quadTo(cPoint, endPoint);    // 二次贝塞尔曲线
            path.moveTo(endPoint);

            {
                QPainterPath testpath;

                testpath.moveTo(startPoint);
                testpath.quadTo(cPoint, endPoint);    // 二次贝塞尔曲线
                testpath.moveTo(endPoint);
                for(double i = 0; i <= 1; i+=1.0/testpath.length()) testpathlist.append(testpath.pointAtPercent(i));
            }

            nowPositon = endPoint;

            for(int i=0; i<2; i++) vNum.removeFirst();
        }
        break;
    }
    case 8:  // a
    {
        while(vNum.length()/7>=1) {
            QPointF startPoint = nowPositon;
            float rx = vNum.at(0);
            float ry = vNum.at(1);
            float x_axis_rotation = vNum.at(2);
            float large_arc_flag = vNum.at(3);
            float sweep_flag = vNum.at(4);
            QPointF endPoint;

            double cx;
            double cy;
            double start_angle;
            double delta_angle;

            if(coordinates == ABSOLUTE_COORDINATES){
                endPoint = QPointF(vNum.at(5), vNum.at(6));
            } else {
                float x = startPoint.x();
                float y = startPoint.y();
                endPoint = QPointF(x+vNum.at(5), y+vNum.at(6));
            }

            // svg : [A | a] (rx ry x-axis-rotation large-arc-flag sweep-flag x y)+
            // x1 y1 rx ry φ fA fS x2 y2
            svgArcToCenterParam(startPoint.x(), startPoint.y(), rx, ry, x_axis_rotation, large_arc_flag, sweep_flag, endPoint.x(), endPoint.y(),
                                cx, cy, start_angle, delta_angle);

            start_angle = qRadiansToDegrees(start_angle);
            delta_angle = qRadiansToDegrees(delta_angle);

            QRectF rect(cx-rx, cy-ry, 2*rx, 2*ry);

            if(delta_angle != 0) {
                path.moveTo(startPoint);
                path.arcTo(rect, 360-start_angle, -delta_angle);     // 绘图的坐标系与笛卡尔坐标系不同, 需要转换

                {
                    QPainterPath testpath;

                    testpath.moveTo(startPoint);
                    testpath.arcTo(rect, 360-start_angle, -delta_angle);
                    testpath.moveTo(endPoint);
                    for(double i = 0; i <= 1; i+=1.0/testpath.length()) testpathlist.append(testpath.pointAtPercent(i));
                }
            }
            path.moveTo(endPoint);

            nowPositon = endPoint;

            for(int i=0; i<7; i++) vNum.removeFirst();
        }

        break;
    }
    case 9:  // z
        path.lineTo(pathStartPosition);
        testpathlist.append(pathStartPosition);
        break;
    }
}

QVector<float> SvgParser::segmentationCoordinates(QString value)
{
    // 将科学记数法暂时替换, 防止分割出错
    if(value.contains("e", Qt::CaseInsensitive)) {
        value.replace("e-", "[KXJSFF]");
        value.replace("E-", "[KXJSFF]");
    }

    if(value.contains(" -")){
        value.replace(" -"," [KGFS]");
    }

    if(value.contains(",-")){
        value.replace(",-",",[DHFS]");
    }


    QVector<float> vPos;
    QString num = "";
    foreach(QChar c, value) {
        if(splitList.contains(c)) {
            num = num.trimmed();
            if(!num.isEmpty()) {
                if(num.contains(',')) num.remove(',');
                vPos.append(getValueWithoutUnit(num));
                num.clear();
            }
        }
        num += c;
    }
    num = num.trimmed();
    if(num.contains(',')) num.remove(',');
    if(!num.isEmpty()) vPos.append(getValueWithoutUnit(num));
    return vPos;
}

float SvgParser::getValueWithoutUnit(QString input)
{
    // 将科学记数法替换回来
    if(input.contains("[KXJSFF]")) input.replace("[KXJSFF]", "e-");
    if(input.contains("[KGFS]")) input.replace("[KGFS]","-");
    if(input.contains("[DHFS]")) input.replace("[DHFS]","-");

    if(input.isEmpty()) return -1;
    QString str = input;
    foreach(QString unit, unitList) {
        if(str.contains(unit)) {
            str.remove(unit);
        }
    }
    return str.toFloat();
}

double SvgParser::radian(double ux, double uy, double vx, double vy)
{
    double  dot = ux * vx + uy * vy;
    double  mod = sqrt( ( ux * ux + uy * uy ) * ( vx * vx + vy * vy ) );
    double  rad = acos( dot / mod );
    if( ux * vy - uy * vx < 0.0 ) rad = -rad;
    return  rad;
}

int SvgParser::svgArcToCenterParam(double x1, double y1, double rx, double ry, double phi, double fA, double fS, double x2, double y2, double &cx_out, double &cy_out, double &startAngle_out, double &deltaAngle_out)
{
    double cx, cy, startAngle, deltaAngle, endAngle;
    double PIx2 =  M_PI * 2.0;

    if (rx < 0) {
        rx = -rx;
    }
    if (ry < 0) {
        ry = -ry;
    }
    if (rx == 0.0 || ry == 0.0) {  // invalid arguments
        return -1;
    }

    double s_phi = sin(phi);
    double c_phi = cos(phi);
    double hd_x = (x1 - x2) / 2.0;  // half diff of x
    double hd_y = (y1 - y2) / 2.0;  // half diff of y
    double hs_x = (x1 + x2) / 2.0;  // half sum of x
    double hs_y = (y1 + y2) / 2.0;  // half sum of y

    // F6.5.1
    double x1_ = c_phi * hd_x + s_phi * hd_y;
    double y1_ = c_phi * hd_y - s_phi * hd_x;

    // F.6.6 Correction of out-of-range radii
    //   Step 3: Ensure radii are large enough
    double lambda = (x1_ * x1_) / (rx * rx) + (y1_ * y1_) / (ry * ry);
    if (lambda > 1) {
        rx = rx * sqrt(lambda);
        ry = ry * sqrt(lambda);
    }

    double rxry = rx * ry;
    double rxy1_ = rx * y1_;
    double ryx1_ = ry * x1_;
    double sum_of_sq = rxy1_ * rxy1_ + ryx1_ * ryx1_;  // sum of square
    if (!sum_of_sq) {
        return -1;
    }
    double coe = sqrt(abs((rxry * rxry - sum_of_sq) / sum_of_sq));
    if (fA == fS) { coe = -coe; }

    // F6.5.2
    double cx_ = coe * rxy1_ / ry;
    double cy_ = -coe * ryx1_ / rx;

    // F6.5.3
    cx = c_phi * cx_ - s_phi * cy_ + hs_x;
    cy = s_phi * cx_ + c_phi * cy_ + hs_y;

    double xcr1 = (x1_ - cx_) / rx;
    double xcr2 = (x1_ + cx_) / rx;
    double ycr1 = (y1_ - cy_) / ry;
    double ycr2 = (y1_ + cy_) / ry;

    // F6.5.5
    startAngle = radian(1.0, 0.0, xcr1, ycr1);

    // F6.5.6
    deltaAngle = radian(xcr1, ycr1, -xcr2, -ycr2);
    while (deltaAngle > PIx2) { deltaAngle -= PIx2; }
    while (deltaAngle < 0.0) { deltaAngle += PIx2; }
    if (fS == false || fS == 0) { deltaAngle -= PIx2; }
    endAngle = startAngle + deltaAngle;
    while (endAngle > PIx2) { endAngle -= PIx2; }
    while (endAngle < 0.0) { endAngle += PIx2; }

    cx_out = cx;
    cy_out = cy;
    startAngle_out = startAngle;
    deltaAngle_out = deltaAngle;

    return 1;
}

double SvgParser::get_angle_with_points(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double theta = atan2(x1 - x3, y1 - y3) - atan2(x2 - x3, y2 - y3);
    if (theta > M_PI)
        theta -= 2 * M_PI;
    if (theta < -M_PI)
        theta += 2 * M_PI;

    theta = abs(theta * 180.0 / M_PI);

    if(y2<=y3) {
        theta = 360.0 - theta;
    }

    return theta;
}
