#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::~MainWindow(){
    SystemInfo::setLogFont(defaultLogFont);
    SystemInfo::setMouseKeys(defaultMouseKeys);
    delete ui;
}

static QVector <QString> codepages;

BOOL EnumCodePagesProc(LPSTR lpCodePageString){
    CPINFOEX cpInfoEx;
    if (0 != GetCPInfoEx(atol(lpCodePageString), 0, &cpInfoEx)){
        codepages.push_back(QString::fromWCharArray(cpInfoEx.CodePageName));
    }
    return true;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //================================================================================
    //=================================================================================
    ui->pcName->setText(SystemInfo::getPcName());
    ui->userName->setText(SystemInfo::getUserName());
    ui->sysDir->setText(SystemInfo::getSysDir());
    ui->winDir->setText(SystemInfo::getWinDir());
    ui->tempDir->setText(SystemInfo::getTempDir());
    ui->winVersion->setText(SystemInfo::getWinVersion());

    ui->sysMetrics->setColumnCount(3);
    ui->sysMetrics->setRowCount(50);
    ui->sysMetrics->setHorizontalHeaderLabels({"Метрика", "Значение", "Пояснение"});
    SystemMetrics m;
    m.getMetrics(ui->sysMetrics);
    ui->sysMetrics->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->sysMetrics->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->sysMetrics->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    ui->mouseInfo->setText(SystemInfo::getMouseParams());
    ui->fastSwitch->setText(SystemInfo::getFastSwitch());
    ui->soundSentry->setText(SystemInfo::getSoundSentry());

    defaultLogFont = SystemInfo::getCurrentLogFont();
    newLogFont = defaultLogFont;

    ui->fontHeight->setRange(0, 72);
    ui->fontHeight->setSingleStep(8);
    ui->fontHeight->setValue(defaultLogFont.lfHeight);

    ui->fontWidth->setRange(0, 72);
    ui->fontWidth->setValue(defaultLogFont.lfWidth);

    ui->fontEscapement->setRange(0, 900);
    ui->fontEscapement->setSingleStep(10);
    ui->fontEscapement->setValue(defaultLogFont.lfEscapement);

    ui->fontOrientation->setRange(0, 900);
    ui->fontOrientation->setSingleStep(10);
    ui->fontOrientation->setValue(defaultLogFont.lfOrientation);

    ui->fontWeight->setRange(0, 1000);
    ui->fontWeight->setSingleStep(100);
    ui->fontWeight->setValue(defaultLogFont.lfWeight);

    //COLOR_BTNHIGHLIGHT, COLOR_INACTIVECAPTION, COLOR_SCROLLBAR
    QPalette brl, iac, scr;
    defaultBrl = SystemColors::getColor(COLOR_BTNHIGHLIGHT);
    defaultIAC = SystemColors::getColor(COLOR_INACTIVECAPTION);
    defaultSCR = SystemColors::getColor(COLOR_SCROLLBAR);

    brl.setColor(QPalette::Background, defaultBrl);
    iac.setColor(QPalette::Background, defaultIAC);
    scr.setColor(QPalette::Background, defaultSCR);

    ui->brighlight->setAutoFillBackground(true);
    ui->brighlight->setPalette(brl);

    ui->inactivecaptions->setAutoFillBackground(true);
    ui->inactivecaptions->setPalette(iac);

    ui->scrollbar->setAutoFillBackground(true);
    ui->scrollbar->setPalette(scr);

    //MOUSEKEYS
    defaultMouseKeys = SystemInfo::getMouseKeys();
    newMouseKeys = defaultMouseKeys;

    if (SystemInfo::isMouseKeyFlagOn(MKF_MOUSEKEYSON, defaultMouseKeys))
        ui->mouseKeysOn->setChecked(1); else ui->mouseKeysOn->setChecked(0);

    if (SystemInfo::isMouseKeyFlagOn(MKF_AVAILABLE, defaultMouseKeys))
        ui->isMouseKeysAvaliable->setText("Режим управления с помощью мыши доступен"); else
        ui->isMouseKeysAvaliable->setText("Режим управления с помощью мыши не доступен");

    if (SystemInfo::isMouseKeyFlagOn(MKF_CONFIRMHOTKEY, defaultMouseKeys))
        ui->mouseConfirmHotkey->setChecked(1); else ui->mouseConfirmHotkey->setChecked(0);

    if (SystemInfo::isMouseKeyFlagOn(MKF_HOTKEYSOUND, defaultMouseKeys))
        ui->mouseHotkeySound->setChecked(1); else ui->mouseHotkeySound->setChecked(0);

    if (SystemInfo::isMouseKeyFlagOn(MKF_MODIFIERS, defaultMouseKeys))
        ui->mouseModifiers->setChecked(1); else ui->mouseModifiers->setChecked(0);

    ui->maxSpeed->setValue(defaultMouseKeys.iMaxSpeed);
    ui->maxSpeed->setSingleStep(10);
    ui->maxSpeed->setRange(10, 360);

    ui->mouseCtrlSpeed->setValue(defaultMouseKeys.iCtrlSpeed);
    ui->mouseCtrlSpeed->setSingleStep(10);
    ui->mouseCtrlSpeed->setRange(0, 10000);

    //GetSystemTime, GetTimeZonelnformation, GetTimeFormat

    SystemTime time;
    ui->systemTime->setDateTime(time.getSystemTime());
    ui->localTime->setDateTime(time.getLocalTime());

    ui->currentBias->setText(SystemTime::getCurrentBias());
    ui->standartBias->setText(SystemTime::getStandartBias());
    ui->daylightBias->setText(SystemTime::getDaylightBias());

    //EnumSystemCodePages, GetInputState, GetLastError

    ui->lastError->setText(m.getError());

    if (GetInputState()) ui->inpState->setText("содержит сообщения от клавиатуры или мыши"); else
        ui->inpState->setText("не содержит сообщения от клавиатуры или мыши");

    ui->codePages->setColumnCount(1);
    ui->codePages->setHorizontalHeaderLabels({"Установленные кодировки"});
    EnumSystemCodePagesA(EnumCodePagesProc, CP_INSTALLED);
    ui->codePages->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->codePages->setRowCount(codepages.size());
    for (int i = 0; i < codepages.size(); i++)
        ui->codePages->setItem(0, i, new QTableWidgetItem(codepages[i]));


}

