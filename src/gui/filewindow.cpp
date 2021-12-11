#include "hdr/gui/filewindow.h"
#include "ui_filewindow.h"

FileWindow::FileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FileWindow)
{
    ui->setupUi(this);
    astFile_ = new AsterixFile();
    appConfig_ = AppConfig::GetInstance();
    playTimer_ = new QTimer();
    loadingThread = new QThread();
    packetCounter_ = 0;
    alreadyAdded_ = QList<QString>();
    secsValue_ = 0;
    astFile_->moveToThread(loadingThread);
    ui->widget->SetPosition(WGS84Coordinates(41.29742220817759, 2.083346335275707,0));
    ui->widget->SetZoom(10);
    ConnectSignalsSlots();
}

FileWindow::~FileWindow()
{
    delete astFile_;
    delete ui;
    delete loadingThread;
}

void FileWindow::DecodeFile(QString filePath) {
    loadingThread->start();
    emit startLoading(filePath);
}

void FileWindow::closeEvent(QCloseEvent *event) {
    delete this;
}

void FileWindow::on_PacketLoaded() {
    emit packetLoaded();
}

void FileWindow::on_FinishLoading() {

    ui->tableView->setModel(astFile_->packetTable_);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->verticalHeader()->setVisible(false);
    ui->loadedPackets->setText("Loaded " + QString::number(astFile_->numberOfPackets) + " packets");

    ui->loadedFlights->setModel(astFile_->emitterTable_);
    ui->loadedFlights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loadedFlights->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->loadedFlights->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->loadedFlights->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int hour = astFile_->dataBlocks->first()->GetTimeOfReception().hour();
    int min = astFile_->dataBlocks->first()->GetTimeOfReception().minute();
    int sec = astFile_->dataBlocks->first()->GetTimeOfReception().second();

    this->SetFileDetailsTab();

    currentTime_ = QTime(hour,min,sec,0);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
    this->show();
    this->raise();
    loadingThread->quit();
    emit finishedLoading();
}

int FileWindow::GetFileLength(QString filePath) {
    return this->astFile_->GetTotalPackets(filePath);
}


void FileWindow::on_playButton_clicked()
{
    playTimer_->start(500);
}

void FileWindow::on_stopButton_clicked()
{
    playTimer_->stop();
}

void FileWindow::ConnectSignalsSlots() {
    connect(this, &FileWindow::startLoading, astFile_, &AsterixFile::readFile);
    connect(astFile_, &AsterixFile::packetLoaded, this, &FileWindow::on_PacketLoaded);
    connect(astFile_, &AsterixFile::finishLoading, this, &FileWindow::on_FinishLoading);
    connect(this->ui->playButton, &QAbstractButton::clicked, this, &FileWindow::on_playButton_clicked);
    connect(this->ui->stopButton, &QAbstractButton::clicked, this, &FileWindow::on_stopButton_clicked);
    connect(playTimer_, &QTimer::timeout, this, &FileWindow::on_TimerTick);
    connect(this->ui->filtersButton, &QAbstractButton::clicked, this, &FileWindow::on_filtersButton_clicked);
    connect(this->ui->showPacketDetailsButton, &QAbstractButton::clicked, this, &FileWindow::on_PacketRowClicked);
    connect(this->ui->actionSave_File, &QAction::triggered, this, &FileWindow::on_SaveFileClicked);
    connect(this->ui->actionKML, &QAction::triggered, this, &FileWindow::on_ExportAsKMLCLicked);
    connect(this->ui->actionCSV, &QAction::triggered, this, &FileWindow::on_ExportAsCSVCLicked);
    connect(this->ui->seeEmitterDetailsButton, &QAbstractButton::clicked, this, &FileWindow::on_SeeEmittersDetailsClicked);
}

void FileWindow::on_TimerTick() {
    currentTime_ = currentTime_.addMSecs(500);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
    this->RefreshMap();
}


void FileWindow::on_filtersButton_clicked()
{
    FiltersDialog *filtersDialog = new FiltersDialog(this);
    connect(filtersDialog, &FiltersDialog::ResetPacketsClicked, this, &FileWindow::on_ResetPacketsClicked);
    int code = filtersDialog->exec();

    if (code == QDialog::Accepted) {

        QString callSign = filtersDialog->callSign_;
        QString address = filtersDialog->address_;
        int trackNumber = filtersDialog->trackNumber_;
        int category = filtersDialog->category_;
        astFile_->ApplyFilters(category,callSign,address,trackNumber);
    }
}

void FileWindow::RefreshMap() {

    alreadyAdded_.clear();
    this->ui->widget->ClearItemsWithTwoCycles();

    int numOfItems = this->ui->widget->GetAddedItemsLength();

    int i = 0;

    while (i < numOfItems) {
        alreadyAdded_.append(this->ui->widget->GetAddedItem(i));
        i++;
    }

    for (;packetCounter_ < astFile_->dataBlocks->length(); packetCounter_++) {
        DataBlock* dataBlock = astFile_->dataBlocks->at(packetCounter_);
        int msecsTo = this->currentTime_.msecsTo(dataBlock->GetTimeOfReception());
        if (msecsTo >= -500 && msecsTo <= 500) {
            if (alreadyAdded_.indexOf(dataBlock->GetIdentifier()) == -1) {
                this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,"red", dataBlock->GetIdentifier());
                alreadyAdded_.append(dataBlock->GetIdentifier());
            }
            else {
                this->ui->widget->DeleteMarker(dataBlock->GetIdentifier());
                this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,"red", dataBlock->GetIdentifier());
            }
        }

        else if (msecsTo <= -500) {

        }

        else if (msecsTo >= 500) {
            break;
        }
    }
}

