#include "manualvehicleentry.hpp"
#include "ui_manualvehicleentry.h"

#include "databasemanager.hpp"
#include <QTimer>

ManualVehicleEntry::ManualVehicleEntry(DatabaseManager* dbmanager,bool isNightPlan, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualVehicleEntry)
{
    ui->setupUi(this);
    this->setAttribute( Qt::WA_DeleteOnClose, true );
    m_dbmanager = dbmanager;
    m_nightplan = isNightPlan;
    QStringList colors;
    for(qint32 id : m_dbmanager->getColors()) colors.append(m_dbmanager->getColors().key(id));
    ui->comboBox_colors->addItems(colors);
    QStringList types;
    for(qint32 id : m_dbmanager->getVehicleTypes()) types.append(m_dbmanager->getVehicleTypes().key(id));
    ui->comboBox_types->addItems(types);
}

ManualVehicleEntry::~ManualVehicleEntry()
{
    delete ui;
}

void ManualVehicleEntry::on_pushButton_clicked()
{
    if(validateForm()){
        QString errormsg;
        qint32 vehicleid;
        if(!m_dbmanager->NewVehicleEntry(ui->lineEdit_plate->text(),ui->lineEdit_model->text(),ui->comboBox_types->currentText(),ui->comboBox_colors->currentText(),errormsg,vehicleid)){
            ui->label_error->setText(errormsg);
            return;
        }
        if(!m_dbmanager->NewPaymentEntry(vehicleid,errormsg)){
            ui->label_error->setText(errormsg);
            return;
        }
        ui->pushButton->setEnabled(false);
        ui->label_error->setStyleSheet("color:green;");
        ui->label_error->setText("Giriş yapıldı.");
        QTimer::singleShot(2000,this,&QDialog::close);
    }
}

bool ManualVehicleEntry::validateForm()
{
    if(ui->lineEdit_plate->text().isEmpty()){
        ui->label_error->setText("ARAÇ PLAKASINI GİRİN");
        return false;
    }
    return true;
}