// AVI MetaEdit GUI - A GUI for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "GUI/Qt/GUI_Main_xxxx_CodingHistoryDialog.h"
#include "Common/Core.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include <QtGui/QLabel>
#include <QtCore/QEvent>
#include <QtGui/QFont>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QTableWidget>
#include <QtGui/QFileDialog>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include <QtGui/QComboBox>
#include <QtGui/QTextEdit>
#include <QtGui/QMessageBox>
#include <QtGui/QDesktopWidget>
//---------------------------------------------------------------------------

//***************************************************************************
// CodingHistoryDialog_TableWidget
//***************************************************************************

//---------------------------------------------------------------------------
CodingHistoryDialog_TableWidget::CodingHistoryDialog_TableWidget (ZtringListList &List_, QWidget *parent)
: QTableWidget(parent)
{
    Updating=false;
    List=&List_;
}

//---------------------------------------------------------------------------
void CodingHistoryDialog_TableWidget::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight ) 
{
    if (Updating)
        return;

    //Retrieving data
    size_t Row=(size_t)topLeft.row();
    size_t Column=(size_t)topLeft.column();
    string Value=topLeft.model()->data(topLeft.model()->index(topLeft.row(), topLeft.column(), rootIndex())).toString().toLocal8Bit().data();
    
    //Sizing
    if (Row>=List->size())
        List->resize(Row+1);    
    if (Column>=(*List)[Row].size())
        (*List)[Row].resize(Column+1);    

    //Filling
    (*List)[Row][Column]=Value;

    //Adapting
    if (Row+1==(*List).size())
    {
        bool IsEmpty=true;
        for (size_t Pos=0; Pos<(*List)[Row].size(); Pos++)
            if (!(*List)[Row][Pos].empty())
                IsEmpty=false;
        if (!IsEmpty)
        {
            setRowCount((int)(*List).size()+1);
            resizeRowsToContents();
        }
    }
}

//***************************************************************************
// CodingHistoryDialog_Delegate
//***************************************************************************

//---------------------------------------------------------------------------
CodingHistoryDialog_Delegate::CodingHistoryDialog_Delegate(QObject *parent)
: QItemDelegate(parent)
{
}

//---------------------------------------------------------------------------
QWidget *CodingHistoryDialog_Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
    QComboBox* Editor=new QComboBox(parent);
    Editor->setEditable(true);
    Editor->installEventFilter(const_cast<CodingHistoryDialog_Delegate*>(this));

    return Editor;
}

//---------------------------------------------------------------------------
void CodingHistoryDialog_Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString Value=index.model()->data(index, Qt::DisplayRole).toString();
    QComboBox* Editor=static_cast<QComboBox*>(editor);

    Fill(Editor);
    
    for (int Pos=0; Pos<Editor->count(); Pos++)
        if (Value==Editor->itemText(Pos))
            Editor->setCurrentIndex(Pos);
}

//---------------------------------------------------------------------------
void CodingHistoryDialog_Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* Editor=static_cast<QComboBox*>(editor);
    QString Value=Editor->currentText();

    model->setData(index, Value);
}

//---------------------------------------------------------------------------
void CodingHistoryDialog_Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}


//***************************************************************************
// RoleDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void RoleDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("source object");
    Editor->addItem("playback device");
    Editor->addItem("capture device");
    Editor->addItem("capture software");
    Editor->addItem("operating system");
}

//***************************************************************************
// SignalDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void SignalDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("IEEE1394");
    Editor->addItem("SDI");
    Editor->addItem("Component");
    Editor->addItem("Composite");
    Editor->addItem("HD-SDI");
    Editor->addItem("S-Video");
}

//***************************************************************************
// FrameRateDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void FrameRateDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("10");
    Editor->addItem("12");
    Editor->addItem("15");
    Editor->addItem("18");
    Editor->addItem("20");
    Editor->addItem("23.98");
    Editor->addItem("24");
    Editor->addItem("25");
    Editor->addItem("29.97");
    Editor->addItem("30");
}

//***************************************************************************
// SamplingFrequencyDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void SamplingFrequencyDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("8000");
    Editor->addItem("11000");
    Editor->addItem("22050");
    Editor->addItem("24000");
    Editor->addItem("32000");
    Editor->addItem("44100");
    Editor->addItem("48000");
    Editor->addItem("64000");
    Editor->addItem("88200");
    Editor->addItem("96000");
}

