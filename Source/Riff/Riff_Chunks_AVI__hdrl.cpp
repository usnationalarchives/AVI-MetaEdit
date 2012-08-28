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
// AVI_ fmt
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl::Read_Internal ()
{
    //Integrity
    if (Global->AVI__hdrl)
        throw exception_valid("2 hdrl chunks");

    
    //Filling
    Global->AVI__hdrl=new Riff_Base::global::chunk_AVI__hdrl;
}

//---------------------------------------------------------------------------
void Riff_AVI__hdrl::Seek_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_AVI__hdrl::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVI__hdrl_avih : Chunk=new Riff_AVI__hdrl_avih(this); break;
        case Elements::AVI__hdrl_odml : Chunk=new Riff_AVI__hdrl_odml(this); break;
        case Elements::AVI__hdrl_strl : Chunk=new Riff_AVI__hdrl_strl(this); break;
        default                       : ;
    }
}