void FileWindow::on_PacketRowClicked() {

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    QModelIndex index = indexes.at(0);
    int packet = index.data().toInt();
    QTreeWidgetItem *packetDetails = astFile_->dataBlocks->at(packet-1)->GetPacketInfo();
    PacketDetailDialog* details = new PacketDetailDialog(this,packetDetails);
    details->show();
    details->raise();
}

void FileWindow::SetFileDetailsTab() {
    QLocale locale = QLocale();

    ui->fileLabel->setText("File Name: " + astFile_->fileInfo_.baseName() + "." + astFile_->fileInfo_.completeSuffix());
    ui->directoryLabel->setText("Directory: " + astFile_->fileInfo_.absoluteDir().absolutePath());
    ui->sizeLabel->setText("File Size: " + locale.formattedDataSize(astFile_->fileInfo_.size()));
    ui->hourLabel->setText("Start Hour: " + astFile_->dataBlocks->at(0)->GetTimeOfReception().toString("hh:mm:ss:zzz") +
                           " ;" + "Final Hour: " + astFile_->dataBlocks->last()->GetTimeOfReception().toString("hh:mm:ss:zzz"));
    QList<int> categories = astFile_->categoryStats_.keys();
    QList<int> values = astFile_->categoryStats_.values();
    this->ui->statsTable->setRowCount(2);
    this->ui->statsTable->setColumnCount(categories.count() + 2);
    QTableWidgetItem *labelCat = new QTableWidgetItem("Category");
    QTableWidgetItem *labelCount = new QTableWidgetItem("Number Of Packets");
    this->ui->statsTable->setItem(0, 0, labelCat);
    this->ui->statsTable->setItem(1, 0, labelCount);
    int i;


    for (i = 0; i < categories.count(); i++) {
        QTableWidgetItem *category = new QTableWidgetItem(QString::number(categories.at(i)));
        this->ui->statsTable->setItem(0, i+1, category);
        QTableWidgetItem *count = new QTableWidgetItem(QString::number(values.at(i)));
        this->ui->statsTable->setItem(1, i+1, count);
    }
    QTableWidgetItem *totalLabel = new QTableWidgetItem("Total");
    QTableWidgetItem *totalCount = new QTableWidgetItem(QString::number(astFile_->numberOfPackets));
    this->ui->statsTable->setItem(0,i+1, totalLabel);
    this->ui->statsTable->setItem(1,i+1, totalCount);

    ui->statsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statsTable->verticalHeader()->setVisible(false);
}

void FileWindow::on_SaveFileClicked() {
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Valid Files (*.ast *.gps)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.length() == 1) {
        QString filePath = fileNames.at(0);
        this->astFile_->writeFile(filePath);
    }

    else {
    }
}

void FileWindow::on_ResetPacketsClicked() {
    astFile_->ResetFilters();
}

void FileWindow::on_ExportAsKMLCLicked() {
    SaveKMLFile();
}

void FileWindow::on_ExportAsCSVCLicked() {
    int c = 1;
}


void FileWindow::on_showMarkersCheck_stateChanged(int arg1)
{
    if (this->ui->showMarkersCheck->isChecked()) {
        this->ui->widget->ShowLabels();
    }

    else if (!this->ui->showMarkersCheck->isChecked()) {
        this->ui->widget->HideLabels();
    }
}

void FileWindow::SaveKMLFile() {


    QString filename = QDir::currentPath() + "/test.kml";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
            stream << "<kml xmlns='http://www.opengis.net/kml/2.2'>" << endl;
            stream << "<Document>" << endl;
            stream << "<Folder><name>CAT21</name><open>1</open>" << endl;
            stream << "<Style id='cat21Style'>" << endl;
            stream << "<LineStyle>" << endl;
            stream << "<color>641400FF</color>" << endl;
            stream << "<width>4</width>" << endl;
            stream << "</LineStyle>" << endl;
            stream << "<PolyStyle>" << endl;
            stream << "<color>641400FF</color>" << endl;
            stream << "</PolyStyle>" << endl;
            stream <<"</Style>" << endl;

            for (Emitter emitter : this->astFile_->emitters_) {
                stream << "<Placemark>" << endl;
                stream << "<name>" << emitter.GetIdentifier().replace(" ","") << "</name>" << endl;
                stream << "<styleUrl>#cat21Style</styleUrl>" << endl;
                stream << "<LineString>" << endl;
                stream << "<coordinates>" << endl;

                for (WGS84Coordinates coord : emitter.pointsCat21) {

                    stream << QString::number(coord.longitude,'g',15) << "," << QString::number(coord.latitude,'g',15) << endl;

                }

                stream << "</coordinates>" << endl;
                stream << "</LineString>" << endl;
                stream << "</Placemark>" << endl;

            }

            stream << "</Folder>" << endl;
            stream << "</Document>" << endl;
            stream << "</kml>" << endl;
        }

}

void FileWindow::on_SeeEmittersDetailsClicked() {

    QModelIndexList indexes = ui->loadedFlights->selectionModel()->selectedRows();
    QModelIndex index = indexes.at(0);
    int emitterNum = index.row();
    Emitter emitterSelected = this->astFile_->emitters_.at(emitterNum);

    EmitterDetailsWindow* emitterWindow = new EmitterDetailsWindow(this, &emitterSelected);
    emitterWindow->show();
    emitterWindow->raise();
}

