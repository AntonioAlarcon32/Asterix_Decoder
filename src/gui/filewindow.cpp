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
    ui->loadedPackets->setText("Loaded " + QString::number(astFile_->numberOfPackets_) + " packets");

    ui->loadedFlights->setModel(astFile_->emitterTable_);
    ui->loadedFlights->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->loadedFlights->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->loadedFlights->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->loadedFlights->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int hour = astFile_->dataBlocks->first()->GetTimeOfReception().hour();
    int min = astFile_->dataBlocks->first()->GetTimeOfReception().minute();
    int sec = astFile_->dataBlocks->first()->GetTimeOfReception().second();

    this->ui->horizontalSlider->setMinimum(0);
    this->ui->horizontalSlider->setMaximum(astFile_->numberOfPackets_-1);
    this->ui->horizontalSlider->setValue(0);

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
    connect(this->ui->x1Button, &QAbstractButton::clicked, this, &FileWindow::on_x1Clicked);
    connect(this->ui->x2Button, &QAbstractButton::clicked, this, &FileWindow::on_x2Clicked);
    connect(this->ui->x8Button, &QAbstractButton::clicked, this, &FileWindow::on_x8Clicked);
    connect(this->ui->x16Button, &QAbstractButton::clicked, this, &FileWindow::on_x16Clicked);
    connect(this->ui->actionStart_Multicast, &QAction::triggered, this, &FileWindow::on_StartMulticastClicked);
    connect(this->ui->horizontalSlider, &QSlider::sliderMoved, this, &FileWindow::on_SliderMoved);
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

        QStringList callSign = filtersDialog->callSigns_;
        QStringList address = filtersDialog->addresses_;
        QList<int> trackNumber = filtersDialog->trackNumbers_;
        QList<int> categories = filtersDialog->categories_;
        QList<int> mode3ACode = filtersDialog->mode3ACodes_;
        astFile_->ApplyFilters(categories,callSign,address,trackNumber, mode3ACode);
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

    for (;packetCounter_ < astFile_->filteredPackets_.length(); packetCounter_++) {
        DataBlock* dataBlock = astFile_->filteredPackets_.at(packetCounter_);
        int msecsTo = this->currentTime_.msecsTo(dataBlock->GetTimeOfReception());
        QString address = "", id = "", callSign = "", trackNumber = "";
        int color;
        double trackAngle = 400;
        if (dataBlock->GetCategory() == 21) {
            color = CustomMap::CAT21;
            address = dataBlock->GetAddress();
            id = address + "ADSB";
            if (dataBlock->GetCallSign() != "N/A") {
                callSign = dataBlock->GetCallSign();
            }
            else {
                callSign = "";
            }
            trackNumber = dataBlock->GetTrackNumber();
            trackAngle = dataBlock->GetTrackAngle();
        }
        else if (dataBlock->GetCategory() == 20) {
            color = CustomMap::CAT20;
            address = dataBlock->GetAddress();
            id = address + "MLAT20";
            if (dataBlock->GetCallSign() != "N/A") {
                callSign = dataBlock->GetCallSign();
            }
            else {
                callSign = "";
            }
            trackNumber = dataBlock->GetTrackNumber();
            trackAngle = dataBlock->GetTrackAngle();
        }
        else if (dataBlock->GetCategory() == 10 && dataBlock->GetTypeOfTransmission() == "CAT 10: PSR") {
            color = CustomMap::CAT10SMR;
            address = "";
            callSign = "";
            id = dataBlock->GetTrackNumber() + "SMR10";
            trackNumber = dataBlock->GetTrackNumber();
            trackAngle = dataBlock->GetTrackAngle();
        }
        else if (dataBlock->GetCategory() == 10 && dataBlock->GetTypeOfTransmission() == "CAT 10: MLAT") {
            color = CustomMap::CAT10MLAT;
            address = dataBlock->GetAddress();
            id = address + "MLAT10";
            if (dataBlock->GetCallSign() != "N/A") {
                callSign = dataBlock->GetCallSign();
            }
            else {
                callSign = "";
            }
            trackNumber = dataBlock->GetTrackNumber();
            trackAngle = dataBlock->GetTrackAngle();
        }
        if (msecsTo >= -500 && msecsTo <= 500) {
            if (alreadyAdded_.indexOf(id) == -1) {
                this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,color,id,callSign,address,trackNumber,trackAngle);
                alreadyAdded_.append(id);
            }
            else {
                this->ui->widget->DeleteMarker(id);
                this->ui->widget->AddCircleMarker(dataBlock->GetPosition(),10,color,id,callSign,address,trackNumber,trackAngle);
            }
        }

        else if (msecsTo <= -500) {

        }

        else if (msecsTo >= 500) {
            break;
        }
        this->ui->horizontalSlider->setValue(packetCounter_);
    }
}

