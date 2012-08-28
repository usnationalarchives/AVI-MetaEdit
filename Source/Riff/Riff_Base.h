// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef Riff_BaseH
#define Riff_BaseH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "ZenLib/ZtringList.h"
#include "ZenLib/Ztring.h"
#include "ZenLib/File.h"
#include "ZenLib/CriticalSection.h"
#include <vector>
#include <map>
#include <set>
#include <sstream>
extern "C"
{
#include "MD5/md5.h"
}
using namespace ZenLib;
using namespace std;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
const int64u RIFF_Size_Limit=0xFFFFFFFF; //Limit about when we implement ds64
const int64u RIFF_AVI__JUNK_DefaultSise=65536; //Default size of JUNK at the beginning of a file
//---------------------------------------------------------------------------

//***************************************************************************
// Exceptions
//***************************************************************************

class exception_read : public exception
{
    virtual const char* what() const throw()
    {
        return "error during reading";
    }
};

class exception_canceled : public exception
{
    virtual const char* what() const throw()
    {
        return "canceled";
    }
};

class exception_valid : public exception
{
public:
    exception_valid(const string &text_in) throw () : exception() {text="invalid AVI ("+text_in+")";}
    ~exception_valid() throw () {};
    virtual const char* what() const throw()
    {
        return text.c_str();
    }

protected:
    string text;    
};

class exception_read_chunk : public exception
{
public:
    exception_read_chunk(const string &text_in) throw () : exception() {text=text_in;}
    ~exception_read_chunk() throw () {};
    virtual const char* what() const throw()
    {
        return text.c_str();
    }

protected:
    string text;    
};

class exception_write : public exception
{
public:
    exception_write(const string &text_in) throw () : exception() {text=text_in;}
    exception_write() throw () {text="error during writing";};
    ~exception_write() throw () {};
    virtual const char* what() const throw()
    {
        return text.c_str();
    }

protected:
    string text;    
};


//***************************************************************************
// Riff_Base
//***************************************************************************

class Riff_Base
{
public:
    //***************************************************************************
    // Structures
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Global structure for handling common data
    struct global
    {
        struct chunk_AVI_
        {
            int64u          File_Offset;
            int64u          Size_Original;

            chunk_AVI_()
            {
                File_Offset=(int64u)-1;
                Size_Original=(int64u)-1;
            }
        };
        struct chunk_AVI__hdrl_avih
        {
            int32u  TotalFrames;
            int32u  MicrossecPerFrame;

            chunk_AVI__hdrl_avih()
            {
                MicrossecPerFrame=(int32u)-1;
                TotalFrames=(int32u)-1;
            }
        };
        struct chunk_AVI__hdrl_dmlh
        {
            chunk_AVI__hdrl_dmlh()
            {
            }
        };
        struct chunk_AVI__hdrl
        {
            chunk_AVI__hdrl()
            {
            }
        };
        struct chunk_AVI__hdrl_strl_strh
        {
            int32u fccType;
            int32u Scale;
            int32u Rate;
            
            chunk_AVI__hdrl_strl_strh()
            {
                fccType=0;
            }
        };
        struct chunk_AVI__hdrl_strl_strf
        {
            //Video
            int32u Width;
            int32u Height;
            int16u BitCount;
            int32u Compression;
            int32u SizeImage;

            //Audio
            int16u FormatTag;
            int16u Channels;
            int32u SamplesPerSec;
            int32u AvgBytesPerSec;
            int16u BitsPerSample;

            //MD5
            MD5Context* MD5;
            
            chunk_AVI__hdrl_strl_strf()
            {
                //Video
                Compression=0;
                
                //Audio
                FormatTag=0;

                //MD5
                MD5=NULL;
            }

            ~chunk_AVI__hdrl_strl_strf()
            {
                delete MD5; //MD5=NULL;
            }
        };
        struct chunk_AVI__movi
        {
            int64u          File_Offset;
            int64u          Size;

            chunk_AVI__movi()
            {
                File_Offset=(int64u)-1;
                Size=(int64u)-1;
            }
        };
        struct chunk_strings
        {
            map<string, Ztring> Strings;
            map<string, ZtringList> Histories;
        };
        struct buffer
        {
            int8u*  Data;
            size_t  Size;
            size_t  Size_Maximum;

            buffer()
            {
                Data=NULL;
                Size=0;
                Size_Maximum=0;
            }
        };

        File                In;
        File                Out;
        buffer              Out_Buffer_Begin;
        buffer              Out_Buffer_End;
        bool                Out_Buffer_WriteAtEnd;

