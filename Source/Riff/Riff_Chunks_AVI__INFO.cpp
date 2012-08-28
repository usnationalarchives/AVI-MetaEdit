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
// Read
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__INFO::Read_Internal ()
{
    //Integrity
    if (Global->INFO)
        throw exception_valid("2 INFO chunks");

    //Filling
    Global->INFO=new Riff_Base::global::chunk_strings;
}

//---------------------------------------------------------------------------
void Riff_AVI__INFO::Seek_Internal ()
{
}

//***************************************************************************
// Insert
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__INFO::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    Chunk=new Riff_AVI__INFO_xxxx(this);
}
