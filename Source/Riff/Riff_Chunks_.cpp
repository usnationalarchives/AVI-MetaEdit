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
// Top level element
//***************************************************************************

//---------------------------------------------------------------------------
Riff::Riff ()
:Riff_Base(NULL)
{
    Global=new global();
}

//---------------------------------------------------------------------------
Riff::~Riff ()
{
    delete Global; //Global=NULL
}

//---------------------------------------------------------------------------
void Riff::Read_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVI_ : Chunk=new Riff_AVI_(this); break;
        case Elements::AVIX : Chunk=new Riff_AVIX(this); break;
        default                  : ;
    }
}

