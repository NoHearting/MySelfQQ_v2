#ifndef MYSPLITTER_H
#define MYSPLITTER_H

#include <QWidget>
#include <QSplitter>


class MySplitter : public QSplitter
{
    Q_OBJECT
public:
    explicit MySplitter(QWidget *parent = nullptr);

    void moveSplitter(int pos, int index);

signals:

public slots:
};

#endif // MYSPLITTER_H
