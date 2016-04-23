#include "rec.h"
#include "ui_rec.h"
#include "window.h"

#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QPainter>
#include <vector>

extern std::vector<QLine> middleman;
extern std::vector<QColor> middlecolour;
extern bool middledata;

rec::rec(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::rec)
{
    ui->setupUi(this);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void rec::paintEvent(QPaintEvent *event)
{
    qDebug() << "paint loop";
    QPainter painter(this);
    QPen pen;
    QFont font;
    font.setPixelSize(15);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);

    for(int i=0;i<getl.size();i++)
    {
        painter.setPen(getcolour[i]);
        painter.drawLine(getl[i]);
    }
}

//void rec::getDraw()
//{
//    int y= w::l.size();
//    for(int i=0;i<y;i++)
//    {
//        getl[i]= w.l;
//    }
//}

void rec::ScreenUpdated()
{
    qDebug() << "passing";
}

rec::~rec()
{
    delete ui;
}
