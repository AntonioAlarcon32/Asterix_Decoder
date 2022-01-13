#include <hdr/asterix_lib/asterixfile.h>



AsterixFile::AsterixFile()
{
    dataBlocks = new QList<DataBlock*>(); //List of Datablocks of all categories, decoded packets go here.
    packetTable_ = new QStandardItemModel; //Model for frontend to show packets in table
    emitterTable_ = new QStandardItemModel; //Model for frontend to show emitters in table
    emitters_ = QList<Emitter>(); //List of all emitters detected
    fileInfo_ = QFileInfo(); //Info of file for getting statistics about it
    categoryStats_ = QMap<int,int>(); //Map for saving how many packets of each category are in the file;
    filteredPackets_ = QList<DataBlock*>(); //Modifiable list for filtered packets, at start, same as datablocks
    numberOfPackets_ = 0;
}

AsterixFile::~AsterixFile() {


    while (dataBlocks->count())
         delete dataBlocks->takeLast(); //Delete all datablocks

    delete dataBlocks; //Delete list structure
    delete packetTable_; //Delete model
}

void AsterixFile::readFile(QString path) {

    dataBlocks->clear();
    packetTable_->clear();      //Clear all starting data

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))        //Check if file can be opened
        return;
    fileInfo_ = QFileInfo(file);                //Get info of file
    QByteArray fileBinary = file.readAll();     //Get all the file at one array
    int numOfPackets = 0;
    QElapsedTimer* testTime = new QElapsedTimer();  //Timer for calculating loading time
    testTime->start();
    int offset;                                     //Location of the start of each datablock
    bool packetDecoded = false;                     //Bool to check if the packet has been decoded properly
    if (fileInfo_.completeSuffix() == "ast") {
        offset = 0;
    }
    else if (fileInfo_.completeSuffix() == "gps") {         //Add the offset to remove the header of gps files
        offset = 2200;
    }
    else {
        return;
    }

    for (; offset < fileBinary.length(); ) {                //loop all the file


        int category = fileBinary[offset];                      //First byte is category
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1] ;            //Bytes 2 and 3 carry size
        packetDecoded = false;

        try {

            if (category == 10) {

                Cat10 *cat10Block = new Cat10();                    //Manually allocate and create the class
                cat10Block->SetLength(length);                      //Set the length of the datablock
                QByteArray data = fileBinary.mid(offset,length);
                cat10Block->SetData(data);                          //Save that bytes for being able to save them later
                cat10Block->offset = 3;                             //Offset to remove cat and size inside the packet
                cat10Block->DecodeFSPEC();                          //Execute function to get full FSPEC
                cat10Block->FullDecode();                           //Decode full packet
                dataBlocks->append(cat10Block);                     //Add the packet to decoded packets list
            }

            else if (category == 19) {
                Cat19 *cat19Block = new Cat19();
                cat19Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat19Block->SetData(data);
                cat19Block->offset = 3;
                cat19Block->DecodeFSPEC();
                cat19Block->FullDecode();
                dataBlocks->append(cat19Block);

            }

            else if (category == 20) {
                Cat20 *cat20Block = new Cat20();
                cat20Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat20Block->SetData(data);
                cat20Block->offset = 3;
                cat20Block->DecodeFSPEC();
                cat20Block->FullDecode();
                dataBlocks->append(cat20Block);

            }

            else if (category == 21) {
                Cat21 *cat21Block = new Cat21();
                cat21Block->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                cat21Block->SetData(data);
                cat21Block->offset = 3;
                cat21Block->DecodeFSPEC();
                cat21Block->FullDecode();
                dataBlocks->append(cat21Block);
            }

            else {

                OtherDataBlocks *other = new OtherDataBlocks(category);         //Class in case packet can be decoded
                other->SetLength(length);
                QByteArray data = fileBinary.mid(offset,length);
                other->SetData(data);
                other->offset = 3;
                dataBlocks->append(other);
            }
            packetDecoded = true;                                       //Packet has been decoded completely


        }  catch (...) {

            packetDecoded = false;                              //Packet decoding failed
            qDebug() << "ERROR IN PACKET" << numOfPackets + 1;      //Print error

        }

        if (packetDecoded == true) {
            numOfPackets++;                 //Add one to decoded packets

            if (categoryStats_.value(category,0) == 0) {
                categoryStats_.insert(category,1);              //If category wasnt detected, add it to the map
            }
            else {
                categoryStats_[category]++;                     //Add one to the detected category
            }

            dataBlocks->at(numOfPackets-1)->SetNumOfPacket(numOfPackets);       //Set the num of packet of the decoded packet

            QString typeOfMessage = dataBlocks->last()->GetTypeOfMessage();
            QTime timeOfReception = dataBlocks->last()->GetTimeOfReception();
            QString sicsac = dataBlocks->last()->GetSACSIC();                       //Get data common to all categories
            QString timeToShow = "N/A";

            if (!timeOfReception.isNull()) {
                timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
            }

            if ((numOfPackets % 1000) == 0) {
                emit packetLoaded();
            }
            packetTable_->appendRow({new QStandardItem(QString::number(numOfPackets)),new QStandardItem(QString::number(category)),
                                     new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                     new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});          //Add row to the model
        }
        offset += length;                               //Add offset so next time the loop gets next packet
        if (fileInfo_.completeSuffix() == "gps") {
            offset += 10;                               //Add another 10 of offset between gps packets
        }
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"}); //Set horizontal headers
    this->ProcessEmitters();            //When we get all the packets decoded, proccess all the emitters
    filteredPackets_ = *dataBlocks;     //At first, filtered packets are equal to all of them

    emit finishLoading();
     qDebug() << "Loading took" << testTime->elapsed() << "milliseconds";
     qDebug() << "Loaded " << numOfPackets << " packets";
     this->numberOfPackets_ = numOfPackets;
}

