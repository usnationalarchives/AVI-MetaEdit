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
#include <cstring>
//---------------------------------------------------------------------------

//***************************************************************************
// Read
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__MD5_::Read_Internal ()
{
    //Integrity
    if (Global->MD5Stored && !Global->MD5Stored->Strings["md5stored"].empty())
        throw exception_valid("2 MD5 chunks");

    //Reading
    Read_Internal_ReadAllInBuffer();
    
    //Parsing
    Ztring MD5_Total;
    for (size_t Pos=0; Pos<Global->AVI__hdrl_strl_strf.size(); Pos++)
    {
        int128u MD5Stored;
        Get_L16   (     MD5Stored);
        Ztring MD5_PerItem;
        MD5_PerItem.From_Number(MD5Stored, 16);
        while (MD5_PerItem.size()<32)
            MD5_PerItem.insert(MD5_PerItem.begin(), '0'); //Padding with 0, this must be a 32-byte string
        if (!MD5_Total.empty())
            MD5_Total+=_T(" / ");
        MD5_PerItem.MakeLowerCase();
        MD5_Total+=MD5_PerItem;
    }

    Global->MD5Stored=new Riff_Base::global::chunk_strings;
    Global->MD5Stored->Strings["md5stored"]=MD5_Total;
}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__MD5_::Modify_Internal ()
{
    if (!Global->EmbedMD5_AuthorizeOverWritting && !(Global->MD5Stored && !Global->MD5Stored->Strings["md5stored"].empty()))
        return; //Should never happen (test in Riff_Handler), but in case of.

    if (!(Global->MD5Stored && !Global->MD5Stored->Strings["md5stored"].empty()))
    {
        Chunk.Content.IsRemovable=true;
        return;
    }

    ZtringList Values;
    Values.Separator_Set(0, _T(" / "));
    Values.Write(Global->MD5Stored->Strings["md5stored"]);

    //Creating buffer
    Chunk.Content.Buffer_Offset=0;
    Chunk.Content.Size=16*Values.size();
    delete[] Chunk.Content.Buffer; Chunk.Content.Buffer=new int8u[Chunk.Content.Size];
    memset(Chunk.Content.Buffer, '\0', 16);

    //Parsing
    string Message;
    for (size_t ValuePos=0; ValuePos<Values.size(); ValuePos++)
    {
        Put_L16   (     Values[ValuePos].To_int128u());
    }

    Chunk.Content.IsModified=true;
    Chunk.Content.Size_IsModified=true;
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__MD5_::Write_Internal ()
{
}

