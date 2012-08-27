// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Riff/Riff_Handler.h"
#include "Riff/Riff_Chunks.h"
#include "FromMediaInfo/FromMediaInfo.h"
#include <sstream>
#include <iostream>
#include "ZenLib/ZtringListList.h"
#include "ZenLib/File.h"
#include "ZenLib/Dir.h"
#undef __TEXT
//#include "MediaInfoDLL/MediaInfoDLL.h"
using namespace std;
using namespace ZenLib;
using namespace MediaInfoLib;
//using namespace MediaInfoDLL;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
const Ztring Riff_Handler_EmptyZtring_Const; //Use it when we can't return a reference to a true Ztring, const version
//---------------------------------------------------------------------------

//***************************************************************************
// Const
//***************************************************************************

enum xxxx_Fields
{
    Fields_Tech,
    Fields_Tdat,
    Fields_Info,
    Fields_Max,
};

size_t xxxx_Strings_Size[]=
{
    4,  //Tech
    4,  //Tdat
    20, //Info
};

const char* xxxx_Strings[][24]=
{
    {
        "XMP",
        "aXML",
        "iXML",
        "MD5Stored",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
        "",
    },
    {
        //Note: from Tdat
        "tc_A",
        "tc_O",
        "rn_A",
        "rn_O",
    },
    {
        //Note: there is a duplicate in Riff_Chunks_INFO_xxxx
        "IARL", //Archival Location
        "IART", //Artist
        "ICMS", //Commissioned
        "ICMT", //Comment
        "ICOP", //Copyright
        "ICRD", //Date Created
        "IENG", //Engineer
        "IGNR", //Genre
        "IKEY", //Keywords
        "IMED", //Medium
        "INAM", //Title
        "IPRD", //Product
        "ISBJ", //Subject
        "ISFT", //Software
        "ISRC", //Source
        "ISRF", //Source Form
        "ITCH", //Technician
        "ISMP", //SMPTE time code
        "IDIT", //Digitization Time
        "IMIT", //More Info Text
    },
};

//***************************************************************************
// Constructor/Destructor
//***************************************************************************

//---------------------------------------------------------------------------
Riff_Handler::Riff_Handler ()
{
    //Configuration
    Avi2Avix_Reject=false;
    Overwrite_Reject=false;
    NoPadding_Accept=false;
    NewChunksAtTheEnd=false;
    GenerateMD5=false;
    VerifyMD5=false;
    EmbedMD5=false;
    EmbedMD5_AuthorizeOverWritting=false;
    Bext_DefaultVersion=0;

    //Internal
    Chunks=NULL;
    File_IsValid=false;
    File_IsCanceled=false;
}

//---------------------------------------------------------------------------
Riff_Handler::~Riff_Handler ()
{
    delete Chunks; //Chunks=NULL;
}

//***************************************************************************
// I/O
//***************************************************************************