void FileWindow::on_PacketRowClicked() {

    QModelIndexList indexes = ui->tableView->selectionModel()->selection().indexes();
    if (indexes.length() != 0) {
        QModelIndex index = indexes.at(0);
        int packet = index.data().toInt();
        QTreeWidgetItem *packetDetails = astFile_->dataBlocks->at(packet-1)->GetPacketInfo();
        PacketDetailDialog* details = new PacketDetailDialog(this,packetDetails);
        details->show();
        details->raise();
    }

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
    QTableWidgetItem *totalCount = new QTableWidgetItem(QString::number(astFile_->numberOfPackets_));
    this->ui->statsTable->setItem(0,i+1, totalLabel);
    this->ui->statsTable->setItem(1,i+1, totalCount);

    ui->statsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->statsTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->statsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->statsTable->verticalHeader()->setVisible(false);
}

void FileWindow::on_SaveFileClicked() {

    SelectSaveDialog *saveDialog = new SelectSaveDialog(this);

    int code = saveDialog->exec();
    bool saveAll = false;
    bool notClosed = true;

    if (code == 0) { //CLOSED
        notClosed = false;
    }

    else if (code == 5) {//SAVE FILTERED
        saveAll = false;
    }

    else if (code == 6) {//SAVE ALL
        saveAll = true;
    }

    if (notClosed) {

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
            this->astFile_->writeFile(filePath,saveAll);
        }

        else {
        }
    }
}

void FileWindow::on_ResetPacketsClicked() {
    astFile_->ResetFilters();
}

void FileWindow::on_ExportAsKMLCLicked() {
    SaveKMLFile();
}