void MainWindow::on_strikeOut_stateChanged(int arg1){
    if (arg1) newLogFont.lfStrikeOut = 1; else newLogFont.lfStrikeOut = 0;
}
void MainWindow::on_underLine_stateChanged(int arg1){
    if (arg1) newLogFont.lfUnderline = 1; else newLogFont.lfUnderline = 0;
}
void MainWindow::on_italic_stateChanged(int arg1){
    if (arg1) newLogFont.lfItalic = 1; else newLogFont.lfItalic = 0;
}
void MainWindow::on_confirmation_clicked(){
    newLogFont.lfWidth = ui->fontWidth->value();
    newLogFont.lfHeight = ui->fontWidth->value();
    newLogFont.lfWeight = ui->fontWeight->value();
    newLogFont.lfEscapement = ui->fontEscapement->value();
    newLogFont.lfOrientation = ui->fontOrientation->value();

    SystemInfo::setLogFont(newLogFont);
}
void MainWindow::on_setDefault_clicked(){
    SystemInfo::setLogFont(defaultLogFont);
}
void MainWindow::on_confirmBrighlight_clicked(){
    QColor c = QColorDialog::getColor();
    QPalette tmp;
    SystemColors::setColor(COLOR_BTNHIGHLIGHT, c);
    tmp.setColor(QPalette::Background, c);
    ui->brighlight->setPalette(tmp);
    ui->brighlight->update();
}
void MainWindow::on_confirmInactivecaptions_clicked(){
    QColor c = QColorDialog::getColor();
    QPalette tmp;
    SystemColors::setColor(COLOR_INACTIVECAPTION, c);
    tmp.setColor(QPalette::Background, c);
    ui->inactivecaptions->setPalette(tmp);
}
void MainWindow::on_confirmScrollbar_clicked(){
    QColor c = QColorDialog::getColor();
    QPalette tmp;
    SystemColors::setColor(COLOR_SCROLLBAR, c);
    tmp.setColor(QPalette::Background, c);
    ui->scrollbar->setPalette(tmp);
}
void MainWindow::on_setDefaultColors_clicked(){
    SystemColors::setColor(COLOR_BTNHIGHLIGHT, defaultBrl);
    SystemColors::setColor(COLOR_INACTIVECAPTION, defaultIAC);
    SystemColors::setColor(COLOR_SCROLLBAR, defaultSCR);
}
void MainWindow::on_mouseSetDefault_clicked(){
    SystemInfo::setMouseKeys(defaultMouseKeys);
}
void MainWindow::on_mouseConfirmation_clicked(){
    qDebug() << newMouseKeys.dwFlags;
    SystemInfo::setMouseKeys(newMouseKeys);
}
void MainWindow::on_mouseKeysOn_stateChanged(int arg1){
    if (arg1){
        SystemInfo::addMouseKeysFlag(MKF_MOUSEKEYSON, newMouseKeys);
        qDebug() << "MOUSEKEYSON 1";
    } else {
        SystemInfo::removeMouseKeysFlag(MKF_MOUSEKEYSON, newMouseKeys);
        qDebug() << "MOUSEKEYSON 0";
    }
}
void MainWindow::on_mouseAvailable_stateChanged(int arg1){
    if (arg1) SystemInfo::addMouseKeysFlag(MKF_AVAILABLE, newMouseKeys); else
        SystemInfo::removeMouseKeysFlag(MKF_AVAILABLE, newMouseKeys);
}
void MainWindow::on_mouseConfirmHotkey_stateChanged(int arg1){
    if (arg1) SystemInfo::addMouseKeysFlag(MKF_CONFIRMHOTKEY , newMouseKeys); else
        SystemInfo::removeMouseKeysFlag(MKF_CONFIRMHOTKEY, newMouseKeys);
}
void MainWindow::on_mouseHotkeyActive_stateChanged(int arg1){
    if (arg1)  SystemInfo::addMouseKeysFlag(MKF_HOTKEYACTIVE , newMouseKeys); else
        SystemInfo::removeMouseKeysFlag(MKF_HOTKEYACTIVE, newMouseKeys);
}
void MainWindow::on_mouseHotkeySound_stateChanged(int arg1){
    if (arg1) SystemInfo::addMouseKeysFlag(MKF_HOTKEYSOUND , newMouseKeys); else
        SystemInfo::removeMouseKeysFlag(MKF_HOTKEYSOUND, newMouseKeys);
}
void MainWindow::on_maxSpeed_valueChanged(int arg1){
    newMouseKeys.iMaxSpeed = arg1;
}
void MainWindow::on_mouseCtrlSpeed_valueChanged(int arg1){
    newMouseKeys.iCtrlSpeed = arg1;
    //newMouseKeys.iTimeToMaxSpeed = arg1;
}
void MainWindow::on_mouseModifiers_stateChanged(int arg1){
    if (arg1) SystemInfo::addMouseKeysFlag(MKF_MODIFIERS, newMouseKeys); else
        SystemInfo::removeMouseKeysFlag(MKF_MODIFIERS, newMouseKeys);
}
void MainWindow::on_localTime_dateTimeChanged(const QDateTime &dateTime){
    SystemTime::setLocalTime(dateTime);
}
