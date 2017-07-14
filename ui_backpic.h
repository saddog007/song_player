/********************************************************************************
** Form generated from reading UI file 'backpicp11096.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BACKPICP11096_H
#define BACKPICP11096_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_BackPic
{
public:

    void setupUi(QDialog *BackPic)
    {
        if (BackPic->objectName().isEmpty())
            BackPic->setObjectName(QStringLiteral("BackPic"));
        BackPic->resize(290, 380);

        retranslateUi(BackPic);

        QMetaObject::connectSlotsByName(BackPic);
    } // setupUi

    void retranslateUi(QDialog *BackPic)
    {
        BackPic->setWindowTitle(QApplication::translate("BackPic", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class BackPic: public Ui_BackPic {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BACKPICP11096_H