int AsterixFile::GetTotalPackets(QString path) { //Function that loops around the file to calculate the number of packets on them.

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return 0;
    QFileInfo fileInfo = QFileInfo(file);
    QByteArray fileBinary = file.readAll();
    int numOfPackets = 0;
    QElapsedTimer* testTime = new QElapsedTimer();
    testTime->start();
    int offset;
    if (fileInfo.completeSuffix() == "ast") {
        offset = 0;
    }
    else if (fileInfo.completeSuffix() == "gps") {
        offset = 2200;
    }
    else {
        return 0;
    }

    for (; offset < fileBinary.length(); ) {
        int length =  fileBinary[offset + 2] << fileBinary[offset + 1];
        numOfPackets++;
        offset += length;
        if (fileInfo.completeSuffix() == "gps") {
            offset += 10;
        }
    }
    return numOfPackets;
}

void AsterixFile::ProcessEmitters() {

    QList<QString> addresses = QList<QString>();        //List of already added addresses
    int c = 0;

    for (DataBlock *dataBlock : *dataBlocks) {          //Loop all the datablocks

        if (dataBlock->GetAddress() != "N/A") {
            QString address = dataBlock->GetAddress();      //Get address of the datablock if is not null
            int index = addresses.indexOf(address);             //Search for it in the list of addresses

            if (index == -1) {
                Emitter emitter = Emitter(address,dataBlock->GetTypeOfTransmission());
                emitter.AddPoint(dataBlock->GetPosition(),dataBlock->GetTimeOfReception(),dataBlock->GetCategory(),dataBlock->GetTypeOfTransmission());     //if not detected, we create the emitter and add the point and timestamp
                if (dataBlock->GetCallSign() != "N/A") {
                    emitter.SetCallSign(dataBlock->GetCallSign());
                }
                if (dataBlock->GetTrackNumber() != "N/A") {
                    emitter.SetTrackNumber(dataBlock->GetTrackNumber());
                }

                if (dataBlock->GetMode3A() != "N/A") {
                    emitter.SetMode3ACode(dataBlock->GetMode3A());
                }

                emitters_.append(emitter);          //Add the emitter to the list of emitters and addresses
                addresses.append(address);
            }
            else {
                emitters_[index].AddPoint(dataBlock->GetPosition(),dataBlock->GetTimeOfReception(),dataBlock->GetCategory(),dataBlock->GetTypeOfTransmission());   //if the packet is detected, just add the point and timestamp
            }
        }
    }
    for (Emitter emitter: emitters_) {
        QString detectedEmission = "N/A";
        if (emitter.GetDetectedEmissions().length() != 0) {         //Get all categories of the emitter
            detectedEmission = emitter.GetDetectedEmissions().join(",");
        }

        emitterTable_->appendRow({new QStandardItem(emitter.GetCallSign()), new QStandardItem(emitter.GetTargetAddress()),
                                  new QStandardItem(emitter.GetFirstReport().toString("hh:mm:ss:zzz")),
                                  new QStandardItem(emitter.GetLastReport().toString("hh:mm:ss:zzz")),new QStandardItem(detectedEmission)});        //add the emitter to the table
    }
    emitterTable_->setHorizontalHeaderLabels({"CallSign","Target Address", "First Report at", "Last Report At", "Detected Emissions"});
}

