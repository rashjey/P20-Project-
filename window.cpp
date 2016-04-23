#include "window.h"
#include "ui_window.h"
#include "rec.h"

#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QPainter>
#include <vector>
#include <QTime>
#include <QPoint>
#include <QString>

extern std::vector<QLine> middleman;
extern std::vector<QColor> middlecolour;
extern bool middledata;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    clicked = false;

    QTimer *timings = new QTimer(this);
    connect(timings, SIGNAL(timeout()), this, SLOT(time_overflow()));
    timings->start(50);

    ui->setupUi(this);

    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    colour = Qt::black;
}

void Window::paintEvent(QPaintEvent *event)
{
    qDebug() << "paint loop";
    QPainter painter(this);
    QPen pen(colour);
    QFont font;
    font.setPixelSize(15);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setFont(font);
//    connect(timings, SIGNAL(update()), this, SLOT(rec::ScreenUpdated()));

    for(int i=0;i<l.size();i++)
    {
        painter.setPen(ShadesOfRainbow[i]);
        painter.drawLine(l[i]);
    }
}

void Window::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "click";
    clicked = true;
    x1 = event->x();
    y1 = event->y();
    x2 = event->x();
    y2 = event->y();
}

void Window::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "unclick";
    clicked = false;

    x2 = event->x();
    y2 = event->y();
    l.push_back(QLine(x1,y1,x2,y2));
    ShadesOfRainbow.push_back(colour);
    pass_x1 = x1;
    pass_y1 = y1;
    pass_x2 = x2;
    pass_y2 = y2;
    DataAhoy = true;
}

void Window::mouseMoveEvent(QMouseEvent *event)
{
    //qDebug() << "move+click";
    x2 = event->x();
    y2 = event->y();
    update(); // ?
}

void Window::time_overflow()
{
    qDebug() << "time";
    if(clicked)
    {
        l.push_back(QLine(x1,y1,x2,y2));
        ShadesOfRainbow.push_back(colour);
        pass_x1 = x1;
        pass_y1 = y1;
        pass_x2 = x2;
        pass_y2 = y2;
        DataAhoy = true;
        x1 = x2;
        y1 = y2;
        update();
    }
}

Window::~Window()
{
    delete ui;
}


void Window::on_actionClear_triggered()
{
    qDebug() << "cleary";
    l.clear();
    update();
}

void Window::on_actionUndo_triggered()
{
    qDebug() << "undodo";
    l.pop_back();
    update();
}

void Window::on_actionBlack_triggered()
{
    colour = Qt::black;
}

void Window::on_actionRed_triggered()
{
    colour = Qt::red;
}

void Window::on_actionBlue_triggered()
{
    colour = Qt::blue;
}

void Window::on_actionGreen_triggered()
{
    colour = Qt::green;
}

void Window::on_actionPurple_triggered()
{
    colour = QColor(160,32,240);
}

void Window::on_actionYellow_triggered()
{
    colour = Qt::yellow;
}

void Window::on_actionOrange_triggered()
{
    colour = QColor(255, 165, 0);
}