        string              File_Name;
        int64u              File_Size;
        string              File_Date;
        std::set<int32u>    UnprocessedChunks;
        ostringstream       Trace;
        chunk_AVI_*             AVI_;
        std::set<void*>         AVI__Pointers;
        chunk_AVI__hdrl*        AVI__hdrl;
        chunk_AVI__hdrl_avih*   AVI__hdrl_avih;
        chunk_AVI__hdrl_dmlh*   AVI__hdrl_dmlh;
        std::vector<chunk_AVI__hdrl_strl_strh*> AVI__hdrl_strl_strh;
        std::vector<chunk_AVI__hdrl_strl_strf*> AVI__hdrl_strl_strf;
        std::vector<int64u>     AVI__hdrl_strl_indx_In_Position_Indexes_List;
        std::set<void*>         AVI__hdrl_strl_indx_Pointers;
        chunk_AVI__movi*        AVI__movi;
        std::set<void*>         AVI__movi_Pointers;
        std::set<void*>         AVI__movi___ix_Pointers;
        std::map<void*, int64s> AVI__movi___ix_Difference; //Key is pointer
        std::map<int32u, bool>  AVI__movi___ix_WithFields; //Key is ChunkId
        void*                   AVI__idx1_Pointer;
        bool                    AVI__idx1_IsAbsolute;
        int64s                  AVI__idx1_Difference;
        chunk_strings      *Tdat;
        chunk_strings      *INFO;
        chunk_strings      * XMP;
        chunk_strings      *aXML;
        chunk_strings      *iXML;
        chunk_strings      *MD5Stored;
        chunk_strings      *MD5Generated;
        int64u              AVI__movi_FirstDataChunkMoviOffset;
        int64u              AVI__movi_FirstDataChunkPosition;
        int64u              AVI__movi_FirstDataChunkSize;
        bool                NoPadding_Accept;
        bool                NoPadding_IsCorrected;
        bool                NewChunksAtTheEnd;
        bool                GenerateMD5;
        bool                VerifyMD5;
        bool                EmbedMD5;
        bool                EmbedMD5_AuthorizeOverWritting;
        bool                Out_Buffer_File_TryModification;
        bool                Out_Buffer_File_IsModified;

        CriticalSection     CS;
        float               Progress;
        bool                Canceling;

        global()
        {
            File_Size=0;
            AVI_=NULL;
            AVI__hdrl=NULL;
            AVI__hdrl_avih=NULL;
            AVI__hdrl_dmlh=NULL;
            AVI__movi=NULL;
            Tdat=NULL;
            INFO=NULL;
             XMP=NULL;
            aXML=NULL;
            iXML=NULL;
            MD5Stored=NULL;
            MD5Generated=NULL;
            AVI__idx1_Pointer=NULL;
            AVI__idx1_IsAbsolute=true;
            AVI__idx1_Difference=0;
            AVI__movi_FirstDataChunkMoviOffset=(int64u)-1;
            AVI__movi_FirstDataChunkPosition=(int64u)-1;
            AVI__movi_FirstDataChunkSize=(int64u)-1;
            NoPadding_Accept=false;
            NoPadding_IsCorrected=false;
            NewChunksAtTheEnd=false;
            GenerateMD5=false;
            VerifyMD5=false;
            EmbedMD5=false;
            EmbedMD5_AuthorizeOverWritting=false;
            Out_Buffer_WriteAtEnd=false;
            Out_Buffer_File_TryModification=true;
            Out_Buffer_File_IsModified=false;
            Progress=0;
            Canceling=false;
        }

        ~global()
        {
            delete AVI_; //AVI_=NULL;
            delete AVI__hdrl; //AVI__hdrl=NULL;
            delete AVI__hdrl_dmlh; //AVI__hdrl_dmlh=NULL;
            delete AVI__movi; //AVI__movi=NULL;
            delete Tdat; //Tdat=NULL;
            delete INFO; //INFO=NULL;
            delete  XMP; // XMP=NULL;
            delete aXML; //aXML=NULL;
            delete iXML; //iXML=NULL;
            for (size_t Pos=0; Pos<AVI__hdrl_strl_strh.size(); Pos++)
                delete AVI__hdrl_strl_strh[Pos]; //AVI__hdrl_strl_sthr[Pos]=NULL
            for (size_t Pos=0; Pos<AVI__hdrl_strl_strf.size(); Pos++)
                delete AVI__hdrl_strl_strf[Pos]; //AVI__hdrl_strl_strf[Pos]=NULL
        }
    };

    //---------------------------------------------------------------------------
    //Chunk specific
    struct chunk
    {
        struct header
        {
            int32u  Name;
            bool    IsList; //If header is 12 byte long
            bool    IsModified;
            bool    IsOpaqueData;
            
            header()
            {
                Name=0x00000000;
                IsList=false;
                IsModified=false;
                IsOpaqueData=false;
            }

            int64u Size()
            {
                if (IsOpaqueData)
                    return 0;
                return Name==0x00000000?0:(IsList?12:8);
            }
        };
        struct content
        {
            int8u*  Buffer;
            size_t  Buffer_Offset; //Internal use
            int64u  Size; //Header excluded
            bool    IsModified;
            bool    IsRemovable;
            bool    Size_IsModified;
            
            content()
            {
                Buffer=NULL;
                Buffer_Offset=0;
                Size=0;
                IsModified=false;
                IsRemovable=false;
                Size_IsModified=false;
            }