void AsterixFile::FilterByCallSign(QStringList callSign, QList<DataBlock*> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        DataBlock* dataBlock = packetList.at(i);
        int present = callSign.indexOf(dataBlock->GetCallSign());
        if (present != -1) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByCategory(QList<int> category, QList<DataBlock*> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        DataBlock* dataBlock = packetList.at(i);
        int present = category.indexOf(dataBlock->GetCategory());
        if (present != -1) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByAddress(QStringList address, QList<DataBlock*> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        DataBlock* dataBlock = packetList.at(i);
        int present = address.indexOf(dataBlock->GetAddress());
        if (present != -1) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByTrackNumber(QList<int> trackNumber, QList<DataBlock*> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        DataBlock* dataBlock = packetList.at(i);
        int present = trackNumber.indexOf(dataBlock->GetTrackNumber().toInt());
        if (present != -1) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::FilterByMode3A(QList<int> mode3ACode, QList<DataBlock*> &packetList) {
    int i = 0;
    while (i < packetList.length()) {
        DataBlock* dataBlock = packetList.at(i);
        int present = mode3ACode.indexOf(dataBlock->GetMode3A().toInt());
        if (present != -1) {
            i++;
        }
        else {
            packetList.removeAt(i);
        }

    }
}

void AsterixFile::ApplyFilters(QList<int> category, QStringList callSign, QStringList address, QList<int> trackNumber, QList<int> mode3ACode) {

    if (category.length() != 0) {
        this->FilterByCategory(category,this->filteredPackets_);
    }

    if (callSign.length() != 0) {
        this->FilterByCallSign(callSign,this->filteredPackets_);
    }

    if (address.length() != 0) {
        this->FilterByAddress(address,this->filteredPackets_);                  //Check input to see which filters are required, then execute them
    }

    if (trackNumber.length() != 0) {
        this->FilterByTrackNumber(trackNumber,this->filteredPackets_);
    }

    if (mode3ACode.length() != 0) {
        this->FilterByMode3A(mode3ACode,this->filteredPackets_);
    }

    packetTable_->clear();                                                  //Clear the packet table

    for (DataBlock* dataBlock : this->filteredPackets_) {

        QString typeOfMessage = dataBlock->GetTypeOfMessage();
        QTime timeOfReception = dataBlock->GetTimeOfReception();
        QString sicsac = dataBlock->GetSACSIC();
        QString timeToShow = "N/A";
        int category = dataBlock->GetCategory();
        int packetNumber = dataBlock->GetNumOfPacket();                         //Add just the filtered packets to the table
        int length = dataBlock->GetLength();

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(packetNumber)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
}

void AsterixFile::ResetFilters() {
    filteredPackets_ = *dataBlocks;
    packetTable_->clear();
    for (DataBlock *dataBlock : *dataBlocks) {
        QString typeOfMessage = dataBlock->GetTypeOfMessage();
        QTime timeOfReception = dataBlock->GetTimeOfReception();
        QString sicsac = dataBlock->GetSACSIC();
        QString timeToShow = "N/A";
        int category = dataBlock->GetCategory();
        int packetNumber = dataBlock->GetNumOfPacket();                         //Add all the packets to the filtered packets to reset it, then rebuild the table
        int length = dataBlock->GetLength();

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(packetNumber)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
    }
    packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
}

void AsterixFile::writeFile(QString filePath, bool saveAll) {           //Function to save asterix file
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly)) {
        qDebug() << "Could not open file for writing";
        return;
    }

    if (saveAll) {
        for (DataBlock* dataBlock : *this->dataBlocks) {                //If all packets want to be saved, loop the list of datablocks
            file.write(dataBlock->GetData());
        }
    }

    else {
        for (DataBlock* dataBlock : this->filteredPackets_) {           //If just filtered packets want to be saved, save filtered packets list
            file.write(dataBlock->GetData());
        }
    }
}

bool AsterixFile::AddPacketToList(QByteArray data) {                    //Function that adds a packet given the bytes of it, used in liveCapture

    int category = data.at(0);
    int length =  data.at(2) << data.at(1) ;
    bool packetDecoded = false;

    try {

        if (category == 10) {
            Cat10 *cat10Block = new Cat10();
            cat10Block->SetLength(length);
            cat10Block->SetData(data);
            cat10Block->offset = 3;
            cat10Block->DecodeFSPEC();
            cat10Block->FullDecode();
            dataBlocks->append(cat10Block);
        }

        else if (category == 19) {
            Cat19 *cat19Block = new Cat19();
            cat19Block->SetLength(length);
            cat19Block->SetData(data);
            cat19Block->offset = 3;
            cat19Block->DecodeFSPEC();
            cat19Block->FullDecode();
            dataBlocks->append(cat19Block);

        }

        else if (category == 20) {
            Cat20 *cat20Block = new Cat20();
            cat20Block->SetLength(length);
            cat20Block->SetData(data);
            cat20Block->offset = 3;
            cat20Block->DecodeFSPEC();
            cat20Block->FullDecode();
            dataBlocks->append(cat20Block);

        }

        else if (category == 21) {
            Cat21 *cat21Block = new Cat21();
            cat21Block->SetLength(length);
            cat21Block->SetData(data);
            cat21Block->offset = 3;
            cat21Block->DecodeFSPEC();
            cat21Block->FullDecode();
            dataBlocks->append(cat21Block);
        }

        else {
            OtherDataBlocks *other = new OtherDataBlocks(category);
            other->SetLength(length);
            other->SetData(data);
            other->offset = 3;
            dataBlocks->append(other);
        }
        packetDecoded = true;
    }  catch (...) {
        packetDecoded = false;
        qDebug() << "ERROR IN PACKET";

    }

    if (packetDecoded == true) {

        numberOfPackets_++;

        if (categoryStats_.value(category,0) == 0) {
            categoryStats_.insert(category,1);
        }
        else {
            categoryStats_[category]++;
        }

        dataBlocks->at(numberOfPackets_-1)->SetNumOfPacket(numberOfPackets_);

        int numberOfPacket = dataBlocks->last()->GetNumOfPacket();
        QString typeOfMessage = dataBlocks->last()->GetTypeOfMessage();
        QTime timeOfReception = dataBlocks->last()->GetTimeOfReception();
        QString sicsac = dataBlocks->last()->GetSACSIC();
        QString timeToShow = "N/A";

        if (!timeOfReception.isNull()) {
            timeToShow = timeOfReception.toString("hh:mm:ss:zzz");
        }

        packetTable_->appendRow({new QStandardItem(QString::number(numberOfPacket)),new QStandardItem(QString::number(category)),
                                 new QStandardItem(QString::number(length)),new QStandardItem(sicsac),
                                 new QStandardItem(timeToShow),new QStandardItem(typeOfMessage)});
        packetTable_->setHorizontalHeaderLabels({"Packet","Category", "Length", "SAC/SIC", "Time of Transmission", "Type of Message"});
    }
    return packetDecoded;
}





