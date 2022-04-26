#ifndef STATISTIQUE_EMP_H
#define STATISTIQUE_EMP_H

#include <QWidget>

namespace Ui {
class statistique_emp;


class statistique_emp : public QWidget
{
    Q_OBJECT

public:
    explicit statistique_emp(QWidget *parent = nullptr);
    ~statistique_emp();

private:
    statistique_emp *ui;
};
}
#endif // STATISTIQUE_EMP_H
