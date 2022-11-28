/********************************************************************************
** Form generated from reading UI file 'mapeditor.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEDITOR_H
#define UI_MAPEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapEditor
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton_7;
    QListWidget *listWidget;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton_5;
    QPushButton *pushButton_8;
    QLabel *label_6;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QListWidget *listWidget_4;
    QComboBox *comboBox;
    QTextEdit *textEdit_2;
    QComboBox *comboBox_2;
    QListWidget *listWidget_5;
    QTextEdit *textEdit_3;
    QListWidget *listWidget_7;
    QListWidget *listWidget_8;
    QTextEdit *textEdit;
    QPushButton *pushButton_14;
    QPushButton *pushButton_19;
    QPushButton *pushButton_20;
    QPushButton *pushButton_21;

    void setupUi(QMainWindow *MapEditor)
    {
        if (MapEditor->objectName().isEmpty())
            MapEditor->setObjectName(QString::fromUtf8("MapEditor"));
        MapEditor->resize(1600, 840);
        MapEditor->setMinimumSize(QSize(1600, 840));
        MapEditor->setMaximumSize(QSize(1600, 840));
        QPalette palette;
        QBrush brush(QColor(0, 255, 127, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        MapEditor->setPalette(palette);
        centralWidget = new QWidget(MapEditor);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 130, 131, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        pushButton->setFont(font);
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 230, 131, 41));
        pushButton_2->setFont(font);
        pushButton_2->setAutoDefault(false);
        pushButton_2->setFlat(false);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(40, 180, 131, 41));
        pushButton_3->setFont(font);
        pushButton_3->setAutoDefault(false);
        pushButton_3->setFlat(false);
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(40, 280, 131, 41));
        pushButton_4->setFont(font);
        pushButton_4->setAutoDefault(false);
        pushButton_4->setFlat(false);
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(40, 480, 131, 71));
        pushButton_6->setFont(font);
        pushButton_6->setAcceptDrops(true);
        pushButton_6->setFlat(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(430, 780, 461, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(14);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 560, 101, 31));
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(40, 610, 141, 31));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(40, 330, 131, 41));
        pushButton_7->setFont(font);
        pushButton_7->setAutoDefault(false);
        pushButton_7->setFlat(false);
        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(1230, 430, 331, 341));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1230, 330, 331, 51));
        label_4->setFont(font1);
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setWordWrap(true);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(1230, 380, 331, 51));
        label_5->setFont(font1);
        label_5->setAlignment(Qt::AlignCenter);
        label_5->setWordWrap(true);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(40, 380, 131, 41));
        pushButton_5->setFont(font);
        pushButton_5->setAutoDefault(false);
        pushButton_5->setFlat(false);
        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(40, 430, 131, 41));
        pushButton_8->setFont(font);
        pushButton_8->setAutoDefault(false);
        pushButton_8->setFlat(false);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(350, 20, 681, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(18);
        label_6->setFont(font2);
        label_6->setAlignment(Qt::AlignCenter);
        pushButton_9 = new QPushButton(centralWidget);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(1070, 30, 131, 41));
        pushButton_9->setFont(font);
        pushButton_10 = new QPushButton(centralWidget);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(190, 30, 131, 41));
        pushButton_10->setFont(font);
        pushButton_10->setStyleSheet(QString::fromUtf8(""));
        pushButton_11 = new QPushButton(centralWidget);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(190, 770, 131, 41));
        pushButton_11->setFont(font);
        pushButton_12 = new QPushButton(centralWidget);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(1060, 770, 131, 41));
        pushButton_12->setFont(font);
        pushButton_13 = new QPushButton(centralWidget);
        pushButton_13->setObjectName(QString::fromUtf8("pushButton_13"));
        pushButton_13->setGeometry(QRect(30, 770, 131, 41));
        pushButton_13->setFont(font);
        listWidget_4 = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget_4);
        listWidget_4->setObjectName(QString::fromUtf8("listWidget_4"));
        listWidget_4->setGeometry(QRect(1230, 220, 51, 41));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(1290, 220, 161, 41));
        textEdit_2 = new QTextEdit(centralWidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(1290, 120, 161, 41));
        comboBox_2 = new QComboBox(centralWidget);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(1290, 270, 161, 41));
        listWidget_5 = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget_5);
        listWidget_5->setObjectName(QString::fromUtf8("listWidget_5"));
        listWidget_5->setGeometry(QRect(1230, 270, 51, 41));
        textEdit_3 = new QTextEdit(centralWidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(1290, 170, 161, 41));
        listWidget_7 = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget_7);
        listWidget_7->setObjectName(QString::fromUtf8("listWidget_7"));
        listWidget_7->setGeometry(QRect(1230, 120, 51, 41));
        listWidget_8 = new QListWidget(centralWidget);
        new QListWidgetItem(listWidget_8);
        listWidget_8->setObjectName(QString::fromUtf8("listWidget_8"));
        listWidget_8->setGeometry(QRect(1230, 170, 51, 41));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(1290, 70, 161, 41));
        pushButton_14 = new QPushButton(centralWidget);
        pushButton_14->setObjectName(QString::fromUtf8("pushButton_14"));
        pushButton_14->setGeometry(QRect(1460, 120, 101, 41));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font3.setPointSize(11);
        pushButton_14->setFont(font3);
        pushButton_19 = new QPushButton(centralWidget);
        pushButton_19->setObjectName(QString::fromUtf8("pushButton_19"));
        pushButton_19->setGeometry(QRect(1460, 170, 101, 41));
        pushButton_19->setFont(font3);
        pushButton_20 = new QPushButton(centralWidget);
        pushButton_20->setObjectName(QString::fromUtf8("pushButton_20"));
        pushButton_20->setGeometry(QRect(1460, 220, 101, 41));
        pushButton_20->setFont(font3);
        pushButton_21 = new QPushButton(centralWidget);
        pushButton_21->setObjectName(QString::fromUtf8("pushButton_21"));
        pushButton_21->setGeometry(QRect(1460, 270, 101, 41));
        pushButton_21->setFont(font3);
        MapEditor->setCentralWidget(centralWidget);

        retranslateUi(MapEditor);

        pushButton->setDefault(false);
        pushButton_2->setDefault(false);
        pushButton_3->setDefault(false);
        pushButton_4->setDefault(false);
        pushButton_7->setDefault(false);
        pushButton_5->setDefault(false);
        pushButton_8->setDefault(false);


        QMetaObject::connectSlotsByName(MapEditor);
    } // setupUi

    void retranslateUi(QMainWindow *MapEditor)
    {
        MapEditor->setWindowTitle(QCoreApplication::translate("MapEditor", "\345\260\217\351\225\207\345\234\260\345\233\276\347\274\226\350\276\221\345\231\250", nullptr));
        pushButton->setText(QCoreApplication::translate("MapEditor", "\346\267\273\345\212\240\347\202\271", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MapEditor", "\346\267\273\345\212\240\350\267\257\345\276\204", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MapEditor", "\345\210\240\351\231\244\347\202\271", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MapEditor", "\345\210\240\351\231\244\350\267\257\345\276\204", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MapEditor", "\346\261\202\346\211\200\346\234\211\350\267\257\345\276\204", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("MapEditor", "\347\202\271\346\225\260\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MapEditor", "\350\267\257\345\276\204\346\225\260\357\274\232", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MapEditor", "\347\274\226\350\276\221\347\202\271\346\240\207\347\255\276", nullptr));
        label_4->setText(QString());
        label_5->setText(QString());
        pushButton_5->setText(QCoreApplication::translate("MapEditor", "\344\277\256\346\224\271\350\267\257\345\276\204\351\225\277", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MapEditor", "\346\230\276\347\244\272\350\267\257\345\276\204\351\225\277", nullptr));
        label_6->setText(QCoreApplication::translate("MapEditor", "\345\260\217\351\225\207\345\234\260\345\233\276", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MapEditor", "\344\277\256\346\224\271\346\240\207\351\242\230", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MapEditor", "\346\270\205\351\231\244\345\234\260\345\233\276", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MapEditor", "\350\275\275\345\205\245\345\234\260\345\233\276", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MapEditor", "\344\277\235\345\255\230\345\234\260\345\233\276", nullptr));
        pushButton_13->setText(QCoreApplication::translate("MapEditor", "\346\233\264\346\215\242\350\203\214\346\231\257", nullptr));

        const bool __sortingEnabled = listWidget_4->isSortingEnabled();
        listWidget_4->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_4->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("MapEditor", "\350\265\267\347\202\271", nullptr));
        listWidget_4->setSortingEnabled(__sortingEnabled);

        textEdit_2->setHtml(QCoreApplication::translate("MapEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));

        const bool __sortingEnabled1 = listWidget_5->isSortingEnabled();
        listWidget_5->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = listWidget_5->item(0);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("MapEditor", "\347\273\210\347\202\271", nullptr));
        listWidget_5->setSortingEnabled(__sortingEnabled1);

        textEdit_3->setHtml(QCoreApplication::translate("MapEditor", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));

        const bool __sortingEnabled2 = listWidget_7->isSortingEnabled();
        listWidget_7->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = listWidget_7->item(0);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("MapEditor", "\347\273\217\345\272\246", nullptr));
        listWidget_7->setSortingEnabled(__sortingEnabled2);


        const bool __sortingEnabled3 = listWidget_8->isSortingEnabled();
        listWidget_8->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem3 = listWidget_8->item(0);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("MapEditor", "\347\272\254\345\272\246", nullptr));
        listWidget_8->setSortingEnabled(__sortingEnabled3);

        pushButton_14->setText(QCoreApplication::translate("MapEditor", "\344\277\256\346\224\271\347\273\217\345\272\246", nullptr));
        pushButton_19->setText(QCoreApplication::translate("MapEditor", "\344\277\256\346\224\271\347\272\254\345\272\246", nullptr));
        pushButton_20->setText(QCoreApplication::translate("MapEditor", "\346\211\200\346\234\211\350\267\257\345\276\204", nullptr));
        pushButton_21->setText(QCoreApplication::translate("MapEditor", "\346\234\200\347\237\255\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapEditor: public Ui_MapEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEDITOR_H