//---------------------------------------------------------------------------
bool Riff_Handler::Open(const string &FileName)
{
    //MediaInfo
    /*
    MediaInfo MI;
    MI.Option(_T("ParseSpeed"), _T("0"));
    if (MI.Open(FileName))
    {
        MediaInfo_General_Format=MI.Get(Stream_General, 0, _T("Format"));
        if (!MI.Get(Stream_General, 0, _T("Format_Profile")).empty())
            MediaInfo_General_Format+=_T(" (")+MI.Get(Stream_General, 0, _T("Format_Profile"))+_T(')');
        MediaInfo_General_Duration=MI.Get(Stream_General, 0, _T("Duration/String3"));
        MediaInfo_Video_Format.clear();
        MediaInfo_Video_CodecID.clear();
        MediaInfo_Video_Width.clear();
        MediaInfo_Video_Height.clear();
        MediaInfo_Video_BitDepth.clear();
        MediaInfo_Video_BitRate.clear();
        for (size_t Pos=0; Pos<MI.Count_Get(Stream_Video); Pos++)
        {
            if (!MediaInfo_Video_Format.empty())
            {
                MediaInfo_Video_Format+=_T(" / ");
                MediaInfo_Video_CodecID+=_T(" / ");
                MediaInfo_Video_Width+=_T(" / ");
                MediaInfo_Video_Height+=_T(" / ");
                MediaInfo_Video_BitDepth+=_T(" / ");
                MediaInfo_Video_BitRate+=_T(" / ");
            }
            MediaInfo_Video_Format+=MI.Get(Stream_Video, 0, _T("Format"));
            MediaInfo_Video_CodecID+=MI.Get(Stream_Video, 0, _T("CodecID"));
            MediaInfo_Video_FrameRate+=MI.Get(Stream_Video, 0, _T("FrameRate"));
            MediaInfo_Video_Width+=MI.Get(Stream_Video, 0, _T("Width"));
            MediaInfo_Video_Height+=MI.Get(Stream_Video, 0, _T("Height"));
            MediaInfo_Video_BitDepth+=MI.Get(Stream_Video, 0, _T("BitDepth"));
            MediaInfo_Video_BitRate+=MI.Get(Stream_Video, 0, _T("BitRate/String"));
        }
        MediaInfo_Audio_Format.clear();
        MediaInfo_Audio_CodecID.clear();
        MediaInfo_Audio_Channels.clear();
        MediaInfo_Audio_SampleRate.clear();
        MediaInfo_Audio_BitDepth.clear();
        MediaInfo_Audio_BitRate.clear();
        for (size_t Pos=0; Pos<MI.Count_Get(Stream_Audio); Pos++)
        {
            if (!MediaInfo_Audio_Format.empty())
            {
                MediaInfo_Audio_Format+=_T(" / ");
                MediaInfo_Audio_CodecID+=_T(" / ");
                MediaInfo_Audio_Channels+=_T(" / ");
                MediaInfo_Audio_SampleRate+=_T(" / ");
                MediaInfo_Audio_BitDepth+=_T(" / ");
                MediaInfo_Audio_BitRate+=_T(" / ");
            }
            MediaInfo_Audio_Format+=MI.Get(Stream_Audio, 0, _T("Format"));
            MediaInfo_Audio_CodecID+=MI.Get(Stream_Audio, 0, _T("CodecID"));
            MediaInfo_Audio_Channels+=MI.Get(Stream_Audio, 0, _T("Channel(s)"));
            MediaInfo_Audio_SampleRate+=MI.Get(Stream_Audio, 0, _T("SamplingRate"));
            MediaInfo_Audio_BitDepth+=MI.Get(Stream_Audio, 0, _T("BitDepth"));
            MediaInfo_Audio_BitRate+=MI.Get(Stream_Audio, 0, _T("BitRate/String"));
        }
    }
    */
    
    //Init
    PerFile_Error.str(string());
    File_IsValid=false;
    File_IsCanceled=false;
    bool ReturnValue=true;
    
    //Global info
    delete Chunks; Chunks=new Riff();
    Chunks->Global->File_Name=FileName;

    //Opening file
    if (!File::Exists(FileName) || !Chunks->Global->In.Open(FileName))
    {
        Errors<<FileName<<": File does not exist"<<endl;
        PerFile_Error<<"File does not exist"<<endl;
        return false;
    }
    Chunks->Global->File_Size=Chunks->Global->In.Size_Get();
    Chunks->Global->File_Date=Chunks->Global->In.Created_Local_Get();
    if (Chunks->Global->File_Date.empty())
        Chunks->Global->File_Date=Chunks->Global->In.Modified_Local_Get();

    //Base
    Riff_Base::chunk Chunk;
    Chunk.File_In_Position=0;
    Chunk.Header.IsList=true;
    Chunk.Content.Size=Chunks->Global->File_Size;
    Options_Update();

    //Parsing
    try
    {
        Chunks->Read(Chunk);
        if (Chunks->Global->AVI__hdrl_strl_strh.size()!=Chunks->Global->AVI__hdrl_strl_strf.size())
            throw exception_read_chunk("Coherency problem during strl parsing");
        File_IsValid=true;
    }
    catch (exception_canceled &)
    {
        CriticalSectionLocker(Chunks->Global->CS);
        File_IsCanceled=true;
        Chunks->Global->Canceling=false;
        ReturnValue=false;
    }
    catch (exception_read_chunk &e)
    {
        Errors<<Chunks->Global->File_Name<<": "<<e.what()<<endl;
        PerFile_Error<<e.what()<<endl;
    }
    catch (exception &e)
    {
        Errors<<Chunks->Global->File_Name<<": "<<e.what()<<endl;
        PerFile_Error<<e.what()<<endl;
        ReturnValue=false;
    }

    //Cleanup
    Chunks->Global->In.Close();

    if (File_IsValid)
    {
        //Log
        if (Chunks->Global->NoPadding_IsCorrected)
        {
            Information<<Chunks->Global->File_Name<<": no-padding correction"<<endl;
            PerFile_Information<<"no-padding correction"<<endl;
        }

        //Saving initial values
        Core_FromFile=Core_Get();

        //MD5
        if (Chunks->Global->GenerateMD5)
        {
            Ztring MD5_Total;
            for (size_t Pos=0; Pos<Chunks->Global->AVI__hdrl_strl_strf.size(); Pos++)
            {
                Ztring MD5_PerItem;
                if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->MD5)
                {
                    int8u Digest[16];
                    MD5Final(Digest, Chunks->Global->AVI__hdrl_strl_strf[Pos]->MD5);
                    int128u DigestI=BigEndian2int128u(Digest);
                    MD5_PerItem.From_Number(DigestI, 16);
                    while (MD5_PerItem.size()<32)
                        MD5_PerItem.insert(MD5_PerItem.begin(), '0'); //Padding with 0, this must be a 32-byte string
                }
                if (!MD5_Total.empty())
                    MD5_Total+=_T(" / ");
                MD5_Total+=MD5_PerItem;
            }
            MD5_Total.MakeLowerCase();
            Chunks->Global->MD5Generated=new Riff_Base::global::chunk_strings;
            Chunks->Global->MD5Generated->Strings["md5generated"]=MD5_Total;
        }

        //MD5 verification
        if (Chunks->Global->VerifyMD5)
        {
            //Removing all MD5 related info
            Ztring PerFile_Error_Temp=PerFile_Error.str();
            PerFile_Error_Temp.FindAndReplace(Ztring("MD5, failed verification\n"), Ztring());
            PerFile_Error.str(PerFile_Error_Temp);
            Ztring PerFile_Information_Temp=PerFile_Information.str();
            PerFile_Information_Temp.FindAndReplace(Ztring("MD5, no existing MD5 chunk\n"), Ztring());
            PerFile_Information_Temp.FindAndReplace(Ztring("MD5, verified\n"), Ztring());
            PerFile_Information.str(PerFile_Information_Temp);
            
            //Checking
            if (!(Chunks->Global->MD5Stored && !Chunks->Global->MD5Stored->Strings["md5stored"].empty()))
            {
                Information<<Chunks->Global->File_Name<<": MD5, no existing MD5 chunk"<<endl;
                PerFile_Information<<"MD5, no existing MD5 chunk"<<endl;
            }
            else if (Chunks->Global->MD5Generated && Chunks->Global->MD5Generated->Strings["md5generated"]!=Chunks->Global->MD5Stored->Strings["md5stored"])
            {
                Errors<<Chunks->Global->File_Name<<": MD5, failed verification"<<endl;
                PerFile_Error.str(string());
                PerFile_Error<<"MD5, failed verification"<<endl;
            }
            else
            {
                Information<<Chunks->Global->File_Name<<": MD5, verified"<<endl;
                PerFile_Information.str(string());
                PerFile_Information<<"MD5, verified"<<endl;
            }
            }
        if (EmbedMD5
         && Chunks->Global->MD5Generated && !Chunks->Global->MD5Generated->Strings["md5generated"].empty()
         && (!(Chunks->Global->MD5Stored && !Chunks->Global->MD5Stored->Strings["md5stored"].empty())
          || EmbedMD5_AuthorizeOverWritting))
                Set("MD5Stored", Chunks->Global->MD5Generated->Strings["md5generated"], rules());
        
        //Tech info
        if (Chunks->Global->AVI__hdrl_dmlh)
            MediaInfo_General_Format=_T("AVI (OpenDML)");
        else
            MediaInfo_General_Format=_T("AVI");
        MediaInfo_General_Duration=Duration_Duration3(float64_int64s(((float64)Chunks->Global->AVI__hdrl_avih->TotalFrames)*Chunks->Global->AVI__hdrl_avih->MicrossecPerFrame/1000));
        MediaInfo_Video_Format.clear();
        MediaInfo_Video_CodecID.clear();
        MediaInfo_Video_FrameRate.clear();
        MediaInfo_Video_Width.clear();
        MediaInfo_Video_Height.clear();
        MediaInfo_Video_BitDepth.clear();
        MediaInfo_Video_BitRate.clear();
        MediaInfo_Audio_Format.clear();
        MediaInfo_Audio_CodecID.clear();
        MediaInfo_Audio_Channels.clear();
        MediaInfo_Audio_SampleRate.clear();
        MediaInfo_Audio_BitDepth.clear();
        MediaInfo_Audio_BitRate.clear();
        for (size_t Pos=0; Pos<Chunks->Global->AVI__hdrl_strl_strf.size(); Pos++)
        {
            switch (Chunks->Global->AVI__hdrl_strl_strh[Pos]->fccType)
            {
                case Elements::AVI__hdlr_strl_strh_auds :
                                                            if (!MediaInfo_Audio_Format.empty())
                                                            {
                                                                MediaInfo_Audio_Format+=_T(" / ");
                                                                MediaInfo_Audio_CodecID+=_T(" / ");
                                                                MediaInfo_Audio_Channels+=_T(" / ");
                                                                MediaInfo_Audio_SampleRate+=_T(" / ");
                                                                MediaInfo_Audio_BitDepth+=_T(" / ");
                                                                MediaInfo_Audio_BitRate+=_T(" / ");
                                                            }
                                                            MediaInfo_Audio_Format+=Format_FromCodecID_Audio(Chunks->Global->AVI__hdrl_strl_strf[Pos]->FormatTag);
                                                            MediaInfo_Audio_CodecID+=Ztring().From_CC2(Chunks->Global->AVI__hdrl_strl_strf[Pos]->FormatTag);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->Channels)
                                                                MediaInfo_Audio_Channels+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->Channels);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->SamplesPerSec)
                                                                MediaInfo_Audio_SampleRate+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->SamplesPerSec);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitsPerSample)
                                                                MediaInfo_Audio_BitDepth+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitsPerSample);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->AvgBytesPerSec)
                                                                MediaInfo_Audio_BitRate+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->AvgBytesPerSec*8);
                                                            break;

                //case Elements::AVI__hdlr_strl_strh_iavs : AVI__hdlr_strl_strf_iavs(); break;
                //case Elements::AVI__hdlr_strl_strh_mids : AVI__hdlr_strl_strf_mids(); break;
                //case Elements::AVI__hdlr_strl_strh_txts : AVI__hdlr_strl_strf_txts(); break;
                case Elements::AVI__hdlr_strl_strh_vids : 
                                                            if (!MediaInfo_Video_Format.empty())
                                                            {
                                                                MediaInfo_Video_Format+=_T(" / ");
                                                                MediaInfo_Video_CodecID+=_T(" / ");
                                                                MediaInfo_Video_FrameRate+=_T(" / ");
                                                                MediaInfo_Video_Width+=_T(" / ");
                                                                MediaInfo_Video_Height+=_T(" / ");
                                                                MediaInfo_Video_BitDepth+=_T(" / ");
                                                                MediaInfo_Video_BitRate+=_T(" / ");
                                                            }
                                                            MediaInfo_Video_Format+=Format_FromCodecID_Video(Chunks->Global->AVI__hdrl_strl_strf[Pos]->Compression);
                                                            MediaInfo_Video_CodecID+=Ztring().From_CC4(Chunks->Global->AVI__hdrl_strl_strf[Pos]->Compression);
                                                            if (Chunks->Global->AVI__hdrl_strl_strh[Pos]->Rate && Chunks->Global->AVI__hdrl_strl_strh[Pos]->Scale)
                                                                MediaInfo_Video_FrameRate+=Ztring().From_Number(((float64)Chunks->Global->AVI__hdrl_strl_strh[Pos]->Rate)/Chunks->Global->AVI__hdrl_strl_strh[Pos]->Scale);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->Width)
                                                                MediaInfo_Video_Width+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->Width);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->Height)
                                                                MediaInfo_Video_Height+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->Height);
                                                            if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount)
                                                            {
                                                                if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount<16)
                                                                    MediaInfo_Video_BitDepth+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount); //Per component?
                                                                else if (Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount==16)
                                                                    MediaInfo_Video_BitDepth+=Ztring().From_Number(8); //RGB is per pixel, BitDepth is per component, but data is 16 for YUYV422 8 bits
                                                                else if ((Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount%8)==0)
                                                                    MediaInfo_Video_BitDepth+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount/3); //RGB is per pixel, BitDepth is per component
                                                                else
                                                                    MediaInfo_Video_BitDepth+=Ztring().From_Number(Chunks->Global->AVI__hdrl_strl_strf[Pos]->BitCount); //Unknown
                                                            }
                                                            if (Chunks->Global->AVI__hdrl_strl_strh[Pos]->Rate && Chunks->Global->AVI__hdrl_strl_strh[Pos]->Scale && Chunks->Global->AVI__hdrl_strl_strf[Pos]->SizeImage)
                                                                MediaInfo_Video_BitRate+=Ztring().From_Number(((float64)Chunks->Global->AVI__hdrl_strl_strh[Pos]->Rate)/Chunks->Global->AVI__hdrl_strl_strh[Pos]->Scale*Chunks->Global->AVI__hdrl_strl_strf[Pos]->SizeImage*8, 0);
                                                            break;
                default                                 : ;
            }
        }
    }
        
    CriticalSectionLocker(Chunks->Global->CS);
    Chunks->Global->Progress=1;
    
    return ReturnValue;
}

