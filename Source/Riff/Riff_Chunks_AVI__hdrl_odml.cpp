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
void Riff_AVI__hdrl_odml::Read_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_odml::Seek_Internal ()
{
}

//***************************************************************************
// Insert
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__hdrl_odml::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVI__hdrl_odml_dmlh : Chunk=new Riff_AVI__hdrl_odml_dmlh(this); break;
        default                            : ;
    }
}
