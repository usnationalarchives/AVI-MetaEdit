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
// AVIX
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVIX::Read_Internal ()
{
    //Integrity
    if (Global->AVI__movi==NULL)
        throw exception_valid("AVI chunk must be before AVIX chunk");

}

//---------------------------------------------------------------------------
void Riff_AVIX::Seek_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_AVIX::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVIX_movi : Chunk=new Riff_AVI__movi(this); break;
        default                  : ;
    }
}