//---------------------------------------------------------------------------
bool Riff_Handler::Save()
{
    Chunks->Global->CS.Enter();
    Chunks->Global->Progress=(float)0.05;
    Chunks->Global->CS.Leave();
    
    //Init
    PerFile_Error.str(string());

    //Integrity
    if (Chunks==NULL)
    {
        Errors<<"(No file name): Internal error"<<endl;
        return false;
    }

    //Write only if modified
    if (!IsModified_Get())
    {
        Information<<Chunks->Global->File_Name<<": Nothing to do"<<endl;
        return false;
    }

    //Modifying the chunks in memory
    for (size_t Fields_Pos=0; Fields_Pos<Fields_Max; Fields_Pos++)
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
        {
            if (!IsOriginal(xxxx_Strings[Fields_Pos][Pos], Get(xxxx_Strings[Fields_Pos][Pos])))
                Chunks->Modify(Elements::AVI_, Chunk_Name2_Get(xxxx_Strings[Fields_Pos][Pos]), Chunk_Name3_Get(xxxx_Strings[Fields_Pos][Pos]));
        }

    //Opening files
    if (!Chunks->Global->In.Open(Chunks->Global->File_Name))
    {
        Errors<<Chunks->Global->File_Name<<": File does not exist anymore"<<endl;
        PerFile_Error<<"File does not exist anymore"<<endl;
        return false;
    }

    //Old temporary file
    if (File::Exists(Chunks->Global->File_Name+".tmp") && !File::Delete(Chunks->Global->File_Name+".tmp"))
    {
        Errors<<Chunks->Global->File_Name<<": Old temporary file can't be deleted"<<endl;
        PerFile_Error<<"Old temporary file can't be deleted"<<endl;
        return false;
    }
    
    //Parsing
    try
    {
        Chunks->Write();
    }
    catch (exception_canceled &)
    {
        Chunks->Global->In.Close();
        Chunks->Global->Out.Close();
        File::Delete(Chunks->Global->File_Name+".tmp");
        CriticalSectionLocker(Chunks->Global->CS);
        File_IsCanceled=true;
        Chunks->Global->Canceling=false;
        return false;
    }
    catch (exception &e)
    {
        Chunks->Global->In.Close();
        Chunks->Global->Out.Close();
        Errors<<Chunks->Global->File_Name<<": "<<e.what()<<endl;
        PerFile_Error<<e.what()<<endl;
        return false;
    }
    Chunks->Global->In.Close();
    Chunks->Global->Out.Close();

    //Log
    Information<<(Chunks?Chunks->Global->File_Name:"")<<": Is modified"<<endl;

    //Loading the new file (we are verifying the integraty of the generated file)
    string FileName=Chunks->Global->File_Name;
    bool GenerateMD5_Temp=Chunks->Global->GenerateMD5;
    GenerateMD5=false;
    if (!Open(FileName) && Chunks==NULL) //There may be an error but file is open (eg MD5 error)
    {
        Errors<<FileName<<": WARNING, the resulting file can not be validated, file may be CORRUPTED"<<endl;
        PerFile_Error<<"WARNING, the resulting file can not be validated, file may be CORRUPTED"<<endl;
        Chunks->Global->GenerateMD5=GenerateMD5_Temp;
        return false;
    }
    GenerateMD5=GenerateMD5_Temp;

    CriticalSectionLocker(Chunks->Global->CS);
    Chunks->Global->Progress=1;
    
    return true;
}

//---------------------------------------------------------------------------
bool Riff_Handler::BackToLastSave()
{
    for (size_t Fields_Pos=0; Fields_Pos<Fields_Max; Fields_Pos++)
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
        {
            if (!IsOriginal(xxxx_Strings[Fields_Pos][Pos], Get(xxxx_Strings[Fields_Pos][Pos])))
            {
                ZtringList HistoryList; HistoryList.Write(History(xxxx_Strings[Fields_Pos][Pos]));
                if (!HistoryList.empty())
                    Set(xxxx_Strings[Fields_Pos][Pos], HistoryList[0], rules());
            }
        }

    Chunks->IsModified_Clear();
        
    return true;
}

//***************************************************************************
// Per Item
//***************************************************************************

//---------------------------------------------------------------------------
string Riff_Handler::Get(const string &Field)
{
    //Special cases
    if (Field=="FrameRate")
        return MediaInfo_Video_FrameRate;
    
    return Get(Field_Get(Field), *chunk_strings_Get(Field)); 
}

//---------------------------------------------------------------------------
bool Riff_Handler::Set(const string &Field_, const string &Value_, rules Rules)
{
    //Integrity
    if (Chunks==NULL)
    {
        Errors<<"(No file name): Internal error"<<endl;
        return false;
    }

    string Field=Field_Get(Field_);
    
    //Testing if useful
    if (Field=="filename"
     || Field=="version"
     || Field=="errors"
     || Field=="information"
     || Value_=="NOCHANGE")
        return true;
    
    Ztring Value=Value_; 
    Value.FindAndReplace("\r\n", "\n", 0, Ztring_Recursive);
    Value.FindAndReplace("\n\r", "\n", 0, Ztring_Recursive); //Bug in v0.2.1 XML, \r\n was inverted
    Value.FindAndReplace("\r", "\n", 0, Ztring_Recursive);
    Value.FindAndReplace("\n", "\r\n", 0, Ztring_Recursive);

    if (Value.size()>7
     && Value[0]=='f'
     && Value[1]=='i'
     && Value[2]=='l'
     && Value[3]=='e'
     && Value[4]==':'
     && Value[5]=='/'
     && Value[6]=='/')
    {
        if (!Value.Assign_FromFile(Value.substr(7, string::npos)))
        {
            Errors<<Chunks->Global->File_Name<<": Malformed input ("<<Field<<"="<<Value<<", File does not exist)"<<endl;
            return false;
        }
    }

    //Testing validity
    if (!IsValid(Field, Value, Rules)
     && !IsOriginal(Field, Value))
        return false;

    //Setting it
    bool ToReturn=Set(Field, Value, *chunk_strings_Get(Field), Chunk_Name2_Get(Field), Chunk_Name3_Get(Field)); 
    
    //Special cases - After
    if (ToReturn && Field=="originator")
    {
        if (Rules.USNA_Rec && Chunks && Chunks->Global && Chunks->Global->INFO)
            Set("IARL", Value, Rules); //If INFO is present, IARL is filled with the same value
    }

    return ToReturn;
}

