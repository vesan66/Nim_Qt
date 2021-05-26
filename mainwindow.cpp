#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->SetupGui();

    // Wire the Signals
    this->connect(_pInterface, &GUI_Qt::Send_PrepareNewSession, this, &MainWindow::Receive_PrepareNewSession);
    this->connect(_pInterface, &GUI_Qt::Send_EndSession, this, &MainWindow::Receive_EndSession);
    //this->connect(_pInterface, &GUI_Qt::Send_SticksToShow, this, &MainWindow::Receive_DrawPlayground);
    this->connect(_pInterface, &GUI_Qt::Send_SticksToShowAfterMove, this, &MainWindow::Receive_DrawPlayground);
    this->connect(_pInterface, &GUI_Qt::Send_Players, this, &MainWindow::Receive_Playerlist);
    this->connect(_pInterface, &GUI_Qt::Send_SessionsToPlay, this, &MainWindow::Receive_SessionsToPlay);

    this->connect(_pInterface, &GUI_Qt::Send_BrainBefore, this, &MainWindow::Receive_BrainBefore);
    this->connect(_pInterface, &GUI_Qt::Send_BrainAfter, this, &MainWindow::Receive_BrainAfter);

    this->connect(_pChooser, &Chooser::Send_HU_Move, this, &MainWindow::Receive_HU_Move);
    this->connect(_pInterface, &GUI_Qt::Send_AskForMove, this, &MainWindow::Receive_AskForMove);

    this->connect(_pInterface, &GUI_Qt::Send_Winner, this, &MainWindow::Receive_Winner);
    this->connect(_pInterface, &GUI_Qt::Send_LoopState, this, &MainWindow::Receive_LoopState);

    //this->connect(ui->horizontalSlider, &QSlider::sliderMoved, ui->label_games_num, &QLabel::setNum);  // Does not work!

}


MainWindow::~MainWindow() {
    delete _pInterface;
    delete ui;
}


void MainWindow::SetupGui() {
    SHOWO;

    // Controls
    _pBoard = new Board(this);
    QRect boardRect = _pBoard->geometry();
    this->update(boardRect);

    _pDots = new Dots(this);
    QRect dotsRect = _pDots->geometry();
    this->update(dotsRect);

    _pMugList = new MugList(this);
    QRect mugListRect = _pMugList->geometry();
    this->update(mugListRect);
    _pMugList->setVisible(false);

    _pChooser = new Chooser(this);
    QRect chooserRect = _pChooser->geometry();
    this->update(chooserRect);
    _pChooser->setVisible(false);

    ui->label_winner->setVisible(false); ui->label_winner->setText("");

    ui->pushButton_stop_games->setEnabled(false);
    ui->pushButton_pause_game->setEnabled(false);
    ui->pushButton_pause_game->setProperty("P", QVariant(false));
    ui->pushButton->setEnabled(true);
    ui->pushButton->setProperty("V", QVariant(false));

    ui->frameConfig->setGeometry(QRect(711, 399, 631, 311));
    // Target QRect(120, 130, 631, 311)

    AnimationConfig();



    // Interface
    _pInterface = new GUI_Qt(this);
    //Con::troller();
    Start::menu().InitializeOnly();
    Con::troller().SetGUIInterface(_pInterface);


    // Configuration-sheet
    ui->horizontalSlider->setValue(Confi::guration().NumberOfSessions());
    ui->label_games_num->setText(QString::number(ui->horizontalSlider->value()));


    // Get the players.
    int pl1 = Confi::guration().PlayerOne();
    int pl2 = Confi::guration().PlayerTwo();

    CPlayers pl = Confi::guration().GetCPlayers();
    for( const CPlayer& item: pl) {
        QString playerText = "";
        playerText = QString::fromStdString(item.name) + " ";
        switch (item.type) {
        case Player::PTypes::human: {
            playerText += QString("[HU] ");
            break;
        }
        case Player::PTypes::machineAI: {
            playerText += QString("[AI] ");
            break;
        }
        case Player::PTypes::machineRnd: {
            playerText +=  QString("[RN] ");
            break;
        }
        default: {
            playerText +=  QString("[UD] ");
            break;
        }
        }

        ui->comboBox_p1->addItem(playerText, item.id);
        ui->comboBox_p2->addItem(playerText, item.id);
    }
    int idx1 = ui->comboBox_p1->findData(pl1);
    int idx2 = ui->comboBox_p2->findData(pl2);
    ui->comboBox_p1->setCurrentIndex(idx1);
    ui->comboBox_p2->setCurrentIndex(idx2);

}


void MainWindow::closeEvent(QCloseEvent* ev ) {
    qDebug() << __FUNCTION__;

    if (_pInterface != nullptr) {
        _pInterface->SetMagicChar(cnst::terminateChar);
        GameThread* pGT = _pInterface->GetGameThread();
        if (pGT != nullptr) {
            pGT->wait(8000);
        }
    }
    //ev->ignore();
    ev->accept();
}


