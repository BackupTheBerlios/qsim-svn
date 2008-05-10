/********************************************************************************
** Form generated from reading ui file 'configdialog.ui'
**
** Created: Sat 10. May 10:51:35 2008
**      by: Qt User Interface Compiler version 4.4.0-rc1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QSpacerItem *spacerItem;
    QTabWidget *simulation_tab;
    QWidget *tab;
    QWidget *widget;
    QWidget *widget1;
    QGridLayout *gridLayout;
    QDoubleSpinBox *doubleSpinBox_3;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_6;
    QCheckBox *draw_potential;
    QWidget *tab1;
    QWidget *widget2;
    QGridLayout *gridLayout1;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_5;

    void setupUi(QDialog *ConfigDialog)
    {
    if (ConfigDialog->objectName().isEmpty())
        ConfigDialog->setObjectName(QString::fromUtf8("ConfigDialog"));
    ConfigDialog->resize(531, 338);
    layoutWidget = new QWidget(ConfigDialog);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(435, 9, 87, 320));
    vboxLayout = new QVBoxLayout(layoutWidget);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    okButton = new QPushButton(layoutWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    vboxLayout->addWidget(okButton);

    cancelButton = new QPushButton(layoutWidget);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    vboxLayout->addWidget(cancelButton);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout->addItem(spacerItem);

    simulation_tab = new QTabWidget(ConfigDialog);
    simulation_tab->setObjectName(QString::fromUtf8("simulation_tab"));
    simulation_tab->setGeometry(QRect(9, 9, 420, 320));
    tab = new QWidget();
    tab->setObjectName(QString::fromUtf8("tab"));
    widget = new QWidget(tab);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(70, 40, 194, 109));
    widget1 = new QWidget(tab);
    widget1->setObjectName(QString::fromUtf8("widget1"));
    widget1->setGeometry(QRect(10, 10, 194, 83));
    gridLayout = new QGridLayout(widget1);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
    gridLayout->setMargin(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    doubleSpinBox_3 = new QDoubleSpinBox(widget1);
    doubleSpinBox_3->setObjectName(QString::fromUtf8("doubleSpinBox_3"));

    gridLayout->addWidget(doubleSpinBox_3, 2, 1, 1, 1);

    label_7 = new QLabel(widget1);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    gridLayout->addWidget(label_7, 2, 0, 1, 1);

    doubleSpinBox_2 = new QDoubleSpinBox(widget1);
    doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));

    gridLayout->addWidget(doubleSpinBox_2, 1, 1, 1, 1);

    label_6 = new QLabel(widget1);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    gridLayout->addWidget(label_6, 1, 0, 1, 1);

    draw_potential = new QCheckBox(widget1);
    draw_potential->setObjectName(QString::fromUtf8("draw_potential"));

    gridLayout->addWidget(draw_potential, 0, 0, 1, 2);

    simulation_tab->addTab(tab, QString());
    tab1 = new QWidget();
    tab1->setObjectName(QString::fromUtf8("tab1"));
    widget2 = new QWidget(tab1);
    widget2->setObjectName(QString::fromUtf8("widget2"));
    widget2->setGeometry(QRect(20, 10, 151, 130));
    gridLayout1 = new QGridLayout(widget2);
#ifndef Q_OS_MAC
    gridLayout1->setSpacing(6);
#endif
    gridLayout1->setMargin(0);
    gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
    gridLayout1->setContentsMargins(0, 0, 0, 0);
    label_3 = new QLabel(widget2);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    gridLayout1->addWidget(label_3, 2, 0, 1, 1);

    label = new QLabel(widget2);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout1->addWidget(label, 0, 0, 1, 1);

    label_2 = new QLabel(widget2);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    gridLayout1->addWidget(label_2, 1, 0, 1, 1);

    label_4 = new QLabel(widget2);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    gridLayout1->addWidget(label_4, 3, 0, 1, 1);

    doubleSpinBox = new QDoubleSpinBox(widget2);
    doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));

    gridLayout1->addWidget(doubleSpinBox, 0, 1, 1, 1);

    label_5 = new QLabel(widget2);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    gridLayout1->addWidget(label_5, 4, 0, 1, 1);

    simulation_tab->addTab(tab1, QString());

    retranslateUi(ConfigDialog);
    QObject::connect(okButton, SIGNAL(clicked()), ConfigDialog, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), ConfigDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(ConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ConfigDialog)
    {
    ConfigDialog->setWindowTitle(QApplication::translate("ConfigDialog", "ConfigDialog", 0, QApplication::UnicodeUTF8));
    ConfigDialog->setWindowIconText(QString());
    okButton->setText(QApplication::translate("ConfigDialog", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("ConfigDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("ConfigDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("ConfigDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    draw_potential->setText(QApplication::translate("ConfigDialog", "Desenhar campo potencial", 0, QApplication::UnicodeUTF8));
    simulation_tab->setTabText(simulation_tab->indexOf(tab), QApplication::translate("ConfigDialog", "Simulador", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("ConfigDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("ConfigDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Tamanho</p></body></html>", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("ConfigDialog", "<html><head><meta name=\"qrichtext\" content=\"1\" /></head><body style=\" white-space: pre-wrap; font-family:Sans Serif; font-weight:400; font-style:normal; text-decoration:none;\"><p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Cor</p></body></html>", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("ConfigDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("ConfigDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
    simulation_tab->setTabText(simulation_tab->indexOf(tab1), QApplication::translate("ConfigDialog", "Agentes", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(ConfigDialog);
    } // retranslateUi

};

namespace Ui {
    class ConfigDialog: public Ui_ConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
