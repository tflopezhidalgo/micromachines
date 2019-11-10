/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QStackedWidget *stackedWidget;
    QWidget *selectTypeScreen;
    QGridLayout *gridLayout_4;
    QLabel *serviceLabel;
    QLineEdit *serviceNameField;
    QLabel *hostLabel;
    QLabel *label;
    QLineEdit *hostNameField;
    QPushButton *create_match_button;
    QPushButton *join_match_button;
    QWidget *availableMatches;
    QGridLayout *gridLayout_8;
    QLineEdit *playerNameField;
    QDialogButtonBox *okCancelButtons;
    QTableWidget *tableWidget;
    QLabel *nameLabel;
    QLabel *availableMatchesLabel;
    QWidget *createScreen;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_3;
    QLabel *lapsAmountLabel;
    QLineEdit *playerNameField_2;
    QLabel *mapNameLabel;
    QLineEdit *matchNameField;
    QLabel *nameLabel_2;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QLabel *matchNameLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *playersAmountLabel;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_4;
    QComboBox *comboBox;
    QSpacerItem *verticalSpacer_5;
    QLabel *createMatchLabel;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;
    QWidget *waitingPlayersScreen;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_11;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(589, 522);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setToolTipDuration(3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        stackedWidget->setMinimumSize(QSize(571, 301));
        selectTypeScreen = new QWidget();
        selectTypeScreen->setObjectName(QStringLiteral("selectTypeScreen"));
        sizePolicy1.setHeightForWidth(selectTypeScreen->sizePolicy().hasHeightForWidth());
        selectTypeScreen->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(selectTypeScreen);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        serviceLabel = new QLabel(selectTypeScreen);
        serviceLabel->setObjectName(QStringLiteral("serviceLabel"));

        gridLayout_4->addWidget(serviceLabel, 3, 0, 1, 1);

        serviceNameField = new QLineEdit(selectTypeScreen);
        serviceNameField->setObjectName(QStringLiteral("serviceNameField"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(serviceNameField->sizePolicy().hasHeightForWidth());
        serviceNameField->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(serviceNameField, 3, 1, 1, 1);

        hostLabel = new QLabel(selectTypeScreen);
        hostLabel->setObjectName(QStringLiteral("hostLabel"));

        gridLayout_4->addWidget(hostLabel, 2, 0, 1, 1);

        label = new QLabel(selectTypeScreen);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setBaseSize(QSize(8, 0));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label, 0, 0, 1, 3);

        hostNameField = new QLineEdit(selectTypeScreen);
        hostNameField->setObjectName(QStringLiteral("hostNameField"));
        sizePolicy2.setHeightForWidth(hostNameField->sizePolicy().hasHeightForWidth());
        hostNameField->setSizePolicy(sizePolicy2);

        gridLayout_4->addWidget(hostNameField, 2, 1, 1, 1);

        create_match_button = new QPushButton(selectTypeScreen);
        create_match_button->setObjectName(QStringLiteral("create_match_button"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(create_match_button->sizePolicy().hasHeightForWidth());
        create_match_button->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(create_match_button, 5, 2, 1, 1);

        join_match_button = new QPushButton(selectTypeScreen);
        join_match_button->setObjectName(QStringLiteral("join_match_button"));
        sizePolicy3.setHeightForWidth(join_match_button->sizePolicy().hasHeightForWidth());
        join_match_button->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(join_match_button, 5, 0, 1, 1);

        stackedWidget->addWidget(selectTypeScreen);
        availableMatches = new QWidget();
        availableMatches->setObjectName(QStringLiteral("availableMatches"));
        sizePolicy1.setHeightForWidth(availableMatches->sizePolicy().hasHeightForWidth());
        availableMatches->setSizePolicy(sizePolicy1);
        gridLayout_8 = new QGridLayout(availableMatches);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        playerNameField = new QLineEdit(availableMatches);
        playerNameField->setObjectName(QStringLiteral("playerNameField"));

        gridLayout_8->addWidget(playerNameField, 2, 1, 1, 1);

        okCancelButtons = new QDialogButtonBox(availableMatches);
        okCancelButtons->setObjectName(QStringLiteral("okCancelButtons"));
        okCancelButtons->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_8->addWidget(okCancelButtons, 3, 1, 1, 1);

        tableWidget = new QTableWidget(availableMatches);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setShowGrid(false);
        tableWidget->setGridStyle(Qt::NoPen);

        gridLayout_8->addWidget(tableWidget, 1, 0, 1, 2);

        nameLabel = new QLabel(availableMatches);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));

        gridLayout_8->addWidget(nameLabel, 2, 0, 1, 1);

        availableMatchesLabel = new QLabel(availableMatches);
        availableMatchesLabel->setObjectName(QStringLiteral("availableMatchesLabel"));

        gridLayout_8->addWidget(availableMatchesLabel, 0, 0, 1, 1);

        stackedWidget->addWidget(availableMatches);
        createScreen = new QWidget();
        createScreen->setObjectName(QStringLiteral("createScreen"));
        gridLayout_6 = new QGridLayout(createScreen);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setVerticalSpacing(0);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        lapsAmountLabel = new QLabel(createScreen);
        lapsAmountLabel->setObjectName(QStringLiteral("lapsAmountLabel"));

        gridLayout_3->addWidget(lapsAmountLabel, 8, 1, 1, 1, Qt::AlignHCenter);

        playerNameField_2 = new QLineEdit(createScreen);
        playerNameField_2->setObjectName(QStringLiteral("playerNameField_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(playerNameField_2->sizePolicy().hasHeightForWidth());
        playerNameField_2->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(playerNameField_2, 0, 2, 1, 1);

        mapNameLabel = new QLabel(createScreen);
        mapNameLabel->setObjectName(QStringLiteral("mapNameLabel"));

        gridLayout_3->addWidget(mapNameLabel, 6, 1, 1, 1, Qt::AlignHCenter);

        matchNameField = new QLineEdit(createScreen);
        matchNameField->setObjectName(QStringLiteral("matchNameField"));
        sizePolicy2.setHeightForWidth(matchNameField->sizePolicy().hasHeightForWidth());
        matchNameField->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(matchNameField, 2, 2, 1, 1);

        nameLabel_2 = new QLabel(createScreen);
        nameLabel_2->setObjectName(QStringLiteral("nameLabel_2"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(nameLabel_2->sizePolicy().hasHeightForWidth());
        nameLabel_2->setSizePolicy(sizePolicy5);

        gridLayout_3->addWidget(nameLabel_2, 0, 1, 1, 1, Qt::AlignHCenter);

        spinBox = new QSpinBox(createScreen);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        sizePolicy2.setHeightForWidth(spinBox->sizePolicy().hasHeightForWidth());
        spinBox->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(spinBox, 4, 2, 1, 1);

        spinBox_2 = new QSpinBox(createScreen);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        sizePolicy2.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(spinBox_2, 8, 2, 1, 1);

        matchNameLabel = new QLabel(createScreen);
        matchNameLabel->setObjectName(QStringLiteral("matchNameLabel"));

        gridLayout_3->addWidget(matchNameLabel, 2, 1, 1, 1, Qt::AlignHCenter);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 3, 1, 1);

        playersAmountLabel = new QLabel(createScreen);
        playersAmountLabel->setObjectName(QStringLiteral("playersAmountLabel"));

        gridLayout_3->addWidget(playersAmountLabel, 4, 1, 1, 1, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 9, 2, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_6, 7, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_3, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer, 1, 2, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_4, 3, 2, 1, 1);

        comboBox = new QComboBox(createScreen);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);

        gridLayout_3->addWidget(comboBox, 6, 2, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_5, 5, 2, 1, 1);


        gridLayout->addLayout(gridLayout_3, 2, 0, 1, 3);

        createMatchLabel = new QLabel(createScreen);
        createMatchLabel->setObjectName(QStringLiteral("createMatchLabel"));
        QFont font;
        font.setFamily(QStringLiteral("FreeSans"));
        font.setPointSize(27);
        createMatchLabel->setFont(font);
        createMatchLabel->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(createMatchLabel, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);


        gridLayout_6->addLayout(gridLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(createScreen);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_6->addWidget(buttonBox, 1, 0, 1, 1);

        stackedWidget->addWidget(createScreen);
        waitingPlayersScreen = new QWidget();
        waitingPlayersScreen->setObjectName(QStringLiteral("waitingPlayersScreen"));
        sizePolicy.setHeightForWidth(waitingPlayersScreen->sizePolicy().hasHeightForWidth());
        waitingPlayersScreen->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(waitingPlayersScreen);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_10 = new QLabel(waitingPlayersScreen);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy6(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy6);
        label_10->setPixmap(QPixmap(QString::fromUtf8("../Escritorio/racecars2d/mechanic/mechanic_gray_red.png")));

        gridLayout_2->addWidget(label_10, 0, 0, 1, 1);

        label_11 = new QLabel(waitingPlayersScreen);
        label_11->setObjectName(QStringLiteral("label_11"));
        sizePolicy2.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        label_11->setFont(font1);

        gridLayout_2->addWidget(label_11, 1, 0, 1, 1);

        stackedWidget->addWidget(waitingPlayersScreen);

        formLayout->setWidget(0, QFormLayout::LabelRole, stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        serviceLabel->setText(QApplication::translate("MainWindow", "Servicio", Q_NULLPTR));
        hostLabel->setText(QApplication::translate("MainWindow", "Host", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        hostNameField->setText(QString());
        create_match_button->setText(QApplication::translate("MainWindow", "Crear partida", Q_NULLPTR));
        join_match_button->setText(QApplication::translate("MainWindow", "Unirse a partida", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("MainWindow", "Ingresa tu nombre  ", Q_NULLPTR));
        availableMatchesLabel->setText(QApplication::translate("MainWindow", "Partidas disponibles", Q_NULLPTR));
        lapsAmountLabel->setText(QApplication::translate("MainWindow", "Cantidad de vueltas", Q_NULLPTR));
        mapNameLabel->setText(QApplication::translate("MainWindow", "Mapa", Q_NULLPTR));
        nameLabel_2->setText(QApplication::translate("MainWindow", "Tu nombre", Q_NULLPTR));
        matchNameLabel->setText(QApplication::translate("MainWindow", "Nombre de la partida", Q_NULLPTR));
        playersAmountLabel->setText(QApplication::translate("MainWindow", "Cantidad de jugadores  ", Q_NULLPTR));
        createMatchLabel->setText(QApplication::translate("MainWindow", "Crear partida", Q_NULLPTR));
        label_10->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "Esperando jugadores...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