//***************************************************************************
// VideoPixelFormatDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void VideoPixelFormatDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("abgr");
    Editor->addItem("argb");
    Editor->addItem("bgr24");
    Editor->addItem("bgr444be");
    Editor->addItem("bgr444le");
    Editor->addItem("bgr48be");
    Editor->addItem("bgr48le");
    Editor->addItem("bgra");
    Editor->addItem("bgra64be");
    Editor->addItem("bgra64le");
    Editor->addItem("gray");
    Editor->addItem("gray16be");
    Editor->addItem("gray16le");
    Editor->addItem("gray8a");
    Editor->addItem("monob");
    Editor->addItem("monow");
    Editor->addItem("pal8");
    Editor->addItem("rgb0");
    Editor->addItem("rgb24");
    Editor->addItem("rgb4");
    Editor->addItem("rgb444be");
    Editor->addItem("rgb444le");
    Editor->addItem("rgb48be");
    Editor->addItem("rgb48le");
    Editor->addItem("rgba");
    Editor->addItem("rgba64be");
    Editor->addItem("rgba64le");
    Editor->addItem("uyvy422");
    Editor->addItem("uyyvyy411");
    Editor->addItem("yuv410p");
    Editor->addItem("yuv411p");
    Editor->addItem("yuv420p");
    Editor->addItem("yuv420p10be");
    Editor->addItem("yuv420p10le");
    Editor->addItem("yuv420p16be");
    Editor->addItem("yuv420p16le");
    Editor->addItem("yuv420p9be");
    Editor->addItem("yuv420p9le");
    Editor->addItem("yuv422p");
    Editor->addItem("yuv422p10be");
    Editor->addItem("yuv422p10le");
    Editor->addItem("yuv422p16be");
    Editor->addItem("yuv422p16le");
    Editor->addItem("yuv422p9be");
    Editor->addItem("yuv422p9le");
    Editor->addItem("yuv440p");
    Editor->addItem("yuv444p");
    Editor->addItem("yuv444p10be");
    Editor->addItem("yuv444p10le");
    Editor->addItem("yuv444p16be");
    Editor->addItem("yuv444p16le");
    Editor->addItem("yuv444p9be");
    Editor->addItem("yuv444p9le");
    Editor->addItem("yuva420p");
    Editor->addItem("yuvj420p");
    Editor->addItem("yuvj422p");
    Editor->addItem("yuvj440p");
    Editor->addItem("yuvj444p");
    Editor->addItem("yuyv422");
}

//***************************************************************************
// AudioBitDepthDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void VideoBitDepthDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("1");
    Editor->addItem("4");
    Editor->addItem("8");
    Editor->addItem("9");
    Editor->addItem("10");
    Editor->addItem("12");
    Editor->addItem("16");
}

//***************************************************************************
// AudioBitDepthDelegate
//***************************************************************************

