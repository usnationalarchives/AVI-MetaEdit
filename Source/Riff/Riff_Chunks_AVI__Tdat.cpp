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
// AVI_ data
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__Tdat::Read_Internal ()
{
    //Integrity
    if (Global->Tdat)
        throw exception_valid("2 Tdat chunks");

    //Filling
    Global->Tdat=new Riff_Base::global::chunk_strings;
}

//---------------------------------------------------------------------------
void Riff_AVI__Tdat::Seek_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_AVI__Tdat::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVI__Tdat_tc_A : Chunk=new Riff_AVI__Tdat_tc_A(this); break;
        case Elements::AVI__Tdat_tc_O : Chunk=new Riff_AVI__Tdat_tc_O(this); break;
        case Elements::AVI__Tdat_rn_A : Chunk=new Riff_AVI__Tdat_rn_A(this); break;
        case Elements::AVI__Tdat_rn_O : Chunk=new Riff_AVI__Tdat_rn_O(this); break;
        default                     : ;
    }
}

