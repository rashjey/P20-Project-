#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPixmap>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QTimer>
#include <vector>
#include <QString>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Window(QWidget *parent = 0);
    ~Window();

    bool clicked;
    QTimer *timer;
    QColor colour;

    std::vector<QLine> l;
    std::vector<QColor> ShadesOfRainbow;

    int x1;
    int y1;
    int x2;
    int y2;
    int pass_x1;
    int pass_y1;
    int pass_x2;
    int pass_y2;

    bool DataAhoy;

public slots:
    void time_overflow();


protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent * event);
    
private slots:
    void on_actionClear_triggered();

    void on_actionUndo_triggered();

    void on_actionBlack_triggered();

    void on_actionRed_triggered();

    void on_actionBlue_triggered();

    void on_actionGreen_triggered();

    void on_actionPurple_triggered();

    void on_actionYellow_triggered();

    void on_actionOrange_triggered();

private:
    Ui::Window *ui;
};

#endif // WINDOW_H
