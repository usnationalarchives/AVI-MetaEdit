// AVI MetaEdit GUI - A GUI for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "GUI/Qt/GUI_Main_xxxx_TimeReferenceDialog.h"
#include "Common/Core.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include <QtGui/QTimeEdit>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtCore/QEvent>
#include <QtGui/QGridLayout>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QIcon>
#include <QtGui/QMessageBox>
#include <QtGui/QSpinBox>
#include <QtGui/QCheckBox>
#include <ZenLib/Ztring.h>
using namespace ZenLib;
//---------------------------------------------------------------------------

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_xxxx_TimeReferenceDialog::GUI_Main_xxxx_TimeReferenceDialog(Core* _C, const std::string &FileName_, const std::string &Field_, QWidget* parent)
: QDialog(parent)
{
    //Internal
    C=_C;
    FileName=FileName_;
    Field=Field_;

    //Configuration
    setWindowFlags(windowFlags()&(0xFFFFFFFF-Qt::WindowContextHelpButtonHint));
    setWindowTitle(Field.c_str());
    setWindowIcon (QIcon(":/Image/Brand/Logo.gif"));

    //Get info
    FrameRate=Ztring(C->Get(FileName, "FrameRate")).To_float32();
    if (FrameRate==0)
        FrameRate=29.97;    
    
    //Buttons
    QDialogButtonBox* Dialog=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    connect(Dialog, SIGNAL(accepted()), this, SLOT(OnAccept()));
    connect(Dialog, SIGNAL(rejected()), this, SLOT(reject()));

    TimeEdit_Label=new QLabel(this);
    TimeEdit_Label->setText(tr("HH:MM:SS"));
    TimeEdit=new QTimeEdit(this);
    TimeEdit->setDisplayFormat("hh:mm:ss");
    connect(TimeEdit, SIGNAL(timeChanged (const QTime&)), this, SLOT(OnTimeChanged (const QTime&)));
    FrameEdit_Label=new QLabel(this);
    FrameEdit_Label->setText(tr("FF"));
    FrameEdit=new QSpinBox(this);
    if (FrameRate-((int8u)FrameRate))
        FrameEdit->setRange(0, ((int8u)FrameRate));
    else
        FrameEdit->setRange(0, ((int8u)FrameRate)-1);
    DropFrameEdit=new QCheckBox(this);
    DropFrameEdit->setText("Drop frame");
    Label=new QLabel(this);
    Label->setText(("Video stream is at "+C->Get(FileName, "FrameRate")+" frames per seconds").c_str());
        
    QGridLayout* L=new QGridLayout();
    L->addWidget(TimeEdit_Label, 0, 0);
    L->addWidget(TimeEdit, 1, 0);
    L->addWidget(FrameEdit_Label, 0, 1);
    L->addWidget(FrameEdit, 1, 1);
    L->addWidget(DropFrameEdit, 2, 0, 1, 2);
    L->addWidget(Label, 3, 0, 1, 2);
    L->addWidget(Dialog, 4, 0, 1, 2);

    setLayout(L);

    //Filling
    Ztring TimeReference=C->Get(FileName, Field);
    Ztring FrameCount;
    bool DropFrame=(FrameRate!=(int8u)FrameRate);
    if (TimeReference.size()>9 && C->IsValid(FileName, Field, TimeReference))
    {
        FrameCount=TimeReference.substr(9, string::npos);
        if (Field_!="ISMP")
            DropFrame=TimeReference[8]==_T(';');
        TimeReference.resize(8);
    }
    TimeEdit->setTime(QTime::fromString(QString().fromUtf8(TimeReference.To_Local().c_str()), Qt::ISODate));
    FrameEdit->setValue(FrameCount.To_int32u());
    if (Field_=="ISMP")
        DropFrameEdit->setVisible(false); //No Drop frame for ISMP
    else
        DropFrameEdit->setChecked(DropFrame);
    IsChanging=false;
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main_xxxx_TimeReferenceDialog::OnAccept ()
{
    std::string Value=TimeEdit->time().toString("HH:mm:ss").toLocal8Bit().data();
    if (Value.size()!=8)
    {
        accept();
        return; //Error somewhere in the box, silently discard
    }

    if (Field=="ISMP")
        Value+='.';
    else
        Value+=DropFrameEdit->isChecked()?';':':';
    Ztring FrameCount; FrameCount.From_Number(FrameEdit->value());
    if (FrameCount.size()==1)
        FrameCount.insert(0, 1, _T('0'));
    Value+=FrameCount;
    if (!C->IsValid(FileName, Field, Value))
    {
        QMessageBox MessageBox;
        MessageBox.setWindowTitle("AVI MetaEdit");
        MessageBox.setText((string("Field does not conform to rules:\n")+C->IsValid_LastError(FileName)).c_str());
        #if (QT_VERSION >= 0x040200)
            MessageBox.setStandardButtons(QMessageBox::Ok);
        #endif // (QT_VERSION >= 0x040200)
        MessageBox.setIcon(QMessageBox::Warning);
        MessageBox.setWindowIcon(QIcon(":/Image/Brand/Logo.gif"));
        MessageBox.exec();
        return;
    }

    C->Set(FileName, Field, Value);

    accept();
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_TimeReferenceDialog::OnTimeChanged (const QTime &Time)
{
    if (IsChanging)
        return;

    QTime Time_Temp=TimeEdit->time();
    if (Time_Temp.msec()>=FrameRate)
    {
        Time_Temp=Time_Temp.addMSecs(-1);
        TimeEdit->setTime(Time_Temp);
    }
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_TimeReferenceDialog::OnValueEdited (const QString &Value)
{
}