//---------------------------------------------------------------------------
bool Riff_Handler::Remove(const string &Field)
{
    //Integrity
    if (Chunks==NULL)
    {
        Errors<<"(No file name): Internal error"<<endl;
        return false;
    }

    //Tdat and INFO
    if (Ztring(Field).MakeLowerCase()=="core")
    {
        bool ToReturn=true;
        for (size_t Fields_Pos=Fields_Tdat; Fields_Pos<=Fields_Info; Fields_Pos++) //Tdat and Info
            for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
                if (!Set(Field_Get(xxxx_Strings[Fields_Pos][Pos]), string(), *chunk_strings_Get(xxxx_Strings[Fields_Pos][Pos]), Chunk_Name2_Get(xxxx_Strings[Fields_Pos][Pos]), Chunk_Name3_Get(xxxx_Strings[Fields_Pos][Pos])))
                    ToReturn=false;
       return ToReturn;
    }

    return Set(Field, string(), *chunk_strings_Get(Field), Chunk_Name2_Get(Field), Chunk_Name3_Get(Field)); 
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsModified(const string &Field)
{
    //Special cases
    if (Field_Get(Field)=="Tdat")
    {
        bool ToReturn=false;
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Tdat]; Pos++)
             if (IsModified(xxxx_Strings[Fields_Tdat][Pos]))
                 ToReturn=true;
        return ToReturn;
    }
    if (Field_Get(Field)=="INFO")
    {
        bool ToReturn=false;
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Info]; Pos++)
             if (IsModified(xxxx_Strings[Fields_Info][Pos]))
                 ToReturn=true;
        return ToReturn;
    }
    
    return IsModified(Field_Get(Field=="timereference (translated)"?Ztring("timereference"):Field), *chunk_strings_Get(Field)); 
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsValid(const string &Field_, const string &Value_, rules Rules)
{
    //Reformating
    IsValid_Errors.str(string());
    Ztring Field=Field_Get(Field_);
    Ztring Value=Value_;
    Value.FindAndReplace("\r\n", "\n", 0, Ztring_Recursive);
    Value.FindAndReplace("\n\r", "\n", 0, Ztring_Recursive); //Bug in v0.2.1 XML, \r\n was inverted
    Value.FindAndReplace("\r", "\n", 0, Ztring_Recursive);
    Value.FindAndReplace("\n", "\r\n", 0, Ztring_Recursive);

    //Rules
    if (Rules.USNA_Rec)
        Rules.AVI_Rec=true;
    if (Rules.AVI_Rec)
        Rules.AVI_Req=true;
    if (Rules.INFO_Rec)
        Rules.INFO_Req=true;

    //FileName
    if (Field=="filename")
    {
        //Test
        string Message;
        if (!PerFile_Error.str().empty())
            Message=PerFile_Error.str();

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<Message;
    }
    else if (!File_IsValid && Field!="errors")
        return true; //Do nothing on invalid files

    //MD5Stored
    if (Field=="md5stored")
    {
        //Test
        ZtringList Values;
        Values.Separator_Set(0, _T(" / "));
        Values.Write(Value);
        string Message;
        for (size_t ValuePos=0; ValuePos<Values.size(); ValuePos++)
        {
            for (size_t Pos=0; Pos<Values[ValuePos].size(); Pos++)
                if (!((Values[ValuePos][Pos]>='0' && Values[ValuePos][Pos]<='9') || (Values[ValuePos][Pos]>='a' && Values[ValuePos][Pos]<='f') || (Values[ValuePos][Pos]>='A' && Values[ValuePos][Pos]<='F')))
                    Message="allowed characters are 0-9, a-z, A-Z";
            if (Message.empty())
            {
                if (!Values[ValuePos].empty() && Values[ValuePos].size()!=32)
                    Message="must be 16 byte long hexadecimal coded text (32 byte long) value";
            }

            if (!Message.empty())
                break;
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, MD5Stored "<<Message;
    }

    //MD5Stored
    else if (Field=="md5generated")
    {
        //Test
        ZtringList Values;
        Values.Separator_Set(0, _T(" / "));
        Values.Write(Value);
        string Message;
        for (size_t ValuePos=0; ValuePos<Values.size(); ValuePos++)
        {
            for (size_t Pos=0; Pos<Values[ValuePos].size(); Pos++)
                if (!((Values[ValuePos][Pos]>='0' && Values[ValuePos][Pos]<='9') || (Values[ValuePos][Pos]>='a' && Values[ValuePos][Pos]<='f') || (Values[ValuePos][Pos]>='A' && Values[ValuePos][Pos]<='F')))
                    Message="allowed characters are 0-9, a-z, A-Z";
            if (Message.empty())
            {
                if (!Values[ValuePos].empty() && Values[ValuePos].size()!=32)
                    Message="must be 16 byte long hexadecimal coded text (32 byte long) value";
            }

            if (!Message.empty())
                break;
        }

        if (Message.empty())
        {
            if (!Value.empty() && !Get("MD5Stored").empty())
            {
                Ztring ValueL(Value); ValueL.MakeLowerCase();
                Ztring MD5StoredL(Get("MD5Stored")); MD5StoredL.MakeLowerCase();
                if (ValueL!=MD5StoredL)
                    Message="failed verification";
            }
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, MD5Generated "<<Message;
    }

    else if (Field=="IARL")
    {
        //Test
        string Message;
        if (Rules.USNA_Rec)
        {
            if (Value.empty())
                Message="must not be empty (U.S. National Archives recommandations)";
            else if (Value.size()>0 && (Value[0] < 'A' || Value[0] > 'Z'))
                Message="1st character must be between 'A' and 'Z' (U.S. National Archives recommandations)";
            else if (Value.size()>1 && (Value[1] < 'A' || Value[1] > 'Z'))
                Message="2nd character must be between 'A' and 'Z' (U.S. National Archives recommandations)";
            else if (Value.size()>2 && Value[2] !=',')
                Message="3rd character must be a comma (U.S. National Archives recommandations)";
            else if (Value.size()>3 && Value[3] !=' ')
                Message="4th character must be a space (U.S. National Archives recommandations)";
            else if (Value.size()<5)
                Message="length is minimum 5 characters (U.S. National Archives recommandations)";
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, IARL "<<Message;
    }

    else if (Field=="ICMD" && Rules.INFO_Req)
    {
        if (Value.find_first_of("\r\n"))
        {
            Errors<<(Chunks?Chunks->Global->File_Name:"")<<": malformed input (ICMD="<<Value<<", carriage return are not acceptable)"<<endl;
            return false;
        }
    }

    //ICMT
    else if (Field=="ICMT")
    {
        //Test
        string Message;
        if (Rules.USNA_Rec && Value.empty())
            Message="must not be empty (U.S. National Archives recommandations)";

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, Description "<<Message;
    }

    //ICRD
    else if (Field=="ICRD")
    {
        //Test
        string Message;
        if (Rules.INFO_Rec)
        {
            if (Value.empty())
                {}
            else if (Value.size()<=10 && Value.size()!=4 && Value.size()!=7 && Value.size()!=10)
                Message="must be YYYY, YYYY-MM, or YYYY-MM-DD or YYYY-MM-DD+junk (INFO Recommandations)";
            else
            {
                     if (Value[0]< '0' || Value[0]> '9') //Year
                    Message="1st to 4th characters (Year) must be between '0000' and '9999' (INFO Recommandations)";
                else if (Value[1]< '0' || Value[1]> '9') //Year
                    Message="1st to 4th characters (Year) must be between '0000' and '9999' (INFO Recommandations)";
                else if (Value[2]< '0' || Value[2]> '9') //Year
                    Message="1st to 4th characters (Year) must be between '0000' and '9999' (INFO Recommandations)";
                else if (Value[3]< '0' || Value[3]> '9') //Year
                    Message="1st to 4th characters (Year) must be between '0000' and '9999' (INFO Recommandations)";
                else if (Value.size()>=7) //YYYY-DD
                {
                         if (Value[4]!='-') //Hyphen
                        Message="5th character must be '-' (INFO Recommandations)";
                    else if (Value[5]< '0' || Value[5]> '1') //Month
                        Message="6th and 7th characters (Month) must be between '01' and '12' (INFO Recommandations)";
                    else if ((Value[6]< (Value[5]=='0'?'1':'0')) || (Value[6]> (Value[5]=='1'?'2':'9'))) //Only 01-12 //Month
                        Message="6th and 7th characters (Month) must be between '01' and '12' (INFO Recommandations)";
                    else if (Value.size()>=10) //YYYY-DD-MM
                    {
                             if (Value[7]!='-') //Hyphen
                            Message="8th character must be '-' (INFO Recommandations)";
                        else if (Value[8]< '0' || Value[8]> '3') //Day
                            Message="9th and 10th characters (Day) must be between '01' and '23' (INFO Recommandations)";
                        else if ((Value[9]< (Value[8]=='0'?'1':'0')) || (Value[9]> (Value[8]=='3'?'1':'9'))) //Only 01-31 //Day
                            Message="9th and 10th characters (Day) must be between '01' and '23' (INFO Recommandations)";
                    }
                }
            }
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, ICRD "<<Message;
    }


    else if (Field=="ISMP" || Field=="tc_a" || Field=="tc_o")
    {
        //Test
        string Message;
        if (Rules.INFO_Req)
        {
            if (Value.empty())
                {}
            else if (Value.size()<11
            ||  Value[Value.size()-11]< '0' || Value[Value.size()-11]> '9' 
            ||  Value[Value.size()-10]< '0' || Value[Value.size()-10]> '9' 
            ||  Value[Value.size()- 9]!=':'
            ||  Value[Value.size()- 8]< '0' || Value[Value.size()- 8]> '5' 
            ||  Value[Value.size()- 7]< '0' || Value[Value.size()- 7]> '9' 
            ||  Value[Value.size()- 6]!=':'
            ||  Value[Value.size()- 5]< '0' || Value[Value.size()- 5]> '5' 
            ||  Value[Value.size()- 4]< '0' || Value[Value.size()- 4]> '9' 
            || (Field=="ISMP" && Value[Value.size()- 3]!='.')
            || (Field!="ISMP" && Value[Value.size()- 3]!=':' && Value[Value.size()- 3]!=';')
            ||  Value[Value.size()- 2]< '0' || Value[Value.size()- 2]> '9' 
            ||  Value[Value.size()- 1]< '0' || Value[Value.size()- 1]> '9')
            {
                if (Field=="ISMP")
                    Message="format must be HH:MM:SS.FF (INFO Requirements)";
                else
                    Message="format must be HH:MM:SS:FF of HH:MM:SS;FF";
            }
            else if (!MediaInfo_Video_FrameRate.empty() && Ztring(Value.substr(9)).To_int8u()>=MediaInfo_Video_FrameRate.To_float32())
            {
                Message="frame number must not be more or equal to frame rate";
                if (Field=="ISMP")
                    Message+=" (INFO Requirements)";
            }
        }

        if (Rules.USNA_Rec)
        {
            if (Value.empty())
                {}
            else if (Ztring(Value.substr(9)).To_int8u()>=MediaInfo_Video_FrameRate.To_float32())
                Message="frame number must not be more or equal to frame rate (U.S. National Archives Recommandations)";
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, "<<Field<<" "<<Message;
    }

    else if (Field=="IDIT")
    {
        //Test
        string Message;
        if (Rules.INFO_Req)
        {
            if (Value.empty())
                {}
            else if (!((Value[0]=='S' && Value[1]=='u' && Value[2]=='n')
                    || (Value[0]=='M' && Value[1]=='o' && Value[2]=='n')
                    || (Value[0]=='T' && Value[1]=='u' && Value[2]=='e')
                    || (Value[0]=='W' && Value[1]=='e' && Value[2]=='d')
                    || (Value[0]=='T' && Value[1]=='h' && Value[2]=='u')
                    || (Value[0]=='F' && Value[1]=='r' && Value[2]=='i')
                    || (Value[0]=='S' && Value[1]=='a' && Value[2]=='t')))
                Message="1st to 3rd characters must be a 3-letter week (first letter uppercase) (INFO Requirements)";
            else if (Value[3]!=' ')
                Message="4th character must be space character";
            else if (!((Value[4]=='J' && Value[5]=='a' && Value[6]=='n')
                    || (Value[4]=='F' && Value[5]=='e' && Value[6]=='b')
                    || (Value[4]=='M' && Value[5]=='a' && Value[6]=='r')
                    || (Value[4]=='A' && Value[5]=='p' && Value[6]=='r')
                    || (Value[4]=='M' && Value[5]=='a' && Value[6]=='y')
                    || (Value[4]=='J' && Value[5]=='u' && Value[6]=='n')
                    || (Value[4]=='J' && Value[5]=='u' && Value[6]=='l')
                    || (Value[4]=='A' && Value[5]=='u' && Value[6]=='g')
                    || (Value[4]=='S' && Value[5]=='e' && Value[6]=='p')
                    || (Value[4]=='O' && Value[5]=='c' && Value[6]=='t')
                    || (Value[4]=='N' && Value[5]=='o' && Value[6]=='v')
                    || (Value[4]=='D' && Value[5]=='e' && Value[6]=='c')))
                Message="5th to 7th characters must be a 3-letter month (first letter uppercase) (INFO Requirements)";
            else if (Value[7]!=' ')
                Message="8th character must be space character";
            else if (Value[8]< '0' || Value[8]> '3') //Days
                Message="9th and 10th characters (Day) must be between '00' and '31' (INFO Requirements)";
            else if (Value[9]< '0' || (Value[9]> (Value[8]=='3'?'1':'9'))) //Only 00-31 //Days
                Message="9th and 10th characters (Day) must be between '00' and '31' (INFO Requirements)";
            else if (Value[10]!=' ')
                Message="11th character must be space character";
            else if (Value[11]< '0' || Value[11]> '2') //Hours
                Message="12th and 13th characters (Hours) must be between '00' and '23' (INFO Requirements)";
            else if (Value[12]< '0' || (Value[12]> (Value[11]=='2'?'3':'9'))) //Only 00-23 //Hours
                Message="12th and 13th characters (Hours) must be between '00' and '23' (INFO Requirements)";
            else  if (Value[13]!=':') //Separator
                Message="14th character must be ':' (INFO Requirements)";
            else if (Value[14]< '0' || Value[14]> '5') //Minutes
                Message="15th and 16th characters (Minutes) must be between '00' and '59' (INFO Requirements)";
            else if (Value[15]< '0' || Value[15]> '9' ) //Minutes
                Message="15th and 16th characters (Minutes) must be between '00' and '59' (INFO Requirements)";
            else if (Value[16]!=':') //Separator
                Message="17th character must be ':' (INFO Requirements)";
            else if (Value[17]< '0' || Value[17]> '5') //Seconds
                Message="18th and 19th characters (Seconds) must be between '00' and '59' (INFO Requirements)";
            else if (Value[18]< '0' || Value[18]> '9' ) //Seconds
                Message="19th and 19th characters (Seconds) must be between '00' and '59' (INFO Requirements)";
            else if (Value[19]!=' ')
                Message="20th character must be space character";
            else if (Value[20]< '0' || Value[20]> '9') //Year
                Message="21th to 24th characters (Year) must be between '0000' and '9999' (INFO Requirements)";
            else if (Value[21]< '0' || Value[21]> '9') //Year
                Message="21th to 24th characters (Year) must be between '0000' and '9999' (INFO Requirements)";
            else if (Value[22]< '0' || Value[22]> '9') //Year
                Message="21th to 24th characters (Year) must be between '0000' and '9999' (INFO Requirements)";
            else if (Value[23]< '0' || Value[23]> '9') //Year
                Message="21th to 24th characters (Year) must be between '0000' and '9999' (INFO Requirements)";
            else if (Value.size()!=24)
                Message="must be \"Www Mmm dd hh:mm:ss yyyy\" (\\n\\0 is added automaticly)";
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, IDIT "<<Message;
    }

    //md5generated
    else if (Field=="md5generated")
    {
        //Test
        string Message;
        if (!(Chunks->Global->MD5Generated && !Chunks->Global->MD5Generated->Strings["md5generated"].empty()) && !(Chunks->Global->MD5Stored && !Chunks->Global->MD5Stored->Strings["md5stored"].empty()))
        {
            Ztring md5generated(Chunks->Global->MD5Generated->Strings["md5generated"]); md5generated.MakeLowerCase();
            Ztring md5stored(Chunks->Global->MD5Stored->Strings["md5stored"]); md5stored.MakeLowerCase();
            if (md5generated!=md5stored)
                Message="does not equal MD5Stored";
        }

        //If error
        if (!Message.empty()) 
            IsValid_Errors<<"malformed input, MD5Generated "<<Message;
    }

    else if (Field=="errors")
    {
        return PerFile_Error.str().empty();
    }

    else if (Field=="information")
    {
        return true;
    }

    if (!IsValid_Errors.str().empty())
    {
        Errors<<(Chunks?Chunks->Global->File_Name:"")<<": "<<IsValid_Errors.str()<<endl;
        return false;
    }
    else
        return true;
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsOriginal(const string &Field, const string &Value)
{
    return IsOriginal(Field_Get(Field=="timereference (translated)"?Ztring("timereference"):Field), Value, *chunk_strings_Get(Field)); 
}

//---------------------------------------------------------------------------
string Riff_Handler::History(const string &Field)
{
    return History(Field_Get(Field), *chunk_strings_Get(Field)); 
}

//***************************************************************************
// Global
//***************************************************************************

//---------------------------------------------------------------------------
string Riff_Handler::Core_Header()
{
    string ToReturn;
    ToReturn+="FileName,";
    for (size_t Fields_Pos=Fields_Tdat; Fields_Pos<=Fields_Info; Fields_Pos++) //Only Tdat and Info
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
        {
            ToReturn+=xxxx_Strings[Fields_Pos][Pos];
            ToReturn+=',';
        }

    //Remove the extra ","
    if (ToReturn.empty())
        ToReturn.resize(ToReturn.size()-1);

    return ToReturn;
}

//---------------------------------------------------------------------------
string Riff_Handler::Core_Get(bool Batch_IsBackuping)
{
    //FromFile
    if (Batch_IsBackuping)
        return Core_FromFile;
    
    ZtringList List;
    List.Separator_Set(0, ",");

    List.push_back(Chunks->Global->File_Name);
    for (size_t Fields_Pos=Fields_Tdat; Fields_Pos<=Fields_Info; Fields_Pos++) //Only Tdat and Info
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
             List.push_back(Get(xxxx_Strings[Fields_Pos][Pos]));

    return List.Read();
}

//---------------------------------------------------------------------------
string Riff_Handler::Technical_Header()
{
    ostringstream ToReturn;
    ToReturn<<"FileName"<<',';
    ToReturn<<"FileSize"<<',';
    ToReturn<<"Format"<<',';
    ToReturn<<"Duration"<<',';
    ToReturn<<"Vid Format"<<',';
    ToReturn<<"Vid CodecID"<<',';
    ToReturn<<"Vid FrameRate"<<',';
    ToReturn<<"Vid Width"<<',';
    ToReturn<<"Vid Height"<<',';
    ToReturn<<"Vid BitDepth"<<',';
    ToReturn<<"Vid BitRate"<<',';
    ToReturn<<"Aud Format"<<',';
    ToReturn<<"Aud CodecID"<<',';
    ToReturn<<"Aud Channels"<<',';
    ToReturn<<"Aud SampleRate"<<',';
    ToReturn<<"Aud BitDepth"<<',';
    ToReturn<<"Aud BitRate"<<',';
    ToReturn<<"UnprocessedChunks"<<",";
    ToReturn<<"Tdat"<<',';
    ToReturn<<"INFO"<<',';
    ToReturn<<"XMP"<<',';
    ToReturn<<"aXML"<<',';
    ToReturn<<"iXML"<<',';
    ToReturn<<"MD5Stored"<<',';
    ToReturn<<"MD5Generated"<<',';
    ToReturn<<"Errors"<<',';
    ToReturn<<"Information";

    return ToReturn.str();
}

//---------------------------------------------------------------------------
string Riff_Handler::Technical_Get()
{
    ZtringList List;
    List.Separator_Set(0, _T(","));
    List.push_back(Chunks->Global->File_Name);
    List.push_back(Ztring::ToZtring(Chunks->Global->File_Size));
    if (File_IsValid)
    {
        List.push_back(MediaInfo_General_Format);
        List.push_back(MediaInfo_General_Duration);
        List.push_back(MediaInfo_Video_Format);
        List.push_back(MediaInfo_Video_CodecID);
        List.push_back(MediaInfo_Video_FrameRate);
        List.push_back(MediaInfo_Video_Width);
        List.push_back(MediaInfo_Video_Height);
        List.push_back(MediaInfo_Video_BitDepth);
        List.push_back(MediaInfo_Video_BitRate);
        List.push_back(MediaInfo_Audio_Format);
        List.push_back(MediaInfo_Audio_CodecID);
        List.push_back(MediaInfo_Audio_Channels);
        List.push_back(MediaInfo_Audio_SampleRate);
        List.push_back(MediaInfo_Audio_BitDepth);
        List.push_back(MediaInfo_Audio_BitRate);
        Ztring UnprocessedChunks;
        for (std::set<int32u>::iterator ChunkId=Chunks->Global->UnprocessedChunks.begin(); ChunkId!=Chunks->Global->UnprocessedChunks.end(); ChunkId++)
        {
            if (!UnprocessedChunks.empty())
                UnprocessedChunks+=" ";
            UnprocessedChunks+=Ztring().From_CC4(*ChunkId);
        }
        List.push_back(UnprocessedChunks);
        List.push_back(Get("Tdat").empty()?"No":"Yes");
        List.push_back(Get("INFO").empty()?"No":"Yes");
        List.push_back(Get("XMP").empty()?"No":"Yes");
        List.push_back(Get("aXML").empty()?"No":"Yes");
        List.push_back(Get("iXML").empty()?"No":"Yes");
        List.push_back(Get("MD5Stored"));
        List.push_back(Get("MD5Generated"));
    }
    else
        List.resize(1+26-2);
    string Errors_Temp=PerFile_Error.str();
    if (!Errors_Temp.empty())
        Errors_Temp.resize(Errors_Temp.size()-1);
    List.push_back(Errors_Temp);
    string Information_Temp=PerFile_Information.str();
    if (!Information_Temp.empty())
        Information_Temp.resize(Information_Temp.size()-1);
    List.push_back(Information_Temp);
    return List.Read();
}

//***************************************************************************
// Info
//***************************************************************************

//---------------------------------------------------------------------------
string Riff_Handler::Trace_Get()
{
    return Chunks->Global->Trace.str();
}

//---------------------------------------------------------------------------
string Riff_Handler::FileName_Get()
{
    return Chunks->Global->File_Name;
}

//---------------------------------------------------------------------------
string Riff_Handler::FileDate_Get()
{
    return Chunks->Global->File_Date;
}

//---------------------------------------------------------------------------
float Riff_Handler::Progress_Get()
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return 0;    
    CriticalSectionLocker(Chunks->Global->CS);
    if (Chunks->Global->Progress==1)
        return (float)0.99; //Must finish opening, see Open()
    return Chunks->Global->Progress;
}

//---------------------------------------------------------------------------
void Riff_Handler::Progress_Clear()
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return;

    CriticalSectionLocker(Chunks->Global->CS);
    Chunks->Global->Progress=0;
}

//---------------------------------------------------------------------------
bool Riff_Handler::Canceled_Get()
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return false;    
    CriticalSectionLocker(Chunks->Global->CS);
    return File_IsCanceled;
}

//---------------------------------------------------------------------------
void Riff_Handler::Cancel()
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return;    
    CriticalSectionLocker(Chunks->Global->CS);
    Chunks->Global->Canceling=true;
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsModified_Get()
{
    bool ToReturn=false;
    for (size_t Fields_Pos=0; Fields_Pos<Fields_Max; Fields_Pos++)
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Pos]; Pos++)
            if (IsModified(xxxx_Strings[Fields_Pos][Pos]))
                ToReturn=true;

    return ToReturn;
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsValid_Get()
{
    return File_IsValid;
}

//***************************************************************************
// Helpers - Per item
//***************************************************************************

//---------------------------------------------------------------------------
string Riff_Handler::Get(const string &Field, Riff_Base::global::chunk_strings* &Chunk_Strings)
{
    if (Field=="errors")
        return PerFile_Error.str();
    if (Field=="information")
        return PerFile_Information.str();

    if (!File_IsValid)
        return string();

    //Special cases
    if (Field=="tdat" && &Chunk_Strings && Chunk_Strings)
    {
        ZtringList List;
        List.Separator_Set(0, _T(","));
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Tdat]; Pos++)
            List.push_back(Chunk_Strings->Strings[Ztring(xxxx_Strings[Fields_Tdat][Pos]).MakeLowerCase()]);
        return List.Read();
    }
    if (Field=="INFO" && &Chunk_Strings && Chunk_Strings)
    {
        ZtringList List;
        List.Separator_Set(0, _T(","));
        for (size_t Pos=0; Pos<xxxx_Strings_Size[Fields_Info]; Pos++)
             List.push_back(Chunk_Strings->Strings[xxxx_Strings[Fields_Info][Pos]]);
        return List.Read();
    }

    if (&Chunk_Strings && Chunk_Strings && Chunk_Strings->Strings.find(Field)!=Chunk_Strings->Strings.end())
        return Chunk_Strings->Strings[Field];
    else
        return Riff_Handler_EmptyZtring_Const;
}

//---------------------------------------------------------------------------
bool Riff_Handler::Set(const string &Field, const string &Value, Riff_Base::global::chunk_strings* &Chunk_Strings, int32u Chunk_Name2, int32u Chunk_Name3)
{
    if (!File_IsValid
     || &Chunk_Strings==NULL) 
        return false;
    
    if ((Chunk_Strings!=NULL && Value==Chunk_Strings->Strings[Field])
     || (Chunk_Strings==NULL && Value.empty()))
        return true; //Nothing to do

    //Overwrite_Reject
    if (Overwrite_Reject && Chunk_Strings!=NULL && !Chunk_Strings->Strings[Field].empty())
    {
        Errors<<(Chunks?Chunks->Global->File_Name:"")<<": overwriting is not authorized ("<<Field<<")"<<endl;
        return false;
    }

    //Log
    Ztring Value_ToDisplay=Value;
    Value_ToDisplay.FindAndReplace("\r", " ", 0, Ztring_Recursive);
    Value_ToDisplay.FindAndReplace("\n", " ", 0, Ztring_Recursive);
    Information<<(Chunks?Chunks->Global->File_Name:"")<<": "<<Field<<", "<<((Chunk_Strings==NULL || Chunk_Strings->Strings[Field].empty())?"(empty)":((Field=="xmp" || Field=="axml" || Field=="ixml")?"(XML data)":Chunk_Strings->Strings[Field].c_str()))<<" --> "<<(Value.empty()?"(removed)":((Field=="xmp" || Field=="axml" || Field=="ixml")?"(XML data)":Value_ToDisplay.c_str()))<<endl;
       
    //Special cases - Before
    if (Chunk_Strings==NULL)
        Chunk_Strings=new Riff_Base::global::chunk_strings();

    //Filling
    bool Alreadyexists=false;
    for (size_t Pos=0; Pos<Chunk_Strings->Histories[Field].size(); Pos++)
        if (Chunk_Strings->Histories[Field][Pos]==Chunk_Strings->Strings[Field])
            Alreadyexists=true;
    if (!Alreadyexists)
        Chunk_Strings->Histories[Field].push_back(Chunk_Strings->Strings[Field]);
    Chunk_Strings->Strings[Field]=Value;

    return true;
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsOriginal(const string &Field, const string &Value, Riff_Base::global::chunk_strings* &Chunk_Strings)
{
    if (!File_IsValid || &Chunk_Strings==NULL || Chunk_Strings==NULL)
        return Value.empty();
   
    //Special cases
    if (Field=="timereference (translated)" && &Chunk_Strings && Chunk_Strings && Chunk_Strings->Strings.find("timereference")!=Chunk_Strings->Strings.end())
        return IsOriginal("timereference", Get("timereference"));

    if (Chunk_Strings->Histories[Field].empty())
        return Value==Chunk_Strings->Strings[Field];
   
    return Value==Chunk_Strings->Histories[Field][0];
}

//---------------------------------------------------------------------------
bool Riff_Handler::IsModified(const string &Field, Riff_Base::global::chunk_strings* &Chunk_Strings)
{
    if (!File_IsValid)
        return false;

    //Special cases
    if (Field=="timereference (translated)" && &Chunk_Strings && Chunk_Strings && Chunk_Strings->Strings.find("timereference")!=Chunk_Strings->Strings.end())
        return IsModified("timereference");

    if (&Chunk_Strings!=NULL && Chunk_Strings && Chunk_Strings->Histories.find(Field)!=Chunk_Strings->Histories.end())
    {
        //Special cases
        if (Field=="bextversion")
            return !Chunk_Strings->Histories["bextversion"].empty() && !(Chunk_Strings->Strings["bextversion"]=="0" || Chunk_Strings->Histories["bextversion"][0]==Chunk_Strings->Strings["bextversion"]);

        return !Chunk_Strings->Histories[Field].empty() && Chunk_Strings->Histories[Field][0]!=Chunk_Strings->Strings[Field];
    }
    else
        return false;
}

//---------------------------------------------------------------------------
string Riff_Handler::History(const string &Field, Riff_Base::global::chunk_strings* &Chunk_Strings)
{
    if (!File_IsValid)
        return string();

    if (&Chunk_Strings!=NULL && Chunk_Strings && Chunk_Strings->Strings.find(Field)!=Chunk_Strings->Strings.end())
        return Chunk_Strings->Histories[Field].Read();
    else
        return Riff_Handler_EmptyZtring_Const;
}

//***************************************************************************
// Configuration
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_Handler::Options_Update()
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return;

    Chunks->Global->NoPadding_Accept=NoPadding_Accept;
    Chunks->Global->NewChunksAtTheEnd=false; //NewChunksAtTheEnd;
    Chunks->Global->GenerateMD5=GenerateMD5;
    Chunks->Global->VerifyMD5=VerifyMD5;
    Chunks->Global->EmbedMD5=EmbedMD5;
    Chunks->Global->EmbedMD5_AuthorizeOverWritting=EmbedMD5_AuthorizeOverWritting;

    //MD5
    if (Chunks->Global->VerifyMD5)
    {
        //Removing all MD5 related info
        Ztring PerFile_Error_Temp=PerFile_Error.str();
        PerFile_Error_Temp.FindAndReplace(Ztring("MD5, failed verification\n"), Ztring());
        PerFile_Error.str(PerFile_Error_Temp);
        Ztring PerFile_Information_Temp=PerFile_Information.str();
        PerFile_Information_Temp.FindAndReplace(Ztring("MD5, no existing MD5 chunk\n"), Ztring());
        PerFile_Information_Temp.FindAndReplace(Ztring("MD5, verified\n"), Ztring());
        PerFile_Information.str(PerFile_Information_Temp);
        
        //Checking
        Ztring md5generated(Chunks->Global->MD5Generated->Strings["md5generated"]); md5generated.MakeLowerCase();
        Ztring md5stored(Chunks->Global->MD5Stored->Strings["md5stored"]); md5stored.MakeLowerCase();
        if (!(Chunks->Global->MD5Stored && !md5stored.empty()))
        {
            Information<<Chunks->Global->File_Name<<": MD5, no existing MD5 chunk"<<endl;
            PerFile_Information<<"MD5, no existing MD5 chunk"<<endl;
        }
        else if (Chunks->Global->MD5Generated && md5generated!=md5stored)
        {
            Errors<<Chunks->Global->File_Name<<": MD5, failed verification"<<endl;
            PerFile_Error.str(string());
            PerFile_Error<<"MD5, failed verification"<<endl;
        }
        else
        {
            Information<<Chunks->Global->File_Name<<": MD5, verified"<<endl;
            PerFile_Information.str(string());
            PerFile_Information<<"MD5, verified"<<endl;
        }
    }
    if (EmbedMD5
     && Chunks->Global->MD5Generated && !Chunks->Global->MD5Generated->Strings["md5generated"].empty()
     && (!(Chunks->Global->MD5Stored && !Chunks->Global->MD5Stored->Strings["md5stored"].empty())
      || EmbedMD5_AuthorizeOverWritting))
            Set("MD5Stored", Chunks->Global->MD5Generated->Strings["md5generated"], rules());
}

//***************************************************************************
// Helpers - Retrieval of chunks info
//***************************************************************************

//---------------------------------------------------------------------------
Riff_Base::global::chunk_strings** Riff_Handler::chunk_strings_Get(const string &Field)
{
    if (Chunks==NULL || Chunks->Global==NULL)
        return NULL;    
        
    Ztring Field_Lowered=Ztring(Field).MakeLowerCase();
    if (Field_Lowered=="history")
        Field_Lowered="codinghistory";

    //MXP
    else if (Field_Lowered=="xmp")
        return &Chunks->Global->XMP;

    //aXML
    else if (Field_Lowered=="axml")
        return &Chunks->Global->aXML;
    
    //iXML
    else if (Field_Lowered=="ixml")
        return &Chunks->Global->iXML;
    
    //MD5Stored
    else if (Field_Lowered=="md5stored")
        return &Chunks->Global->MD5Stored;
    
    //MD5Stored
    else if (Field_Lowered=="md5generated")
        return &Chunks->Global->MD5Generated;

    //Tdat
    else if (Field_Lowered=="tdat" || Field_Lowered=="rn_a" || Field_Lowered=="rn_o" || Field_Lowered=="tc_a" || Field_Lowered=="tc_o")
        return &Chunks->Global->Tdat;
    
    //INFO
    else if (Field.size()==4)
        return &Chunks->Global->INFO;
    
    //Unknown
    return NULL;
}

//---------------------------------------------------------------------------
string Riff_Handler::Field_Get(const string &Field)
{
    Ztring Field_Lowered=Ztring(Field).MakeLowerCase();
    if (Field_Lowered=="history")
        Field_Lowered="codinghistory";

    if (Field_Lowered=="filename"
     || Field_Lowered=="bext"
     || Field_Lowered=="description"
     || Field_Lowered=="originator"
     || Field_Lowered=="originatorreference"
     || Field_Lowered=="originationdate"
     || Field_Lowered=="originationtime"
     || Field_Lowered=="timereference (translated)"
     || Field_Lowered=="timereference"
     || Field_Lowered=="bextversion"
     || Field_Lowered=="umid"
     || Field_Lowered=="loudnessvalue"
     || Field_Lowered=="loudnessrange"
     || Field_Lowered=="maxtruepeaklevel"
     || Field_Lowered=="maxmomentaryloudness"
     || Field_Lowered=="maxshorttermloudness"
     || Field_Lowered=="codinghistory"
     || Field_Lowered=="xmp"
     || Field_Lowered=="axml"
     || Field_Lowered=="ixml"
     || Field_Lowered=="md5stored"
     || Field_Lowered=="md5generated")
        return Field_Lowered; 

    //Tdat
    else if (Field_Lowered=="tdat" || Field_Lowered=="rn_a" || Field_Lowered=="rn_o" || Field_Lowered=="tc_a" || Field_Lowered=="tc_o")
        return Field_Lowered;

    //Unknown 4 chars --> In INFO chunk, in uppercase
    if (Field.size()==4)
        return Ztring(Field).MakeUpperCase();

    //Unknown --> In INFO chunk, in uppercase
    return Field_Lowered;
}

//---------------------------------------------------------------------------
int32u Riff_Handler::Chunk_Name2_Get(const string &Field)
{
    Ztring Field_Lowered=Ztring(Field).MakeLowerCase();
    if (Field_Lowered=="history")
        Field_Lowered="codinghistory";

    //XMP
    else if (Field_Lowered=="xmp")
        return Elements::AVI___PMX; 

    //aXML
    else if (Field_Lowered=="axml")
        return Elements::AVI__aXML; 

    //iXML
    else if (Field_Lowered=="ixml")
        return Elements::AVI__iXML; 

    //MD5Stored
    else if (Field_Lowered=="md5stored")
        return Elements::AVI__MD5_; 

    //MD5Generated
    else if (Field_Lowered=="md5generated")
        return Elements::AVI__MD5_; 

    //Tdat
    else if (Field_Lowered=="tdat" || Field_Lowered=="rn_a" || Field_Lowered=="rn_o" || Field_Lowered=="tc_a" || Field_Lowered=="tc_o")
        return Elements::AVI__Tdat;

    //INFO
    else if (Field.size()==4)
        return Elements::AVI__INFO;
    
    //Unknown
    return 0x00000000;
}

//---------------------------------------------------------------------------
int32u Riff_Handler::Chunk_Name3_Get(const string &Field)
{
    //Tdat
    if (Chunk_Name2_Get(Field)==Elements::AVI__Tdat)
    {
        Ztring Field_Lowered=Ztring(Field).MakeLowerCase();
        if (Field_Lowered=="rn_a")
            return Elements::AVI__Tdat_rn_A;
        if (Field_Lowered=="rn_o")
            return Elements::AVI__Tdat_rn_O;
        if (Field_Lowered=="tc_a")
            return Elements::AVI__Tdat_tc_A;
        if (Field_Lowered=="tc_o")
            return Elements::AVI__Tdat_tc_O;
    }
    
    //INFO
    if (Chunk_Name2_Get(Field)==Elements::AVI__INFO)
        return Ztring(Field).MakeUpperCase().To_CC4(); 
    
    //Unknown / not needed
    return 0x00000000;
}
