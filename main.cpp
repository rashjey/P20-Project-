#include <QApplication>
#include <QDebug>

#include <pthread.h>
//#include <wiringPi.h>

#include "window.h"
#include "rec.h"

std::vector<QLine> middleman;
std::vector<QColor> middlecolour;
bool middledata;

void* worker(void* thread_id)
{
    long tid = (long)thread_id;
    // do something....
    qDebug() << "Worker thread " << tid << "started.";

    //qDebug() << "get x1: " << w.x1;

    // end thread
    pthread_exit(NULL);
}

void* send(void* windo)
{
    Window* w = (Window*)windo;
    while(true)
    {
        if(w->DataAhoy)
        {
            middleman.push_back(QLine(w->pass_x1,w->pass_y1,w->pass_x2,w->pass_y2));
            middlecolour.push_back(w->colour);
            w->DataAhoy = false;
            middledata = true;
        }
    }
    // end thread
    pthread_exit(NULL);
}

void* recieve(void* recev)
{
    rec* r = (rec*)recev;
    while(true)
    {
        if(middledata)
        {
            int i = middleman.size();
            r->getl.push_back( middleman[i-1] );
            r->getcolour.push_back( middlecolour[i-1] );
            r->update();
            middledata = false;
        }
    }

    // end thread
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    // setup GPIO interface - uncomment when needed
    // needs to run with root via sudo in terminal.
    //wiringPiSetup();
    //pinMode (0, OUTPUT);

    // setup Qt GUI
    QApplication a(argc, argv);
    Window w;
    w.show();
    rec r;
    r.show();
    // QObject::connect(w.timer, SIGNAL(timeout()), &r, SLOT(r.ScreenUpdated()));

    // starting worker thread(s)
    int rc;
    pthread_t worker_thread;
    rc = pthread_create(&worker_thread, NULL, worker, (void*)1);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }
    pthread_t send_thread;
    rc = pthread_create(&send_thread, NULL, send, (void*)&w);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }
    pthread_t rec_thread;
    rc = pthread_create(&rec_thread, NULL, recieve, (void*)&r);
    if (rc) {
        qDebug() << "Unable to start worker thread.";
        exit(1);
    }

    // start window event loop
    qDebug() << "Starting event loop...";
    int ret = a.exec();
    qDebug() << "Event loop stopped.";

    // cleanup pthreads
    pthread_exit(NULL);

    // exit
    return ret;
}
