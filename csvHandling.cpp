#include "mainwindow.h"
#include "ui_mainwindow.h"

// speichert den Pfad aus der Tabelle ins Array
void MainWindow::on_acceptPath_clicked()
{
    QModelIndex index;
    for (int i = 0; i < model->rowCount(); ++i) {
            for (int x = 0; x < 8; ++x) {
                index = model->index(i,x);
                if(index.isValid())
                {   path[x][i] = model->data(index).toInt();
                }
                else qDebug() << "invalid String";
            }
            qDebug() << path[0][i] << path[1][i] << path[2][i] << path[3][i] << path[4][i] << path[5][i] << path[6][i] << path[7][i];
        }
}

// schreibt alle Punkte aus dem path Array in ein csv file "," getrennt "\n" newline
void MainWindow::on_saveCsv_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Speicherort festlegen..."),
                                                 QDir::currentPath(),"CSV (*.csv);;Text Files (*.txt);;log Files (*.log);;All files (*.*)");
    waypointsWrite.setFileName(fileName);
    if (waypointsWrite.exists()) waypointsWrite.remove();
    waypointsWrite.open(QIODevice::WriteOnly | QIODevice::Text);
    if(waypointsWrite.isOpen()) qDebug() << "File erstellt.";
    else qDebug() << "File erstellen oder öffnen fehlgeschlagen";

    QByteArray waypointsByteArray;
    for (int i = 0; i < 256; ++i) {
        for (int x = 0; x < 8; ++x) {
            waypointsByteArray.append(QByteArray::number(path[x][i]));
            waypointsByteArray.append(",");
        }
        waypointsByteArray.append("\n");
    }
    waypointsWrite.write(waypointsByteArray);
    waypointsWrite.close();
}

//csv Datei mit Pfad öffnen und in Tabelle anzeigen
void MainWindow::on_chooseFile_triggered()
{
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv);;Text Files (*.txt);;log Files (*.log);;All files (*.*)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QString data = file.readAll();
        data.remove( QRegExp("\r") ); //remove all ocurrences of CR (Carriage Return)
        QString temp;
        QChar character;
        QTextStream textStream(&data);
        while (!textStream.atEnd()) {
            textStream >> character;
            if (character == ',') {
                checkString(temp, character);
            } else if (character == '\n') {
                checkString(temp, character);
            } else if (textStream.atEnd()) {
                temp.append(character);
                checkString(temp);
            } else {
                temp.append(character);
            }
        }
    }

    ui->tabWidget->setCurrentIndex(1); //öffnet Tab mit Index 1
}

// für loadCsv, sucht nächsten Datenpunkt im table. schneidet Feld zwischen zwei ',' aus, casten zu float und gibt diesen Wert zurück
int MainWindow::getDataFloat(QByteArray waypointsByteArray)
{
    searchIndex++;uint startData = searchIndex;               //zu nächstem Datenpaket springen
    bool conversion_OK;

    while(!(waypointsByteArray.at(searchIndex) == ',')) searchIndex++;    //Iteriert bis nächsten ','
    QByteArray data = waypointsByteArray.mid(startData, searchIndex - startData); //Datenpunkt aus File extrahieren
    return(data.toFloat(&conversion_OK));                     //Wert von hexString nach float
}

// String des Datastreams wird überprüft und anschließend ins Objekt "model" geschrieben
void MainWindow::checkString(QString &temp, QChar character)
{
    if(temp.count("\"")%2 == 0) {
        //if (temp.size() == 0 && character != ',') //problem with line endings
        //    return;
        if (temp.startsWith( QChar('\"')) && temp.endsWith( QChar('\"') ) ) {
            temp.remove( QRegExp("^\"") );
            temp.remove( QRegExp("\"$") );
        }
        //FIXME: will possibly fail if there are 4 or more reapeating double quotes
        temp.replace("\"\"", "\"");
        QStandardItem *item = new QStandardItem(temp);
        standardItemList.append(item);
        if (character != QChar(',')) {
            model->appendRow(standardItemList);
            standardItemList.clear();
        }
        temp.clear();
    } else {
        temp.append(character);
    }
}

//Pfad des Arrays in Tabelle anzeigen
void MainWindow::on_showArrayPath_triggered()
{
    QModelIndex index;

    model = new QStandardItemModel(this);
    model->setRowCount(256);
    model->setColumnCount(8);

    ui->tableView->setModel(model);

    for (int i = 0; i < 256; ++i) {
            for (int x = 0; x < 8; ++x) {
                index = model->index(i,x);
                model->setData(index,path[x][i]);
                }
//            qDebug() << path[0][i] << path[1][i] << path[2][i] << path[3][i] << path[4][i] << path[5][i] << path[6][i] << path[7][i];
        }
ui->tabWidget->setCurrentIndex(1); //öffnet Tab mit Index 1
}