void MainWindow::Receive_PrepareNewSession() {
    SHOWO;
    if ((_pBoard == nullptr)||(_pDots == nullptr)) { return;}
    _pMugList->setVisible(false);
    _pChooser->setVisible(false);
    ui->label_winner->setVisible(false); ui->label_winner->setText("");
    _pBoard->ExpandMe();
    _pDots->ShowMe();
}


void MainWindow::Receive_EndSession() {
    SHOWO;
    if ((_pBoard == nullptr)||(_pDots == nullptr)) { return;}
    _pMugList->setVisible(false);
    _pChooser->setVisible(false);
    _pBoard->CollapseMe();
    _pDots->HideMe();
}


void MainWindow::Receive_DrawPlayground(const int& sticks) {
    SHOWO;
    if ((_pBoard == nullptr)||(_pDots == nullptr)) { return;}
    _pDots->SetAmountOfDotsVisible(sticks);
}


void MainWindow::Receive_Playerlist(const CPlayers &players, const bool &isMultiSession) {
    SHOWO;
//    qDebug() << players.size();
//    qDebug() <<isMultiSession;
    QString playerText{};

    bool displayBrain = false;
    bool displayHUInput = false;
    int playerCount = 0;
    for (const CPlayer& item : players) {

        playerText = QString().fromStdString(item.name) + QString(" ");

        switch (item.type) {
        case Player::PTypes::human: {
            playerText += QString("[HU] ");
            if (item.isActive) { displayHUInput = true; }
            break;
        }
        case Player::PTypes::machineAI: {
            playerText += QString("[AI] ");
            if (item.isActive) { displayBrain = true; }
            break;
        }
        case Player::PTypes::machineRnd: {
            playerText +=  QString("[RN] ");
            break;
        }
        default: {
            playerText +=  QString("[UD] ");
            break;
        }
        }

        // Won Lost
        if (isMultiSession == true) {
            playerText += QString(" [ ") + QString().number(item.sessionsWon) +  QString(" / ") + QString().number(item.sessionsLost) +  QString(" ] ");
        }
        if (playerCount == 0) {
            SetActiveLabel(ui->label_player_1,item.isActive);
            ui->label_player_1->setText(playerText);
            playerText = "";
            playerCount++;
            continue;
        }
        if (playerCount == 1) {
            SetActiveLabel(ui->label_player_2,item.isActive);
            ui->label_player_2->setText(playerText);
            playerText = "";
            playerCount++;
            continue;
        }
        if (playerCount > 1) {
            break;
        }

    }
    _pMugList->setVisible(displayBrain);
    _pChooser->setVisible(displayHUInput);
}


void MainWindow::Receive_SessionsToPlay(const CSessions& ses) {
    int a = 0;
    int b = 0;
    QString out;
    if ((ses.sessionsToPlay <= 1) == false) {
        a = ses.sessionsPlayed + 1;
        b = ses.sessionsToPlay;
    }
    out =  "Spiel " + QString().number(a) + " von " + QString().number(b);
    ui->label_game->setText(out);
}


void MainWindow::Receive_BrainBefore(const CMugs& cm) {
    SHOWO;
    _pMugList->ClearAllMarksAndHideElements();
    Receive_BrainAfter(cm);
}


void MainWindow::Receive_BrainAfter(const CMugs & cm) {
    SHOWO;
    _pChooser->setVisible(false);
    _pMugList->setVisible(cm.size() != 0);
    _pMugList->SetMugs(cm);
}


void MainWindow::Receive_AskForMove() {
    SHOWO;
    _pMugList->setVisible(false);
    _pChooser->setVisible(true);
}


void MainWindow::Receive_HU_Move(const int & no) {
    SHOWO;
    qDebug() << "Wants Number: " << no;
    char c = to_string(no).c_str()[0];
    qDebug() << "This is the char:" << c;
    this->_pInterface->SetMagicChar(c);
}


void MainWindow::Receive_Winner(const QString& name) {
    SHOWO;
    QString s = " *!* " + name + " *!*";
    ui->label_winner->setVisible(true);
    ui->label_winner->setText(s);
}


void MainWindow::Receive_LoopState(const Con::CLoopStates& state) {
    // enum class CLoopStates { running, paused, undefined, stepRunning, otherInput, wantQuitFromTheRun, finished };
    switch (state) {
    case Con::CLoopStates::running: {
        ui->pushButton_start_games->setEnabled(false);
        ui->pushButton_stop_games->setEnabled(true);
        ui->pushButton_pause_game->setEnabled(true);
        ui->pushButton_pause_game->setText("Pause");
        ui->pushButton_pause_game->setProperty("P", QVariant(true));
        ui->pushButton->setEnabled(false);
        break;
    }
    case Con::CLoopStates::finished: {
        ui->pushButton_start_games->setEnabled(true);
        ui->pushButton_stop_games->setEnabled(false);
        ui->pushButton_pause_game->setEnabled(false);
        ui->pushButton_pause_game->setText("Pause");
        ui->pushButton_pause_game->setProperty("P", QVariant(true));
        ui->pushButton->setEnabled(true);
        break;
    }
    case Con::CLoopStates::paused: {
        ui->pushButton_start_games->setEnabled(false);
        ui->pushButton_stop_games->setEnabled(false);
        ui->pushButton_pause_game->setEnabled(true);
        ui->pushButton_pause_game->setText("Weiter");
        ui->pushButton_pause_game->setProperty("P", QVariant(false));
        ui->pushButton->setEnabled(false);
        break;
    }
    default: {
        break;
    }
    }

}