            ~content()
            {
                delete[] Buffer; //Buffer=NULL;
            }   
        };

        header  Header;
        content Content;

        int64u  File_In_Position;
        int64u  File_Out_Position;
        bool    ShouldParse;
        bool    IsMoovable;

        chunk()
        {
            File_In_Position=(int64u)-1;
            File_Out_Position=(int64u)-1;
            ShouldParse=true;
            IsMoovable=true;
        }

        int64u TotalSize()
        {
            int64u Size=Header.Size()+Content.Size;
            if (Size%2)
                Size++;
            return Size;
        }
        bool IsFiller();
    };

    //***************************************************************************
    // Interface
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Constructor/Destructor
             Riff_Base          (Riff_Base* Parent_);
    virtual ~Riff_Base          ();
    
    //---------------------------------------------------------------------------
    //Read/Write
    void Read                   (const chunk &Chunk_In);
    void Modify                 (int32u Chunk_Name_1, int32u Chunk_Name_2, int32u Chunk_Name_3);
    void Modify                 ()                                              {Modify_Internal();};
    bool Insert                 (int32u Chunk_Name);
    bool InsertVirtual          (size_t Pos, int64u Size);
    bool InsertJunk             (size_t Pos, int64u Size);
    bool ClearJunk              ();
    void UpdateIndexes          ();
    void Write                  ();

    //---------------------------------------------------------------------------
    //Data
    int64u Block_Size_Get       ();
    int64u Block_Size_Get       (int32u Element);
    size_t Subs_Pos_Get         (int32u Element);
    bool   Read_Header          (chunk &NewChunk);
    bool   IsModified           ()                                              {return Chunk.Content.IsModified;};
    void   IsModified_Clear     ()                                              {Chunk.Content.IsModified=false;};
    bool   IsRemovable          ()                                              {return Chunk.Content.IsRemovable;};
    int32u Header_Name_Get      ()                                              {return Chunk.Header.Name;};
    void   Header_Name_Set      (int32u Name)                                   {Chunk.Header.Name=Name;};
    bool   CanOverwrite         (int64u &File_Out_Position, int64u &SizeToRead, int64u &ShouldAddFilling, bool Refactorize);
    bool   WriteOut             (bool Refactorize);

    //Chunk
    chunk   Chunk;
    Riff_Base*  Parent;

protected :
    //***************************************************************************
    // Buffer handling (virtual)
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Read/Write
    virtual void    Read_Internal       ();
    virtual void    Seek_Internal       ();
    virtual void    Modify_Internal     ()                                      {}
    virtual void    Insert_Internal     (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos);
    virtual void    Write_Internal      ()                                      ;

    //***************************************************************************
    // Buffer handling (buffer read/write)
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Buffer handling - Little endian values
    void Get_L1     (int8u  &Value);
    void Put_L1     (int8u   Value);
    void Get_L2     (int16u &Value);
    void Put_L2     (int16u  Value);
    void Get_L3     (int32u &Value);
    void Put_L3     (int32u  Value);
    void Get_L4     (int32u &Value);
    void Put_L4     (int32u  Value);
    void Get_L8     (int64u &Value);
    void Put_L8     (int64u  Value);
    void Get_L16    (int128u &Value);
    void Put_L16    (int128u  Value);

    //---------------------------------------------------------------------------
    //Buffer handling - Character codes
    void Get_C4     (int32u &Value);
    void Put_C4     (int32u  Value);

    //---------------------------------------------------------------------------
    //Buffer handling - UUID
    void Get_UUID   (int128u &Value);
    void Put_UUID   (int128u  Value);
    void Skip_UUID  ();

    //---------------------------------------------------------------------------
    //Buffer handling - Stirngs
    void Get_String (int64u Value_Size, string &Value);
    void Put_String (int64u Value_Size, string Value);

    //---------------------------------------------------------------------------
    //Buffer handling - Other
    void Skip_XX    (int64u Value_Size);

    //***************************************************************************
    // Buffer handling (internal)
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Read/Write helpers
    void Read_Internal_ReadAllInBuffer  ();
    void Modify_Internal_Subs           (int32u Chunk_Name_0, int32u Chunk_Name_1, int32u Chunk_Name_2);
    void Write_Internal_Subs            ();

    //***************************************************************************
    // Data
    //***************************************************************************

    //---------------------------------------------------------------------------
    //Subs
    public :
    std::vector<Riff_Base*> Subs;
    protected :

    //---------------------------------------------------------------------------
    //Global
    global *Global;

    //---------------------------------------------------------------------------
    //Internal

    size_t  Level()
    {
        size_t ToReturn=0;
        Riff_Base* ToReturn_Parent=Parent;
        while (ToReturn_Parent)
        {
            ToReturn++;
            ToReturn_Parent=ToReturn_Parent->Parent;
        }
        return ToReturn;
    }
    //---------------------------------------------------------------------------
    //Friends
    friend class Riff_Handler;
};

#endif
