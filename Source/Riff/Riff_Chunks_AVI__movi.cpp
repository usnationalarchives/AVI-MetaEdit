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
#include "ZenLib/Utils.h"
#include <algorithm>
//---------------------------------------------------------------------------

//***************************************************************************
// AVI_ data
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi::Read_Internal ()
{
    //Filling
    Global->AVI__movi=new Riff_Base::global::chunk_AVI__movi;
    Global->AVI__movi->File_Offset=Global->In.Position_Get();
    Global->AVI__movi->Size=Chunk.Content.Size;
    Global->AVI__movi_Pointers.insert(this);

    //Config
    Chunk.ShouldParse=false;
    Chunk.IsMoovable=false;

    Seek_Internal();
}

//---------------------------------------------------------------------------
void Riff_AVI__movi::Seek_Internal ()
{
    if (Global->AVI__movi_FirstDataChunkSize==(int64u)-1 || Global->GenerateMD5)
    {
        Chunk.ShouldParse=true;
        return;
    }

    Chunk.ShouldParse=false;

    size_t Pos=0;
    int64u Size=0;
    bool Size_Found=false;
    std::sort(Global->AVI__hdrl_strl_indx_In_Position_Indexes_List.begin(), Global->AVI__hdrl_strl_indx_In_Position_Indexes_List.end());
    while (Pos<Global->AVI__hdrl_strl_indx_In_Position_Indexes_List.size())
    {
        if (Global->AVI__hdrl_strl_indx_In_Position_Indexes_List[Pos]>=Global->In.Position_Get() && Global->AVI__hdrl_strl_indx_In_Position_Indexes_List[Pos]<Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size)
        {
            Size=Global->AVI__hdrl_strl_indx_In_Position_Indexes_List[Pos]-Global->In.Position_Get();
            Size_Found=true;
            break;
        }
        Pos++;
    }
    
    if (Size_Found)
    {
        if (Size)
        {
            InsertVirtual(Subs.size(), Size);
            Global->In.GoTo(Global->In.Position_Get()+Size);
        }
        Chunk.ShouldParse=true;
    }

    if (!Chunk.ShouldParse && !Subs.empty())
    {
        InsertVirtual(Subs.size(), Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size-Global->In.Position_Get());
        Global->In.GoTo(Chunk.File_In_Position+Chunk.Header.Size()+Chunk.Content.Size);
    }
}

//---------------------------------------------------------------------------
void Riff_AVI__movi::Insert_Internal (int32u Chunk_Name_Insert, Riff_Base* &Chunk, size_t &Chunk_Pos)
{
    switch (Chunk_Name_Insert&0x0000FFFF)
    {
        case Elements::AVI__movi___db : Chunk=new Riff_AVI__movi_xxxx(this); break;
        case Elements::AVI__movi___dc : Chunk=new Riff_AVI__movi_xxxx(this); break;
        case Elements::AVI__movi___ix : Chunk=new Riff_AVI__movi___ix(this); break;
        case Elements::AVI__movi___pc : Chunk=new Riff_AVI__movi_xxxx(this); break;
        case Elements::AVI__movi___wb : Chunk=new Riff_AVI__movi_xxxx(this); break;
        default                     : ;
    }
    switch (Chunk_Name_Insert&0xFFFF0000)
    {
        case Elements::AVI__movi_ix__ : Chunk=new Riff_AVI__movi___ix(this); break;
        default                     : ;
    }
}

