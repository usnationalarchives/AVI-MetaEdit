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
void Riff_AVI__movi___ix::Read_Internal ()
{
    //Filling
    Global->AVI__movi___ix_Pointers.insert(this);

    //Reading
    Read_Internal_ReadAllInBuffer();

    //Parsing
    int64u BaseOffset;
    int32u Entry_Count, ChunkId;
    int16u LongsPerEntry;
    int8u  IndexType, IndexSubType;
    Get_L2 (LongsPerEntry);
    Get_L1 (IndexSubType);
    Get_L1 (IndexType);
    Get_L4 (Entry_Count);
    Get_C4 (ChunkId);

    //Integrity
    if (LongsPerEntry!=(Global->AVI__movi___ix_WithFields[ChunkId]?3:2) || (IndexSubType&0xFE) || IndexType!=0x01 || 24+Entry_Count*(Global->AVI__movi___ix_WithFields[ChunkId]?12:8)>Chunk.Content.Size)
        throw exception_valid("movi___ix form is not supported");

    //Parsing
    Get_L8 (BaseOffset);
    Skip_XX(4); //Reserved

    /*
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        int32u Offset, Size;
        Get_L4 (Offset);
        Get_L4 (Size);
        Skip_XX(4); //Duration
    }*/

}

//***************************************************************************
// Modify
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi___ix::Modify_Internal ()
{
    //Useful data
    size_t EntrySize=LittleEndian2int16u(Chunk.Content.Buffer)*4;
    int32u Entry_Count=LittleEndian2int32u(Chunk.Content.Buffer+4);
    int32u ChunkId=LittleEndian2int32u(Chunk.Content.Buffer+8);
    int64u BaseOffset_In=LittleEndian2int64u(Chunk.Content.Buffer+12);

    //Finding the minimal Value
    int32u Value_Minimal=(int32u)-1;
    Chunk.Content.Buffer_Offset=24;
    for (int32u Pos=0; Pos<Entry_Count; Pos++)
    {
        int32u Value=LittleEndian2int32u(Chunk.Content.Buffer+Chunk.Content.Buffer_Offset);
        if (Value<Value_Minimal)
            Value_Minimal=Value;
        Chunk.Content.Buffer_Offset+=8;
    }

    //Finding the right AVI chunk for BaseOffset
    int64s BaseOffset_Difference=0;
    int64u BaseOffset_Out=0;
    bool   BaseOffset_Difference_Found=false;
    for (std::set<void*>::iterator movi=Global->AVI__movi_Pointers.begin(); movi!=Global->AVI__movi_Pointers.end(); movi++)
    {
        if (((Riff_AVI__movi*)(*movi))->Chunk.Content.IsModified || ((Riff_AVI__movi*)(*movi))->Chunk.Content.Size_IsModified)
            throw exception_valid("ix: modified movi chunk is not supported");

        if (BaseOffset_In+Value_Minimal>=((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position && BaseOffset_In+Value_Minimal<((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position+((Riff_AVI__movi*)(*movi))->Chunk.Content.Size)
        {
            BaseOffset_Difference=((Riff_AVI__movi*)(*movi))->Chunk.File_Out_Position-((Riff_AVI__movi*)(*movi))->Chunk.File_In_Position;
            BaseOffset_Difference_Found=true;
            BaseOffset_Out=BaseOffset_In+BaseOffset_Difference;
            break;
        }
    }
    if (!BaseOffset_Difference_Found)
        throw exception_write("Coherency problem during AVI__movi_ix parsing");
    
    //BaseOffset
    BaseOffset_Difference-=Global->AVI__movi___ix_Difference[this];
    if (BaseOffset_Difference)
    {
        int64u2LittleEndian(Chunk.Content.Buffer+12, BaseOffset_Out);
        Global->AVI__movi___ix_Difference[this]+=BaseOffset_Difference;
        Chunk.Content.IsModified=true;
    }
}

//***************************************************************************
// Write
//***************************************************************************

//---------------------------------------------------------------------------
void Riff_AVI__movi___ix::Write_Internal ()
{
}


