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
// AVI_
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI_::Read_Internal ()
{
    //Integrity
    if (Global->AVI_)
        throw exception_valid("2 AVI_ chunks");
    
    //Filling
    Global->AVI_=new Riff_Base::global::chunk_AVI_;
    Global->AVI_->Size_Original=Chunk.Content.Size;
    Global->AVI__Pointers.insert(this);
}

//---------------------------------------------------------------------------
void Riff_AVI_::Seek_Internal ()
{
}

//---------------------------------------------------------------------------
void Riff_AVI_::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert)
    {
        case Elements::AVI___PMX : Chunk=new Riff_AVI___PMX(this); break;
        case Elements::AVI__aXML : Chunk=new Riff_AVI__aXML(this); break;
        case Elements::AVI__hdrl : Chunk=new Riff_AVI__hdrl(this); break;
        case Elements::AVI__INFO : Chunk=new Riff_AVI__INFO(this); break;
        case Elements::AVI__iXML : Chunk=new Riff_AVI__iXML(this); break;
        case Elements::AVI__idx1 : Chunk=new Riff_AVI__idx1(this); break;
        case Elements::AVI__MD5_ : Chunk=new Riff_AVI__MD5_(this); break;
        case Elements::AVI__movi : Chunk=new Riff_AVI__movi(this); break;
        case Elements::AVI__Tdat : Chunk=new Riff_AVI__Tdat(this); break;
        default                  : ;
    }
    switch (Chunk_Name_Insert&0x0000FFFF)
    {
        case Elements::AVI__movi___ix : Chunk=new Riff_AVI__movi___ix(this); break;
        default                     : ;
    }
    switch (Chunk_Name_Insert&0xFFFF0000)
    {
        case Elements::AVI__movi_ix__ : Chunk=new Riff_AVI__movi___ix(this); break;
        default                     : ;
    }

    switch (Chunk_Name_Insert)
    {
        case Elements::AVI__INFO :
        case Elements::AVI__MD5_ :
                                    if (!Global->NewChunksAtTheEnd)
                                        Chunk_Pos=Subs_Pos_Get(Elements::AVI__hdrl)+1;
                                    break;
        default                  : ;
    }
}