void MainWindow::SetActiveLabel(QLabel* label, const bool& isActive){
    // Set active
    QPalette palette{};

    if (label == nullptr) {return;}

    palette = label->palette();
    if (isActive) {
        palette.setColor(label->foregroundRole(), Qt::red);
    } else {
        palette.setColor(label->foregroundRole(), Qt::black);
    }
   label->setPalette(palette);
}


void MainWindow::on_pushButton_start_games_clicked() {
    qDebug() << __FUNCTION__;
    ui->pushButton->setEnabled(false);
    _pInterface->StartGameThread();
}


void MainWindow::on_pushButton_stop_games_clicked() {
    qDebug() << __FUNCTION__;
    if (_pInterface == nullptr) { return;}
    _pInterface->SetMagicChar(cnst::terminateChar);
}


void MainWindow::on_pushButton_pause_game_clicked() {
    QVariant p = ui->pushButton_pause_game->property("P");
    if (p.toBool() == true){
        _pInterface->SetMagicChar(cnst::pauseChar);
    } else {
        _pInterface->SetMagicChar(cnst::continueChar);
    }
}



void MainWindow::AnimationConfig() {
    this->_pHideC = new QParallelAnimationGroup(this);
    this->_pShowC = new QParallelAnimationGroup(this);
    QPropertyAnimation *animationHide = new QPropertyAnimation(ui->frameConfig, "geometry");
    animationHide->setDuration(500);
    animationHide->setStartValue(QRect(120, 130, 631, 311));
    animationHide->setEndValue(QRect(711, 399, 631, 311));
    animationHide->setEasingCurve(QEasingCurve::OutCirc);
    _pHideC->addAnimation(animationHide);

    QPropertyAnimation *animationShow = new QPropertyAnimation(ui->frameConfig, "geometry");
    animationShow->setDuration(500);
    animationShow->setStartValue(QRect(711, 399, 631, 311));
    animationShow->setEndValue(QRect(120, 130, 631, 311));
    animationShow->setEasingCurve(QEasingCurve::OutCirc);
    _pShowC->addAnimation(animationShow);
}


void MainWindow::on_pushButton_clicked() {
    if (_pHideC == nullptr) { return; }
    if (_pShowC == nullptr) { return; }
    ui->frameConfig->raise();
    QVariant v = ui->pushButton->property("V");
    if (v.toBool() == true){
        ui->pushButton->setProperty("V", QVariant(false));
        ui->pushButton_start_games->setEnabled(true);
        _pBoard->raise();
        _pDots->raise();
        _pHideC->start();
        Confi::guration().SetNumberOfSessions(ui->horizontalSlider->value());
        Confi::guration().SetClearMind(ui->checkBox_clear->isChecked());
        QVariant qPl1 = ui->comboBox_p1->currentData();
        QVariant qPl2 = ui->comboBox_p2->currentData();
        int pl1 = qPl1.toInt();
        int pl2 = qPl2.toInt();
        if (pl1 != pl2) {
            if ((pl1 != 0) && (pl2 != 0)) {
                Confi::guration().SetPlayerOne(pl1);
                Confi::guration().SetPlayerTwo(pl2);
            }
        }

    } else {
        ui->pushButton->setProperty("V", QVariant(true));
        ui->pushButton_start_games->setEnabled(false);
        ui->checkBox_clear->setChecked(Confi::guration().ClearMind());
        _pBoard->lower();
        _pDots->lower();
        _pShowC->start();
    }
}


void MainWindow::on_horizontalSlider_sliderMoved(int position) {
    ui->label_games_num->setNum(position);
}


void MainWindow::on_pushButton_info_clicked() {
    Info* pInfo = new Info(this);
    pInfo->exec();
}


void MainWindow::on_pushButton_showBrain_clicked(){

    CPlayers cPlayers = Confi::guration().GetCPlayers();

    PlayerList* pPlayerList = Confi::guration().GetPlayerList();
    if (pPlayerList == nullptr) { return; }

    Matrix* pMatrix = new Matrix(this);

    int player = 0;
    for (const auto item : *pPlayerList) {
        if (item != nullptr) {
            if (item->GetType() == Player::PTypes::machineAI) {
                CMugs brain = Con::troller().GetBrain(item, Confi::guration().MaxTake());
                CPlayer cPlayer = GetCPlayerByID(cPlayers, item->Id());
                if (player == 0) {
                    pMatrix->SetPlayerName_Player_One(QString().fromStdString(cPlayer.name));
                    pMatrix->SetMatrix_Player_One(brain);
                    player++;
                    continue;
                }
                if (player == 1) {
                    pMatrix->SetPlayerName_Player_Two(QString().fromStdString(cPlayer.name));
                    pMatrix->SetMatrix_Player_Two(brain);
                    break;
                }
            }
        }
    }

    pMatrix->exec();
}