//---------------------------------------------------------------------------
void AudioBitDepthDelegate::Fill(QComboBox* Editor) const
{
    Editor->addItem("");
    Editor->addItem("8");
    Editor->addItem("12");
    Editor->addItem("13");
    Editor->addItem("14");
    Editor->addItem("16");
    Editor->addItem("18");
    Editor->addItem("20");
    Editor->addItem("22");
    Editor->addItem("24");
    Editor->addItem("32");
}

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
GUI_Main_xxxx_CodingHistoryDialog::GUI_Main_xxxx_CodingHistoryDialog(Core* C_, const std::string &FileName_, const std::string &Field_, const QString &OldText, bool Rules_Recommendations_, QWidget* parent)
: QDialog(parent)
{
    //Internal
    C=C_;
    FileName=FileName_;
    Field=Field_;
    Rules_Recommendations=Rules_Recommendations_;

    //Configuration
    setWindowFlags(windowFlags()&(0xFFFFFFFF-Qt::WindowContextHelpButtonHint));
    setWindowTitle("Coding History");
    setWindowIcon (QIcon(":/Image/Brand/Logo.gif"));

    //Buttons
    Load=new QPushButton("&Load file...");
    Save=new QPushButton("&Save file...");
    QDialogButtonBox* Dialog=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    Dialog->addButton(Load, QDialogButtonBox::ResetRole);
    Dialog->addButton(Save, QDialogButtonBox::ResetRole);
    connect(Dialog, SIGNAL(accepted()), this, SLOT(OnAccept()));
    connect(Dialog, SIGNAL(rejected()), this, SLOT(reject()));
    connect(Load, SIGNAL(clicked()), this, SLOT(OnMenu_Load()));
    connect(Save, SIGNAL(clicked()), this, SLOT(OnMenu_Save()));

    //Central
    TextEdit=new QTextEdit(this);
    Table=new CodingHistoryDialog_TableWidget(List, this);
    connect(Table, SIGNAL(currentCellChanged (int, int, int, int)), this, SLOT(OnMenu_currentCellChanged(int, int, int, int)));
    Central=new QTabWidget(this);
    Central->addTab(Table   , tr("NARA Technical Recommendation"));
    Central->addTab(TextEdit, tr("Free text"));
    connect(Central, SIGNAL(currentChanged (int)), this, SLOT(OnCurrentChanged(int)));
        
    //Label
    Label=new QLabel(this);
    Label->setWordWrap(true);
    Label->setOpenExternalLinks(true);

    QVBoxLayout* L=new QVBoxLayout();
    L->addWidget(Central);
    L->addWidget(Label);
    L->addWidget(Dialog);

    setLayout(L);

    resize(QApplication::desktop()->screenGeometry().width()/2, QApplication::desktop()->screenGeometry().height()/3);

    //Filling
    TextEdit->setPlainText(OldText);
    string Text=OldText.toLocal8Bit().data();
    if (Text.find("Coding History ")==0)
        Text.erase(0, 15);    
    if (Text.size()==0
     || (Text.size()>=3
      && ((Text[1]=='='
        && (Text[0]=='R' || Text[0]=='T'))
       || (Text[2]=='='
        && ((Text[0]=='M' && Text[0]=='N') || (Text[0]=='M' && Text[0]=='D') || (Text[0]=='S' && Text[0]=='N') || (Text[0]=='S' && Text[0]=='G')  || (Text[0]=='S' && Text[0]=='T') || (Text[0]=='V' && Text[0]=='E'))))
      && Text.find("ANALOG,")==string::npos
      && Text.find(", ")==string::npos))
        OnCurrentChanged(0); //By default, index=0
    else
        Central->setCurrentIndex(1);
}

