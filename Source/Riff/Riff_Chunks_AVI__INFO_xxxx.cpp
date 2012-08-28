// AVI MetaEdit Riff - RIFF stuff for AVI MetaEdit
//
// This code was created in 2010 for the Library of Congress and the
// other federal government agencies participating in the Federal Agencies
// Digitization Guidelines Initiative and it is in the public domain.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#include "Riff/Riff_Chunks.h"
//---------------------------------------------------------------------------

//***************************************************************************
// Const
//***************************************************************************

const size_t INFO_Strings_Size=20;
const char* INFO_Strings[20]=
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
};

//***************************************************************************
// Read
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__INFO_xxxx::Read_Internal ()
{
    //Junk
    switch (Chunk.Header.Name)
    {
        case Elements::AVI__filr :
        case Elements::AVI__FILR :
        case Elements::AVI__fllr :
        case Elements::AVI__FLLR :
        case Elements::AVI__junk :
        case Elements::AVI__JUNK :
        case Elements::AVI__junq :
        case Elements::AVI__JUNQ :
        case Elements::AVI__pad_ :
        case Elements::AVI__PAD_ :
                                    return;
        default                  :  break;
    }

    //Integrity
    if (Global->INFO->Strings.find(Ztring().From_CC4(Chunk.Header.Name))!=Global->INFO->Strings.end())
        throw exception_valid("2 "+Ztring().From_CC4(Chunk.Header.Name)+" chunks");

    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    Ztring Value;    
    Get_String(Chunk.Content.Size, Value);
    if (Chunk.Header.Name==Elements::AVI__INFO_IDIT && Value.size()==25 && Value[24]=='\n')
        Value.resize(24);

    //Filling
    Ztring Field=Ztring().From_CC4(Chunk.Header.Name);
    Global->INFO->Strings[Field]=Value;

    //Details
    bool Unprocessed=true;
    for (size_t Pos=0; Pos<INFO_Strings_Size; Pos++)
         if (INFO_Strings[Pos]==Field)
             Unprocessed=false;
    if (Unprocessed)
        Global->UnprocessedChunks.insert(Chunk.Header.Name);
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__INFO_xxxx::Modify_Internal ()
{
    string Field=Ztring().From_CC4(Chunk.Header.Name).MakeUpperCase();
    if (Global->INFO->Strings[Field].empty())
    {
        Chunk.Content.IsRemovable=true;
        return;
    }

    //Calculating size
    if (Global->INFO->Strings[Field].size()>=0xFFFFFFFF)
        return; //TODO: error

    //Creating buffer
    Chunk.Content.Buffer_Offset=0;
    Chunk.Content.Size=Global->INFO->Strings[Field].size();
    if (Chunk.Header.Name==Elements::AVI__INFO_IDIT && Global->INFO->Strings[Field].size()==24)
        Chunk.Content.Size+=2;
    delete[] Chunk.Content.Buffer; Chunk.Content.Buffer=new int8u[Chunk.Content.Size];

    Put_String(Global->INFO->Strings[Field].size(), Global->INFO->Strings[Field]);
    if (Chunk.Header.Name==Elements::AVI__INFO_IDIT && Global->INFO->Strings[Field].size()==24)
        Put_String(2, "\n\0");

    Chunk.Content.IsModified=true;
    Chunk.Content.Size_IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__INFO_xxxx::Write_Internal ()
{
}

