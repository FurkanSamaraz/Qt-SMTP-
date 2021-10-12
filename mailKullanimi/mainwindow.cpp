#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SmtpMime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    gonderilecek_mail = ui->lineEdit->text();
    gonderilecek_konu = ui->lineEdit_2->text();
    gonderilecek_mesaj = ui->textEdit->toPlainText();

    // This is a first demo application of the SmtpClient for Qt project

    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.gmail.com, port 465, ssl)

   SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and the password
    // for smtp authentification.

    smtp.setUser("samaraz545454@gmail.com");
    smtp.setPassword("sifren");

    // Now we create a MimeMessage object. This will be the email.

    MimeMessage message;

    message.setSender(new EmailAddress("samaraz545454@gmail.com", "Kurumsal"));
    message.addRecipient(new EmailAddress(gonderilecek_mail, "Kişisel"));
    message.setSubject(gonderilecek_konu);

    // Now add some text to the email.
    // First we create a MimeText object.

    MimeText text;

    text.setText(gonderilecek_mesaj);

    // Now add it to the mail

    message.addPart(&text);

    // Now we can send the mail

    smtp.connectToHost();
    smtp.login();
    if(smtp.sendMail(message)){
        QMessageBox::information(this,"Başarılı","Mail iletilmiştir.");
    }else{
        QMessageBox::critical(this,"Başarısız","Mail iletilemedi.");
    }
    //smtp.sendMail(message);
    smtp.quit();
}