//***************************************************************************
// Menu actions
//***************************************************************************

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnAccept ()
{
    if (Central->currentIndex()!=1)
        OnCurrentChanged(1);
    
    std::string Value=TextEdit->toPlainText().toLocal8Bit().data();
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
void GUI_Main_xxxx_CodingHistoryDialog::OnMenu_Load()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getOpenFileName(this, "", "", "");
    
    if (FileNamesQ.isEmpty())
        return;

    File F;
    if (!F.Open(ZenLib::Ztring().From_UTF8(FileNamesQ.toUtf8().data())))
        return;
    int64u F_Size=F.Size_Get();
    if (F_Size>((size_t)-1)-1)
        return;

    //Creating buffer
    int8u* Buffer=new int8u[(size_t)F_Size+1];
    size_t Buffer_Offset=0;

    //Reading the file
    while(Buffer_Offset<F_Size)
    {
        size_t BytesRead=F.Read(Buffer+Buffer_Offset, (size_t)F_Size-Buffer_Offset);
        if (BytesRead==0)
            break; //Read is finished
        Buffer_Offset+=BytesRead;
    }
    if (Buffer_Offset<F_Size)
        return;
    Buffer[Buffer_Offset]='\0';

    //Filling
    Ztring ModifiedContent((const char*)Buffer);
    delete[] Buffer;
    ModifiedContent.FindAndReplace("\r\n", "\n", 0, Ztring_Recursive);
    ModifiedContent.FindAndReplace("\r", "\n", 0, Ztring_Recursive);
    QString ModifiedContentQ=QString().fromUtf8(ModifiedContent.To_Local().c_str());

    TextEdit->setPlainText(ModifiedContentQ);
    if (Central->currentIndex()==0)
        OnMenu_List();
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnMenu_Save()
{
    //User interaction
    QString FileNamesQ = QFileDialog::getSaveFileName(this, "", "", "");
    
    if (FileNamesQ.isEmpty())
        return;

    File F;
    if (!F.Create(ZenLib::Ztring().From_UTF8(FileNamesQ.toUtf8().data())))
        return;

    //Filling
    F.Write(Ztring(TextEdit->toPlainText().toLocal8Bit().data()));
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnMenu_List ()
{
    Text2List();
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnMenu_Text ()
{
    List2Text();
    Label->setText(QString());
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnCurrentChanged (int Index)
{
    //Showing
    switch (Index)
    {
        case 0  : OnMenu_List(); break;
        case 1  : OnMenu_Text(); break;
        default : ;
    }
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::OnMenu_currentCellChanged (int currentRow, int currentColumn, int previousRow, int previousColumn)
{
    //Showing
    switch (currentColumn)
    {
        case 0  : Label->setText("The 'role' element defines the generic use or task performed by a given generation of the media or tool used in the processing of the media."); break;
        case 1  : Label->setText("A free text string for internal use to clarify technical aspects of the coding history record. This string may not contain commas (use semicolons instead) or line breaks."); break;
        case 2  : Label->setText("The manufacturer of the tape, file, device, tool, software or piece of technology described in the coding history record."); break;
        case 3  : Label->setText("The name of the model of the tape, file, device, tool, software or piece of technology described in the coding history record. For products use the commericial name of the product, for tape formats use the name of the physical format (<a href=\"http://metadataregistry.org/concept/list/vocabulary_id/145.html\">suggested vocabulary</a>)"); break;
        case 4  : Label->setText("When applicable, this element may store the serial number of the object described in the coding history record."); break;
        case 5  : Label->setText("The 'signal' element describes any standardized audiovisual interface that is used to transmit the signal between tools or elements."); break;
        case 6  : Label->setText("The 'version' element expresses the version number of the software, tool, or object used in the process."); break;
        case 7  : Label->setText("The codec identifier of the video encoding. It is recommended to express video encoding using the <a href=\"http://www.fourcc.org/codecs.php\">fourCC (four character code)</a>."); break;
        case 8  : Label->setText("The codec identifier of the audio encoding. It is recommended to express video encoding using the twoCC (two character code) or fourCC (four character code)."); break;
        case 9  : Label->setText(""); break;
        case 10 : Label->setText(""); break;
        case 11 : Label->setText("The pixel format used in the encoded video, including a reference to the colorspace and chroma subsampling."); break;
        case 12 : Label->setText("The bit rate of the encoded video track. Not including other portions of the file."); break;
        case 13 : Label->setText("The bit rate of the encoded audio track. Not including other portions of the file."); break;
        case 14 : Label->setText("This element expresses the sampling size of the encoding video data. Express as the bit depth used per channel rather than per pixel."); break;
        case 15 : Label->setText("This element expresses the sampling size of the encoding video data. Express as the bit depth used per channel rather than per stream."); break;
        case 16 : Label->setText("Description of settings used at this step of the process."); break;
        default : Label->setText(QString());
    }
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::List2Text ()
{
    if (List.empty())
        return;

    Ztring ToReturn;
    for (size_t Line=0; Line<List.size(); Line++)
    {
        for (size_t Column=0; Column<List[Line].size(); Column++)
        {
            if (!List[Line][Column].empty())
            {
                Ztring Header;
                switch (Column)
                {
                    case 0 : Header="R"; break;
                    case 1 : Header="T"; break;
                    case 2 : Header="MN"; break;
                    case 3 : Header="MD"; break;
                    case 4 : Header="SN"; break;
                    case 5 : Header="SG"; break;
                    case 6 : Header="V"; break;
                    case 7 : Header="VE"; break;
                    case 8 : Header="AE"; break;
                    case 9 : Header="VR"; break;
                    case 10 : Header="AR"; break;
                    case 11 : Header="PX"; break;
                    case 12 : Header="VB"; break;
                    case 13 : Header="AB"; break;
                    case 14 : Header="VD"; break;
                    case 15 : Header="AD"; break;
                    case 16 : Header="ST"; break;
                    default: Header="\0";
                }
                if (!Header.empty())
                {
                    ToReturn+=Header;
                    ToReturn+='=';
                }
                ToReturn+=List[Line][Column];
                if (Column!=List[Line].size())
                    ToReturn+=',';
            }
        }
        
        while (!ToReturn.empty() && (*(ToReturn.end()-1))==',')
            ToReturn.erase(ToReturn.end()-1);
            
        ToReturn+='\n';
    }
    
    if (!ToReturn.empty())
        TextEdit->setPlainText(ToReturn.To_Local().c_str());
}

//---------------------------------------------------------------------------
void GUI_Main_xxxx_CodingHistoryDialog::Text2List ()
{
    //Preparing
    Table->Updating=true;
    
    //Warning display
    bool Ununderstable=false;
    bool Modified=false;

    //Loading
    string Text=TextEdit->toPlainText().toLocal8Bit().data();
    List.Separator_Set(0, "\n");
    if (Text.find(", ")==string::npos)
        List.Separator_Set(1, ",");
    else
        List.Separator_Set(1, ", ");
    List.Write(Text);

    Table->setRowCount((int)List.size()+1);
    Table->setColumnCount(17);

    Table->setHorizontalHeaderItem(0, new QTableWidgetItem("Role                        "));
    Table->setHorizontalHeaderItem(1, new QTableWidgetItem("Description"));
    Table->setHorizontalHeaderItem(2, new QTableWidgetItem("Manufacturer"));
    Table->setHorizontalHeaderItem(3, new QTableWidgetItem("Model name"));
    Table->setHorizontalHeaderItem(4, new QTableWidgetItem("Serial number"));
    Table->setHorizontalHeaderItem(5, new QTableWidgetItem("Signal               "));
    Table->setHorizontalHeaderItem(6, new QTableWidgetItem("Version"));
    Table->setHorizontalHeaderItem(7, new QTableWidgetItem("Video encoding"));
    Table->setHorizontalHeaderItem(8, new QTableWidgetItem("Audio encoding"));
    Table->setHorizontalHeaderItem(9, new QTableWidgetItem("Video frame rate"));
    Table->setHorizontalHeaderItem(10, new QTableWidgetItem("Audio sampling rate"));
    Table->setHorizontalHeaderItem(11, new QTableWidgetItem("Video pixel format"));
    Table->setHorizontalHeaderItem(12, new QTableWidgetItem("Video bit rate"));
    Table->setHorizontalHeaderItem(13, new QTableWidgetItem("Audio bit rate"));
    Table->setHorizontalHeaderItem(14, new QTableWidgetItem("Video bit depth"));
    Table->setHorizontalHeaderItem(15, new QTableWidgetItem("Audio bit depth"));
    Table->setHorizontalHeaderItem(16, new QTableWidgetItem("Settings"));
    for (size_t Line_Pos=0; Line_Pos<List.size(); Line_Pos++)
    {
        for (size_t Data_Pos=0; Data_Pos<List[Line_Pos].size(); Data_Pos++)
        {
            int Column=-1;
            Ztring &Value=List[Line_Pos][Data_Pos];
            if (Line_Pos==0 && Data_Pos==0 && Value.find("Coding History ")==0)
            {
                Modified=true;
                Value.erase(0, 15);
            }
            if (Value.size()>=2 && Value[1]=='=')
            {
                switch (Value[0])
                {
                    case 'R' : Column=0; break;
                    case 'T' : Column=1; break;
                    case 'V' : Column=6; break;
                    default  : Ununderstable=true;
                }
            }
            else if (Value.size()>=3 && Value[2]=='=')
            {
                switch (Value[0])
                {
                    case 'M' : 
                                switch (Value[1])
                                {
                                    case 'N' : Column=2; break;
                                    case 'D' : Column=3; break;
                                    default  : Ununderstable=true;
                                }
                                break;
                    case 'S' : 
                                switch (Value[1])
                                {
                                    case 'N' : Column=4; break;
                                    case 'G' : Column=5; break;
                                    case 'T' : Column=16; break;
                                    default  : Ununderstable=true;
                                }
                                break;
                    case 'V' : 
                                switch (Value[1])
                                {
                                    case 'E' : Column=7; break;
                                    case 'R' : Column=9; break;
                                    case 'B' : Column=12; break;
                                    case 'D' : Column=14; break;
                                    default  : Ununderstable=true;
                                }
                                break;
                    case 'A' : 
                                switch (Value[1])
                                {
                                    case 'E' : Column=8; break;
                                    case 'R' : Column=10; break;
                                    case 'B' : Column=13; break;
                                    case 'D' : Column=15; break;
                                    default  : Ununderstable=true;
                                }
                                break;
                    case 'P' : 
                                switch (Value[1])
                                {
                                    case 'X' : Column=11; break;
                                    default  : Ununderstable=true;
                                }
                                break;
                    default  : Ununderstable=true;
                }
            }
            else
                Ununderstable=true;
            if (Column==Data_Pos)
            {
                if (Value.size()>=2 && Value[1]==_T('='))
                    Value.erase(0, 2);
                if (Value.size()>=3 && Value[2]==_T('='))
                    Value.erase(0, 3);
                QTableWidgetItem* Item=new QTableWidgetItem(QString().fromUtf8(Value.To_Local().c_str()));
            
                Table->setItem((int)Line_Pos, Column, Item);
            }
            else if (Column!=-1 || Data_Pos>5)
            {
                List[Line_Pos].insert(List[Line_Pos].begin()+Data_Pos, Ztring());
                if (List[Line_Pos].size()>17)
                {
                    Ununderstable=true;
                    break;
                }
            }
        }
    }

    Table->setItemDelegateForColumn(0, new RoleDelegate);
    Table->setItemDelegateForColumn(5, new SignalDelegate);
    Table->setItemDelegateForColumn(9, new FrameRateDelegate);
    Table->setItemDelegateForColumn(10, new SamplingFrequencyDelegate);
    Table->setItemDelegateForColumn(11, new VideoPixelFormatDelegate);
    Table->setItemDelegateForColumn(14, new VideoBitDepthDelegate);
    Table->setItemDelegateForColumn(15, new AudioBitDepthDelegate);

    Table->resizeColumnsToContents();
    Table->resizeRowsToContents();

    if (Ununderstable)
    {
        if (isVisible())
        {
            QMessageBox MessageBox;
            MessageBox.setWindowTitle("AVI MetaEdit");
            MessageBox.setText("Text does not meet specifications, and matching is not possible");
                #if (QT_VERSION >= 0x040200)
                    MessageBox.setStandardButtons(QMessageBox::Close);
                #endif // (QT_VERSION >= 0x040200)
            MessageBox.setIcon(QMessageBox::Critical);
            MessageBox.setWindowIcon(QIcon(":/Image/Brand/Logo.gif"));
            MessageBox.exec();
        }

        //Clear
        List.clear();

        //Preparing
        Table->Updating=false;

        //Going back
        Central->setCurrentIndex(1);
        return;
    }

    if (Modified)
    {
        QMessageBox MessageBox;
        MessageBox.setWindowTitle("AVI MetaEdit");
        MessageBox.setText("Text does not meet specifications, do you accept to modify text to meet specifications?");
        #if (QT_VERSION >= 0x040200)
            MessageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            #if (QT_VERSION >= 0x040300)
                MessageBox.setDefaultButton(QMessageBox::No);
            #endif // (QT_VERSION >= 0x040300)
        #endif // (QT_VERSION >= 0x040200)
        MessageBox.setIcon(QMessageBox::Question);
        MessageBox.setWindowIcon(QIcon(":/Image/Brand/Logo.gif"));
        switch (MessageBox.exec())
        {
            case QMessageBox::No    :   //Save was clicked
                                        List.clear();

                                        //Preparing
                                        Table->Updating=false;

                                        //Going back
                                        Central->setCurrentIndex(1);
                                        return;
            default                 : ; //Continue
        } 
    }

    //Preparing
    Table->Updating=false;
}

//***************************************************************************
// Events
//***************************************************************************

void GUI_Main_xxxx_CodingHistoryDialog::hideEvent (QHideEvent*)
{
    if (Central->currentIndex()==0)
        List2Text();
}