void FileWindow::on_ExportAsCSVCLicked() {
    SaveCSVFile();
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

void FileWindow::SaveCSVFile() {

    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Valid Files (*.csv)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.length() == 1) {
        QString filePath = fileNames.at(0);
        QFile file(filePath);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);

            stream << "Address,CallSign,Mode 3/A,Track Number" << endl;
            stream << "Category,Coordinates" << endl;
            stream << "TimeStamps" << endl;

            for (Emitter emitter : this->astFile_->emitters_) {
                stream << emitter.GetTargetAddress() << "," << emitter.GetCallSign() << "," << emitter.GetMode3ACode() << "," << emitter.GetTrackNumber() << endl;
                if (emitter.pointsCat21.length() > 0) {
                    stream << "CAT21" << endl;
                    for (int c = 0; c < emitter.pointsCat21.length(); c++) {
                        WGS84Coordinates coord = emitter.pointsCat21.at(c);
                        stream << QString::number(coord.GetLatitude(),'g',15) << ";" << QString::number(coord.GetLongitude(),'g',15) << ",";
                    }
                    stream << endl;
                    for (int c = 0; c < emitter.timeStampsCat21.length(); c++) {
                        QTime timestamp = emitter.timeStampsCat21.at(c);
                        stream << timestamp.toString("hh:mm:ss:zzz") << ",";
                    }
                    stream << endl;
                }

                if (emitter.pointsCat20.length() > 0) {
                    stream << "CAT20" << endl;
                    for (int c = 0; c < emitter.pointsCat21.length(); c++) {
                        WGS84Coordinates coord = emitter.pointsCat20.at(c);
                        stream << QString::number(coord.GetLatitude(),'g',15) << ";" << QString::number(coord.GetLongitude(),'g',15) << ",";
                    }
                    stream << endl;
                    for (int c = 0; c < emitter.timeStampsCat20.length(); c++) {
                        QTime timestamp = emitter.timeStampsCat20.at(c);
                        stream << timestamp.toString("hh:mm:ss:zzz") << ",";
                    }
                    stream << endl;
                }

                if (emitter.pointsCat10Mlat.length() > 0) {
                    stream << "CAT10: MLAT" << endl;
                    for (int c = 0; c < emitter.pointsCat10Mlat.length(); c++) {
                        WGS84Coordinates coord = emitter.pointsCat10Mlat.at(c);
                        stream << QString::number(coord.GetLatitude(),'g',15) << ";" << QString::number(coord.GetLongitude(),'g',15) << ",";
                    }
                    stream << endl;
                    for (int c = 0; c < emitter.timeStampsCat10Mlat.length(); c++) {
                        QTime timestamp = emitter.timeStampsCat10Mlat.at(c);
                        stream << timestamp.toString("hh:mm:ss:zzz") << ",";
                    }
                    stream << endl;
                }
            }
            stream << "END" << endl;

            QMessageBox *msg = new QMessageBox(this);
            msg->setText("CSV Exported succesfully");
            msg->setStandardButtons(QMessageBox::Ok);
            msg->open();

        }

    }

    else {
    }

}

