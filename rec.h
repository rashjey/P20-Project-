#ifndef REC_H
#define REC_H

#include <QMainWindow>
#include <QLine>
#include <vector>

namespace Ui {
class rec;
}

class rec : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit rec(QWidget *parent = 0);
    ~rec();
//    void getDraw();
    std::vector<QLine> getl;
    std::vector<QColor> getcolour;

protected:
    void paintEvent(QPaintEvent * event);
    
public slots:
    void ScreenUpdated();

private:
    Ui::rec *ui;
};

#endif // REC_H