void FileWindow::SaveKMLFile() {

    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter(tr("Valid Files (*.kml)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setAcceptMode(QFileDialog::AcceptSave);

    QStringList fileNames;

    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if (fileNames.length() == 1) {
        QString filePath = fileNames.at(0);
        QFile file(filePath);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << "<?xml version='1.0' encoding='UTF-8'?>" << endl;
            stream << "<kml xmlns='http://www.opengis.net/kml/2.2'>" << endl;
            stream << "<Document>" << endl;
            stream << "<Style id='cat21Style'>" << endl;
            stream << "<LineStyle>" << endl;
            stream << "<color>641400FF</color>" << endl;
            stream << "<width>4</width>" << endl;
            stream << "</LineStyle>" << endl;
            stream << "<PolyStyle>" << endl;
            stream << "<color>641400FF</color>" << endl;
            stream << "</PolyStyle>" << endl;
            stream <<"</Style>" << endl;
            stream << "<Style id='cat20Style'>" << endl;
            stream << "<LineStyle>" << endl;
            stream << "<color>50FF78F0</color>" << endl;
            stream << "<width>4</width>" << endl;
            stream << "</LineStyle>" << endl;
            stream << "<PolyStyle>" << endl;
            stream << "<color>50FF78F0</color>" << endl;
            stream << "</PolyStyle>" << endl;
            stream <<"</Style>" << endl;
            stream << "<Style id='cat10Style'>" << endl;
            stream << "<LineStyle>" << endl;
            stream << "<color>5014B4FF</color>" << endl;
            stream << "<width>4</width>" << endl;
            stream << "</LineStyle>" << endl;
            stream << "<PolyStyle>" << endl;
            stream << "<color>5014B4FF</color>" << endl;
            stream << "</PolyStyle>" << endl;
            stream <<"</Style>" << endl;

            for (Emitter emitter : this->astFile_->emitters_) {
                stream << "<Folder><name>"+ emitter.GetCallSign() + "</name><open>1</open>" << endl;


                if (emitter.pointsCat21.length() != 0) {
                    stream << "<Placemark>" << endl;
                    stream << "<name>" << "CAT 21: ADS-B" << "</name>" << endl;
                    stream << "<styleUrl>#cat21Style</styleUrl>" << endl;
                    stream << "<LineString>" << endl;
                    stream << "<coordinates>" << endl;
                    for (WGS84Coordinates coord : emitter.pointsCat21) {

                        stream << QString::number(coord.GetLongitude(),'g',15) << "," << QString::number(coord.GetLatitude(),'g',15) << endl;

                    }

                    stream << "</coordinates>" << endl;
                    stream << "</LineString>" << endl;
                    stream << "</Placemark>" << endl;

                }
                if (emitter.pointsCat20.length() != 0) {
                    stream << "<Placemark>" << endl;
                    stream << "<name>" << "CAT 20: MLAT" << "</name>" << endl;
                    stream << "<styleUrl>#cat20Style</styleUrl>" << endl;
                    stream << "<LineString>" << endl;
                    stream << "<coordinates>" << endl;
                    for (WGS84Coordinates coord : emitter.pointsCat20) {

                        stream << QString::number(coord.GetLongitude(),'g',15) << "," << QString::number(coord.GetLatitude(),'g',15) << endl;

                    }

                    stream << "</coordinates>" << endl;
                    stream << "</LineString>" << endl;
                    stream << "</Placemark>" << endl;
                }
                if (emitter.pointsCat10Mlat.length() != 0) {

                    stream << "<Placemark>" << endl;
                    stream << "<name>" << "CAT 10: MLAT" << "</name>" << endl;
                    stream << "<styleUrl>#cat10Style</styleUrl>" << endl;
                    stream << "<LineString>" << endl;
                    stream << "<coordinates>" << endl;
                    for (WGS84Coordinates coord : emitter.pointsCat10Mlat) {

                        stream << QString::number(coord.GetLongitude(),'g',15) << "," << QString::number(coord.GetLatitude(),'g',15) << endl;

                    }

                    stream << "</coordinates>" << endl;
                    stream << "</LineString>" << endl;
                    stream << "</Placemark>" << endl;
                }
                stream << "</Folder>" << endl;
            }
            stream << "</Document>" << endl;
            stream << "</kml>" << endl;

            QMessageBox *msg = new QMessageBox(this);
            msg->setText("KML Exported succesfully");
            msg->setStandardButtons(QMessageBox::Ok);
            msg->open();
        }
    }

    else {
    }

}

void FileWindow::on_SeeEmittersDetailsClicked() {

    QModelIndexList indexes = ui->loadedFlights->selectionModel()->selectedRows();
    if (indexes.length() != 0) {
        QModelIndex index = indexes.at(0);
        int emitterNum = index.row();
        Emitter emitterSelected = this->astFile_->emitters_.at(emitterNum);

        EmitterDetailsWindow* emitterWindow = new EmitterDetailsWindow(this, &emitterSelected);
        emitterWindow->show();
        emitterWindow->raise();
    }
    else {
        QMessageBox *errorDialog = new QMessageBox(this);
        errorDialog->setText("Select a Emitter first");
        errorDialog->setIcon(QMessageBox::Warning);
        errorDialog->exec();
    }
}

void FileWindow::on_x1Clicked() {
    playTimer_->setInterval(500);
}

void FileWindow::on_x2Clicked() {
    playTimer_->setInterval(250);
}
void FileWindow::on_x8Clicked() {
    playTimer_->setInterval(62);

}
void FileWindow::on_x16Clicked() {
    playTimer_->setInterval(31);
}

void FileWindow::on_StartMulticastClicked() {

    EmitFileDialog *emitWindow = new EmitFileDialog(this,astFile_);
    emitWindow->show();
    emitWindow->raise();
}

void FileWindow::on_SliderMoved(int position) {
    packetCounter_ = position;
    DataBlock *dataBlock = astFile_->dataBlocks->at(position);
    int hour = dataBlock->GetTimeOfReception().hour();
    int min = dataBlock->GetTimeOfReception().minute();
    int sec = dataBlock->GetTimeOfReception().second();

    currentTime_ = QTime(hour,min,sec,0);
    this->ui->timerLabel->setText(currentTime_.toString("hh:mm:ss:zzz"));
}



